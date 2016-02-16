
//
// MPI_ParticleStroke.h
//
// Description:
//   A stroke which manages particles embedded in it
//

#ifndef __MPI_PARTICLESTROKE_H__
#define __MPI_PARTICLESTROKE_H__

#include "MPI_OneSpaceIsctPolyLine.h"
#include "MPI_ParticleSpace.h"
#include "MPI_CanonicalTimeArclengthMap.h"
#include <deque>

class MPI_Scheduler;
class MPI_TrainElementFactory;

class MPI_ParticleStroke : public MPI_OneSpaceIsctPolyLine
{

  public:

    MPI_ParticleStroke( MPI_Workspace &workspace, MPI_Scheduler &scheduler );
    virtual ~MPI_ParticleStroke();

    virtual void appendPoint( MPI_Point2D const &point );
    virtual void end( void );

    virtual void updateState( void );

    virtual MPI_OneSpace& getOneSpace( void );
    virtual MPI_OneSpace const& getOneSpace( void ) const;
    MPI_Point2D linearPositionToPoint( float position ) const;

    virtual MPI_PointListIterator* allocatePointListIterator( void ) const;

    virtual void acceptVisitor( MPI_PolyLineVisitor const& visitor );

  protected:

    virtual MPI_Segment* allocateSegment( MPI_Point2D const &firstpoint, MPI_Point2D const &secondpoint );
    virtual MPI_Point2D const* getLastPoint( void ) const;
    int getNumPoints( void ) const;
    MPI_CanonicalTimeArclengthMap const& getCanonicalTimeArclengthMap( void ) const;

    virtual void allocatePointAndAddToList( MPI_Point2D const &point );

  private:

    MPI_TrainElementFactory& getTrainElementFactory( void );
    void removeOneSpaceElements( float position );

    std::deque<MPI_PolyLinePoint*> pointList_;
    // do *not* access particlespace_ directly; use getOneSpace()
    MPI_ParticleSpace particlespace_;
    MPI_Scheduler &scheduler_;
    MPI_CanonicalTimeArclengthMap canonicaltimearclengthmap_;
    // do *not* access trainelementfactory_ directly; use getTrainElementFactory()
    MPI_TrainElementFactory *trainelementfactory_;
    MPI_OneSpaceElement *headelement_;
    MPI_Point2D previouspoint_;

};

#endif

// vim:sw=4:et:cindent:
