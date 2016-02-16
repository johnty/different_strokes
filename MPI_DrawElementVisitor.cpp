
//
// MPI_DrawElementVisitor.cpp
//

#include "MPI_DrawElementVisitor.h"

#include "MPI_ParticleStroke.h"
#include "MPI_Point2D.h"
#include "MPI_IntersectionElement.h"
#include "MPI_TrainElement.h"
#include "MPI_IteratorPtr.h"
#include "MPI_FloatTrainConstIterator.h"

#include <GL/gl.h>

MPI_DrawElementVisitor::MPI_DrawElementVisitor( MPI_ParticleStroke const& particlestroke ) :
    particlestroke_( particlestroke )
{
    // empty
}

void MPI_DrawElementVisitor::visitOneSpaceElement( MPI_OneSpaceElement& element )
{
    glColor3f( 1.0, 0.0, 0.0 );
    drawElement( element );
}

void MPI_DrawElementVisitor::visitIntersectionElement( MPI_IntersectionElement& element )
{
    // empty
}

void MPI_DrawElementVisitor::visitPoweredElement( MPI_PoweredElement& element )
{
    glColor3f( 0.0, 1.0, 0.0 );
    drawElement( element );
}

void MPI_DrawElementVisitor::visitTrainElement( MPI_TrainElement& element )
{
#if 1
    // draw the tail based on how old it is
    // NB this code assumes the scheduler time units are in seconds!
    static float const maxage = 0.2;

    // append the current point and clear out old items from the particle train
    // managing the float train here causes it to work at the frame rate.
    // FIXME this causes the tail to move off of the stroke when the movement
    // is quick and frames get dropped.
    element.getFloatTrain().addItem( particlestroke_.getOneSpace().getElementPosition( &element ) );
    element.getFloatTrain().removeOldItems( maxage );

    // preallocate variables used in the tail drawing loop
    MPI_Point2D tailpoint( 0.0, 0.0 );
    MPI_IteratorPtr<MPI_FloatTrainConstIterator> curtimefloat( element.getFloatTrain().allocateFloatTrainConstIterator() );
    float drawcolour = 0.0;

    // draw the tail
    glLineWidth( 4.0 );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable( GL_BLEND );
    glBegin( GL_LINE_STRIP );
    for ( curtimefloat->first(); !curtimefloat->isDone(); curtimefloat->next() ) {

        // get the worldspace position
        tailpoint = particlestroke_.linearPositionToPoint( curtimefloat->getTimeFloat().getValue() );

        // compute colour based on the age of the point
        // map 1.0->0.0 onto 0.0->1 sec
        drawcolour = 1.0 - curtimefloat->getTimeFloat().getAge() / maxage;

        // draw the tail point
        glColor4f( 1.0, 1.0, 1.0, drawcolour );
        glVertex2f( tailpoint.getX(), tailpoint.getY() );

    }
    glEnd();
    glDisable( GL_BLEND );

    // the tail drawing loop above draws the current location of the element,
    // so we're done.
#else
visitOneSpaceElement(element);
#endif
}

void MPI_DrawElementVisitor::drawElement( MPI_OneSpaceElement const& element ) const
{

    // draw the element as a point
    // draws in the current opengl colour

    // get the world space position
    float onespaceposition = particlestroke_.getOneSpace().getElementPosition( &element );
    MPI_Point2D elementpoint = particlestroke_.linearPositionToPoint( onespaceposition );

    // draw the element
    glPointSize( 4.0 );
    glBegin( GL_POINTS );
    glVertex2f( elementpoint.getX(), elementpoint.getY() );
    glEnd();

}

// vim:sw=4:et:cindent:
