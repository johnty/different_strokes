
//
// MPI_AudioCallback.h
//
// Description:
//   A class which contains the global audio callback.
//   Not meant to be instantiated -- just used as a namespace.
//

#ifndef __MPI_AUDIOCALLBACK_H__
#define __MPI_AUDIOCALLBACK_H__

class MPI_AudioCallback
{

  public:

    static int callback( char *buffer, int bufferSize, void *data );

  private:

    MPI_AudioCallback();
    ~MPI_AudioCallback();

};

#endif

// vim:sw=4:et:cindent:
