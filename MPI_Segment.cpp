
//
// MPI_Segment.cpp
//

#include "MPI_Segment.h"

#include "MPI_IsctWithSegmentVisitor.h"

MPI_Segment::MPI_Segment( MPI_Workspace &workspace, MPI_IntersectionPolyLine &intersectionpolyline, MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint ) :
    workspace_( workspace ),
    intersectionpolyline_( intersectionpolyline ),
    firstpoint_( firstpoint ),
    secondpoint_( secondpoint ),
    boundingbox_( firstpoint_, secondpoint_ )
{
    // empty
}

MPI_Workspace& MPI_Segment::getWorkspace( void ) const
{
    return workspace_;
}

MPI_IntersectionPolyLine& MPI_Segment::getIntersectionPolyLine( void ) const
{
    return intersectionpolyline_;
}

MPI_BoundingBox const& MPI_Segment::getBoundingBox( void ) const
{
    return boundingbox_;
}

void MPI_Segment::acceptVisitor( MPI_SegmentVisitor const& visitor )
{
    visitor.visitSegment( *this );
}

MPI_SegmentIntersectionVisitor* MPI_Segment::allocateIntersectionVisitor( void )
{
    return new MPI_IsctWithSegmentVisitor( *this );
}

bool MPI_Segment::findIntersection( MPI_Segment const &otherseg, float &thisisctpoint, float &otherisctpoint ) const
{

    // find the intersection point between this segment and another return true
    // if there is an intersection, false if there isn't the points of
    // intersection are returned in the float reference arguments
    // (thisisctpoint, otherisctpoint).  They are normalized with respect to
    // the length of the segment.

    // if the bounding boxes don't overlap, the segments won't either.  bail.
    if ( !boundingbox_.overlaps( otherseg.boundingbox_ ) )
        return false;

    // get the delta x and y for each segment, and then compute the
    // determiniant to see if they're parallel.  if they are parallel, they
    // can't intersect, so bail.  (we're ignoring the case where the two
    // segments are coincident.)
    float thissegdeltax = secondpoint_.getX() - firstpoint_.getX();
    float thissegdeltay = secondpoint_.getY() - firstpoint_.getY();
    float othersegdeltax = otherseg.secondpoint_.getX() - otherseg.firstpoint_.getX();
    float othersegdeltay = otherseg.secondpoint_.getY() - otherseg.firstpoint_.getY();
    // FIXME I had to comment out this expression and use the equivalent one
    // below because it wouldn't work when optimization was turned on (-O) (the
    // expression should have been equal to 0.0, but it wasn't returning true.)
    // I figured this out by diffing the non-optimized and optimized code
    // (compile with -S, filter with c++filt3).  You can see where the function
    // calls are, and match up the assembly code with the c++ code.  The
    // optimized version was trying to avoid the subtraction, and just compare
    // the two products.  The optimized version works when I do this
    // optimization explicitly by hand, as I did below.  I was able to test out
    // different things by just removing the MPI_Segment object file and
    // recompiling just that with different options.
//  if ( thissegdeltax*othersegdeltay - othersegdeltax*thissegdeltay == 0.0 )
    if ( thissegdeltax*othersegdeltay == othersegdeltax*thissegdeltay )
        return false;

    // we perform a change of basis so that this segment is aligned with the x
    // axis, and the other segment is aligned with the y axis.
    // the matrix that does this transformation is the inverse of
    //   [ thissegdeltax othersegdeltax ]
    //   [ thissegdeltay othersegdeltay ]
    // (which is the transformation from the standard basis to one with axes
    // aligned with the line segments).  The 1/(ad-bc) factor is omitted in
    // the inverse since it doesn't have a bearing on the rest of the
    // computation.
    // The inverse is known to exist since we've already checked above that the
    // matrix's determinant is nonzero.
    // So the matrix we're using is:
    //   [  othersegdeltay -othersegdeltax ]
    //   [ -thissegdeltay   thissegdeltax  ]

    // transform the segments according to this matrix.  do the matrix
    // multiplication by hand since we don't have a nice library to do it at
    // the moment.  We treat points as column vectors:
    //   [ x ]
    //   [ y ]
    // talfirstpt == this aligned segment first point
    // oalfirstpt == other aligned segment first point
    MPI_Point2D talfirstpt(
            firstpoint_.getX()*othersegdeltay + firstpoint_.getY()*(-othersegdeltax),
            firstpoint_.getX()*(-thissegdeltay) + firstpoint_.getY()*thissegdeltax
        );
    MPI_Point2D talsecondpt(
            secondpoint_.getX()*othersegdeltay + secondpoint_.getY()*(-othersegdeltax),
            secondpoint_.getX()*(-thissegdeltay) + secondpoint_.getY()*thissegdeltax
        );
    MPI_Point2D oalfirstpt(
            otherseg.firstpoint_.getX()*othersegdeltay + otherseg.firstpoint_.getY()*(-othersegdeltax),
            otherseg.firstpoint_.getX()*(-thissegdeltay) + otherseg.firstpoint_.getY()*thissegdeltax
        );
    MPI_Point2D oalsecondpt(
            otherseg.secondpoint_.getX()*othersegdeltay + otherseg.secondpoint_.getY()*(-othersegdeltax),
            otherseg.secondpoint_.getX()*(-thissegdeltay) + otherseg.secondpoint_.getY()*thissegdeltax
        );

    // so now we have two segments corresponding to our initial ones that are
    // aligned with the x,y axes.  The first segment ("this aligned segment")
    // is made of the points talfirstpt, talsecondpt; the second segment
    // ("other aligned segment") is made of the points oalfirstpt, oalsecondpt.
    //
    // Now it's easy to test if the two segments intersect.
    // tal is aligned with the x axis, and oal is aligned with the y axis
    // so we have talfirstpt.y == talsecondpt.y
    // and we have oalsecondpt.x == oalsecondpt.x
    //
    // the two segments intersect if:
    // oalfirstpt.x is on (talfirstpt.x,talsecondpt.x( and
    // talfirstpt.y is on (oalfirstpt.y,oalsecondpt.y(
    if ( ((talfirstpt.getX()<=oalfirstpt.getX() && oalfirstpt.getX()<talsecondpt.getX()) ||
          (talsecondpt.getX()<oalfirstpt.getX() && oalfirstpt.getX()<=talfirstpt.getX()))
         &&
         ((oalfirstpt.getY()<=talfirstpt.getY() && talfirstpt.getY()<oalsecondpt.getY()) ||
          (oalsecondpt.getY()<talfirstpt.getY() && talfirstpt.getY()<=oalfirstpt.getY()))
       )
    {

        // compute the intersection point for each segment and return true to
        // indicate that there was an intersection.
        thisisctpoint = (oalfirstpt.getX()-talfirstpt.getX()) / (talsecondpt.getX()-talfirstpt.getX());
        otherisctpoint = (talfirstpt.getY()-oalfirstpt.getY()) / (oalsecondpt.getY()-oalfirstpt.getY());
        return true;

    }

    // if we reach this point, we haven't found an intersection.  return false.
    return false;

    // FIXME do this stuff with matrix operations -- it might be cleaner.

}

// vim:sw=4:et:cindent:
