
//
// MPI_DrawPolyLineVisitor.h
//
// Description:
//   Draws the visited polyline using opengl
//

#ifndef __MPI_DRAWPOLYLINEVISITOR_H__
#define __MPI_DRAWPOLYLINEVISITOR_H__

#include "MPI_PolyLineVisitor.h"

class MPI_PolyLine;

class MPI_DrawPolyLineVisitor : public MPI_PolyLineVisitor
{

  public:

    void visitPolyLine( MPI_PolyLine& polyline ) const;

    void visitBasicStroke( MPI_BasicStroke& polyline ) const;
    void visitParticleStroke( MPI_ParticleStroke& polyline ) const;
    void visitRemovalStroke( MPI_RemovalStroke& polyline ) const;
    void visitPlayheadStroke( MPI_PlayheadStroke& polyline ) const;

  private:

    void drawPolyLine( MPI_PolyLine& polyline ) const;

    void getRGBFromHSV( float hue, float saturation, float value, float &red, float &green, float &blue ) const;

};

#endif

// vim:sw=4:et:cindent:
