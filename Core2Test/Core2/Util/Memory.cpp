/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#include "Memory.h"

unsigned char * const Module::Freelancer = reinterpret_cast<unsigned char *>(GetModuleHandleA("Freelancer.exe"));
unsigned char * const Module::Common = reinterpret_cast<unsigned char *>(GetModuleHandleA("Common.dll"));