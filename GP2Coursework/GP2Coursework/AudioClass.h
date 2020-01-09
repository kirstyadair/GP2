#pragma once
// Include statements
#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class AudioClass
{
	// Declare data struct
	struct data {
		// Declare variables
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		// Constructor
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	// Declare a Vector3 struct
	struct Vector3
	{
		float x, y, z;
	};
	// Declare variables
	std::vector<data> datas;
	ALCcontext* context;
	ALCdevice *device;
	// Declare methods
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	// Declare constructor and deconstructor
	AudioClass();
	~AudioClass();
	// Declare methods
	unsigned int loadSound(const char* filename);
	void playSound(unsigned int id);
	void playSound(unsigned int id, glm::vec3& pos);
	void stopSound(unsigned int id);
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt);
	
};

