#pragma once

/**
* \brief Represents Audio
*/

struct Audio
{
	/**
	* \brief Path to the audiofile
	*/
	std::string _path;

	/**
	* \brief Constructor
	*/
	Audio() {}

	/**
	* \brief Destructor
	*/
	virtual ~Audio() {}

	/**
	* \brief Update the audio object
	*/
	virtual void update() = 0;
};

/**
* \brief Represents Music (Subclass of Audio)
*/
struct Music : Audio
{
	/**
	* \brief A music chunk interpreted via mikmod
	*/
	Mix_Music* _music = nullptr;

	/**
	* \brief Constructor
	* @param path: a string as path
	*/
	Music(const std::string path)
	{
		this->_path = path;
		Music::update();
	}

	/**
	* \brief Destructor
	*/
	~Music()
	{
		if (_music != nullptr)
		{
			Mix_FreeMusic(_music);
			_music = nullptr;
		}
	}

	/**
	* \brief Update this music chunk
	*/
	void update() override
	{
		if (_music != nullptr) Mix_FreeMusic(_music);

		_music = Mix_LoadMUS(_path.c_str());
		if (_music == nullptr) LogError("Error loading file " + _path);
	}

	/**
	* \brief Start playing the music
	* @param loop: default value = -1
	*/
	void start(const int loop = -1) const
	{
		if (Mix_PlayingMusic() == 0) Mix_PlayMusic(_music, loop);
		else LogWarning("Music " + _path + " started while it's already playing!");
	}

	/**
	* \brief Pause the music
	*/
	void pause() const
	{
		if (Mix_PlayingMusic() != 0 && Mix_PausedMusic() != 1) Mix_PauseMusic();
		else LogWarning("Music " + _path + " is not playing or already paused!");
	}

	/**
	* \brief Resume the music
	*/
	void resume() const
	{
		if (Mix_PlayingMusic() != 0 && Mix_PausedMusic() == 1) Mix_ResumeMusic();
		else LogWarning("Music " + _path + " is not playing or not paused!");
	}
};

/**
* \brief Represents SoundFX (Subclass of Audio)
*/
struct SoundFX : Audio
{
	/**
	* \brief A sound chunk
	*/
	Mix_Chunk* _sound = nullptr;

	/**
	* \brief Constructor
	* @param path: a string as path
	*/
	SoundFX(const std::string path)
	{
		this->_path = path;
		SoundFX::update();
	}

	/**
	* \brief Destructor
	*/
	~SoundFX()
	{
		if (_sound != nullptr)
		{
			Mix_FreeChunk(_sound);
			_sound = nullptr;
		}
	}

	/**
	* \brief Update this sound chunk
	*/
	void update() override
	{
		if (_sound != nullptr) Mix_FreeChunk(_sound);

		_sound = Mix_LoadWAV(_path.c_str());
		if (_sound == nullptr) LogError("Error loading file " + _path);
	}

	/**
	* \brief Play this sound chunk
	* @param loop: default value = -1
	*/
	void play(const int loop = 0) const
	{
		Mix_PlayChannel(-1, _sound, loop);
	}
};