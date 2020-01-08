#include "AudioClass.h"


AudioClass::AudioClass()
{
	// Open the sound card
	device = alcOpenDevice(NULL);
	// If null, show an error message
	if (device == NULL)
	{
		std::cout << "Opening sound card failed" << std::endl;
	}

	// Create the context
	context = alcCreateContext(device, NULL);

	// If context fails to create, show an error
	if (context == NULL)
	{
		std::cout << "Create context failed" << std::endl;
	}

	// Make the context current
	alcMakeContextCurrent(context);
}

AudioClass::~AudioClass()
{
	// Iterate through the array of data
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		// Delete the audio source
		alDeleteSources(1, (unsigned int*)&datas[i].sourceID);
		if (datas[i].bufferID != -1)
		{
			// Delete the buffers
			alDeleteBuffers(1, (unsigned int*)&datas[i].bufferID);
			delete[] datas[i].buffer;
		}
	}
	// Destroy the context
	alcDestroyContext(context);
	// Close the sound card
	alcCloseDevice(device);
}

// Finds if using big endian
bool AudioClass::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

// COnverts to integer
int AudioClass::convertToInt(char* buffer, int length)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

// Load WAV file
char* AudioClass::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	// Read required information
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);

	// Create a new array of characters for sound data
	char* soundData = new char[size];
	// Read the sound data
	in.read(soundData, size);
	// Return the sound data
	return soundData;
}

unsigned int AudioClass::loadSound(const char* filename)
{
	// Set up variables
	bool found = false;
	unsigned int sourceID, bufferID;
	char* soundData = NULL;

	// Iterate through datas
	for (unsigned int i = 0; i < datas.size(); i++)
	{
		if (datas[i].name == filename && datas[i].bufferID != -1)
		{
			// Assign buffer IDs
			bufferID = datas[i].bufferID;
			found = true;
			break;
		}
	}

	// If found is false
	if(!found)
	{	
		// Create variables to store data
		int channel, sampleRate, bps, size;
		// Load the sound data
		soundData = loadWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		// Generate buffers
		alGenBuffers(1, &bufferID);

		// Check the audio channel
		if (channel == 1)
		{
			// Check BPS
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}
		// Buffer data
		alBufferData(bufferID, format, soundData, size, sampleRate);
	}

	// Create source ID and return it
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);
	datas.push_back(data(sourceID, (!found ? bufferID : -1), soundData, filename));
	return sourceID;
}

// Play sound
void AudioClass::playSound(unsigned int id) 
{
	alSourcePlay(id);
}

// Play sound with listener position
void AudioClass::playSound(unsigned int id, glm::vec3& pos) 
{
	alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
	alSourcePlay(id);
}

// Stop sound
void AudioClass::stopSound(unsigned int id) 
{
	alSourceStop(id);
}

// Set the listener position
void AudioClass::setlistener(glm::vec3& pos, glm::vec3& camLookAt) 
{
	alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
	float orinet[6] = { camLookAt.x,camLookAt.y,camLookAt.z,0,1,0 };
	alListenerfv(AL_ORIENTATION, orinet);
}