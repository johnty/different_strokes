
//
// MPI_PlayheadStroke.h
//
// Description:
//   Playhead stroke which embeds a wavetable along its length.
//   The audio subclass is the one that does the work; this is mostly for
//   exposing properties of the underlying audio subclass.
//   I need to be able to draw the audio strokes without having the drawing
//   system depend on an audio class.
//

#ifndef __MPI_PLAYHEADSTROKE_H__
#define __MPI_PLAYHEADSTROKE_H__

#include "MPI_ParticleStroke.h"

class MPI_PlayheadStroke : public MPI_ParticleStroke
{

  public:

    MPI_PlayheadStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler );

    virtual float getLength( void ) const;

    virtual void acceptVisitor( MPI_PolyLineVisitor const& visitor );

};

#endif

// vim:sw=4:et:cindent:
