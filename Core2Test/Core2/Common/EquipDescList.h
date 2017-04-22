/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

template class IMPORT std::vector<EquipDesc>;
template class IMPORT std::list<EquipDesc>;

class IMPORT EquipDescVector
{
	EquipDescVector(EquipDescVector const &);
	EquipDescVector(EquipDescList const &);
	EquipDescVector(void);
	~EquipDescVector(void);
	EquipDescVector & operator=(EquipDescVector const &);
	int add_equipment_item(EquipDesc const &,bool);
	void append(EquipDescVector const &);
	EquipDesc * traverse_equipment_type(unsigned int,EquipDesc const *);

public:
	std::vector<EquipDesc> equipDescVec;
};

class IMPORT EquipDescList
{
public:
	EquipDescList(EquipDescVector const &);
	EquipDescList(EquipDescList const &);
	EquipDescList(void);
	~EquipDescList(void);
	EquipDescList & operator=(EquipDescList const &);
	int add_equipment_item(EquipDesc const &,bool);
	void append(class EquipDescList const &);
	EquipDesc * find_equipment_item(CacheString const &);
	EquipDesc * find_equipment_item(unsigned short);
	EquipDesc const * find_equipment_item(CacheString const &)const ;
	EquipDesc const * find_equipment_item(unsigned short)const ;
	EquipDesc const * find_matching_cargo(unsigned int,int,float)const ;
	float get_cargo_space_occupied(void)const ;
	int remove_equipment_item(unsigned short,int);
	EquipDesc * traverse_equipment_type(unsigned int,EquipDesc const *);
	EquipDesc const * traverse_equipment_type(unsigned int,EquipDesc const *)const ;

public:
	std::list<EquipDesc> equipDescList;
};