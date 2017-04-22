/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: NOT STARTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

namespace Archetype
{
	class Root;
	class Equipment;

	class IMPORT CollisionGroup
	{
		CollisionGroup(CollisionGroup const &);
		CollisionGroup(void);
		~CollisionGroup(void);
		CollisionGroup & operator=(CollisionGroup const &);

	public:
		//needs updation
	};

	class DamageObjInfoList;
	class FuseIgnitionList;
	class EqObj;
};