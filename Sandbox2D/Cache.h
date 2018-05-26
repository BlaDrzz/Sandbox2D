#pragma once

template <typename T>
struct BaseCache
{
	std::unordered_map<std::string, T*> typeCache;
	
	//! push an object to _cache
	T* push(std::string name, T* object)
	{
		// Return if a _bitmap already exists with that name
		if (typeCache.count(name) != 0)
		{
			LogWarning("Object name already exists, please erase the old reference first!");
			return nullptr; 
		}

		typeCache[name] = object;

		// Return the object
		return object;
	}
	
	//! Searches for an object with given name and returns the object
	//! Returns nullptr if name was not found
	T* findByName(std::string name)
	{
		return typeCache.count(name) > 0 ? typeCache[name] : nullptr;
	}

	//! Searches for an object with given _path and returns the object
	//! Returns nullptr if name was not found
	T* findByPath(std::string path)
	{
		for (auto i : typeCache)
		{
			if (i.second->_path == path) return i.second;
		}
		return nullptr;
	}

	//! Delete and erase all objects with a given name
	void erase(std::string name)
	{
		if (typeCache.count(name) == 0)	return LogWarning("No object with that name was found");

		// Delete the _bitmap object
		delete typeCache[name];

		// Delete record from the hashmap
		typeCache.erase(name);
	}

	//! Deletes the contents of the typeCache and clears it.
	void clear()
	{
		for (auto obj : typeCache)
		{
			delete obj.second;
		}

		typeCache.clear();
	}

	std::string dump(int tabAmount = 0)
	{
		std::string dumpText = Indent(tabAmount) + typeid(T).name() + " _cache:\n";

		dumpText += Indent(tabAmount) + "[\n";
		for (auto bmp : typeCache)
		{
			dumpText += Indent(tabAmount + 1) + "{ \"" + bmp.first + "\" : \"" + bmp.second->_path + "\" },\n";
		}
		dumpText += Indent(tabAmount) + "]";

		return dumpText;
	}
};

struct BitmapCache : BaseCache<Bitmap>
{
	Bitmap* createCachableBitmap(const std::string path)
	{
		// Try to find an object with that _path alread
		auto bmp = findByPath(path);
		
		// If no obj with that _path was found, create a new one
		if (bmp == nullptr) bmp = new Bitmap(path);

		return bmp;
	}
};

struct FontCache : BaseCache<Font>
{
	Font* createCachableFont(const std::string path, int size, int index = -1)
	{
		// Try to find an object with that _path already
		auto fnt = findByPath(path);

		// If no obj with that _path was found, create a new one
		if (fnt == nullptr) fnt = new Font(path, size, index);

		return fnt;
	}
};

struct MusicCache : BaseCache<Music>
{
	Music* createCachableMusic(const std::string path)
	{
		// Try to find an object with that _path alread
		auto mus = findByPath(path);

		// If no obj with that _path was found, create a new one
		if (mus == nullptr) mus = new Music(path);

		return mus;
	}
};

struct SoundFXCache : BaseCache<SoundFX>
{
	SoundFX* createCachableSound(const std::string path)
	{
		// Try to find an object with that _path alread
		auto sfx = findByPath(path);

		// If no obj with that _path was found, create a new one
		if (sfx == nullptr) sfx = new SoundFX(path);

		return sfx;
	}
};

struct Cache
{
	BitmapCache bmpCache;
	FontCache fntCache;
	MusicCache musCache;
	SoundFXCache sfxCache;

	~Cache()
	{
		bmpCache.clear();
		fntCache.clear();
		musCache.clear();
		sfxCache.clear();
	}

	std::string dump()
	{
		LogInfo("Dumping _cache");

		std::string dump = "[DUMP] Cache:\n[\n";

		dump += bmpCache.dump(1) + "\n";
		dump += fntCache.dump(1) + "\n";
		dump += musCache.dump(1) + "\n";
		dump += sfxCache.dump(1) + "\n";

		return dump += "]";
	}
};

