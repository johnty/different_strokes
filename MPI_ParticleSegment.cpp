
//
// MPI_ParticleSegment.cpp
//

#include "MPI_ParticleSegment.h"

#include "MPI_IsctWithParticleSegmentVisitor.h"
#include "MPI_IntersectionElement.h"

MPI_ParticleSegment::MPI_ParticleSegment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint, MPI_OneSpace &onespace, float const firstposition, float const secondposition, MPI_ElementFactory const& elementfactory ) :
    MPI_Segment( workspace, intersectionpolyline, firstpoint, secondpoint ),
    onespace_( onespace ),
    firstposition_( firstposition ),
    secondposition_( secondposition ),
    elementfactory_( elementfactory )
{
    // empty
}

void MPI_ParticleSegment::acceptVisitor( MPI_SegmentVisitor const& visitor )
{
    visitor.visitParticleSegment( *this );
}

MPI_SegmentIntersectionVisitor* MPI_ParticleSegment::allocateIntersectionVisitor( void )
{
    return new MPI_IsctWithParticleSegmentVisitor( *this );
}

void MPI_ParticleSegment::addParticleSegIntersection( MPI_ParticleSegment &otherseg, float thissegpos, float othersegpos )
{

    // Add an intersection between this segment and otherseg at the parameter
    // positions thissegpos and othersegpos.
    // The intersection and parameter positions are assumed to be valid.
    // The parameter positions are assumed to be given in local segment
    // coordinates (0.0,1.0) as is returned by findIntersection().

    // All we need to do is create an intersection pair linking the two
    // onespaces that underlie the two particle segments.
    // The static method createIntersectionPair() does this work for us.

    // convert between local segment coordinates (0.0,1.0) to onespace
    // coordinates using linear interpolation.
    float thisonespacepos = thissegpos * (secondposition_ - firstposition_) + firstposition_;
    float otheronespacepos = othersegpos * (otherseg.secondposition_ - otherseg.firstposition_) + otherseg.firstposition_;

    // create the intersection pair linking the two onespaces
    MPI_IntersectionElement::createIntersectionPair( onespace_, elementfactory_, thisonespacepos, otherseg.onespace_, otherseg.elementfactory_, otheronespacepos );

}

// vim:sw=4:et:cindent:
