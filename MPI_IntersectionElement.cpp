
//
// MPI_IntersectionElement.cpp
//

#include "MPI_IntersectionElement.h"

#include "MPI_OneSpace.h"
#include "MPI_ElementFactory.h"
#include "MPI_ElementVisitor.h"
#include "MPI_ElementConstVisitor.h"

MPI_IntersectionElement::MPI_IntersectionElement( MPI_OneSpace &onespace, MPI_ElementFactory const& elementfactory ) :
    onespace_( onespace ),
    elementfactory_( elementfactory ),
    otherintersection_( NULL )
{
    // empty
}

MPI_IntersectionElement::~MPI_IntersectionElement()
{

    // remove the corresponding intersection if it exists
    if ( otherintersection_ != NULL ) {
        otherintersection_->setOtherIntersection( NULL );
        otherintersection_->onespace_.removeElement( otherintersection_ );
    }

}

void MPI_IntersectionElement::setOtherIntersection( MPI_IntersectionElement *intersection )
{
    otherintersection_ = intersection;
}

MPI_IntersectionElement* MPI_IntersectionElement::getOtherIntersection( void ) const
{
    return otherintersection_;
}

void MPI_IntersectionElement::spawnElement( void ) const
{
    // create an element and add it to our onespace at our location
    onespace_.addElement( elementfactory_.createElement(),
            onespace_.getElementPosition(this) );
}

void MPI_IntersectionElement::acceptVisitor( MPI_ElementVisitor& visitor )
{
    visitor.visitIntersectionElement( *this );
}

void MPI_IntersectionElement::acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const
{
    visitor.visitIntersectionElement( *this );
}

void MPI_IntersectionElement::createIntersectionPair( MPI_OneSpace &onespaceone, MPI_ElementFactory const& elementfactoryone, float positionone, MPI_OneSpace &onespacetwo, MPI_ElementFactory const& elementfactorytwo, float positiontwo )
{

    MPI_IntersectionElement *intersectionone = new MPI_IntersectionElement( onespaceone, elementfactoryone );
    MPI_IntersectionElement *intersectiontwo = new MPI_IntersectionElement( onespacetwo, elementfactorytwo );
    intersectionone->setOtherIntersection( intersectiontwo );
    intersectiontwo->setOtherIntersection( intersectionone );
    onespaceone.addElement( intersectionone, positionone );
    onespacetwo.addElement( intersectiontwo, positiontwo );

}

// vim:sw=4:et:cindent:
