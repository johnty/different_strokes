
//
// MPI_AudioParticleSpace.cpp
//

#include "MPI_AudioParticleSpace.h"

#include "MPI_AudioWavetable.h"
#include "MPI_CanonicalTimeArclengthMap.h"

MPI_AudioParticleSpace::MPI_AudioParticleSpace( MPI_Audio &audioinstance, MPI_AudioWavetable &wavetable, MPI_CanonicalTimeArclengthMap const& canonicaltimearclengthmap ) :
    wavetablesynth_( audioinstance, wavetable ),
    playhead_( NULL ),
    canonicaltimearclengthmap_( canonicaltimearclengthmap ),
    resamplingperiod_( 1.0 / 5.0 ) // for slope calc, resample at 5Hz FIXME magic number?
{
    // empty
}

void MPI_AudioParticleSpace::addElement( MPI_OneSpaceElement *element, float position )
{

    MPI_ParticleSpace::addElement( element, position );

    // if the particle wasn't added, don't go any further
    if ( !MPI_ParticleSpace::containsElement(element) )
        return;

    // grab the element as the new play head
    playhead_ = element;

    // reset all of the wavetable playback settings according to the element's
    // position and speed
    wavetablesynth_.reset();
    wavetablesynth_.addTime( canonicalToWavetableSamples( position ) );
    wavetablesynth_.setGain( 1.0 );
    wavetablesynth_.setActiveFlag( true );
    refreshPlayRate();

}

void MPI_AudioParticleSpace::removeElement( MPI_OneSpaceElement const *element )
{

    MPI_ParticleSpace::removeElement( element );

    if ( playhead_ == element ) {
        // clear the the play head pointer and stop the wavetable synth
        playhead_ = NULL;
        wavetablesynth_.setActiveFlag( false );
    }

}

void MPI_AudioParticleSpace::refreshPlayRate( void )
{

    // update the play rate as appropriate
    if ( playhead_ != NULL )
        wavetablesynth_.setRate( getPlayRate( getElementPosition( playhead_ ) ) );

    // this method should be called fast enough to keep the wavetable playback
    // in sync with the play head movement.  they will get out of sync a
    // little, but hopefully not too much as long as this method is called
    // fairly often.

    // I'm assuming it will be sufficient to call this method once at every
    // frame.  only at those points do you know that the element positions are
    // consistent with the current real time, up to the latency caused by
    // dispatching all of the events in the scheduler.

    // NB: this will only sample the play rate curve where there are frames!
    // the framelist defines where the timevsarclengthmap_ is sampled during
    // the stroke playback, and it's expected that the framelist will have
    // a much higher sampling rate than the timevsarclengthmap_.
    // if there are very few frames, it'll only get the speed from the
    // timevsarclengthmap_ at those frames.

}

MPI_AudioWavetable const& MPI_AudioParticleSpace::getWavetable( void ) const
{
    return wavetablesynth_.getWavetable();
}

float MPI_AudioParticleSpace::arclengthToWavetableSeconds( float arclengthpos ) const
{
    // convert the arclength position to wavetable position in seconds.
    // this amounts to multiplying by the ratio wavetablelength / arclength, so
    // you can also use it to convert speeds (ie, arclengh/sec ->
    // wavetablelength/sec).
    return arclengthpos * wavetablesynth_.getWavetable().getLength() /
        canonicaltimearclengthmap_.getTotalArclength();
}

float MPI_AudioParticleSpace::getPlayRate( float canonicalpos ) const
{

    // this method assumes
    // canonicaltimearclengthmap_.inCanonicalRange(canonicalpos) is true

    // get the stroke time corresponding to canonicalpos
    float time = canonicaltimearclengthmap_.getTimeFromCanonical( canonicalpos );

    // if we're at the end of the stroke, return speed 0.0
    if ( time == canonicaltimearclengthmap_.getTotalTime() )
        return 0.0;

    // get the slope of the arclength/time curve for this point and convert it
    // into a wavetable play rate using arclengthToWavetableSeconds()
    return arclengthToWavetableSeconds(
            canonicaltimearclengthmap_.getResampledArclengthVsTimeSlope( time, resamplingperiod_ ) );

}

float MPI_AudioParticleSpace::canonicalToWavetableSamples( float canonicalpos ) const
{
    return arclengthToWavetableSeconds( canonicaltimearclengthmap_.getArclengthFromCanonical( canonicalpos ) ) *
        wavetablesynth_.getWavetable().getFileRate();
}

// vim:sw=4:et:cindent:
