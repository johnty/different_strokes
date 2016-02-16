
//
// MPI_AudioCallback.cpp
//

#include "MPI_AudioCallback.h"

#include "MPI_Audio.h"
#include "MPI_Application.h"

int MPI_AudioCallback::callback( char *buffer, int bufferSize, void *data )
{

    // get the audio instance and fill the buffer

    // FIXME why does this have to go through the application?
    // just because it's a singleton and globally accessible?
    // why not make the audio callback a singleton itself or something?
    // this class shouldn't rely on the application to grab the audio instance.
    MPI_Audio& audioinstance = MPI_Application::getInstance().getAudio();
    // FIXME each of these ticks should be in a try/catch block (see rtsine.cpp)
    audioinstance.tickBuffer( (double*) buffer, bufferSize );

    return 0;

}

int MPI_AudioCallback::callback2(void *outputBuffer, void* inBuf, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *data)
{

    // this class shouldn't rely on the application to grab the audio instance.
    MPI_Audio& audioinstance = MPI_Application::getInstance().getAudio();
    audioinstance.tickBuffer( (double*)outputBuffer , nBufferFrames );


}

MPI_AudioCallback::MPI_AudioCallback()
{
    // empty
}

MPI_AudioCallback::~MPI_AudioCallback()
{
    // empty
}

// vim:sw=4:et:cindent:
