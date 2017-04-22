#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <tlhelp32.h>

//#pragma comment( lib, "Common.lib" )

#include "Core2\Common\Common.h"
#include "Core2\Freelancer\Freelancer.h"

//[[679744] -8 + C + 4]

typedef HANDLE (WINAPI *OpenThread_t)(DWORD, DWORD, DWORD);

//courtesy of Adoxa
__declspec(naked) CObject *getPlayerShip()
{
	__asm {
		mov eax, 0x54baf0
		call eax
		test eax,eax
		jz noship
		add eax,12
		mov eax,[eax+4]
noship:
		ret
	}
}

inline void CreateConsole(void)
{
	if(!AllocConsole())
	{
		throw std::string("Couldn't allocate console");
	}

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
}

/*
	Function to suspend all other threads in the current
	process except the current thread.
	This is invoked before anything is marked as a guard
	page to prevent other threads from raising exceptions.
*/
inline void SuspendOtherThreads(void)
{
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	THREADENTRY32 te;

	if(hThreadSnap == INVALID_HANDLE_VALUE)
	{
		throw std::string("Unable to take thread snapshot");
	}

	te.dwSize = sizeof(THREADENTRY32);

	if(!Thread32First(hThreadSnap, &te))
	{
		CloseHandle(hThreadSnap);
		throw std::string("Thread32First failure");
	}

	DWORD dwMyThread = GetCurrentThreadId();
	DWORD dwFreelancerProcess = GetCurrentProcessId();

	//VC98 doesn't have OpenThread in its headers,
	//so we acquire it via GPA
	OpenThread_t fpnOpenThread = reinterpret_cast<OpenThread_t>(
		GetProcAddress(GetModuleHandleA("kernel32.dll"), "OpenThread")
		);

	do
	{
		//make sure we don't suspend our own thread
		if(te.th32ThreadID == dwMyThread)
		{
			continue;
		}

		//make sure we only suspend Freelancer's threads
		//to avoid freezing the system
		if(te.th32OwnerProcessID != dwFreelancerProcess)
		{
			continue;
		}

		HANDLE hThread = (*fpnOpenThread)(THREAD_SUSPEND_RESUME, FALSE, te.th32ThreadID);

		if(hThread == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hThreadSnap);
			throw std::string("OpenThread failure");
		}

		DWORD dwPrevSuspendCount = SuspendThread(hThread);
		std::cout << "Suspended thread " << te.th32ThreadID;
		std::cout << " (dwPrevSuspendCount=" << dwPrevSuspendCount << ")" << std::endl;

		CloseHandle(hThread);
	} while(Thread32Next(hThreadSnap, &te));


	CloseHandle(hThreadSnap);
}

/*
	Mark the entirety of common.dll as guarded
*/
inline void InstallGuardPage(LPVOID lpCommon, DWORD dwSize)
{
	MEMORY_BASIC_INFORMATION mbi;

	if(!VirtualQuery(lpCommon, &mbi, sizeof(mbi)))
	{
		throw std::string("VirtualQuery on common.dll failure");
	}

	DWORD dwOldProtect = 0;

	if(!VirtualProtect(lpCommon, dwSize, mbi.Protect | PAGE_GUARD, &dwOldProtect))
	{
		throw std::string("VirtualProtect on common.dll failure");
	}
}

#define LANDING_SUCCESS 0
#define LANDING_WRONG_ADDRESS 1
#define LANDING_UNEXPECTED_EXCEPTION 2

int guard_filter(DWORD dwCode, struct _EXCEPTION_POINTERS *ep, _CONTEXT *pCtx, _EXCEPTION_RECORD *pExc)
{
	if(dwCode == EXCEPTION_GUARD_PAGE)
	{
		memcpy((void*)pCtx, (void*)(ep->ContextRecord), sizeof(_CONTEXT));
		memcpy((void*)pExc, (void*)(ep->ExceptionRecord), sizeof(_EXCEPTION_RECORD));

		return EXCEPTION_EXECUTE_HANDLER;
	}
	else
	{
		//we are only concerned with guard page exceptions
		return EXCEPTION_CONTINUE_SEARCH;
	}
}

/*
	this assert macro tests if a given virtual function lands at
	a particular address. first we mark the entirety of common.dll
	(minus PE headers) as guarded, then invoke the function.
	our exception handler catches the guard page exception and forwards us
	the exception record, from which we extract the offending address.
*/
#define ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(C, N, F, A) \
	InstallGuardPage(lpCommon, dwCommonSize); \
	__try { F; } \
	__except(guard_filter(GetExceptionCode(), GetExceptionInformation(), &ctx, &exc)) \
	{ if(exc.ExceptionCode != EXCEPTION_GUARD_PAGE) { \
		dwLandingSuccess = LANDING_UNEXPECTED_EXCEPTION; \
	} else { \
		lpExceptAddr = (LPVOID)(*((LPDWORD)(exc.ExceptionInformation[1]))); \
		if(lpExceptAddr == (LPVOID)A) \
		{ \
			dwLandingSuccess = LANDING_SUCCESS; \
		} \
		else \
		{ \
			dwLandingSuccess = LANDING_WRONG_ADDRESS; \
		} \
	} } \
	if(dwLandingSuccess == LANDING_WRONG_ADDRESS) \
	{ std::cout << N << " landed at WRONG address " << lpExceptAddr << std::endl; } \
	else if(dwLandingSuccess == LANDING_SUCCESS) \
	{ std::cout << N << " landed at CORRECT address " << lpExceptAddr << std::endl; } \
	else if(dwLandingSuccess == LANDING_UNEXPECTED_EXCEPTION) \
	{ std::cout << N << " encountered UNEXPECTED EXCEPTION " << exc.ExceptionCode \
	<< " at " << exc.ExceptionAddress << std::endl; } \

bool InitiateTesting(void)
{
	HMODULE hCommon = (HMODULE)GetModuleHandle("Common.dll");

	if(!hCommon)
	{
		throw std::string("GetModuleHandle(\"Common.dll\") failed");
	}

	MODULEINFO modInfo;

	BOOL bModInfoSuccess = GetModuleInformation(GetCurrentProcess(), (HMODULE)hCommon, &modInfo, sizeof(MODULEINFO));

	if(!bModInfoSuccess)
	{
		throw std::string("GetModuleInfo() failed");
	}

	//exclude PE headers
	DWORD dwCommonSize = modInfo.SizeOfImage - 0x1000;
	LPVOID lpCommon = (LPVOID)((LPBYTE)modInfo.lpBaseOfDll + 0x1000);

	EngineObject * pl_eo = (EngineObject*)getPlayerShip();
	CObject * pl_co = (CObject*)pl_eo;
	CSimple * pl_cs = (CSimple*)pl_eo;

	if(!pl_eo)
	{
		throw std::string("Player ship was null");
	}

	//some instances of various types
	//for testing purposes
	float aFloat;
	Vector aVector;
	Matrix aMatrix;
	Transform aTransform;

	DWORD dwLandingSuccess;
	LPVOID lpExceptAddr;
	_CONTEXT ctx;
	_EXCEPTION_RECORD exc;

	std::cout << std::endl << "Testing EngineObject functionality..." << std::endl;
	//Test EngineObject functionality
	*((LPDWORD)pl_eo) = 0x639B5BC;
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->initialize_instance", pl_eo->initialize_instance(0), 0x6309910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->create_instance", pl_eo->create_instance(0), 0x628F050);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->destroy_instance", pl_eo->destroy_instance(0), 0x6309920);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_position", pl_eo->set_position(0, aVector), 0x6309930);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_position", pl_eo->get_position(0), 0x6309950);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_orientation", pl_eo->set_orientation(0, aMatrix), 0x6309960);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_orientation", pl_eo->get_orientation(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_transform", pl_eo->set_transform(0, aTransform), 0x6309990);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_transform", pl_eo->get_transform(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_centered_radius", pl_eo->set_centered_radius(0, 0, aVector), 0x6309A60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_centered_radius", pl_eo->get_centered_radius(0, aFloat, aVector), 0x6309A30);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_instance_flags", pl_eo->set_instance_flags(0, 0), 0x6309AA0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_instance_flags", pl_eo->get_instance_flags(0), 0x6309A90);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->joint_changed", pl_eo->joint_changed(0), 0x632C0C0);
	//virtual destructor at this position
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_velocity", pl_eo->get_velocity(0), 0x63099B0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_velocity", pl_eo->set_velocity(0, aVector), 0x62A8910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->get_angular_velocity", pl_eo->get_angular_velocity(0), 0x63099F0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_eo, "pl_eo->set_angular_velocity", pl_eo->set_angular_velocity(0, aVector), 0x62A8910);

	std::cout << std::endl << "Testing CObject functionality..." << std::endl;
	//Test CObject functionality
	*((LPDWORD)pl_co) = 0x639B66C;
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->initialize_instance", pl_co->initialize_instance(0), 0x6309910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->create_instance", pl_co->create_instance(0), 0x628F050);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->destroy_instance", pl_co->destroy_instance(0), 0x62AF610);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_position", pl_co->set_position(0, aVector), 0x6309930);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_position", pl_co->get_position(0), 0x6309950);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_orientation", pl_co->set_orientation(0, aMatrix), 0x6309960);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_orientation", pl_co->get_orientation(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_transform", pl_co->set_transform(0, aTransform), 0x6309990);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_transform", pl_co->get_transform(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_centered_radius", pl_co->set_centered_radius(0, 0, aVector), 0x6309A60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_centered_radius", pl_co->get_centered_radius(0, aFloat, aVector), 0x6309A30);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_instance_flags", pl_co->set_instance_flags(0, 0), 0x6309AA0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_instance_flags", pl_co->get_instance_flags(0), 0x6309A90);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->joint_changed", pl_co->joint_changed(0), 0x632C0C0);
	//virtual destructor at this position
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_velocity", pl_co->get_velocity(), 0x627D120);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_velocity", pl_co->set_velocity(0, aVector), 0x62A8910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_angular_velocity", pl_co->get_angular_velocity(), 0x627D150);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->set_angular_velocity", pl_co->set_angular_velocity(0, aVector), 0x62A8910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->open", pl_co->open(NULL), 0x62AF400);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->update", pl_co->update(0.0f, 0), 0x62AF420);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->disable_controllers", pl_co->disable_controllers(), 0x62A8920);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->enable_controllers", pl_co->enable_controllers(), 0x62A8920);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_physical_radius_r", pl_co->get_physical_radius_r(aVector), 0x62AD980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_center_of_mass", pl_co->get_center_of_mass(), 0x62ADA20);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_mass", pl_co->get_mass(), 0x62ADA60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->get_surface_extents", pl_co->get_surface_extents(aVector, aVector), 0x62AD470);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->unmake_physical", pl_co->unmake_physical(), 0x62AD520);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_co, "pl_co->beam_object", pl_co->beam_object(aVector, aMatrix, 1.0f), 0x62ADA80);

	std::cout << std::endl << "Testing CSimple functionality..." << std::endl;
	//Test CSimple functionality
	*((LPDWORD)pl_cs) = 0x639B884;
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->initialize_instance", pl_cs->initialize_instance(0), 0x6309910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->create_instance", pl_cs->create_instance(0), 0x628F050);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->destroy_instance", pl_cs->destroy_instance(0), 0x62AF610);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_position", pl_cs->set_position(0, aVector), 0x6309930);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_position", pl_cs->get_position(0), 0x6309950);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_orientation", pl_cs->set_orientation(0, aMatrix), 0x6309960);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_orientation", pl_cs->get_orientation(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_transform", pl_cs->set_transform(0, aTransform), 0x6309990);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_transform", pl_cs->get_transform(0), 0x6309980);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_centered_radius", pl_cs->set_centered_radius(0, 0, aVector), 0x6309A60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_centered_radius", pl_cs->get_centered_radius(0, aFloat, aVector), 0x6309A30);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_instance_flags", pl_cs->set_instance_flags(0, 0), 0x6309AA0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_instance_flags", pl_cs->get_instance_flags(0), 0x6309A90);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->joint_changed", pl_cs->joint_changed(0), 0x632C0C0);
	//virtual destructor at this position
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_velocity", pl_cs->get_velocity(), 0x627D120);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_velocity", pl_cs->set_velocity(0, aVector), 0x62A8910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_angular_velocity", pl_cs->get_angular_velocity(), 0x627D150);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_angular_velocity", pl_cs->set_angular_velocity(0, aVector), 0x62A8910);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->open", pl_cs->open(NULL), 0x62B5CD0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->update", pl_cs->update(0.0f, 0), 0x62AF420);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->disable_controllers", pl_cs->disable_controllers(), 0x62A8920);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->enable_controllers", pl_cs->enable_controllers(), 0x62A8920);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_physical_radius_r", pl_cs->get_physical_radius_r(aVector), 0x62B5E60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_center_of_mass", pl_cs->get_center_of_mass(), 0x62ADA20);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_mass", pl_cs->get_mass(), 0x62ADA60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_surface_extents", pl_cs->get_surface_extents(aVector, aVector), 0x62AD470);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->unmake_physical", pl_cs->unmake_physical(), 0x62B5F60);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->beam_object", pl_cs->beam_object(aVector, aMatrix, 1.0f), 0x62B5EA0);
	//todo: test init()
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->cache_physical_props", pl_cs->cache_physical_props(), 0x62B5ED0);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->get_name", pl_cs->get_name(), 0x62B5F70);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->is_targetable", pl_cs->is_targetable(), 0x6281190);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->connect", pl_cs->connect(NULL), 0x62B5F80);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->disconnect", pl_cs->disconnect(NULL), 0x62B5F90);
	ASSERT_VIRTUAL_FUNCTION_LANDING_ADDRESS(pl_cs, "pl_cs->set_hit_pts", pl_cs->set_hit_pts(0.0f), 0x62B5FD0);
	//todo: test init_physics()


	return true;
}

void TestThread(void)
{
	while(1)
	{
		if(GetAsyncKeyState(VK_F12))
		{
			try {
				CreateConsole();
			} catch(std::string e) {
				MessageBoxA(0, e.c_str(), "Initialization Exception", MB_ICONERROR);
			}

			std::cout << "Suspending threads..." << std::endl;

			try {
				SuspendOtherThreads();
			} catch(std::string e) {
				std::cout << "Error: " << e << std::endl;
			}

			Sleep(500);

			std::cout << "Starting testing..." << std::endl;

			bool bTestSuccess = false;

			try {
				bTestSuccess = InitiateTesting();
			} catch(std::string e) {
				std::cout << "Error: " << e << std::endl;
			}

			if(!bTestSuccess)
			{
				std::cout << "Testing failure" << std::endl;
			}
			else
			{
				std::cout << "Testing success" << std::endl;
			}

			MessageBoxA(0, 
				"Freelancer is in an unstable state.\n" \
				"The process will be terminated when this message box\n" \
				"is closed.",
				"Testing Complete", MB_ICONWARNING);

			TerminateProcess(GetCurrentProcess(), 0);
		}
		Sleep(50);
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TestThread, NULL, 0, NULL);
		break;
	}
    return TRUE;
}

