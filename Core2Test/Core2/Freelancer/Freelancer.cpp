/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#include "Freelancer.h"

using namespace FL;

inline EngineCamera * FL::GetActiveCamera(void)
{
	register void * ptr = reinterpret_cast<void *>(Module::Freelancer + 0xF130);
	return Callable<fn::GetActiveCamera_t>::Function(ptr)();
}

inline EngineCamera * FL::SetActiveCamera(EngineCamera *a1)
{
	register void * ptr = reinterpret_cast<void *>(Module::Freelancer + 0xF140);
	return Callable<fn::SetActiveCamera_t>::Function(ptr)(a1);
}

inline EngineCamera * FL::GetChaseCamera(void)
{
	register void * ptr = reinterpret_cast<void *>(Module::Freelancer + 0x14BC40);
	return Callable<fn::GetChaseCamera_t>::Function(ptr)();
}

inline EngineCamera * FL::GetTurretCamera(void)
{
	register void * ptr = reinterpret_cast<void *>(Module::Freelancer + 0x14BC50);
	return Callable<fn::GetTurretCamera_t>::Function(ptr)();
}
