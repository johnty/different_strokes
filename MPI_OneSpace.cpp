
//
// MPI_OneSpace.cpp
//

#include "MPI_OneSpace.h"

#include "MPI_OneSpaceElement.h"
#include "MPI_ElementVisitor.h"
#include "MPI_ElementConstVisitor.h"
#include "MPI_OneSpaceIterator.h"
#include "MPI_OneSpaceConstIterator.h"

bool MPI_OneSpace::ItemBefore::operator()( MPI_OneSpaceElementPos const& a, MPI_OneSpaceElementPos const& b ) const
{
    return a.getPosition() < b.getPosition();
}

bool MPI_OneSpace::ItemContainsElement::operator()( MPI_OneSpaceElementPos const& elementpos ) const
{
    return elementpos.getElement() == element_;
}

MPI_OneSpace::~MPI_OneSpace()
{
    while ( !items_.empty() )
        removeItem( items_.begin() );
}

void MPI_OneSpace::addElement( MPI_OneSpaceElement *element, float position )
{

    // adds the element to the one space
    // ensures the elements are ordered
    // assumes the items_ list is already ordered properly

    // find the insert point according to position;
    // insert the element (nb the insertion point can't be a const iterator)
    items_.insert( getInsertIterator(position),
            MPI_OneSpaceElementPos(element, position) );

    // activate the item; this amounts to a post-add hook that the element can
    // supply
    // FIXME I'd prefer not to have an activate() method in the base element
    // class -- too specific, I feel like I'm polluting it.
    element->activate();

}

void MPI_OneSpace::removeElement( MPI_OneSpaceElement const *element )
{

    // removes an element from the items_ list
    // assumes the element exists in the list already
    // assumes the items_ list is already ordered properly

    // get the iterator to the given element;
    // remove the element from the list (nb the deletion point can't be a const
    // iterator)
    // FIXME can't assume getItemIterator() will return a valid iterator; the
    // argument could point to an item that's been removed or something...
    removeItem( getItemIterator(element) );

}

bool MPI_OneSpace::containsElement( MPI_OneSpaceElement const *element ) const
{
    return getItemIterator( element ) != items_.end();
}

float MPI_OneSpace::getElementPosition( MPI_OneSpaceElement const *element ) const
{
    return getItemIterator( element )->getPosition();
}

void MPI_OneSpace::moveElement( MPI_OneSpaceElement const *element, float newpos )
{

    // move the element to some target position, colliding with the other
    // elements along the way
    // this method assumes the list is sorted, and that element appears in it
    // the collisions may modify the list, as long as the list stays consistent
    // (sorted) and the element that's being moved isn't repositioned.

    // FIXME think about obviating advanceBefore/advanceAfter and making this
    // method handle both directions symmetrically.  you'd have to do a test to
    // see if newpos is between givenitem and the appropriate neighbour; if it
    // is, just set the position, if it's not, call moveThroughItem().  so
    // you'd need a step to determine which neighbour to use, cache these in
    // left and right items (either of which could be givenitem) to test
    // whether left <= newpos < right, and then take the appropriate action.
    // moveThroughItem() works symmetrically, so don't need to do any cases
    // there.

    listiterator givenitem;
    listiterator neighbourafter;

    // allocate the visitor to use for element interactions
    // FIXME this visitor should take a reference to the element that's doing
    // the colliding, the call should be able to create different visitors
    // depending on the element's type, and the visitor should be able to
    // modify the element over the course of the iteration below.
    MPI_ElementVisitor *visitor = allocateElementVisitor();

    while ( true ) {

        // find the item, find its neighbourafter
        givenitem = getItemIterator( element );
        neighbourafter = givenitem;
        ++neighbourafter;

        // this is the stopping condition
        // if neighbourafter is equal to the insert iterator, stop
        if ( givenitem->getPosition() == newpos &&
                neighbourafter == getInsertIterator( newpos ) )
            break;

        // if the givenitem <= newpos, move it afterward
        // if the newpos < givenitem, move it before
        if ( newpos < givenitem->getPosition() )
            advanceBefore( givenitem, newpos, *visitor );
        else
            advanceAfter( givenitem, newpos, *visitor );

    }

    // free the visitor
    delete visitor;

}

MPI_OneSpaceElement const* MPI_OneSpace::getLastElement( void ) const
{
    // return null if there's no last element; otherwise, return the element
    if ( items_.empty() )
        return NULL;
    else
        return items_.back().getElement();
}

MPI_ElementIterator* MPI_OneSpace::allocateElementIterator( void ) const
{
    return new MPI_OneSpaceIterator( items_ );
}

MPI_ElementConstIterator* MPI_OneSpace::allocateElementConstIterator( void ) const
{
    return new MPI_OneSpaceConstIterator( items_ );
}

void MPI_OneSpace::print( std::ostream &os ) const
{
    // iterate over the elements and print them out
    listconstiterator currentitem;
    for ( currentitem = items_.begin(); currentitem != items_.end();
            ++currentitem )
        os << "[" << *currentitem << "], ";
    os << "done";
}

MPI_ElementVisitor* MPI_OneSpace::allocateElementVisitor( void ) const
{
    // to be overridden by subclasses to create particular interactions between
    // the elements
    // FIXME think about making this a pure virtual method, so that we couldn't
    // instantiate plain onespaces.
    return new MPI_ElementVisitor;
    // FIXME this visitor should take a reference to the element that's doing
    // the colliding, the call should be able to create different visitors
    // depending on the element's type, and the visitor should be able to
    // modify the element over the course of the iteration.
    //
    // change it to accept the pointer to the element that's doing the
    // visiting.  subclasses can call a visitor on this to create a *second*
    // visitor, which would be returned.  so we have *two* visitors being used,
    // and in this way, we can define actions between pairs of specific types.
    // you could rig it up so that there's no action unless powered elements
    // act on intersections, for example (not sure you'd actually want to do
    // that, though -- need to think about it).
}

void MPI_OneSpace::visitElements( MPI_ElementVisitor &visitor )
{
    std::list<MPI_OneSpaceElementPos>::iterator item;
    for (item = items_.begin(); item != items_.end(); ++item)
        item->getElement()->acceptVisitor( visitor );
}

void MPI_OneSpace::visitConstElements( MPI_ElementConstVisitor &visitor )
{
    std::list<MPI_OneSpaceElementPos>::const_iterator item;
    for (item = items_.begin(); item != items_.end(); ++item)
        item->getElement()->acceptConstVisitor( visitor );
}

MPI_OneSpace::listiterator MPI_OneSpace::getItemIterator( MPI_OneSpaceElement const *element )
{

    // find and return the iterator pointing to the item corresponding to given
    // element

    return find_if( items_.begin(), items_.end(), ItemContainsElement(element) );

}

MPI_OneSpace::listconstiterator MPI_OneSpace::getItemIterator( MPI_OneSpaceElement const *element ) const
{

    // find and return the const iterator pointing to the item corresponding to
    // given element.  this code must be the same as in the non-const version
    // of this method.

    return find_if( items_.begin(), items_.end(), ItemContainsElement(element) );

}

MPI_OneSpace::listiterator MPI_OneSpace::getInsertIterator( float position )
{
    // find an return an iterator at the appropriate insert point for the given
    // position.
    return upper_bound( items_.begin(), items_.end(),
            MPI_OneSpaceElementPos(NULL,position), ItemBefore());
}

void MPI_OneSpace::removeItem( MPI_OneSpace::listiterator item )
{

    // deallocate item's element, and remove the item
    // the element in the item should always be valid, so we can just delete it
    // without checking.

    delete item->getElement();
    items_.erase( item );

}

void MPI_OneSpace::advanceAfter( MPI_OneSpace::listiterator item, float newpos, MPI_ElementVisitor& visitor )
{

    // advance the element contained in the list item toward newpos.
    // if there's another item in the way, collide with it and don't move any
    // further
    // newpos is assumed to not be before item's position
    // item is assumed to be non-null
    // assumes list is sorted properly; this means that
    // neighbourbefore <= item <= neighbourafter

    // get neighbour after the given item
    listiterator neighbourafter( item );
    neighbourafter++;

    // if newpos is strictly before neighbourafter (newpos < neighbourafter),
    // you can just set the position to newpos
    if ( neighbourafter == items_.end() ||
            newpos < neighbourafter->getPosition() ) {
        item->setPosition( newpos );
        return;
    }

    // so neighbourafter <= newpos. move item through neighbourafter.
    moveThroughItem( item, neighbourafter, visitor );

}

void MPI_OneSpace::advanceBefore( MPI_OneSpace::listiterator item, float newpos, MPI_ElementVisitor& visitor )
{

    // advance the element contained in the list item toward newpos.
    // if there's another item in the way, collide with it and don't move any
    // further
    // newpos is assumed to be before item's position
    // item is assumed to be non-null
    // assumes list is sorted properly; this means that
    // neighbourbefore <= item <= neighbourafter

    // get neighbour before the given item
    listiterator neighbourbefore( item );
    neighbourbefore--;

    // if neighbourbefore <= newpos, you can just set the position to newpos
    if ( neighbourbefore == items_.end() ||
            neighbourbefore->getPosition() <= newpos ) {
        item->setPosition( newpos );
        return;
    }

    // so newpos < neighbourbefore.  move item through neighbourbefore.
    moveThroughItem( item, neighbourbefore, visitor );

}

void MPI_OneSpace::moveThroughItem( MPI_OneSpace::listiterator moveitem, MPI_OneSpace::listiterator target, MPI_ElementVisitor& visitor )
{

    // move moveitem to target and through it, leaving the items at the same
    // position in space, but swapped in the items_ list.
    // moveitem interacts with target as it passes through.
    // assumptions: moveitem, target are adjacent in the list; the list is
    // consistent (sorted)

    // swap item, neighbourbefore positions and collide
    // visit (collide with) the item we leapfrogged (originally *target), which
    // ends up sitting in the moveitem iterator after the swap.
    // collide after the swap in case the visitor changes the state of the list
    // (need to do it last).
    moveitem->setPosition( target->getPosition() );
    std::swap( *moveitem, *target );
    moveitem->getElement()->acceptVisitor( visitor );

}

std::ostream &operator<<( std::ostream &os, MPI_OneSpace const &space )
{
    space.print(os);
    return os;
}

// vim:sw=4:et:cindent:
