
//
// MPI_PolyLineVisitor.h
//
// Description:
//   Encapsulates operations on polylines.  Subclass to create particular
//   operations.
//   Taken from the visitor pattern, Gamma et al., page 331.
//

#ifndef __MPI_POLYLINEVISITOR_H__
#define __MPI_POLYLINEVISITOR_H__

// TODO
//  - maybe make this a WorkspaceObject visitor or something if you want to be
//    able to visit non-polyline objects (eg composite objects)

class MPI_BasicStroke;
class MPI_ParticleStroke;
class MPI_RemovalStroke;
class MPI_PlayheadStroke;

class MPI_PolyLineVisitor
{

  public:

    virtual ~MPI_PolyLineVisitor() {};

    virtual void visitBasicStroke( MPI_BasicStroke& polyline ) const {};
    virtual void visitParticleStroke( MPI_ParticleStroke& polyline ) const {};
    virtual void visitRemovalStroke( MPI_RemovalStroke& polyline ) const {};
    virtual void visitPlayheadStroke( MPI_PlayheadStroke& polyline ) const {};

};

#endif

// vim:sw=4:et:cindent:
