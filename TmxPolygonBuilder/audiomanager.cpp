/*
    Copyright (c) 2013, <copyright holder> <email>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY <copyright holder> <email> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL <copyright holder> <email> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "audiomanager.h"

AudioManager::AudioManager()
{
 // Just initialize each of the major components of the Audio API
 
 // Create FMOD interface object
 result = FMOD::System_Create(&system);
 errorCheck(result);
  engaged = 0;
 // Check version
 result = system->getVersion(&version);
 errorCheck(result);
 
 if (version < FMOD_VERSION)
 {
   std::cout << "Error! You are using an old version of FMOD " << version << ". This program requires " << FMOD_VERSION << std::endl;
   exit(0);
 }
 
 // Get number of sound cards
 result = system->getNumDrivers(&numDrivers);
 errorCheck(result);
 
 // No sound cards (disable sound)
 if (numDrivers == 0)
 {   
   
   result = system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
   errorCheck(result);
  
 }else{
   
   soundCardEngage();
}
 
   audioInit();
}

void AudioManager::soundCardEngage()
{
  result = system->getDriverCaps(0, &caps,0, &speakerMode);
  errorCheck(result);
  printf("Default Sound Card Set\n");
  // Set the speaker mode to match that in Control Panel
  result = system->setSpeakerMode(speakerMode);
  errorCheck(result);
  printf("Default Speaker Mode Set\n");
  // Increase buffer size if user has Acceleration slider set to off
  if (caps & FMOD_CAPS_HARDWARE_EMULATED)
  {    printf("Slide Buffer set\n");
  result = system->setDSPBufferSize(1024, 10);
  errorCheck(result);
  }
  // Get name of driver
  result = system->getDriverInfo(0, name, 256, 0);
  errorCheck(result);
  printf("Get Driver Info\n");
  // SigmaTel sound devices crackle for some reason if the format is PCM 16-bit.
  // PCM floating point output seems to solve it.
  if (strstr(name, "SigmaTel"))
  {
    result = system->setSoftwareFormat(48000, FMOD_SOUND_FORMAT_PCMFLOAT, 0, 0, FMOD_DSP_RESAMPLER_LINEAR);
    errorCheck(result);
    printf("Sigma Tel Nabbed\n");
  }
}


void AudioManager::audioInit()
{
  // Initialise FMOD
  result = system->init(100, FMOD_INIT_NORMAL, 0);
  
  // If the selected speaker mode isn't supported by this sound card, switch it back to stereo
  if (result == FMOD_ERR_OUTPUT_CREATEBUFFER)
  {
    result = system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO);
    errorCheck(result);
    
    result = system->init(100, FMOD_INIT_NORMAL, 0);
  }
    errorCheck(result);
  
  
  
}




void AudioManager::errorCheck(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    std::cout << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
    exit(-1);
  }
}
void AudioManager::playEffect(std::string soundname)
{
  result = system->createSound(soundname.c_str(),  FMOD_DEFAULT, 0, &sound1);
  errorCheck(result);
  result = system->playSound(FMOD_CHANNEL_FREE, sound1, false, &channel1);
  errorCheck(result);
}
void AudioManager::loadsong(std::string songname)
{
  printf("SONG LOADED\n");
  result = system->createStream(songname.c_str(), FMOD_DEFAULT, 0, &sound0);
  errorCheck(result);
}

void AudioManager::playStream(std::string songname)
{
  printf("SONG PLAYING\n");
  result = system->playSound(FMOD_CHANNEL_FREE, sound0, false, &channel0);
  errorCheck(result);
  channel0->setMode(FMOD_LOOP_NORMAL);
   channel0->setVolume(1.0);
}
void AudioManager::update()
{
 system->update();
}

void AudioManager::pauseToggle(bool pause)
{
  channel1->getPaused(&pause);
  channel1->setPaused(!pause);
}
void AudioManager::setFadeEffect(float time)
{
    volume_level = volume_max - ((float) sin(M_PI/2 * volume_level));
  volume_level *= volume_level;
  
  if(volume_level == 0.0)
  {
    channel0->setPaused(true);
    channel0->setVolume(0.0);
  }else{
    channel0->setVolume(volume_max - volume_level);
  }
}
void AudioManager::cleanUpstream()
{
    errorCheck(sound0->release());
}

void AudioManager::setVolumeLevel(float volumeLevel)
{
    volume_max = volumeLevel;
    volume_level = volume_max;
}

AudioManager::~AudioManager()
{

}

