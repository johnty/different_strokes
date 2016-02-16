
//
// MPI_RemovePolyLineEvent.cpp
//

#include "MPI_RemovePolyLineEvent.h"

#include "MPI_Workspace.h"

MPI_RemovePolyLineEvent::MPI_RemovePolyLineEvent( MPI_Workspace &workspace, MPI_PolyLine const &polyline ) :
    workspace_( workspace ),
    polyline_( polyline )
{
    // empty
}

void MPI_RemovePolyLineEvent::execute( void )
{
    workspace_.removePolyLine( &polyline_ );
}

// vim:sw=4:et:cindent:
