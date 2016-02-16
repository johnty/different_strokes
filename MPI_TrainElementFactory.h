
//
// MPI_TrainElementFactory.h
//
// Description:
//   Factory for creating MPI_TrainElement elements
//

#ifndef __MPI_TRAINELEMENTFACTORY_H__
#define __MPI_TRAINELEMENTFACTORY_H__

#include "MPI_ElementFactory.h"

class MPI_OneSpace;
class MPI_Framelist;
class MPI_Scheduler;

class MPI_TrainElementFactory : public MPI_ElementFactory
{

  public:

    MPI_TrainElementFactory( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler );

    MPI_OneSpaceElement* createElement( void ) const;

  private:

    MPI_OneSpace &onespace_;
    MPI_Framelist const& framelist_;
    MPI_Scheduler &scheduler_;

};

#endif

// vim:sw=4:et:cindent:
