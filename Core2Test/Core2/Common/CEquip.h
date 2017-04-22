/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\Archetype.h"
#include "Common\CEqObj.h"
#include "Common\EquipDesc.h"

class IMPORT CEquip
{
public:
	//MEMBER FUNCTIONS
	CEquip(CEquip const &);
	CEquip(unsigned int,CEqObj *,unsigned short,Archetype::Equipment const *,bool);
	void ConnectClientEquip(INotify *);
	void ConnectServerEquip(INotify *);
	Archetype::Equipment const * EquipArch(void)const ;
	unsigned short GetID(void)const ;
	CEqObj * GetOwner(void)const ;
	unsigned int GetType(void)const ;
	char const * IdentifyEquipment(void)const ;
	void Notify(INotify::Event,void *);
	void NotifyDisconnecting(INotify *);
	CEquip(void);

	//VIRTUAL FUNCTIONS
	virtual ~CEquip(void);
	virtual bool IsActive(void)const ;
	virtual bool IsDestroyed(void)const ;
	virtual bool IsFunctioning(void)const ;
	virtual bool IsDisabled(void)const ;
	virtual bool IsTemporary(void)const ;
	virtual bool CanDelete(void)const ;
	virtual void SetHitPoints(float);
	virtual bool IsLootable(void)const ;
	virtual bool Update(float,unsigned int);
	virtual bool GetEquipDesc(EquipDesc &)const ;
	virtual void GetStatus(struct EquipStatus &)const ;
	virtual bool Activate(bool);
	virtual void Destroy(void);
	virtual float GetMaxHitPoints(void)const ;
	virtual float GetHitPoints(void)const ;
	virtual void NotifyArchGroupDestroyed(unsigned short);
	virtual float GetRelativeHealth(void)const ;
	virtual bool GetConnectionPosition(Vector *,Matrix *)const ;
	virtual bool EnableController(void);
	virtual bool DisableController(void);
	virtual bool IsControllerEnabled(void)const ;

	//STATIC FUNCTIONS
	static void * operator new(unsigned int);
	static void operator delete(void *);

	//MEMBER FIELDS
	CEqObj * owner;
	unsigned short sID;
	Archetype::Equipment *arch;
	bool bActive;
	bool bDestroyed;
	bool bTemporary;
	unsigned int iType;
	unsigned int field_24;
	unsigned int field_28;
};