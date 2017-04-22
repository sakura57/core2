/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, PARTIALLY TESTED
*/
#pragma once

#include "protos.h"
#include "FLDefs.h"

class EngineCamera
{
	//MEMBER FUNCTIONS
public:
	//EngineCamera *__thiscall EngineCamera::EngineCamera(EngineCamera *this) = 0x40F150

		//VIRTUAL FUNCTIONS
private: virtual void _unknown_do_not_call0(void) = 0; //40F350
private: virtual void _unknown_do_not_call1(void) = 0; //40F360
private: virtual void _unknown_do_not_call2(void) = 0; //40F360
public:  virtual Vector const &get_position(EngineCamera const *) const;

private: virtual void _unknown_do_not_call4(void) = 0; //40F380
private: virtual void _unknown_do_not_call5(void) = 0; //40F470
public:  virtual float get_base_fov(EngineCamera const *) const;
public:  virtual float get_model_fov(EngineCamera const *) const;
public:  virtual float get_near_z(EngineCamera const *) const;
public:  virtual float get_far_z(EngineCamera const *) const;
public:  virtual float get_aspect_ratio(EngineCamera const *) const;

		//returns flRangeHi / flNearZ
private: virtual float _unknown_do_not_call11(EngineCamera const *) = 0; //40F4D0
	
		//returns flRangeLo / flNearZ
private: virtual float _unknown_do_not_call12(EngineCamera const *) = 0; //40F4E0

		 //syntax: project(IN cam, OUT x, OUT y, OUT z, IN world_pos)
public:  virtual bool project(EngineCamera const *, float &, float &, float &, Vector const &);
private: virtual void _unknown_do_not_call14(void) = 0; //40F520
private: virtual void _unknown_do_not_call15(void) = 0; //40FFE0
private: virtual void _unknown_do_not_call16(void) = 0; //40F390

		 //syntax: world_to_screen(IN cam, OUT screen_pos, IN world_pos)
		 //essentially just forwards to project()
public:  virtual bool world_to_screen(EngineCamera const *, Vector &, Vector const &);
public:  virtual ~EngineCamera();

		//seems as though calls to set_named_attrib
		//on TurretCamera persist (even for other cameras)
		//whereas on ChaseCamera it doesn't
public:  virtual bool set_named_attrib(char const *szAttrib, char const *szValue);


	//MEMBER FIELDS
public:
	Transform xform;
	bool bUnknown1;
	Matrix field_56;
	Vector field_92;
	float flHalfWidth1;
	float flHalfHeight1;
	float flHalfWidth2;
	float flHalfHeight2;
	float flRangeHi;
	float flRangeLo;
	float flUnknown1;
	float flUnknown2;
	float flBaseFOV;
	float flModelFOV;
	float flAspectRatio;
	float flNearZ;
	float flFarZ;
	char cPadding1[8];
	int iWidthM1;
	int iHeightM1;
	bool bUnknown2;
};