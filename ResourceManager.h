#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <vector>
#include <string>

class BaseResource
{
protected:
	std::string ref_id;

public:
	std::string GetRefID();
	BaseResource(std::string ref_id);
	~BaseResource();
};

template<class T>
class Resource : public BaseResource
{
private:
	T resource;

public:
	Resource(std::string ref_id, T resource);
	~Resource();

	T GetResource();
};

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static std::vector<BaseResource*> resources;

	static bool RefIDExists(std::string ref_id);

	static bool LoadAudioResource(std::string path, std::string ref_id);
	static bool LoadImageResource(std::string path, std::string ref_id);
	static bool UnloadResource(std::string ref_id);
	
	template<class T>
	static bool LoadTResource(T resource, std::string ref_id);

	template<class T> 
	static T RequestResource(std::string ref_id);
};


#include "ResourceManager.hpp"

#endif