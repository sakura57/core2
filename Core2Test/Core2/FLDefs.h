/*
	Part of CORE2 SDK
	(C) 2017 Jacob Farnsworth
	
	Marked: N/A
*/
#pragma once

#define IMPORT __declspec(dllimport)

class IMPORT Vector
{
public:
	float v[3];
};

class IMPORT Matrix
{
public:
	float m[3][3];
};

class IMPORT Transform
{
public:
	Matrix m;
	Vector v;
};