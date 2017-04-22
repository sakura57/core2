/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include <windows.h>

class Module
{
public:
	static unsigned char * const Freelancer;
	static unsigned char * const Common;
};

template<class T>
class Callable
{
public:
	inline static T Function(void * const ptr)
	{
		return reinterpret_cast<T>(ptr);
	};
	
	inline static T VirtualFunction(void * const ptr, unsigned int idx)
	{
		return (*reinterpret_cast<T*>(ptr))[idx];
	};
};