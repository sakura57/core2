/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"

#include "Common\IVP.h"

//We can't declare IVP classes dllimport because
//they're not exported by any Freelancer libs.
//Disabling this warning is safe as long as
//the IVP class definitions are close enough.
#pragma warning(disable : 4275)

namespace PhySys
{
	struct CreateParms;

	class IMPORT Controller : public IVP_Controller_Dependent
	{
		//MEMBER FUNCTIONS
		Controller(Controller const &);
		Controller(void);
		virtual ~Controller(void);
		Controller & operator=(Controller const &);
		static void  Register(Controller *,CObject *);
		static void  UnRegister(Controller *);
		void push(class Vector const &,float);
		void rotate(class Vector const &,float);
		void wakeup(void);

		//VIRTUAL FUNCTIONS
		virtual void core_is_going_to_be_deleted_event(IVP_Core *);
		virtual IVP_U_Vector<IVP_Core> *get_associated_controlled_cores();

		//MEMBER FIELDS
		bool bUnknown2;
	};
	
	class IMPORT PhyCollisionStateManager : public IVP_Listener_Phantom
	{
	public:
		//MEMBER FUNCTIONS
		PhyCollisionStateManager(PhyCollisionStateManager const &);
		PhyCollisionStateManager(CObject *);
		~PhyCollisionStateManager(void);
		PhyCollisionStateManager & operator=(PhyCollisionStateManager const &);
		void enable_collisions(bool, bool);
		bool get_actual_collision_state(void) const;
		bool get_desired_collision_state(void) const;
		int get_intruding_cobjs(bool, CheapSet<CObject *, std::less<CObject *> > &);
		void update(float);

		IVP_Real_Object * get_other_object(IVP_Mindist_Base *);
		CObject * mindist_to_cobject(IVP_Mindist_Base *);
		
		//VIRTUAL FUNCTIONS
		//vftables indicate core_entered_volume, core_left_volume
		//were probably added in a later version of IVP
		virtual void mindist_entered_volume(IVP_Controller_Phantom *, IVP_Mindist_Base *);
		virtual void mindist_left_volume(IVP_Controller_Phantom *, IVP_Mindist_Base *);
		virtual void phantom_is_going_to_be_deleted_event(IVP_Controller_Phantom *);

		//MEMBER FIELDS
		unsigned int dwUnknown1;
		unsigned int dwUnknown2;
		unsigned int dwUnknown3;
		unsigned char cUnknown1;
	};
}