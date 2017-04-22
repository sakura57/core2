/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\CEquip.h"
#include "Common\EquipDescList.h"
#include "Common\ID_String.h"

template class IMPORT std::list<CEquip *>;

class IMPORT CEquipManager
{
public:
	//MEMBER FUNCTIONS
	CEquipManager(CEquipManager const &);
	CEquipManager(void);
	~CEquipManager(void);
	CEquipManager & operator=(CEquipManager const &);
	bool AddNewEquipment(class CEquip *);
	int CleanUp(void);
	void Clear(void);
	class CExternalEquip * FindByHardpoint(CacheString const &);
	class CExternalEquip const * FindByHardpoint(CacheString const &) const;
	CEquip * FindByID(unsigned short);
	CEquip const * FindByID(unsigned short) const;
	CEquip * FindFirst(unsigned int);
	CEquip const * FindFirst(unsigned int) const;
	bool HasDecayingCargo(void) const;
	bool Init(CEqObj *);
	unsigned short InstToSubObjID(long) const;
	CEquip * ReverseTraverse(class CEquipTraverser &);
	CEquip const * ReverseTraverse(class CEquipTraverser &) const;
	int Size(void) const;
	CEquip * Traverse(class CEquipTraverser &);
	CEquip const * Traverse(class CEquipTraverser &) const;
	bool VerifyListSync(class EquipDescList const &) const;

private:
	int CleanUp(std::list<CEquip *> &);
	static void  Clear(std::list<CEquip *> &);

public:
	CEqObj *owner;
	std::list<CEquip *> equipList;
	EquipDescList equipDescList;
	int iNumDecayingCargo;
};