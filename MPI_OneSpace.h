
//
// MPI_OneSpace.h
//
// Description:
//   A one-dimensional parameter space.  Holds point elements
//   (MPI_OneSpaceElement objects) and can determine their adjacency.
//   Subclasses will specialise this class to handle element interaction.
//   MPI_OneSpace is not responsible for the storage of the elements.
//   FIXME update this description.
//

// TODO
//  - Need to think about finding the next element when we make no guarantees
//    about the ordering of elements that have the same position.  Can't just
//    take the next element in the list; need to compare it to the ones at the
//    same position, too.
//    - don't bother with this for now -- it probably won't matter much for
//      drawn strokes.  I'll have to come back to it later.
//    - that's actually only going to be an issue for the MPI_OneSpace
//      subclasses anyway.  come back to it.
//  - should the list items be pointers or references?
//  - think about adding find next element after a particular point (include
//    this?)
//  - think about adding other stuff to the interface
//    - only add methods that are needed -- keep it minimal
//  - include an updateState() or no?
//  - will probably have to include a resort() method
//  - need to have something to just query the list contents?  subclasses will
//    have to access the list contents through the interface provided here.
//  - add something to visit all elements in a particular range?  that'll be
//    useful when implementing the particle motion
//    - or make this a method to move a particle instantly from one spot to
//      another, colliding with the other elements along the way?
//  - you shouldn't really be able to change the position of an element through
//    its own interface; you should only be able to reposition stuff through
//    this class.  I guess that would neccesitate another private class that
//    pairs an element with its position, and that is only used here.  or make
//    it read-only from outside so you can get but not set an element's
//    position.  you shouldn't have to do a lookup every time you want to get
//    the position of an element.  maybe it's not going to be used much in the
//    end, though, so maybe don't bother.
//  - after I'm done with this implementation, I'll have to go over the classes
//    I wrote in this phase to make sure they're clean, elegant and general.
//  - would it be better to make a class with no positions or ordering, which
//    just moves items around and collides them when they leapfrog adjacent
//    items, and then build a version with positions out of that?  might be
//    easier; think about this for the long term.  the class would have to
//    have some kind of implicit ordering, I guess...  or maybe not, not sure.
//    might be easier to clearly separate the different parts of the class to
//    clarify the algorithms, though.
//    - you could have a class that just has elements in a sorted list, sorted
//      according to details left to the subclasses.  then you could have a
//      methods for move left, move right, and they'd swap the elements and
//      invoke the visitor.  no notion of positions.  then subclass that class
//      to make a class with positions.  then subclass that to handle
//      collisions, particles, intersections.
//      - or not even a sorted list; just a list where you can leapfrog things
//        and visit stuff appropriately.
//      - could have pre-swap, post-swap hooks for overriding in the
//        subclasses.
//  - need to make this class const correct!  make it as const as possible.
//  - think about making allocateElementVisitor() pure virtual
//  - need to take stock of how often the constructors and copy constructors
//    are called with this new MPI_OneSpaceElementPos scheme (efficiency).
//    like, things are copied every time something is inserted into the list.
//  - Okay, I'm having big problems here -- I can't use const references as
//    handles since that doesn't work with swapping elements.  The next idea
//    was to go with const MPI_OneSpaceElementPos pointers, which would work
//    with swapping elements.  The think there, though, is that I'd never be
//    able to ensure that one of those handles would always point to something
//    valid -- an element could be removed by a visitor or something, and you'd
//    still be hanging onto a pointer to the freed memory (eg, a call to
//    handle->getPosition() would segfault).  You could always check that it's
//    valid with some call into the space before using it, but since you can't
//    guarantee that it's valid, you'd have to do a linear search through the
//    list to find it (can't do a binary search since you can't call
//    getPosition() on it).  Right, so if we're going to have to do linear
//    searches all the time, why not just take the hit and use const element
//    pointers as the handles?
//    - the way to solve the problem would be to have some sort of hash mapping
//      handles to element locators (el/pos pair, or index, or something), and
//      then doing a binary search or something once you get the location.
//      You'd have to keep the hash and the list in sync.  Or maybe there's
//      some other combination of stl classes that do what I want to do
//      efficiently...
//  - need to go through this class and make the terminology consistent:
//    elements are elements, and list items are items.  try to get rid of
//    "elementpos" names.

#ifndef __MPI_ONESPACE_H__
#define __MPI_ONESPACE_H__

#include "MPI_OneSpaceElementPos.h"
#include <list>
#include <ostream>

class MPI_ElementVisitor;
class MPI_ElementConstVisitor;
class MPI_ElementIterator;
class MPI_ElementConstIterator;

class MPI_OneSpace
{

  private:

    // comparison operator for use in ordering item list
    class ItemBefore
    {
      public:
        bool operator()( MPI_OneSpaceElementPos const& a, MPI_OneSpaceElementPos const& b ) const;
    };

    // predicate for identifying an item that contains the given element
    class ItemContainsElement
    {
      public:
        ItemContainsElement( MPI_OneSpaceElement const *element ) : element_(element) {};
        bool operator()( MPI_OneSpaceElementPos const& elementpos ) const;
      private:
        MPI_OneSpaceElement const *element_;
    };

  public:

    virtual ~MPI_OneSpace();

    virtual void addElement( MPI_OneSpaceElement *element, float position );
    virtual void removeElement( MPI_OneSpaceElement const *element );

    bool containsElement( MPI_OneSpaceElement const *element ) const;
    float getElementPosition( MPI_OneSpaceElement const *element ) const;

    virtual void moveElement( MPI_OneSpaceElement const *element, float newpos );

    MPI_OneSpaceElement const* getLastElement( void ) const;

    MPI_ElementIterator* allocateElementIterator( void ) const;
    MPI_ElementConstIterator* allocateElementConstIterator( void ) const;

    virtual void print( std::ostream &os ) const;

  protected:

    virtual MPI_ElementVisitor* allocateElementVisitor( void ) const;

    void visitElements( MPI_ElementVisitor &visitor );
    void visitConstElements( MPI_ElementConstVisitor &visitor );

  private:

    typedef std::list<MPI_OneSpaceElementPos>::iterator listiterator;
    typedef std::list<MPI_OneSpaceElementPos>::const_iterator listconstiterator;

    listiterator getItemIterator( MPI_OneSpaceElement const *element );
    listconstiterator getItemIterator( MPI_OneSpaceElement const *element ) const;
    listiterator getInsertIterator( float position );
    void removeItem( listiterator item );

    void advanceAfter( listiterator item, float newpos, MPI_ElementVisitor& visitor );
    void advanceBefore( listiterator item, float newpos, MPI_ElementVisitor& visitor );

    void moveThroughItem( listiterator moveitem, listiterator target, MPI_ElementVisitor& visitor );

    // sorted list of items
    std::list<MPI_OneSpaceElementPos> items_;

};

std::ostream &operator<<( std::ostream &os, MPI_OneSpace const &space );

#endif

// vim:sw=4:et:cindent:
