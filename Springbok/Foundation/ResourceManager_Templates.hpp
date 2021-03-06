// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "ResourceManager.h"
#include <typeinfo>
#include <cassert>
#include <Springbok/Utils/Functions.h>
#include <Springbok/Platform/FileSystem.h>

template<typename T, class... Args>
ObjectPointer< T > ResourceManager::getResource(const std::string& path, Args... args)
{
	auto resourceIter = Resources.find(path);
	if(resourceIter != Resources.end())
	{
		auto& resource = resourceIter->second;
		
		// Reload file
		// resource.Pointer.replaceWith(reinterpret_cast<void*>(new T(resource.ResolvedPath, args...)), true);

		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
	else
	{
		auto& resource = Resources[path];
		resource.RequestedPath = path;
		resource.ResolvedPath  = getPath(path);
		resource.DataType = typeid(T).hash_code();
		if(!FileSystem::Info(resource.ResolvedPath).IsFile)
		{
			if(!PrintedResourceSearchPath)
			{
				PrintedResourceSearchPath = true;
				DebugLog("INFO: Searching for files in: $", PrimaryResourcePath);
				for(const std::string& modpath : ModPaths)
						DebugLog("INFO:  Also in: $", modpath);
			}
			DebugLog("ERROR: Can't find file: $", path);
			resource.Pointer  = new T();
		}
		else
			resource.Pointer  = new T(resource.ResolvedPath, args...);
		return reinterpret_pointer_cast<T*>(resource.Pointer);
	}
};
