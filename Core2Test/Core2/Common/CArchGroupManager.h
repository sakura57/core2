/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\CArchGroup.h"

class IMPORT CArchGroupManager
{
public:
	CArchGroupManager(CArchGroupManager const &);
	CArchGroupManager(void);
	~CArchGroupManager(void);
	CArchGroupManager & operator=(CArchGroupManager const &);
	bool AddNewArchGroup(CArchGroup *);
	int Clear(void);
	bool DeleteArchGroup(unsigned short);
	bool DestroyDeadGroups(void);
	bool DestroyGroups(DamageList const &,bool);
	CArchGroup * FindByID(unsigned short);
	CArchGroup const * FindByID(unsigned short) const;
	CArchGroup * FindByName(CacheString const &);
	CArchGroup const * FindByName(CacheString const &) const;
	bool Init(CEqObj *);
	unsigned short InstToSubObjID(long) const;
	bool IsOnMap(unsigned short,bool) const;
	int NumLiving(void) const;
	int Size(void) const;
	CArchGroup * Traverse(CArchGrpTraverser &);
	CArchGroup const * Traverse(CArchGrpTraverser &) const;

	//protected
	void DestroyDeadGroup(CArchGroup &);
	void DestroyLowerGroups(CArchGroup const &);
	static int const MAX_GROUP_DEPTH;

	//MEMBER FIELDS (size of class may be incorrect)
	CEqObj *owner;
	unsigned int field_4;
	unsigned int field_8;
	unsigned int field_C;
	unsigned int field_10;
	int iSize;
	unsigned int field_18;
	int iBase;
	int iDockTarget;
	unsigned int field_24;
};