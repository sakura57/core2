/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\CSimple.h"
#include "Common\CEquip.h"
#include "Common\CEquipManager.h"
#include "Common\CArchGroupManager.h"
#include "Common\EquipDesc.h"

class IMPORT CEqObj : public CSimple
{
public:
	class IMPORT DockAnimInfo
	{
	public:
		DockAnimInfo(void);
		DockAnimInfo & operator=(DockAnimInfo const &);
		
		bool bUnknown1;
		int iUnknown2;
		int iUnknown3;
		int iUnknown4;
	};

	CEqObj(CEqObj const &);
	CEqObj(CObject::Class);
	void attaching_damaged_obj(CacheString const &);
	float attitude_towards(CEqObj const *)const ;
	void attitude_towards_symmetrical(float &,CEqObj const *,float &)const ;
	void clear_arch_groups(void);
	IBehaviorManager * create_behavior_interface(IObjRW *,int);
	Archetype::EqObj * eqobjarch(void)const ;
	unsigned int get_base(void)const ;
	unsigned int get_base_name(void)const ;
	IBehaviorManager * get_behavior_interface(void);
	float get_cloak_percentage(void)const ;
	void get_collision_group_description(std::list<CollisionGroupDesc> &)const ;
	unsigned int const & get_dock_target(void)const ;
	bool get_explosion_dmg_bounding_sphere(float &,Vector &)const ;
	float get_max_power(void)const ;
	float get_power(void)const ;
	float get_power_ratio(void)const ;
	int get_vibe(void)const ;
	bool is_base(void)const ;
	int is_cloaked(void)const ;
	bool is_control_excluded(unsigned int)const ;
	bool is_damaged_obj_attached(CacheString const &)const ;
	bool is_dock(void)const ;
	bool launch_pos(Vector &,Matrix &,int)const ;
	void load_arch_groups(std::list<CollisionGroupDesc> const &);
	void set_control_exclusion(unsigned int);
	void set_power(float);
	bool sync_cargo(EquipDescList const &);
	bool add_cargo_item(EquipDesc const &);
	bool add_equipped_item(EquipDesc const &);
	void compute_explosion_dmg_bounding_sphere(float &,Vector &)const ;
	void init_docking_points(unsigned int);
	void destroy_equipment(DamageList const &,bool);
	void update_docking_animations(float);

	//VIRTUAL FUNCTIONS
	virtual ~CEqObj(void);
	virtual int update(float,unsigned int);
	virtual void disable_controllers(void);
	virtual void enable_controllers(void);
	virtual void unmake_physical(void);
	virtual void remake_physical(PhySys::CreateParms const &,float);
	virtual unsigned int get_name(void)const ;
	virtual bool is_targetable(void)const ;
	virtual void connect(IObjDB *);
	virtual void disconnect(IObjDB *);
	//init_physics at this position
	virtual void init(CreateParms const &);
	virtual void load_equip_and_cargo(EquipDescVector const &,bool);
	virtual void clear_equip_and_cargo(void);
	virtual void get_equip_desc_list(EquipDescVector &)const ;
	virtual bool add_item(EquipDesc const &);
	virtual enum ObjActivateResult activate(bool,unsigned int);
	virtual bool get_activate_state(std::vector<bool> &);
	virtual void disconnect(IObjRW *);
	virtual void disconnect(INotify *);
	virtual void connect(INotify *);
	virtual void notify(enum INotify::Event,void *);
	virtual void flush_animations(void);
	virtual float get_total_hit_pts(void)const ;
	virtual float get_total_max_hit_pts(void)const ;
	virtual float get_total_relative_health(void)const ;
	virtual bool get_sub_obj_velocity(unsigned short,Vector &)const ;
	virtual bool get_sub_obj_center_of_mass(unsigned short,Vector &)const ;
	virtual bool get_sub_obj_hit_pts(unsigned short,float &)const ;
	virtual bool set_sub_obj_hit_pts(unsigned short,float);
	virtual bool get_sub_obj_max_hit_pts(unsigned short,float &)const ;
	virtual bool get_sub_obj_relative_health(unsigned short,float &)const ;
	virtual unsigned short inst_to_subobj_id(long)const ;
	virtual long sub_obj_id_to_inst(unsigned short)const ;
	virtual void destroy_sub_objs(DamageList const &,bool);
	virtual int enumerate_sub_objs(void)const ;
	virtual CEquip * alloc_equip(unsigned short,Archetype::Equipment *,bool);
	virtual void link_shields(void);

public:
	unsigned int field_E0;
	CEquipManager equip_manager;
	unsigned int iVibe;
	unsigned int field_104;
	unsigned int field_108[13];
	float flCloakPercent;
	CArchGroupManager archgroup_manager;
	unsigned char field_168;
	unsigned int field_16C;
	unsigned int field_170;
	unsigned int field_174;
	unsigned int field_178;
	unsigned char field_17C;
	unsigned int field_180;
	unsigned int field_184;
	unsigned int field_188;
	unsigned int field_18C;
	IBehaviorManager *behavior_interface; //IBehaviorInterface
	float flPower;
	float flMaxPower;
	unsigned int field_19C;
};