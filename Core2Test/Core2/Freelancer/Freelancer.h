/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: IN PROGRESS, UNTESTED
*/
#pragma once

#include "FLDefs.h"
#include "protos.h"
#include "Util\Memory.h"

#include "Freelancer\EngineCamera.h"

namespace FL
{
	namespace fn
	{
		typedef EngineCamera * (*GetActiveCamera_t)(void);
		typedef EngineCamera * (*SetActiveCamera_t)(EngineCamera *);
		typedef EngineCamera * (*GetChaseCamera_t)(void);
		typedef EngineCamera * (*GetTurretCamera_t)(void);
	};
	
	EngineCamera * GetActiveCamera(void); //40F130
	EngineCamera * SetActiveCamera(EngineCamera *); //40F140
	EngineCamera * GetChaseCamera(void); //54BC40
	EngineCamera * GetTurretCamera(void); //54BC50
};
