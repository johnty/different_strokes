
//
// MPI_AudioSynth.h
//
// Description:
//   Abstract base class for synthesizers
//

#ifndef __MPI_AUDIOSYNTH_H__
#define __MPI_AUDIOSYNTH_H__

class MPI_Audio;

class MPI_AudioSynth
{

  public:

    MPI_AudioSynth( MPI_Audio &audioinstance );
    virtual ~MPI_AudioSynth();

    virtual float tick( void ) = 0;

    void addSynthToAudioInstance( void );
    void removeSynthFromAudioInstance( void );
    void setActiveFlag( bool value );
    bool isActive( void ) const;

  private:

    MPI_Audio &audioinstance_;
    bool active_;

};

#endif

// vim:sw=4:et:cindent:
