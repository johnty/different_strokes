
//
// MPI_BoundingBox.h
//
// Description:
//   2D bounding box class for tracking the spatial extents of an object.
//   Used for avoiding unnecessary expensive computations.
//

#ifndef __MPI_BOUNDINGBOX_H__
#define __MPI_BOUNDINGBOX_H__

#include "MPI_Point2D.h"

class MPI_BoundingBox
{

  public:

    MPI_BoundingBox(MPI_Point2D const& firstpoint, MPI_Point2D const& secondpoint);

    // intersection queries
    bool overlaps( MPI_BoundingBox const& otherbox ) const;
    bool contains( MPI_Point2D const& point ) const;

    // extend bounding box to contain the given point
    void extendToContain( MPI_Point2D const& point );

    // get corners
    MPI_Point2D const& getLowerLeft( void ) const;
    MPI_Point2D const& getUpperRight( void ) const;

    void print( std::ostream &os ) const;

  private:

    // the two opposite corners
    MPI_Point2D lowerleft_;
    MPI_Point2D upperright_;

};

std::ostream &operator<<( std::ostream &os, MPI_BoundingBox const &bbox );

#endif

// vim:sw=4:et:cindent:
