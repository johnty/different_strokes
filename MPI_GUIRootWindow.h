
//
// MPI_GUIRootWindow.h
//
// Description:
//   This is the root application window.  It deals with window manager issues,
//   and contains the workspace.
//   There is only one root window and one workspace for the application.
//

#ifndef __MPI_GUIROOTWINDOW_H__
#define __MPI_GUIROOTWINDOW_H__

#include "MPI_Point2D.h"
#include "MPI_Event.h"
#include <sys/time.h>

class MPI_Scheduler;
class MPI_Workspace;

class MPI_GUIRootWindow
{

  private:
    // FIXME these events should be in the workspace, since they should be
    // callable even without the gui.
    class EventNewPolyLine : public MPI_Event {
      public:
        virtual void execute( void );
        EventNewPolyLine( MPI_Workspace* guiworkspace );
      private:
        MPI_Workspace* workspace_;
    };

    class EventAppendPolyLinePoint : public MPI_Event {
      public:
        EventAppendPolyLinePoint( MPI_Workspace* guiworkspace, MPI_Point2D const& point );
        virtual void execute( void );
      private:
        MPI_Workspace* workspace_;
        MPI_Point2D point_;
    };

    class EventEndPolyLine : public MPI_Event {
      public:
        EventEndPolyLine( MPI_Workspace* guiworkspace );
        virtual void execute( void );
      private:
        MPI_Workspace* workspace_;
    };

  public:

    MPI_GUIRootWindow( MPI_Workspace &workspace, MPI_Scheduler &scheduler );

    void start( void );

    // FIXME these methods are allowed to be const since they're not changing
    // anything in the MPI_GUIRootWindow class, but they're changing the
    // contents of the MPI_Scheduler instance.  Does that make sense?
    // Shouldn't it not allow modification of the scheduler?
    // Maybe it's because it's calling static methods, and static methods
    // aren't allowed to be const...
    void displayCallback( void ) const;
    void reshapeCallback( int w, int h );
    void idleCallback( void ) const;
    void mouseCallback( int button, int state, int x, int y ) const;
    void motionCallback( int x, int y ) const;

  private:

    MPI_Point2D screenToWorldCoords( MPI_Point2D const& point ) const;
    MPI_Point2D worldToScreenCoords( MPI_Point2D const& point ) const;

    double getRealTime( void ) const;

    void initialiseOpenGL( void ) const;
    void initialiseGLUT( void ) const;
    void registerCallbacks( void ) const;
    void createWindow( void ) const;

    MPI_Workspace &workspace_;
    MPI_Scheduler &scheduler_;

    int windowWidth;
    int windowHeight;
    float pixelsPerWorldUnit;

};

#endif

// vim:sw=4:et:cindent:
