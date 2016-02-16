
//
// MPI_ParticleFactory.cpp
//

#include "MPI_ParticleFactory.h"

#include "MPI_RemovalStroke.h"
#include "MPI_PlayheadStroke.h"

MPI_PolyLine* MPI_ParticleFactory::ParticleStrokeState::createPolyLine( void ) const
{
    return new MPI_ParticleStroke( particlefactory_.getWorkspace(), particlefactory_.getScheduler() );
}

MPI_PolyLine* MPI_ParticleFactory::RemovalStrokeState::createPolyLine( void ) const
{
    return new MPI_RemovalStroke( particlefactory_.getWorkspace(), particlefactory_.getScheduler() );
}

MPI_PolyLine* MPI_ParticleFactory::PlayheadStrokeState::createPolyLine( void ) const
{
    return new MPI_PlayheadStroke( particlefactory_.getWorkspace(), particlefactory_.getScheduler() );
}

MPI_ParticleFactory::MPI_ParticleFactory( MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    workspace_( workspace ),
    scheduler_( scheduler ),
    state_( NULL ),
    particlestrokestate_( *this ),
    removalstrokestate_( *this ),
    playheadstrokestate_( *this )
{
    // empty
}

MPI_PolyLine* MPI_ParticleFactory::createPolyLine( void ) const
{
    return state_->createPolyLine();
}

MPI_Workspace& MPI_ParticleFactory::getWorkspace( void ) const
{
    return workspace_;
}

MPI_Scheduler& MPI_ParticleFactory::getScheduler( void ) const
{
    return scheduler_;
}

void MPI_ParticleFactory::setStateParticleStroke( void )
{
    setParticleFactoryState( &particlestrokestate_ );
}

void MPI_ParticleFactory::setStateRemovalStroke( void )
{
    setParticleFactoryState( &removalstrokestate_ );
}

void MPI_ParticleFactory::setStatePlayheadStroke( unsigned int strokenum )
{
    setParticleFactoryState( &playheadstrokestate_ );
}

MPI_ParticleFactory::ParticleFactoryState* MPI_ParticleFactory::getParticleFactoryState( void )
{
    return state_;
}

void MPI_ParticleFactory::setParticleFactoryState( MPI_ParticleFactory::ParticleFactoryState* state )
{
    state_ = state;
}

// vim:sw=4:et:cindent:
