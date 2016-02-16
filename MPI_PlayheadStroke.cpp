
//
// MPI_PlayheadStroke.cpp
//

#include "MPI_PlayheadStroke.h"

#include "MPI_PolyLineVisitor.h"

MPI_PlayheadStroke::MPI_PlayheadStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    MPI_ParticleStroke( workspace, scheduler )
{
    // empty
}

float MPI_PlayheadStroke::getLength( void ) const
{
    return 0.0;
}

void MPI_PlayheadStroke::acceptVisitor( MPI_PolyLineVisitor const& visitor )
{
    visitor.visitPlayheadStroke( *this );
}

// vim:sw=4:et:cindent:
