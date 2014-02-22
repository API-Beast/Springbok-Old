//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

template<typename T, typename C, C WithoutPtr<T>::Type::*Member>
List<typename WithoutPtr<T>::Type*> GeometryView<T, C, Member>::getObjectsInRect(Vec2F start, Vec2F end)
{
	auto xrange = XAxisView.getRange(start.X, end.X);
	auto yrange = YAxisView.getRange(start.Y, end.Y);
	List<typename WithoutPtr<T>::Type*> result; 
	
	for(auto& objA : xrange)
		for(auto& objB : yrange)
			if((&objA) == (&objB))
			{
				result.pushBack(&makeRef(objA));
				break;
			}
			
	return result;
};

#include "GeometryView.h"
