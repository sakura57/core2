/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

class IMPORT Watchable
{
	Watchable(void);
	~Watchable(void);
	Watchable &operator=(Watchable const &);
	unsigned int unwatch(void);

public:
	unsigned int field_156;
};