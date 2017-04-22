/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\ID_String.h"

class IMPORT EquipDesc
{
public:

	//MEMBER FUNCTIONS
	EquipDesc(EquipDesc const &);
	EquipDesc(void);
	EquipDesc & operator=(EquipDesc const &);
	bool operator==(EquipDesc const &) const;
	bool operator!=(EquipDesc const &) const;
	bool operator<(EquipDesc const &) const;
	bool operator>(EquipDesc const &) const;

	static CacheString const CARGO_BAY_HP_NAME;
	unsigned int get_arch_id(void) const;
	float get_cargo_space_occupied(void) const;
	int get_count(void) const;
	CacheString const & get_hardpoint(void) const;
	unsigned short get_id(void) const;
	int get_owner(void) const;
	float get_status(void) const; //health

	bool get_temporary(void) const; //tests bMission
	bool is_equipped(void) const;
	bool is_internal(void) const;
	void make_internal(void); //sets szHardPoint to CARGO_BAY_HP_NAME
	void set_arch_id(unsigned int);
	void set_count(int);
	void set_equipped(bool);
	void set_hardpoint(CacheString const &);
	void set_id(unsigned short);
	void set_owner(int);
	void set_status(float); //health
	void set_temporary(bool); //affects bMission

	unsigned short iDunno;
	unsigned short sID;
	unsigned int iArchID;
	CacheString szHardPoint;
	bool bMounted;
	float fHealth;
	unsigned int iCount;
	bool bMission;
	int iOwner;
};