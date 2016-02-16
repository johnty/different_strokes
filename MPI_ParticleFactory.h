
//
// MPI_ParticleFactory.h
//
// Description:
//   Factory for creating strokes in the "particle" stroke set.
//

#ifndef __MPI_PARTICLEFACTORY_H__
#define __MPI_PARTICLEFACTORY_H__

#include "MPI_PolyLineFactory.h"

class MPI_Workspace;
class MPI_Scheduler;

class MPI_ParticleFactory : public MPI_PolyLineFactory
{

    // factory states -- each ParticleFactoryState subclass encapsulates a
    // state that the factory can be in.

  protected:

    class ParticleFactoryState
    {
      public:
        virtual ~ParticleFactoryState() {};
        virtual MPI_PolyLine* createPolyLine( void ) const = 0;
    };

  private:

    class ParticleStrokeState : public ParticleFactoryState
    {
      public:
        ParticleStrokeState( MPI_ParticleFactory const &factory ) : particlefactory_(factory) {}
        MPI_PolyLine* createPolyLine( void ) const;
      private:
        MPI_ParticleFactory const &particlefactory_;
    };

    class RemovalStrokeState : public ParticleFactoryState
    {
      public:
        RemovalStrokeState( MPI_ParticleFactory const &factory ) : particlefactory_(factory) {}
        MPI_PolyLine* createPolyLine( void ) const;
      private:
        MPI_ParticleFactory const &particlefactory_;
    };

    class PlayheadStrokeState : public ParticleFactoryState
    {
      public:
        PlayheadStrokeState( MPI_ParticleFactory const &factory ) : particlefactory_(factory) {}
        MPI_PolyLine* createPolyLine( void ) const;
      private:
        MPI_ParticleFactory const &particlefactory_;
    };

  public:

    // The MPI_ParticleFactory class proper:

    MPI_ParticleFactory( MPI_Workspace &workspace, MPI_Scheduler &scheduler );

    MPI_PolyLine* createPolyLine( void ) const;

    MPI_Workspace& getWorkspace( void ) const;
    MPI_Scheduler& getScheduler( void ) const;

    virtual void setStateParticleStroke( void );
    virtual void setStateRemovalStroke( void );
    virtual void setStatePlayheadStroke( unsigned int strokenum );

  protected:

    ParticleFactoryState* getParticleFactoryState( void );
    void setParticleFactoryState( ParticleFactoryState* state );

  private:

    MPI_Workspace &workspace_;
    MPI_Scheduler &scheduler_;

    // the current state
    ParticleFactoryState* state_;

    // an instance of each possible factory state goes here, and state_
    // points to one of these instances.
    ParticleStrokeState particlestrokestate_;
    RemovalStrokeState removalstrokestate_;
    PlayheadStrokeState playheadstrokestate_;

};

#endif

// vim:sw=4:et:cindent:
