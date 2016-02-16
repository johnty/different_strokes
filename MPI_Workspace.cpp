
//
// MPI_Workspace.cpp
//

#include "MPI_Workspace.h"

#include "MPI_PolyLine.h"
#include "MPI_PolyLinePoint.h"
#include "MPI_PointListIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_PolyLineFactory.h"
#include "MPI_BoundingBox.h"

#include <cassert>

MPI_Workspace::MPI_Workspace() :
    factory_(NULL)
{
    // indicate no current polyline
    currentPolyLine_ = polyLineList_.end();
}

MPI_Workspace::~MPI_Workspace()
{
    // delete the polylines
    std::list<MPI_PolyLine*>::iterator pline;
    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline)
        delete (*pline);
}

void MPI_Workspace::setFactory( MPI_PolyLineFactory const* factory )
{
    factory_ = factory;
}

void MPI_Workspace::beginPolyLine( void )
{

    // assert that there's nothing currently active
    assert( currentPolyLine_ == polyLineList_.end() );

    // allocate a polyline and add it to the list
    polyLineList_.push_back( factory_->createPolyLine() );

    // update the currentPolyLine_ to point to the last polyline in the list
    currentPolyLine_ = polyLineList_.end();
    --currentPolyLine_;

}

void MPI_Workspace::endPolyLine( void )
{
    // set the currentPolyLine_ to null
    // this'll get overridden by derived classes to do housekeeping on a mouse
    // up
    assert( currentPolyLine_ != polyLineList_.end() );
    (*currentPolyLine_)->end();
    currentPolyLine_ = polyLineList_.end();
}

void MPI_Workspace::appendPolyLinePoint( MPI_Point2D const &point )
{

    // assert that something is currently active
    assert( currentPolyLine_ != polyLineList_.end() );

    (*currentPolyLine_)->appendPoint( point );

}

void MPI_Workspace::removePolyLine( MPI_PolyLine const *polyline )
{

    // FIXME this is a little weird since we're not using polyline pointers
    // anywhere in this interface to this class.  Think a bit harder about this
    // design.  I guess it's okay for now, though.

    // assert that we haven't received a NULL pointer, and that we're not
    // deleting the current polyline
    assert( polyline != NULL && *currentPolyLine_ != polyline );

    // find the polyline in the list
    std::list<MPI_PolyLine*>::iterator plinetoremove;
    plinetoremove = find(polyLineList_.begin(), polyLineList_.end(), polyline);
    //assert( plinetoremove != polyLineList_.end() );

    // remove polyline from the list
    //polyLineList_.erase( plinetoremove );

    // delete the polyline
    //delete polyline;

}

void MPI_Workspace::updateState( void )
{

    // update the state of the workspace
    // this method will be overridden by subclasses for dealing with their
    // specific global state issues.

    updatePolyLineStates();

}

void MPI_Workspace::visitPolyLines( MPI_PolyLineVisitor const& visitor ) const
{
    // iterate over the polylines and visit them
    std::list<MPI_PolyLine*>::const_iterator pline;
    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline)
        (*pline)->acceptVisitor(visitor);
}

void MPI_Workspace::visitPoints( MPI_PolyLinePointVisitor const& visitor ) const
{

    // FIXME should this be written in terms of visitPolyLines()?  Could write
    // a polyline visitor that took a point visitor as a parameter, and then
    // passed it to each of the lines.  Would it be hard to restrict the
    // visiting to a bounding like we do in visitPointsInBoundingBox()

    // iterate over all of the polylines, calling the point visitor on each
    // point.
    std::list<MPI_PolyLine*>::const_iterator pline;
    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline) {

        // iterate over each point
        MPI_IteratorPtr<MPI_PointListIterator> curpoint( (*pline)->allocatePointListIterator() );
        for ( curpoint->first(); !curpoint->isDone(); curpoint->next() )
            curpoint->getPoint()->acceptVisitor( visitor );

    }

}

void MPI_Workspace::visitPointsInBoundingBox( MPI_PolyLinePointVisitor const& visitor, MPI_BoundingBox const& boundingbox ) const
{

    // Iterate over all the points, and visit the ones within the given
    // bounding box
    std::list<MPI_PolyLine*>::const_iterator pline;
    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline) {

        MPI_IteratorPtr<MPI_PointListIterator> curpoint( (*pline)->allocatePointListIterator() );
        for ( curpoint->first(); !curpoint->isDone(); curpoint->next() ) {
            // FIXME ...->getPoint()->getPoint() is confusing!
            if ( boundingbox.contains( curpoint->getPoint()->getPoint() ) )
                curpoint->getPoint()->acceptVisitor( visitor );
        }

    }

}

void MPI_Workspace::print( std::ostream &os ) const
{

    std::list<MPI_PolyLine*>::const_iterator pline;

    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline)
    {
        if ( pline != polyLineList_.begin() )
                os << ", ";
        os << '[' << **pline << ']';
    }

}

void MPI_Workspace::updatePolyLineStates( void )
{
    // iterate over the polylines and update their states
    std::list<MPI_PolyLine*>::const_iterator pline;
    for (pline = polyLineList_.begin(); pline != polyLineList_.end(); ++pline)
        (*pline)->updateState();
}

std::ostream &operator<<( std::ostream &os, MPI_Workspace const &workspace )
{
    workspace.print(os);
    return os;
}

// vim:sw=4:et:cindent:
