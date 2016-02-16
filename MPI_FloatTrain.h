
//
// MPI_FloatTrain.h
//
// Description:
//   Holds a list of floats with associated times.
//

#ifndef __MPI_FLOATTRAIN_H__
#define __MPI_FLOATTRAIN_H__

#include "MPI_TimeFloat.h"
#include <list>

class MPI_FloatTrainConstIterator;
class MPI_Scheduler;

class MPI_FloatTrain
{

  public:

    MPI_FloatTrain( MPI_Scheduler const &scheduler );

    void addItem( float value );
    MPI_FloatTrainConstIterator* allocateFloatTrainConstIterator( void ) const;
    void removeOldItems( float age );

  private:

    std::list<MPI_TimeFloat> train_;
    MPI_Scheduler const &scheduler_;

    class TimeFloatBefore
    {
      public:
        bool operator()( MPI_TimeFloat const& a, MPI_TimeFloat const& b ) const;
    };

};

#endif

// vim:sw=4:et:cindent:
