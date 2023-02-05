#include "Audio.hpp"

namespace Framework {
	namespace Audio {
		const uint8_t DEFAULT_CHANNELS = 2;
		const int DEFAULT_FREQUENCY = 44100;
		const int DEFAULT_CHUNKSIZE = 2048;
	}

	AudioHandler::AudioHandler() {

	}

	bool AudioHandler::init(uint8_t channels, int frequency, int chunksize, uint16_t format) {
		if (channels > MIX_CHANNELS) {
			printf("Too many channels for SDL_mixer (%u), defaulting to maximum (%u).\n", channels, MIX_CHANNELS);
			channels = MIX_CHANNELS;
		}

		// We want mp3 and ogg files:
		// For some reason, works for me without this. Breaks with it.
		//int flags = MIX_INIT_OGG | MIX_INIT_MP3;
		/*if (Mix_Init(flags) & flags != flags) {
			printf("Mix_Init: Failed to init required .ogg and .mp3 support!\n");
			printf("Mix_Init: %s\n", Mix_GetError());
			return false;
		}*/

		// Initialize SDL_mixer
		if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}

		this->frequency = frequency;
		this->format = format;
		this->channels = channels;
		this->chunksize = chunksize;

		return true;
	}

	void AudioHandler::quit() {
		// Quit mixer
		Mix_Quit();
	}

	uint8_t AudioHandler::play_sound(Sound sample, int loops, int channel) {
		return Mix_PlayChannel(channel, sample, loops);
	}

	void AudioHandler::set_sound_volume(float volume) {
		Mix_Volume(-1, convert_volume_float_to_int(volume));
	}

	void AudioHandler::set_sound_volume(uint8_t channel, float volume) {
		if (channel < channels) {
			Mix_Volume(channel, convert_volume_float_to_int(volume));
		}
		else {
			printf("Failed to set sound volume! Channel number supplied does not exist.");
		}
	}

	float AudioHandler::get_sound_volume(uint8_t channel) {
		return convert_volume_int_to_float(Mix_Volume(channel, -1));
	}

	Sound AudioHandler::load_sound(std::string path) {
		// Load sample
		Sound sample = Mix_LoadWAV(path.c_str());

		if (sample == NULL) {
			// Failed to load
			printf("Failed to load sound sample, path %s\nSDL_mixer Error: %s\n", path.c_str(), Mix_GetError());
		}

		return sample;
	}

	void AudioHandler::free_sound(Sound* sample) {
		// Free sample
		Mix_FreeChunk(*sample);
		*sample = NULL;
	}


	void AudioHandler::play_music(Music music, int loops) {
		Mix_PlayMusic(music, loops);
	}

	void AudioHandler::halt_music() {
		Mix_HaltMusic();
	}

	bool AudioHandler::is_music_playing() {
		return Mix_PlayingMusic();
	}

	bool AudioHandler::is_music_fading_in() {
		return Mix_FadingMusic() == MIX_FADING_IN;
	}

	bool AudioHandler::is_music_fading_out() {
		return Mix_FadingMusic() == MIX_FADING_OUT;
	}

	void AudioHandler::fade_music_in(Music music, float fade_time, int loops) {
		Mix_FadeInMusic(music, loops, convert_s_to_ms_float_to_int(fade_time));
	}

	void AudioHandler::fade_music_out(float fade_time) {
		Mix_FadeOutMusic(convert_s_to_ms_float_to_int(fade_time));
	}

	void AudioHandler::set_music_volume(float volume) {
		Mix_VolumeMusic(convert_volume_float_to_int(volume));
	}

	float AudioHandler::get_music_volume() {
		return convert_volume_int_to_float(Mix_VolumeMusic(-1));
	}

	Music AudioHandler::load_music(std::string path) {
		// Load music
		Music music = Mix_LoadMUS(path.c_str());

		if (music == NULL) {
			// Failed to load
			printf("Failed to load music, path %s\nSDL_mixer Error: %s\n", path.c_str(), Mix_GetError());
		}

		return music;
	}

	void AudioHandler::free_music(Music* sample) {
		// Free sample
		Mix_FreeMusic(*sample);
		*sample = NULL;
	}

	void AudioHandler::free_all_sounds() {
		for (uint8_t i = 0; i < sound_samples.size(); i++) {
			free_sound(&sound_samples.at(i));
		}
		sound_samples.clear();

	}

	void AudioHandler::free_all_music() {
		for (uint8_t i = 0; i < music_samples.size(); i++) {
			free_music(&music_samples.at(i));
		}
		music_samples.clear();
	}

	void AudioHandler::free_all() {
		free_all_sounds();
		free_all_music();
	}


	int AudioHandler::convert_volume_float_to_int(float volume) {
		return static_cast<int>(volume * MIX_MAX_VOLUME);
	}

	float AudioHandler::convert_volume_int_to_float(int volume) {
		return static_cast<float>(volume) / MIX_MAX_VOLUME;
	}

	int AudioHandler::convert_s_to_ms_float_to_int(float s) {
		return static_cast<int>(s * 1000);
	}
}