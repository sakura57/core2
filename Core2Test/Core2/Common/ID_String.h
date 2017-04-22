/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: FULLY COMPLETED, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

class IMPORT CacheString
{
	void clear(void);

public:
	char* value;
};

class IMPORT ID_String
{
public:
	bool IsEmpty(void) const;
	void clear(void);
	char const * get_string(void) const;

	unsigned int id;
};