
//
// MPI_PolyLine.cpp
//

#include "MPI_PolyLine.h"

#include "MPI_PolyLinePoint.h"
#include "MPI_PointListIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_BoundingBox.h"

MPI_PolyLine::MPI_PolyLine() :
    boundingbox_(NULL)
{
    // empty
}

MPI_PolyLine::~MPI_PolyLine()
{

    // free the bounding box if there is one
    if ( boundingbox_ != NULL )
        delete boundingbox_;

    // NB: subclasses must have their own storage for their point lists, and
    // need to delete the points in their destructors (even though the points
    // were allocated and added from MPI_PolyLine)!
    // We can't do it here since destructors always call the local version of a
    // virtual function (see Satir and Brown, "C++: The Core Language", p.
    // 163), and allocatePointListIterator() is pure virtual in this class.

}

void MPI_PolyLine::appendPoint( MPI_Point2D const &point )
{

    // allocate a point and append it to the list
    // allocatePointAndAddToList() is a virtual function that is
    // defined by MPI_PolyLine subclasses
    allocatePointAndAddToList( point );

    // if this is the first point, allocate boundingbox_
    // otherwise, extend it to contain the new point
    if ( boundingbox_ == NULL )
        boundingbox_ = new MPI_BoundingBox( point, point );
    else
        boundingbox_->extendToContain( point );

}

void MPI_PolyLine::end( void )
{
    // empty
    // this will get overridden by derived classes for specific behaviours
}

MPI_BoundingBox const& MPI_PolyLine::getBoundingBox( void ) const
{
    // this will trip a bus error/segfault if there are no points in the
    // polyline
    return *boundingbox_;
}

void MPI_PolyLine::updateState( void )
{
    // empty
    // this will get overridden by derived classes for specific behaviours
}

void MPI_PolyLine::print( std::ostream &os ) const
{
    MPI_IteratorPtr<MPI_PointListIterator> curpoint( allocatePointListIterator() );
    for ( curpoint->first(); !curpoint->isDone(); curpoint->next() )
        os << *curpoint->getPoint() << ", ";
    os << "done";
}

std::ostream &operator<<( std::ostream &os, MPI_PolyLine const &polyline )
{
    polyline.print(os);
    return os;
}

// vim:sw=4:et:cindent:
