
//
// MPI_FloatTrainConstIterator.h
//
// Description:
//   Iterator for the MPI_FloatTrain object
//

#ifndef __MPI_FLOATTRAINCONSTITERATOR_H__
#define __MPI_FLOATTRAINCONSTITERATOR_H__

#include "MPI_Iterator.h"
#include <list>

class MPI_TimeFloat;

class MPI_FloatTrainConstIterator : public MPI_Iterator
{

  public:

    MPI_FloatTrainConstIterator( std::list<MPI_TimeFloat> const& timefloatlist );

    void first( void );
    void next( void );
    bool isDone( void ) const;
    MPI_TimeFloat const& getTimeFloat( void ) const;

  private:

    std::list<MPI_TimeFloat> const& timefloatlist_;
    std::list<MPI_TimeFloat>::const_iterator iterator_;

};

#endif

// vim:sw=4:et:cindent:
