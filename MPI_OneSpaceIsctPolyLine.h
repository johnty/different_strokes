
//
// MPI_OneSpaceIsctPolyLine.h
//
// Description:
//   A stroke which has an associated onespace
//

#ifndef __MPI_ONESPACEISCTPOLYLINE_H__
#define __MPI_ONESPACEISCTPOLYLINE_H__

#include "MPI_IntersectionPolyLine.h"

class MPI_OneSpace;

class MPI_OneSpaceIsctPolyLine : public MPI_IntersectionPolyLine
{

  public:

    MPI_OneSpaceIsctPolyLine( MPI_Workspace &workspace ) : MPI_IntersectionPolyLine( workspace ) {}

    virtual MPI_OneSpace& getOneSpace( void ) = 0;
    virtual MPI_OneSpace const& getOneSpace( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
