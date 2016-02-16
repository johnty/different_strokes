
//
// MPI_TrainElement.h
//
// Description:
//   A powered element with an associated MPI_FloatTrain.  the float train is
//   meant to be used to manage a train of its previous positions for use in
//   graphical effects.
//

#ifndef __MPI_TRAINELEMENT_H__
#define __MPI_TRAINELEMENT_H__

#include "MPI_PoweredElement.h"
#include "MPI_FloatTrain.h"

class MPI_TrainElement : public MPI_PoweredElement
{

  public:

    MPI_TrainElement( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler );

    MPI_FloatTrain& getFloatTrain( void );

    void acceptVisitor( MPI_ElementVisitor& visitor );

  private:

    MPI_FloatTrain train_;

};

#endif

// vim:sw=4:et:cindent:
