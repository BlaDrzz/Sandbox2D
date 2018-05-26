#pragma once

struct Audio
{
	std::string _path;

	Audio() {}
	virtual ~Audio() {}

	virtual void update() = 0;
};

struct Music : Audio
{
	Mix_Music* _music = nullptr;

	Music(const std::string path)
	{
		this->_path = path;
		Music::update();
	}

	~Music()
	{
		if (_music != nullptr)
		{
			Mix_FreeMusic(_music);
			_music = nullptr;
		}
	}

	void update() override
	{
		if (_music != nullptr) Mix_FreeMusic(_music);

		_music = Mix_LoadMUS(_path.c_str());
		if (_music == nullptr) LogError("Error loading file " + _path);
	}

	void start(const int loop = -1) const
	{
		if (Mix_PlayingMusic() == 0) Mix_PlayMusic(_music, loop);
		else LogWarning("Music " + _path + " started while it's already playing!");
	}

	void pause() const
	{
		if (Mix_PlayingMusic() != 0 && Mix_PausedMusic() != 1) Mix_PauseMusic();
		else LogWarning("Music " + _path + " is not playing or already paused!");
	}

	void resume() const
	{
		if (Mix_PlayingMusic() != 0 && Mix_PausedMusic() == 1) Mix_ResumeMusic();
		else LogWarning("Music " + _path + " is not playing or not paused!");
	}
};

struct SoundFX : Audio
{
	Mix_Chunk* _sound = nullptr;

	SoundFX(const std::string path)
	{
		this->_path = path;
		SoundFX::update();
	}

	~SoundFX()
	{
		if (_sound != nullptr)
		{
			Mix_FreeChunk(_sound);
			_sound = nullptr;
		}
	}

	void update() override
	{
		if (_sound != nullptr) Mix_FreeChunk(_sound);

		_sound = Mix_LoadWAV(_path.c_str());
		if (_sound == nullptr) LogError("Error loading file " + _path);
	}

	void play(const int loop = 0) const
	{
		Mix_PlayChannel(-1, _sound, loop);
	}
};