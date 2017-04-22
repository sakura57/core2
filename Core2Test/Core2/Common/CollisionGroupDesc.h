/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

struct IMPORT CollisionGroupDesc
{
	CollisionGroupDesc & operator=(CollisionGroupDesc const &);
	bool operator==(CollisionGroupDesc const &) const;
	bool operator!=(CollisionGroupDesc const &) const;
	bool operator<(CollisionGroupDesc const &) const;
	bool operator>(CollisionGroupDesc const &) const;

	unsigned short sID;
	float flRelativeHealth;
};

template class IMPORT std::list<CollisionGroupDesc>;
