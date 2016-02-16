
//
// MPI_AudioCallback.h
//
// Description:
//   A class which contains the global audio callback.
//   Not meant to be instantiated -- just used as a namespace.
//

#ifndef __MPI_AUDIOCALLBACK_H__
#define __MPI_AUDIOCALLBACK_H__
#include "Stk.h"
#include "RtAudio.h"

class MPI_AudioCallback
{

  public:

    static int callback( char *buffer, int bufferSize, void *data );
    static int callback2(void *outputBuffer, void* inputBuffer, unsigned int nBufferFrames, double streaTime, RtAudioStreamStatus status, void *data);

  private:

    MPI_AudioCallback();
    ~MPI_AudioCallback();

};

#endif

// vim:sw=4:et:cindent:
