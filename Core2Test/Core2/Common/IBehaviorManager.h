/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

class IMPORT IBehaviorManager
{
public:
	bool allow_head_tracking(void);
	bool cancel_behavior(enum CancelRequestType);
	bool enable_all_maneuvers(void);
	bool enable_maneuver(int,bool);
	enum EvaluateResult  external_player_evaluate(int);
	bool get_camera_level_status(void);
	float get_closest_trailing_ship(void)const ;
	IDirectiveInfo const * get_current_directive(void);
	IObjRW const * get_debugger_target(void)const ;
	bool get_docking_port(IObjRW const * &,int &);
	unsigned int get_parent_id(void);
	void get_personality(pub::AI::Personality &);
	enum pub::AI::ScanResponse  get_scan_response(unsigned int);
	Vector const  get_ship_up_direction(void);
	IStateGraph const * get_state_graph(void);
	SystemManager * get_sys(void);
	bool get_user_turning_input_state(void);
	bool lock_maneuvers(bool);
	void refresh_state_graph(void);
	void reset_current_behavior_direction(void);
	void set_camera_mode(enum IBehaviorCameraMode);
	void set_content_callback(pub::AI::ContentCallback *);
	bool set_current_directive(IDirectiveInfo const &,pub::AI::BaseOp const *);
	void set_directive_callback(pub::AI::DirectiveCallback *);
	enum pub::AI::OP_RTYPE  set_directive_priority(enum pub::AI::DirectivePriority);
	void set_personality(pub::AI::Personality const &);
	void set_ship_up_direction(Vector const &);
	void set_state_graph(int,bool);
	void set_turn_sensitivity(float);
	void set_user_turning_input_state(bool);
	void submit_camera_up(Vector const &);
	void update_current_behavior_afterburner(bool);
	void update_current_behavior_auto_avoidance(bool);
	void update_current_behavior_auto_level(bool);
	void update_current_behavior_brake_reverse(bool);
	void update_current_behavior_cruise(bool);
	void update_current_behavior_direction(Vector const &);
	void update_current_behavior_engage_engine(bool);
	void update_current_behavior_slide_strafe_burst(enum StrafeDir);
	void update_current_behavior_throttle(float);
	void update_level_camera(bool);

public:
};