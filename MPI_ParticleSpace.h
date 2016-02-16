
//
// MPI_ParticleSpace.h
//
// Description:
//   A onespace for the particle stroke set.
//

#ifndef __MPI_PARTICLESPACE_H__
#define __MPI_PARTICLESPACE_H__

#include "MPI_OneSpace.h"

class MPI_ParticleSpace : public MPI_OneSpace
{

  public:

    virtual void addElement( MPI_OneSpaceElement *element, float position );

  protected:

    MPI_ElementVisitor* allocateElementVisitor( void ) const;

  private:

    static int unsigned const maxPoweredElements_;

};

#endif

// vim:sw=4:et:cindent:
