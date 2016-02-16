
//
// MPI_DrawElementVisitor.h
//
// Description:
//   Draws the visited element using opengl
//

#ifndef __MPI_DRAWELEMENTVISITOR_H__
#define __MPI_DRAWELEMENTVISITOR_H__

#include "MPI_ElementVisitor.h"

class MPI_ParticleStroke;

// FIXME FIXME FIXME turn this back into a subclass of MPI_ElementConstVisitor
class MPI_DrawElementVisitor : public MPI_ElementVisitor
{

  public:

    MPI_DrawElementVisitor( MPI_ParticleStroke const& particlestroke );

    void visitOneSpaceElement( MPI_OneSpaceElement& element );
    void visitIntersectionElement( MPI_IntersectionElement& element );
    void visitPoweredElement( MPI_PoweredElement& element );
    void visitTrainElement( MPI_TrainElement& element );

  private:

    void drawElement( MPI_OneSpaceElement const& element ) const;

    MPI_ParticleStroke const& particlestroke_;

};

#endif

// vim:sw=4:et:cindent:
