
//
// MPI_Workspace.h
//
// Description:
//   Top-level workspace.  The interface through which all communication with
//   the interface goes.  Deals with the abstract data in the interface;
//   doesn't handle any graphics, audio, or networking.  Specialised subclasses
//   build all of this in.
//

// FIXME
// does MPI_Workspace::appendPolyLinePoint invoke the copy constructor every
// time we add a point?
// important to know: a) it does all that work, and b) we have to define a
// copy constructor if we need to do that.
// need to be aware of how this behaves.
// the thing that's nice about this is that we don't have to fiddle around
// with allocation and freeing.
// is it possible to avoid doing a copy, but keeping the references?

#ifndef __MPI_WORKSPACE_H__
#define __MPI_WORKSPACE_H__

#include <ostream>
#include <list>

class MPI_Point2D;
class MPI_PolyLine;
class MPI_PolyLineVisitor;
class MPI_PolyLinePointVisitor;
class MPI_PolyLineFactory;
class MPI_BoundingBox;

class MPI_Workspace
{

  public:

    MPI_Workspace();
    virtual ~MPI_Workspace();

    // A factory must be supplied through setFactory() before any polylines
    // are created!
    void setFactory( MPI_PolyLineFactory const* factory );

    void beginPolyLine( void );
    void endPolyLine( void );
    void appendPolyLinePoint( MPI_Point2D const &point );

    void removePolyLine( MPI_PolyLine const *polyline );

    virtual void updateState( void );

    void visitPolyLines( MPI_PolyLineVisitor const& visitor ) const;
    void visitPoints( MPI_PolyLinePointVisitor const& visitor ) const;
    void visitPointsInBoundingBox( MPI_PolyLinePointVisitor const& visitor, MPI_BoundingBox const& boundingbox ) const;

    virtual void print( std::ostream &os ) const;

  protected:

    void updatePolyLineStates( void );

    // list of workspace polylines
    std::list<MPI_PolyLine*> polyLineList_;

  private:

    // pointer to current polyline; set to polyLineList_.end() if none current
    // FIXME change this to a normal pointer -- more straightforward
    std::list<MPI_PolyLine*>::iterator currentPolyLine_;
    MPI_PolyLineFactory const* factory_;

};

std::ostream &operator<<( std::ostream &os, MPI_Workspace const &workspace );

#endif

// vim:sw=4:et:cindent:
