
//
// MPI_PoweredElement.cpp
//

#include "MPI_PoweredElement.h"

#include "MPI_OneSpace.h"
#include "MPI_Framelist.h"
#include "MPI_Scheduler.h"
#include "MPI_ElementVisitor.h"
#include "MPI_ElementConstVisitor.h"

MPI_PoweredElement::EventMoveElement::EventMoveElement( MPI_PoweredElement *poweredelement, float position, MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler ) :
    poweredelement_( poweredelement ),
    position_( position ),
    onespace_( onespace ),
    framelist_( framelist ),
    scheduler_( scheduler )
{
    // empty
}

void MPI_PoweredElement::EventMoveElement::execute( void )
{

    // clear out the element's pending event field
    poweredelement_->setPendingMoveEvent( NULL );

    // bail if the element doesn't exist -- could have been deleted since we
    // scheduled this event.
    if ( !onespace_.containsElement( poweredelement_ ) )
        return;

    // move the element
    onespace_.moveElement( poweredelement_, position_ );

    // schedule the next event
    MPI_PoweredElement::scheduleNextMove( poweredelement_, position_, onespace_, framelist_, scheduler_ );

    // FIXME need to figure out how to make this work when you want the element
    // to follow the tip of the stroke as you draw

}

MPI_PoweredElement::MPI_PoweredElement( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler ) :
    onespace_( onespace ),
    framelist_( framelist ),
    scheduler_( scheduler ),
    pendingmoveevent_( NULL )
{
    // empty
}

MPI_PoweredElement::~MPI_PoweredElement()
{
    // remove pending move event, if any
    if ( pendingmoveevent_ != NULL )
        scheduler_.cancelEvent( pendingmoveevent_ );
}

void MPI_PoweredElement::activate( void )
{

    // this assumes the element has already been added to the onespace
    // properly.
    // start the animation: schedule the first event
    scheduleNextMove( this, onespace_.getElementPosition(this), onespace_, framelist_, scheduler_ );

    // FIXME this method should really be const since it's not changing
    // anything in the object, but to be general, the activate() method in the
    // base class shouldn't be const since we don't know what subclasses are
    // going to want to do with it.

}

void MPI_PoweredElement::setPendingMoveEvent( MPI_Event *pendingmoveevent )
{
    pendingmoveevent_ = pendingmoveevent;
}

void MPI_PoweredElement::scheduleNextMove( MPI_PoweredElement *poweredelement, float position, MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler )
{

    // schedule the next poweredelement move
    // position is assumed to be the correct current position of poweredelement
    // just bail if there's no frame after position

    if ( !framelist.nextFrameExists( position ) )
        return;

    MPI_Event *moveevent = new EventMoveElement( poweredelement, framelist.getNextFrameNumber(position), onespace, framelist, scheduler );
    scheduler.scheduleEvent( moveevent, framelist.getDelayToNextFrame(position) );
    poweredelement->setPendingMoveEvent( moveevent );

}

void MPI_PoweredElement::acceptVisitor( MPI_ElementVisitor& visitor )
{
    visitor.visitPoweredElement( *this );
}

void MPI_PoweredElement::acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const
{
    visitor.visitPoweredElement( *this );
}

// vim:sw=4:et:cindent:
