/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: NOT STARTED
*/
#pragma once

//vftable offs 0x6C
// -> signature: void __stdcall unknown(IEngine *this, unsigned int iObjID, int, int)
//    invoked by CSimple::init (engine keeping track of objects?)

//vftable offs 0x80
// -> signature: CObject * __stdcall unknown(IEngine *this, int qID, int, int)
//    invoked by sub_6284690

//vftable offs 0xA0
// -> signature: int __stdcall unknown(IEngine *this, int iHardpointID)

//vftable offs 0xD8
// -> signature: int __stdcall unknown(IEngine *this, int)
//    invoked by sub_6284690

interface IEngine
{

};