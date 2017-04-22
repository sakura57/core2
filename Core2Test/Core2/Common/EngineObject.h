/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: FULLY COMPLETE, TESTED, FUNCTIONAL
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "IEngineInstance.h"

/*
	EngineObject struct
	
	Base class common to most space object types.
*/
class IMPORT EngineObject : public IEngineInstance
{
public:
	//VIRTUAL FUNCTIONS
	virtual void set_position(long, Vector const &);
	virtual Vector const & get_position(long) const;
	virtual void set_orientation(long, Matrix const &);
	virtual Matrix const & get_orientation(long) const;
	virtual void set_transform(long, Transform const &);
	virtual Transform const & get_transform(long) const;
	virtual void get_centered_radius(long, float &, Vector &) const;
	virtual void set_centered_radius(long, float, Vector const &);
	virtual void set_instance_flags(long, unsigned long);
	virtual unsigned long get_instance_flags(long) const;
	virtual bool joint_changed(long);
	virtual ~EngineObject(void);
	virtual Vector const & get_velocity(long) const;
	virtual void set_velocity(long, Vector const &);
	virtual Vector const & get_angular_velocity(long) const;
	virtual void set_angular_velocity(long, Vector const &);

	//MEMBER FUNCTIONS
	EngineObject(EngineObject const &);
	EngineObject(void);
	EngineObject &operator=(EngineObject const &);
	long get_index(void) const;
	Matrix const & get_orientation(void) const;
	Vector const & get_position(void) const;
	float const get_radius(void) const;
	Transform const & get_transform(void) const;
	void set_orientation(Matrix const &);
	void set_position(Vector const &);
	void set_transform(Transform const &);
	void update_tree(void) const;

	//MEMBER FIELDS
	int iInstance;
	Transform xform;
	float flRadius;
	Vector center;
	unsigned int dwInstanceFlags;
};