/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: FULLY COMPLETE, TESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

interface IMPORT IEngineInstance
{
public:
	virtual void initialize_instance(long);
	virtual void create_instance(long);
	virtual void destroy_instance(long);
};