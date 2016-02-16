
//
// MPI_PoweredElement.h
//
// Description:
//   An element which moves itself through a onespace
//

#ifndef __MPI_POWEREDELEMENT_H__
#define __MPI_POWEREDELEMENT_H__

#include "MPI_OneSpaceElement.h"
#include "MPI_Event.h"

class MPI_OneSpace;
class MPI_Framelist;
class MPI_Scheduler;

class MPI_PoweredElement : public MPI_OneSpaceElement
{

  private:

    class EventMoveElement : public MPI_Event {
      public:
        EventMoveElement( MPI_PoweredElement *poweredelement, float position, MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler );
        void execute( void );
      private:
        MPI_PoweredElement *poweredelement_;
        float position_;
        MPI_OneSpace &onespace_;
        MPI_Framelist const& framelist_;
        MPI_Scheduler &scheduler_;
    };

  public:

    MPI_PoweredElement( MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler );
    ~MPI_PoweredElement();

    void activate( void );

    void setPendingMoveEvent( MPI_Event *pendingmoveevent );

    void acceptVisitor( MPI_ElementVisitor& visitor );
    void acceptConstVisitor( MPI_ElementConstVisitor& visitor ) const;

    // helper method for scheduling an MPI_PoweredElement move.  this is to
    // avoid code duplication -- both MPI_PoweredElement and EventMoveElement
    // use it.  shouldn't be called from outside these classes.
    static void scheduleNextMove( MPI_PoweredElement *poweredelement, float position, MPI_OneSpace &onespace, MPI_Framelist const& framelist, MPI_Scheduler &scheduler );

  private:

    MPI_OneSpace &onespace_;
    MPI_Framelist const& framelist_;
    MPI_Scheduler &scheduler_;
    MPI_Event *pendingmoveevent_;

};

#endif

// vim:sw=4:et:cindent:
