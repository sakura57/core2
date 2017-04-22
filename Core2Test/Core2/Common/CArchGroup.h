/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\ID_String.h"
#include "Common\CEqObj.h"
#include "Common\CollisionGroupDesc.h"

class IMPORT CArchGroup
{
	//MEMBER FUNCTIONS
	CArchGroup(Archetype::CollisionGroup const &,CEqObj * const);
	~CArchGroup(void);
	ID_String const & DebrisTypeName(void)const ;
	bool DestroysParent(void)const ;
	float ExplosionGroupImpulse(void)const ;
	float ExplosionParentImpulse(void)const ;
	float ExplosionResistance(void)const ;
	ID_String const & ExplosionTypeName(void)const ;
	Archetype::FuseIgnitionList const & FuseIgnitions(void)const ;
	bool GetCenterOfMass(class Vector &)const ;
	void GetCollisionGroupDesc(CollisionGroupDesc &)const ;
	unsigned int GetCollisionGroupType(void)const ;
	DamageEntry::SubObjFate  GetFate(void)const ;
	float GetHitPoints(void)const ;
	unsigned short GetID(void)const ;
	float GetMaxHitPoints(void)const ;
	bool GetRadius(float &)const ;
	float GetRelativeHealth(void)const ;
	long GetRootIndex(void)const ;
	bool GetVelocity(class Vector &)const ;
	Archetype::DamageObjInfoList const & GroupDamageObjs(void)const ;
	int InstDepthInGroup(long)const ;
	bool IsDead(void)const ;
	bool IsDestroyed(void)const ;
	bool IsInstInGroup(long)const ;
	bool IsRootHealthProxy(void)const ;
	void Kill(enum DamageEntry::SubObjFate);
	float LinkedEquipmentDamage(void)const ;
	unsigned int LinkedEquipmentType(void)const ;
	CacheString const & Name(void)const ;
	Archetype::DamageObjInfoList const & ParentDamageObjs(void)const ;
	CObject * RetreiveDestroyedObj(void);
	bool Separable(void)const ;
	void SetHitPoints(float);
	void SetRelativeHealth(float);

	//protected
	void AttachDamageObjs(CObject *,Archetype::DamageObjInfoList const &)const ;
	void Destroy(void);
	void FreeDamageObjs(void);
	void GetBoundingSphere(float &,class Vector &)const ;
	void LoadDamageObjs(void);

public:
	CEqObj *owner;
	Archetype::CollisionGroup *collisionGroup;
	unsigned int iRootIndex;
	float flHitPts;
	unsigned int field_16;
	int iState; //2=dead,3=destroyed
	DamageEntry::SubObjFate fate;
	CObject *destroyedObject; //assigned in CArchGroup::Destroy (?)
	bool field_32;
	unsigned int field_36;
	unsigned int field_40;
	unsigned int field_44;
	unsigned int field_48;
};