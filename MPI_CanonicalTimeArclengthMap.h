
//
// MPI_CanonicalTimeArclengthMap.h
//
// Description:
//   Map relating canonical coordinates, time, and arclength.
//

#ifndef __MPI_CANONICALTIMEARCLENGTHMAP_H__
#define __MPI_CANONICALTIMEARCLENGTHMAP_H__

#include "MPI_Framelist.h"
#include "MPI_Point2D.h"

class MPI_Scheduler;

class MPI_CanonicalTimeArclengthMap
{

  public:

    MPI_CanonicalTimeArclengthMap( MPI_Scheduler const& scheduler );

    void appendPoint( MPI_Point2D const &point );

    MPI_Framelist const& getFramelist( void ) const;

    bool inCanonicalRange( float canonicalcoord ) const;
    bool inTimeRange( float time ) const;
    bool inTimeRangeOpenEnd( float time ) const;
    bool inArclengthRange( float arclength ) const;

    bool isEmpty( void ) const;

    float getTimeFromCanonical( float canonicalcoord ) const;
    float getArclengthFromCanonical( float canonicalcoord ) const;
    float getCanonicalFromTime( float time ) const;
    float getArclengthFromTime( float time ) const;
    float getCanonicalFromArclength( float arclength ) const;
    float getTimeFromArclength( float arclength ) const;

    float getLastCanonicalCoord( void ) const;
    float getTotalTime( void ) const;
    float getTotalArclength( void ) const;

    float getArclengthVsTimeSlope( float time ) const;
    float getResampledArclengthVsTimeSlope( float time, float samplingperiod ) const;

    void print( std::ostream &os ) const;

  private:

    float computeSlope( MPI_Point2D const& leftpoint, MPI_Point2D const& rightpoint ) const;
    float computeSegmentLength( MPI_Point2D const& leftpoint, MPI_Point2D const& rightpoint ) const;

    MPI_Scheduler const& scheduler_;

    MPI_Framelist framelist_; // canonical -> time map
    MPI_Map canonicalvstime_; // time -> canonical map
    MPI_Map arclengthvscanonical_; // canonical -> arclength map
    MPI_Map canonicalvsarclength_; // arclength -> canonical map

    MPI_Point2D previouspoint_;

};

std::ostream &operator<<( std::ostream &os, MPI_CanonicalTimeArclengthMap const &canonicaltimearclengthmap );

#endif

// vim:sw=4:et:cindent:
