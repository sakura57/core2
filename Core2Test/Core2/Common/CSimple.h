/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, TESTED, MOSTLY FUNCTIONAL
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\Watchable.h"
#include "Common\CObject.h"

/*
	CSimple struct
*/
class IMPORT CSimple : public CObject, public Watchable
{
public:
	struct CreateParms;

	//VIRTUAL FUNCTIONS
	virtual ~CSimple(void);
	virtual void open(Archetype::Root *);
	virtual float get_physical_radius_r(Vector &) const;
	virtual void unmake_physical(void);
	virtual void beam_object(Vector const &, Matrix const &, bool);
	virtual void init(CreateParms const &);
	virtual void cache_physical_props(void);
	virtual unsigned int get_name(void) const;
	virtual bool is_targetable(void) const;
	virtual void connect(IObjDB *);
	virtual void disconnect(IObjDB *);
	virtual void set_hit_pts(float);
	virtual void init_physics(Vector const &, Vector const &) = 0; //pure virtual
	
	//MEMBER FUNCTIONS
	CSimple(CSimple const &);
	CSimple(CObject::Class);
	unsigned int GetOwnerPlayer(void) const;
	void SetOwnerPlayer(unsigned int);
	float get_hit_pts(void) const;
	unsigned int const &get_id(void) const;
	float get_max_hit_pts(void) const;
	IObjDB * get_object_database(void) const;
	float get_relative_health(void) const;
	float get_scanner_interference(void) const;
	unsigned int get_type(void) const;
	void update_zones(float,unsigned int);
	
	//MEMBER FIELDS
	bool bTargetable;
	unsigned int field_164;
	unsigned int field_168;
	IObjDB *objDB;
	unsigned int iSpaceID;
	unsigned int iOwningPlayerID;
	float flHitPts;
	unsigned int _list_piece1; //part of a std::list of (currently) unknown template parameter
	unsigned int _list_piece2;
	unsigned int _list_piece3;
	unsigned int field_204;
	unsigned int field_208;
	Vector flOrigin;
	unsigned int iType;
};

struct CSimple::CreateParms
{
	unsigned int iSpaceID;
	unsigned int qInteger1; // -> initialize_instance
	unsigned int iOwningPlayerID;
	float init_hit_pts;
	Vector flPosition;
	Matrix flOrientation;
	Vector qPhy1; // -> init_physics
	Vector qPhy2; // -> init_physics
};