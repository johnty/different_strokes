
//
// MPI_ElementFactory.h
//
// Description:
//   Abstract base class for element factories
//

#ifndef __MPI_ELEMENTFACTORY_H__
#define __MPI_ELEMENTFACTORY_H__

class MPI_OneSpaceElement;

class MPI_ElementFactory
{

  public:

    virtual ~MPI_ElementFactory() {}

    virtual MPI_OneSpaceElement* createElement( void ) const = 0;

};

#endif

// vim:sw=4:et:cindent:
