// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

#include "StringParser.h"
#include <Springbok/Resources/ResourceManager.h>
#include <vector>

class ConfigFile
{
public:
	struct PossibleArray
	{
		operator std::string&(){ if(Data.empty()) Data.push_back(""); return Data.front(); };
		operator std::string() const { if(Data.empty()) return ""; else return Data.front(); };
		
		std::vector<std::string> toList(){ return Data; };
		float toFloat(){ return std::stof(Data.front()); };
		int   toInt  (){ return std::stoi(Data.front()); };
		
		//std::string& operator[](int i){ return Data[i]; };
		PossibleArray& operator=(const std::vector<std::string>& other);
		PossibleArray& operator=(const std::string& other);
		bool operator==(const std::string& s);
		bool operator==(const std::vector<std::string>& v);
		PossibleArray(const std::string& s){ Data.push_back(s); };
		std::vector<std::string> Data;
	};
	struct KeyValue
	{
		KeyValue(const std::string& k, const PossibleArray& parray) : Key(k), Value(parray){};
		std::string Key;
		PossibleArray Value;
	};
	struct Object
	{
		Object() = default;
		Object(std::string name, Object* parent)
		{
			TypeHint = name;
			Parent = parent;
			Values.reserve(1);
			Children.reserve(1);
		};
		
		std::string TypeHint = "__undefined__";
		std::vector<KeyValue> Values;
		std::vector<Object> Children;
		Object* Parent = nullptr;
		
		PossibleArray& operator[](const std::string& key);
		Object& getObject(const std::string& key);
	};
public:
	ConfigFile();
	ConfigFile(const std::string& path, ResourceManager* manager = ResourceManager::GetInstance());
	void loadFromBuffer(const std::string& content);
	void loadFromFile(const std::string& path, ResourceManager* manager = ResourceManager::GetInstance());
	operator ConfigFile::Object&(){ return Root; };
	PossibleArray& operator[](const std::string& key){ return Root[key]; };
	Object& getObject(const std::string& key){ return Root.getObject(key); };
public:
	Object Root;
};