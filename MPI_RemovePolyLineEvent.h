
//
// MPI_RemovePolyLineEvent.h
//
// Description:
//   Event which can be used to schedule the removal of a polyline
//

#ifndef __MPI_REMOVEPOLYLINEEVENT_H__
#define __MPI_REMOVEPOLYLINEEVENT_H__

#include "MPI_Event.h"

class MPI_Workspace;
class MPI_PolyLine;

class MPI_RemovePolyLineEvent : public MPI_Event
{

  public:

    MPI_RemovePolyLineEvent( MPI_Workspace &workspace, MPI_PolyLine const &polyline );
    void execute( void );

  private:

    MPI_Workspace &workspace_;
    MPI_PolyLine const &polyline_;

};

#endif

// vim:sw=4:et:cindent:
