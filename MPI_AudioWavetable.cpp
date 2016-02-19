
//
// MPI_AudioWavetable.cpp
//

#include "MPI_AudioWavetable.h"

// the max number of channels allowed.  we have to do it this way since there's
// no nice way to resize lastFrameQueried_[] when a file is opened (openFile()
// is non-virtual, so we can't override and hook an allocation onto the end).
char unsigned const MPI_AudioWavetable::maxChannels_ = 32;

MPI_AudioWavetable::MPI_AudioWavetable( std::string fileName, bool raw, bool doNormalize ) :
    WvIn( fileName, raw, doNormalize )
{

    // normalise to something well below 1.0; it starts to clip at 1.0, so if
    // you have things denseley overlaid, normalising to 1.0 will cause a lot
    // of distortion.
    normalize( 0.1 );

    lastFrameQueried_ = new float[ maxChannels_ ];
}

MPI_AudioWavetable::~MPI_AudioWavetable()
{
    delete [] lastFrameQueried_;
}

float MPI_AudioWavetable::getValueAtTime( float time, bool interpolate )
{

    // return the sample frame at a particular time
    // this code adapted from WvIn::lastOut() in STK

    getFrameAtTime( time, interpolate );

    if ( channels_ == 1 )
        return *lastFrameQueried_;

    float output = 0.0;
    for ( unsigned int i=0; i<channels_; i++ ) {
        output += lastFrameQueried_[i];
    }

    return output / channels_;

}

float const* MPI_AudioWavetable::getFrameAtTime( float time, bool interpolate )
{

    // return the sample frame at a particular time
    // this code adapted from WvIn::tickFrame() in STK

    // throw an error if chunking is on -- we don't handle it in this class
    if ( chunking_ ) {
        errorString_ << "MPI_AudioWavetable::getFrameAtTime(): chunking not supported";
        handleError( StkError::UNSPECIFIED );
    }

    // FIXME what's the deal with these register designations?  in original
    // code, time was copied to a register float.

    // Integer part of time address.
    register unsigned long index = (unsigned long) time;

    register unsigned long i;
    if (interpolate) {
        // Linear interpolation ... fractional part of time address.
        register float alpha = time - (float) index;
        index *= channels_;
        for (i=0; i<channels_; i++) {
            lastFrameQueried_[i] = data_[index];
            lastFrameQueried_[i] += (alpha * (data_[index+channels_] - lastFrameQueried_[i]));
            index++;
        }
    }
    else {
        index *= channels_;
        for (i=0; i<channels_; i++)
            lastFrameQueried_[i] = data_[index++];
    }

    return lastFrameQueried_;

}

float MPI_AudioWavetable::getLength( void ) const
{
    // return the wave length in seconds
    return getSize() / getFileRate();
}

// vim:sw=4:et:cindent:
