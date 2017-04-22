/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: N/A
*/
#pragma once

//compiler complains about typename length of
//certain std::list related types
#pragma warning(disable : 4786)

#include <list>
#include <functional>
#include <vector>

//FLDefs.h
class Vector;
class Matrix;
class Transform;

//EquipDescList.h (should change the name)
class EquipDescVector;
class EquipDescList;

//IVP.h
class IVP_Mindist_Base;
class IVP_Listener_Phantom;
class IVP_Controller_Dependent;
class IVP_Controller;
class IVP_Event_Sim;
class IVP_Real_Object;

//CollisionGroupDesc.h
struct CollisionGroupDesc;

//Watchable.h
class Watchable;

//CArchGroup.h
class CArchGroup;

//CArchGroupManager.h
class CArchGroupManager;

//EngineObject.h
class EngineObject;

//CObject.h
class CObject;

//CSimple.h
class CSimple;

//CEqObj.h
class CEqObj;

//PhySys.h
namespace PhySys
{
	struct CreateParms;
	class PhyCollisionStateManager;
}

//Archetype.h
namespace Archetype
{
	class Root; //proto only
	class Equipment;
	class CollisionGroup;
	class FuseIgnitionList;
	class EqObj;
}

namespace pub
{
	namespace AI
	{
		enum ScanResponse;
		class Personality;
		class ContentCallback;
		class DirectiveCallback;
		class BaseOp;
		enum OP_RTYPE;
		enum DirectivePriority;
	}
}

//alienated classes
template<class A, class B>
class CheapSet;

class CBase;
class IObjDB;
class IObjRW;
class IBehaviorManager;
class IDirectiveInfo;
class IStateGraph;
class DamageList;
class CArchGrpTraverser;
class SystemManager;

class INotify
{
public:
	enum Event;
};

class DamageEntry
{
public:
	enum SubObjFate;
};

//Freelancer.h
class EngineCamera;