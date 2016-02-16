
//
// MPI_TimeFloat.h
//
// Description:
//   A float which can report the time elapsed since its instantiation
//

#ifndef __MPI_TIMEFLOAT_H__
#define __MPI_TIMEFLOAT_H__

class MPI_Scheduler;

class MPI_TimeFloat
{

  public:

    MPI_TimeFloat( float value, MPI_Scheduler const &scheduler );
    MPI_TimeFloat( float value, double time, MPI_Scheduler const &scheduler );

    float getValue( void ) const;
    double getTime( void ) const;
    float getAge( void ) const;

  private:

    float value_;
    double time_;
    MPI_Scheduler const &scheduler_;

};

#endif

// vim:sw=4:et:cindent:
