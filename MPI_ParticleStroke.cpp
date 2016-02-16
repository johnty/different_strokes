
//
// MPI_ParticleStroke.cpp
//

#include "MPI_ParticleStroke.h"

#include "MPI_PolyLinePoint.h"
#include "MPI_PolyLinePointDequeIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_Scheduler.h"
#include "MPI_TrainElementFactory.h"
#include "MPI_PolyLineVisitor.h"
#include "MPI_ParticleSegment.h"

#include <math.h>

MPI_ParticleStroke::MPI_ParticleStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    MPI_OneSpaceIsctPolyLine( workspace ),
    scheduler_( scheduler ),
    canonicaltimearclengthmap_( scheduler_ ),
    trainelementfactory_( NULL ),
    headelement_( NULL ),
    previouspoint_( 0.0, 0.0 )
{
    // empty
}

MPI_ParticleStroke::~MPI_ParticleStroke()
{

    // free allocated points
    MPI_IteratorPtr<MPI_PointListIterator> curpoint( allocatePointListIterator() );
    for ( curpoint->first(); !curpoint->isDone(); curpoint->next() )
        delete curpoint->getPoint();

    if ( trainelementfactory_ != NULL )
        delete trainelementfactory_;

}

void MPI_ParticleStroke::appendPoint( MPI_Point2D const &point )
{

    // filter out duplicate points.  they are safe to filter out of the stroke,
    // and they're not allowed to be added to the canonicaltimearclengthmap_.
    // do this before calling MPI_IntersectionPolyLine::appendPoint() so that
    // the canonicaltimearclengthmap_ and the point list remain consistent.
    if ( point.getX() == previouspoint_.getX() &&
            point.getY() == previouspoint_.getY() &&
            !canonicaltimearclengthmap_.isEmpty() )
        return;
    previouspoint_ = point;

    // record the point in canonicaltimearclengthmap_.  there should be exactly
    // as many breakpoints in the map as we have points in the stroke.
    // this needs to come before MPI_IntersectionPolyLine::appendPoint()
    // so that the point list/segment list/canonicaltimearclengthmap_ are all
    // consistent if some processing needs to occur as a result.
    // MPI_IntersectionPolyLine::appendPoint() can trigger an intersection,
    // which calls into canonicaltimearclengthmap_.
    canonicaltimearclengthmap_.appendPoint( point );

    // append the point
    MPI_IntersectionPolyLine::appendPoint( point );

    // FIXME I think I should be moving an MPI_PoweredElement along the
    // onespace to keep up with the drawing head.
    // would need to add the begin/end methods to create the powered element,
    // and then to finally activate it to move under its own steam
    // oh, wait, it'll get activated on its own once it gets added; how should
    // this work?

    // FIXME should there be a method for this?  updateHeadElement() or something?
    if ( headelement_ == NULL ) {
        headelement_ = getTrainElementFactory().createElement();
        getOneSpace().addElement( headelement_, 0.0 );
    }
    else
        // move headelement to the position numpts-1.
        getOneSpace().moveElement( headelement_, (float) pointList_.size() - 1.0 );

}

void MPI_ParticleStroke::end( void )
{
    // clear the pointer to the head element to indicate that it's not being
    // manipulated anymore
    // NB: don't have to delete it since it will be cleared out on the next
    // updateState() call
    // NB: Since this is end(), we don't need to worry about headelement_ being
    // reallocated since there won't be another appendPoint() call.
    headelement_ = NULL ;
}

void MPI_ParticleStroke::updateState( void )
{

    MPI_OneSpaceIsctPolyLine::updateState();

    // cull particles at the end of the stroke; these can't move any further
    // don't do it while headelement_ is being manually advanced since it'll
    // cause a segfault the next time a point is added.
    if ( headelement_ == NULL ) {
        float lastpos = pointList_.size() - 1.0;
        removeOneSpaceElements( lastpos );
    }
    // FIXME is pointList_.size() - 1.0 the best way to get the last coord?  do
    // it via canonicaltimearclengthmap_ instead?

    // FIXME For MPI_TrainElement objects, they'll get deleted before their
    // tail is finished its animation

    // FIXME it'd be better to have a removal element that is placed at the end
    // of the stroke, but the element visior can only act on the target and not
    // on the source so it won't work with the current design.  See
    // MPI_OneSpace::moveThroughItem() for where the visiting happens.
    // MPI_ElementVisitor doesn't know which item it's being called from, so
    // can't act on the source.
    // FIXME redo the element removal as above with a special collision element
    // visitors can act depending on a source: they can take creation
    // arguments; see MPI_DrawElementVisitor constructor
    // Also, can create different elements based on the class of the invoker.
    // See MPI_Segment::allocateIntersectionVisitor() and its overridden
    // versions for an example; see also the MPI_SegmentVisitor /
    // MPI_SegmentIntersectionVisitor tree

}

MPI_OneSpace& MPI_ParticleStroke::getOneSpace( void )
{

    // FIXME we have this method so that subclasses can subsitute in their own
    // onespaces if they want.  if they do, particlespace_ will get allocated
    // but not used.  I tried to get it to allocate it dynamically on demand,
    // but that scheme didn't work in the const version of this method.  The
    // easiest solution I can see right now is to waste a little storage and
    // have an automatic local in the object.  That way it'll work with the
    // const version, but unfortunately storage is wasted.  I'll have to come
    // back to it sometime later.

    return particlespace_;

}

MPI_OneSpace const& MPI_ParticleStroke::getOneSpace( void ) const
{
    // FIXME see comments in non-const version above
    return particlespace_;
}

MPI_Point2D MPI_ParticleStroke::linearPositionToPoint( float position ) const
{

    // go from a linear position along the stroke in canonical coordinates
    // (where breakpoints corresponsd to successive integer coords) to
    // 2d space coordinates.  linearly interpolate between breakpoints
    // for fractional positions.
    // assumes 0.0 <= position <= pointList_.size()-1

    // if it's the last index, return the last point
    // otherwise, interpolate between current point and the next one

    float integerpart;
    float fractionalpart = modff( position, &integerpart );
    unsigned int firstindex = static_cast<unsigned int>( integerpart );
    unsigned int secondindex = static_cast<unsigned int>( integerpart+1.0 );

    // if we're after the last point, just return it
    if ( firstindex == pointList_.size()-1 )
        return pointList_[firstindex]->getPoint();

    // interpolate between the first and second points
    MPI_Point2D const& firstpoint = pointList_[firstindex]->getPoint();
    MPI_Point2D const& secondpoint = pointList_[secondindex]->getPoint();
    return MPI_Point2D(
            (1.0-fractionalpart)*firstpoint.getX() + fractionalpart*secondpoint.getX(),
            (1.0-fractionalpart)*firstpoint.getY() + fractionalpart*secondpoint.getY() );

}

MPI_PointListIterator* MPI_ParticleStroke::allocatePointListIterator( void ) const
{
    return new MPI_PolyLinePointDequeIterator( pointList_ );
}

void MPI_ParticleStroke::acceptVisitor( MPI_PolyLineVisitor const& visitor )
{
    visitor.visitParticleStroke( *this );
}

MPI_Segment* MPI_ParticleStroke::allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint )
{

    float newsegposstart = getNumSegments();
    float newsegposend = newsegposstart + 1.0;

    return new MPI_ParticleSegment( getWorkspace(), *this, firstpoint, secondpoint, getOneSpace(), newsegposstart, newsegposend, getTrainElementFactory() );

}

MPI_Point2D const* MPI_ParticleStroke::getLastPoint( void ) const
{
    if ( pointList_.empty() )
        return NULL;
    else
        return &pointList_.back()->getPoint();
}

int MPI_ParticleStroke::getNumPoints( void ) const
{
    return pointList_.size();
}

MPI_CanonicalTimeArclengthMap const& MPI_ParticleStroke::getCanonicalTimeArclengthMap( void ) const
{
    return canonicaltimearclengthmap_;
}

void MPI_ParticleStroke::allocatePointAndAddToList( MPI_Point2D const &point )
{
    pointList_.push_back( new MPI_PolyLinePoint( *this, point ) );
}

MPI_TrainElementFactory& MPI_ParticleStroke::getTrainElementFactory( void )
{

    // Allocate the MPI_TrainElementFactory instance if necessary and return a
    // reference to it.  We want the particular kind of onespace to be
    // definable by subclasses, which they do by overriding the getOneSpace()
    // method.  The reason we allocate the factory "on demand" like this
    // instead of in the constructor is because of how virtual function calls
    // are treated from constructors: they always call the class's definition of
    // the method, even if the constructor is being called from a subclass.
    // (see c++: the core language.)  We want the overriden version of
    // getOneSpace() to be the one called when we're in a subclass, so we can't
    // call it in the constructor.  So really what we're doing is trying to
    // defer the allocation the factory any time after the constructor's
    // completed so the right getOneSpace() function gets called.

    if ( trainelementfactory_ == NULL )
        trainelementfactory_ = new MPI_TrainElementFactory( getOneSpace(), canonicaltimearclengthmap_.getFramelist(), scheduler_ );
    return *trainelementfactory_;

}

void MPI_ParticleStroke::removeOneSpaceElements( float position )
{

    // remove particlespace_ elements at or after the given position

    MPI_OneSpace &onespace = getOneSpace();
    float lastelementpos = 0.0;

    do
    {

        MPI_OneSpaceElement const* lastelement = onespace.getLastElement();

        // if lastelement is null, the onespace is empty, so bail
        if ( lastelement == NULL )
            return;

        // otherwise, check its position and remove it if necessary
        lastelementpos = onespace.getElementPosition( lastelement );
        if ( position <= lastelementpos )
            onespace.removeElement( lastelement );

    }
    while( position <= lastelementpos );

}

// vim:sw=4:et:cindent:
