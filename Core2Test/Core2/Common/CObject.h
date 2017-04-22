/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, TESTED, FUNCTIONAL
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\EngineObject.h"

/*
	CObject struct
*/
class IMPORT CObject : public EngineObject
{
public:
	enum Class
	{
		CSOLAR_OBJECT = 0x303,
		CSHIP_OBJECT = 0x503,
	};

	//VIRTUAL FUNCTIONS
	virtual ~CObject(void);
	virtual void open(Archetype::Root *);
	virtual int update(float,unsigned int);
	virtual Vector get_velocity(void) const;
	virtual Vector get_angular_velocity(void) const;
	virtual void disable_controllers(void); //null function
	virtual void enable_controllers(void); //null function
	virtual float get_physical_radius_r(Vector &) const;
	virtual Vector get_center_of_mass(void) const;
	virtual float get_mass(void) const;
	virtual bool get_surface_extents(Vector &, Vector &) const;
	virtual void unmake_physical(void);
	virtual void remake_physical(PhySys::CreateParms const &, float);
	virtual void beam_object(Vector const &, Matrix const &, bool);
	
	//STATIC FUNCTIONS
	static CObject *  Alloc(enum Class);
	static CObject *  Find(unsigned int const &,enum Class);
	static CObject *  Find(long, enum Class);
	static CObject *  FindFirst(enum Class);
	static CObject *  FindNext(void);
	static void ReleaseAll(void);
	static int Count(enum Class);
	static void * operator new(unsigned int);
	static void operator delete(void *);

	//MEMBER FUNCTIONS
	CObject(CObject const &);
	CObject(enum Class);
	unsigned int AddRef(void);
	unsigned int Release(void);
	void add_impulse(Vector const &, Vector const &);
	void add_impulse(Vector const &);
	void advise(CBase *,bool);
	void enable_collisions_r(bool);
	bool flag_part_as_shield(unsigned int);
	Archetype::Root * get_archetype(void) const;
	void get_intruder_set_r(CheapSet<CObject *,std::less<CObject *> > &);
	Vector get_moment_of_inertia(void) const;
	float hierarchy_radius(Vector &) const;
	float hierarchy_radius(void) const;
	unsigned int inst_to_part(long) const;
	bool is_shield_part(unsigned int) const;
	long part_to_inst(unsigned int) const;

	//STATIC MEMBER FIELDS
	static unsigned int const NO_ACTIONS;
	static unsigned int const NO_BEHAVIOR;
	static unsigned int const NO_COUNTERMEASURE_AI;
	static unsigned int const NO_DYNAMICS;
	static unsigned int const NO_SCANNER;
	static unsigned int const UPDATE_DEFAULT;
	static unsigned int const UPDATE_DUMB;

	//MEMBER FIELDS
	Class classid;
	unsigned int iSystem;
	unsigned int dwPhysicsRel1; //ptr to object, causes colMgr->enable_collisions() to get called, also affects impulses
	unsigned int dwPhysicsRel2; //ptr to object
	unsigned int iUnknown1[10];
	PhySys::PhyCollisionStateManager *colMgr;
	Archetype::Root *arch;
	unsigned int iUnknown2[3];
	unsigned int dwRefCount;
};