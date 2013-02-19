/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_BACKENDS_ANDROID_ANDROIDAUDIO_HPP
#define GDX_CPP_BACKENDS_ANDROID_ANDROIDAUDIO_HPP

#include <gdx-cpp/Audio.hpp>
#include <gdx-cpp/files/FileHandle.hpp>
#include <jni.h>

namespace gdx {
class AudioDevice;
class Music;
class AudioRecorder;
class Music;
class Sound;

namespace android {

class AndroidAudio : public gdx::Audio
{
public:
    AndroidAudio();
    
    AudioDevice* newAudioDevice(int samplingRate, bool isMono);
    AudioRecorder* newAudioRecoder(int samplingRate, bool isMono);
    Music* newMusic(const FileHandle::ptr file);
    Sound* newSound(const FileHandle::ptr fileHandle);

    void setupJNI( jobject androidAudioObj );

    ~AndroidAudio();
private:
    jobject androidAudioObj;
    
    jmethodID newAudioDeviceJNI;
    jmethodID newAudioRecoderJNI;
    jmethodID newMusicJNI;
    jmethodID newSoundJNI;
};

}
}

#endif // GDX_CPP_BACKENDS_ANDROID_ANDROIDAUDIO_HPP
