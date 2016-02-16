
//
// MPI_TrainElementFactory.cpp
//

#include "MPI_TrainElementFactory.h"

#include "MPI_TrainElement.h"

MPI_TrainElementFactory::MPI_TrainElementFactory( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler ) :
    onespace_( onespace ),
    framelist_( framelist ),
    scheduler_( scheduler )
{
    // empty
}

MPI_OneSpaceElement* MPI_TrainElementFactory::createElement( void ) const
{
    return new MPI_TrainElement( onespace_, framelist_, scheduler_ );
}

// vim:sw=4:et:cindent:
