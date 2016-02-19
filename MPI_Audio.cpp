
//
// MPI_Audio.cpp
//

#include "MPI_Audio.h"

#include "MPI_AudioSynth.h"
#include "MPI_AudioCallback.h"

#include "RtAudio.h"
#include <cassert>

void MPI_Audio::start( void )
{

    // fire it up
    // we can't do this in the constructor because we need to be sure the
    // MPI_Application constructor returns before we can start calling
    // MPI_Application::getInstance().  the audio callback could fire and try
    // to call this before we're out of the MPI_Application constructor.

    try {
        audio_->setStreamCallback(&MPI_AudioCallback::callback, NULL);
        audio_->startStream();
    }
    catch (RtError &error) {
        error.printMessage();
    }

}

void MPI_Audio::addSynth( MPI_AudioSynth *synth )
{
    // append the synth to the synth list
    synthList_.push_back( synth );
}

void MPI_Audio::removeSynth( MPI_AudioSynth *synth )
{

    // remove the synth from the list

    // find the synth in the list
    std::list<MPI_AudioSynth*>::iterator cursyn;
    cursyn = find( synthList_.begin(), synthList_.end(), synth );

    // assert that we were able to find the synth
    assert( cursyn != synthList_.end() );

    // remove it
    synthList_.erase( cursyn );

}

void MPI_Audio::tickBuffer( double *buffer, int bufferSize ) const
{

    // Tick an entire buffer's worth of samples and write out to the given
    // buffer.  Vectorized code -- cheapest loop on the inside
    int i = 0;
    double *curbufpos = NULL;

    // zero out the buffer
    // the buffer contains stereo interleaved samples, so clear out both the
    // left and right samples.
    curbufpos = buffer;
    for ( i = 0; i < bufferSize; i++ ) {
        *curbufpos++ = 0.0;
        *curbufpos++ = 0.0;
    }

    // for each synth, add in its contribution
    // the buffer contains stereo interleaved samples, so write to both the
    // left and the right channels
    std::list<MPI_AudioSynth*>::const_iterator synth;
    double tickvalue = 0.0;
    for ( synth = synthList_.begin(); synth != synthList_.end(); ++synth ) {
        if ( (*synth)->isActive() ) {
            curbufpos = buffer;
            for ( i = 0; i < bufferSize; i++ ) {
                tickvalue = (*synth)->tick();
                *curbufpos++ += tickvalue;
                *curbufpos++ += tickvalue;
            }
        }
    }

}

MPI_Audio::MPI_Audio()
{

    audio_ = NULL;

    int channels = 2;
    int sampleRate = 44100;
    int bufferSize = 256;  // 256 sample frames
    int nBuffers = 4;      // number of internal buffers used by device
    int device = 0;        // 0 indicates the default or first available device

    // allocate an RtAudio instance
    try {
        audio_ = new RtAudio(device, channels, 0, 0, RTAUDIO_FLOAT64,
                sampleRate, &bufferSize, nBuffers);
    }
    catch (RtError &error) {
        error.printMessage();
    }

}

MPI_Audio::~MPI_Audio()
{

    try {
        // Stop and close the stream
        audio_->stopStream();
        audio_->closeStream();
    }
    catch (RtError &error) {
        error.printMessage();
    }

    delete audio_;

    // make sure the synth list is empty -- these should all have been
    // deallocated before destroying the MPI_Audio object.
    assert( synthList_.empty() );

}

// vim:sw=4:et:cindent:
