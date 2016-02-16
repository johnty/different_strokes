
//
// MPI_TimeFloat.cpp
//

#include "MPI_TimeFloat.h"

#include "MPI_Scheduler.h"

MPI_TimeFloat::MPI_TimeFloat( float value, MPI_Scheduler const &scheduler ) :
    value_( value ),
    scheduler_( scheduler )
{
    time_ = scheduler_.getTime();
}

MPI_TimeFloat::MPI_TimeFloat( float value, double time, MPI_Scheduler const &scheduler ) :
    value_( value ),
    time_( time ),
    scheduler_( scheduler )
{
    // empty
}

float MPI_TimeFloat::getValue( void ) const
{
    return value_;
}

double MPI_TimeFloat::getTime( void ) const
{
    return time_;
}

float MPI_TimeFloat::getAge( void ) const
{
    return scheduler_.getTime() - time_;
}

// vim:sw=4:et:cindent:
