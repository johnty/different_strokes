
//
// MPI_DrawPolyLineVisitor.cpp
//

#include "MPI_DrawPolyLineVisitor.h"

#include "MPI_BoundingBox.h"
#include "MPI_PolyLinePoint.h"
#include "MPI_PointListIterator.h"
#include "MPI_IteratorPtr.h"
#include "MPI_BasicStroke.h"
#include "MPI_ElementIterator.h"
#include "MPI_DrawElementVisitor.h"
#include "MPI_OneSpaceElement.h"
#include "MPI_RemovalStroke.h"
#include "MPI_PlayheadStroke.h"

#include <GL/gl.h>
#include <math.h>

void MPI_DrawPolyLineVisitor::visitPolyLine( MPI_PolyLine& polyline ) const
{
    glColor3f( 1.0, 1.0, 1.0 );
    drawPolyLine( polyline );
}

void MPI_DrawPolyLineVisitor::visitBasicStroke( MPI_BasicStroke& polyline ) const
{
    visitPolyLine( polyline );
}

void MPI_DrawPolyLineVisitor::visitParticleStroke( MPI_ParticleStroke& polyline ) const
{

    glColor3f( 0.0, 0.0, 0.8 );
    drawPolyLine( polyline );

    // draw the elements on the polyline
    MPI_IteratorPtr<MPI_ElementIterator> elementitr( polyline.getOneSpace().allocateElementIterator() );
    MPI_DrawElementVisitor drawelementvisitor( polyline );
    for ( elementitr->first(); !elementitr->isDone(); elementitr->next() )
        elementitr->getElement()->acceptVisitor( drawelementvisitor );

}

void MPI_DrawPolyLineVisitor::visitRemovalStroke( MPI_RemovalStroke& polyline ) const
{
    // empty
}

void MPI_DrawPolyLineVisitor::visitPlayheadStroke( MPI_PlayheadStroke& polyline ) const
{

    // map from the length of the sample to a hue on (0.0,1.0) by wrapping
    // it around every modvalue seconds and normalizing.
    float modvalue = 3.0;
    float hue = fmod( polyline.getLength(), modvalue );
    hue /= modvalue;

    // get the colour in RGB from the hue
    static float reda = 0.0;
    static float greena = 0.0;
    static float bluea = 0.0;
    getRGBFromHSV( hue, 1.0, 0.5, reda, greena, bluea );

    // set the colour and draw the polyline
    glColor3f( reda, greena, bluea );
    drawPolyLine( polyline );

    // draw the elements on the polyline
    MPI_IteratorPtr<MPI_ElementIterator> elementitr( polyline.getOneSpace().allocateElementIterator() );
    MPI_DrawElementVisitor drawelementvisitor( polyline );
    for ( elementitr->first(); !elementitr->isDone(); elementitr->next() )
        elementitr->getElement()->acceptVisitor( drawelementvisitor );

}

void MPI_DrawPolyLineVisitor::drawPolyLine( MPI_PolyLine& polyline ) const
{

    // draw the stroke points as a line
    // draws in the current opengl colour

    MPI_IteratorPtr<MPI_PointListIterator> pt( polyline.allocatePointListIterator() );
    glLineWidth( 4.0 );
    glBegin( GL_LINE_STRIP );
    for ( pt->first(); !pt->isDone(); pt->next() )
        glVertex2f( pt->getPoint()->getX(), pt->getPoint()->getY() );
    glEnd();

}

void MPI_DrawPolyLineVisitor::getRGBFromHSV( float hue, float saturation, float value, float &red, float &green, float &blue ) const
{

    // Set the OpenGL colour from the hue setting
    // hue, saturation, value on [0.0,1.0]
    // the equations for this are from
    //   http://en.wikipedia.org/wiki/HSV_color_space
    // FIXME make a colour class that does interpolation and can convert back
    // and forth between hsv and rgb

    // transform hue to be on [0.0,6.0] and get integer and fractional parts
    float hueintpart = floor( hue*6.0 );
    float huefracpart = fmod( hue*6.0, 1.0 );

    float p = value * ( 1.0 - saturation );
    float q = value * ( 1.0 - huefracpart * saturation );
    float t = value * ( 1.0 - ( 1.0 - huefracpart ) * saturation );

    // determine the final rgb colour from p,q,t and the initial hue
    if ( hueintpart == 0.0 ) {
        red = value; green = t; blue = p;
    }
    else if ( hueintpart == 1.0 ) {
        red = q; green = value; blue = p;
    }
    else if ( hueintpart == 2.0 ) {
        red = p; green = value; blue = t;
    }
    else if ( hueintpart == 3.0 ) {
        red =p ; green = q; blue = value;
    }
    else if ( hueintpart == 4.0 ) {
        red = t; green = p; blue = value;
    }
    else if ( hueintpart == 5.0 ) {
        red = value; green = p; blue = q;
    }

}

// vim:sw=4:et:cindent:
