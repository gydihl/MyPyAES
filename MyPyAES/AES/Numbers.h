/********************************************************************
	created:	2014/10/22
	filename: 	Numbers.h
	author:		µ×»áÀ×
	purpose:	
*********************************************************************/

#pragma once

class Numbers
{
public:
	Numbers(int first, double second)
		: _first(first), _second(second)
	{}

	double memberMult()
	{
		return _first * _second;
	}

protected:
	int _first;
	double _second;
};
