
//
// MPI_OneSpaceElementPos.h
//
// Description:
//   An MPI_OneSpaceElement with an associated postion.  Used in MPI_OneSpace
//   objects to track element positions, and as handles for elements in the
//   space.
//

#ifndef __MPI_ONESPACEELEMENTPOS_H__
#define __MPI_ONESPACEELEMENTPOS_H__

#include <ostream>

class MPI_OneSpaceElement;

class MPI_OneSpaceElementPos
{

  public:

    MPI_OneSpaceElementPos( MPI_OneSpaceElement *element, float position );

    MPI_OneSpaceElement* getElement( void ) const;
    void setElement( MPI_OneSpaceElement *element );

    float getPosition( void ) const;
    void setPosition( float position );

    bool operator==( MPI_OneSpaceElementPos const& elementpos ) const;

    void print( std::ostream &os ) const;

  private:

    MPI_OneSpaceElement *element_;
    float position_;

};

std::ostream &operator<<( std::ostream &os, MPI_OneSpaceElementPos const &elementpos );

#endif

// vim:sw=4:et:cindent:
