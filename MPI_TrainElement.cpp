
//
// MPI_TrainElement.cpp
//

#include "MPI_TrainElement.h"

#include "MPI_ElementVisitor.h"

MPI_TrainElement::MPI_TrainElement( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler ) :
    MPI_PoweredElement( onespace, framelist, scheduler ),
    train_( scheduler )
{
    // empty
}

MPI_FloatTrain& MPI_TrainElement::getFloatTrain( void )
{
    return train_;
}

void MPI_TrainElement::acceptVisitor( MPI_ElementVisitor& visitor )
{
    visitor.visitTrainElement( *this );
}

// vim:sw=4:et:cindent:
