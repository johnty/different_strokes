
//
// MPI_PolyLineFactory.h
//
// Description:
//   Abstract base class for polyline factories
//

#ifndef __MPI_POLYLINEFACTORY_H__
#define __MPI_POLYLINEFACTORY_H__

class MPI_PolyLine;

class MPI_PolyLineFactory
{

  public:

    virtual ~MPI_PolyLineFactory() {};

    virtual MPI_PolyLine* createPolyLine( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
