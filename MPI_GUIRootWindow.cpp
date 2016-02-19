
//
// MPI_GUIRootWindow.cpp
//

#include "MPI_GUIRootWindow.h"

#include "MPI_GUICallbacks.h"
#include "MPI_Scheduler.h"
#include "MPI_Workspace.h"
#include "MPI_DrawPolyLineVisitor.h"

#include <GLUT/glut.h>

MPI_GUIRootWindow::EventNewPolyLine::EventNewPolyLine( MPI_Workspace* workspace ) :
    workspace_(workspace)
{
    // empty
}

void MPI_GUIRootWindow::EventNewPolyLine::execute( void )
{
    workspace_->beginPolyLine();
}

MPI_GUIRootWindow::EventAppendPolyLinePoint::EventAppendPolyLinePoint( MPI_Workspace* workspace, MPI_Point2D const& point ) :
    workspace_(workspace),
    point_(point)
{
    // empty
}

void MPI_GUIRootWindow::EventAppendPolyLinePoint::execute( void )
{
    workspace_->appendPolyLinePoint( point_ );
}

MPI_GUIRootWindow::EventEndPolyLine::EventEndPolyLine( MPI_Workspace* workspace ) :
    workspace_(workspace)
{
    // empty
}

void MPI_GUIRootWindow::EventEndPolyLine::execute( void )
{
    workspace_->endPolyLine();
}

MPI_GUIRootWindow::MPI_GUIRootWindow( MPI_Workspace &workspace, MPI_Scheduler &scheduler ) :
    workspace_(workspace),
    scheduler_(scheduler)
{

    // do the application / window type stuff
    // set up glut, create the window, etc

    // initialise the window size and pixelsPerWorldUnit
    // FIXME hardcoded!
    windowWidth = 500;
    windowHeight = 500;
    pixelsPerWorldUnit = 500.0 / 2.0; // initial window has sides of size 2

    // initialise the graphics and create the window
    initialiseGLUT();
    createWindow();
    registerCallbacks();
    initialiseOpenGL();

}

void MPI_GUIRootWindow::start( void )
{

    // bring the scheduler up to the current time
    scheduler_.dispatchEventsUpToTime( getRealTime() );

    // freak out
    glutMainLoop();

}

void MPI_GUIRootWindow::displayCallback( void ) const
{

    static MPI_DrawPolyLineVisitor drawvisitor;

    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // offer the draw visitor to each of the polylines
    workspace_.visitPolyLines( drawvisitor );

    // swap buffers -- need GLUT_DOUBLE drawing mode
    glutSwapBuffers();

}

void MPI_GUIRootWindow::reshapeCallback( int w, int h )
{

    // update the viewport and the world window with the new dimensions
    // for now, we're fixing the relationship between screen space and world
    // space here.  screen space / world space / world view should all be
    // separated out.

    windowWidth = w;
    windowHeight = h;

    // convert screen coords to world coords
    MPI_Point2D lowerleft = screenToWorldCoords(MPI_Point2D(0,h));
    MPI_Point2D upperright = screenToWorldCoords(MPI_Point2D(w,0));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( lowerleft.getX(), upperright.getX(), lowerleft.getY(),
            upperright.getY());
    glMatrixMode(GL_MODELVIEW);

    // set the viewport to be the whole window
    glViewport(0, 0, windowWidth, windowHeight);

}

void MPI_GUIRootWindow::idleCallback( void ) const
{

    // bring the scheduler logical time up to the current time.
    scheduler_.dispatchEventsUpToTime( getRealTime() );

    // update the state of all of the polylines
    workspace_.updateState();

    // draw the current state of the system
    // FIXME maybe don't redraw if there hasn't been an update?
    glutPostRedisplay();

    // FIXME clear this up -- the application doesn't take all of the cpu,
    // anyway, when audio is running.  check the cpu with/without this sleep,
    // with/without audio.
    // sleep so we don't eat up all of the cpu
    // sleep for ten milliseconds
    usleep(10000);
    // FIXME how will this affect the audio callback?  test with a really long
    // sleep.  ->  doesn't have any effect on the callback, just on this
    // thread!
    // FIXME should we vary the sleep value depending on the current time?
    // less sleeping the more work we do per time slice.

}

void MPI_GUIRootWindow::mouseCallback( int button, int state, int x, int y ) const
{

    // These should be scheduled at the current real time, not the
    // current logical time!  if two points are appended between idle
    // callbacks, it'll look like they got appended at exactly the same time,
    // and it'll produce an infinite drawing speed in the polyline stroke.

    double currenttime = getRealTime();

    if ( state == GLUT_DOWN && button == GLUT_LEFT_BUTTON )
    {
        // create a new polyline
        // convert the point to world coordinates and add it to the polyline
        MPI_Point2D worldpt = screenToWorldCoords( MPI_Point2D(x,y) );
        scheduler_.scheduleEventAbs( new EventNewPolyLine( &workspace_ ), currenttime );
        scheduler_.scheduleEventAbs( new EventAppendPolyLinePoint( &workspace_, worldpt ), currenttime );
    }
    else if ( state == GLUT_UP && button == GLUT_LEFT_BUTTON )
        scheduler_.scheduleEventAbs( new EventEndPolyLine( &workspace_ ), currenttime );

}

void MPI_GUIRootWindow::motionCallback( int x, int y ) const
{

    // These should be scheduled at the current real time, not the
    // current logical time!  if two points are appended between idle
    // callbacks, it'll look like they got appended at exactly the same time,
    // and it'll produce an infinite drawing speed in the polyline stroke.

    // convert the point to world coordinates and add it to the polyline
    MPI_Point2D worldpt = screenToWorldCoords( MPI_Point2D(x,y) );
    scheduler_.scheduleEventAbs( new EventAppendPolyLinePoint( &workspace_, worldpt ), getRealTime() );

}

MPI_Point2D MPI_GUIRootWindow::screenToWorldCoords( MPI_Point2D const& point ) const
{

    // the origin of the screen coords is in the upper left, y is down

    // translate the point so the origin is at screen 0,0
    // flip y
    // scale it so it ends up in world coordinates

    float worldptx = (point.getX() - windowWidth/2.0) / pixelsPerWorldUnit;
    float worldpty = -(point.getY() - windowHeight/2.0) / pixelsPerWorldUnit;
    return MPI_Point2D(worldptx, worldpty);

}

MPI_Point2D MPI_GUIRootWindow::worldToScreenCoords( MPI_Point2D const& point ) const
{

    // scale it so it ends up in screen coordinates with origin at centre
    // flip y
    // translate origin so it's at upper left of screen window

    float screenptx = (point.getX() * pixelsPerWorldUnit) + windowWidth/2.0;
    float screenpty = -(point.getY() * pixelsPerWorldUnit) + windowHeight/2.0;
    return MPI_Point2D(screenptx, screenpty);

}

double MPI_GUIRootWindow::getRealTime( void ) const
{
    // FIXME should this return the time in milliseconds since the program was
    // started?

    // this is adapted from audicle_gfx.cpp, AudicleWindow::get_current_time()
    static struct timeval t; // static to avoid continuous reallocation
    gettimeofday( &t, NULL );
    return t.tv_sec + (double) t.tv_usec/1000000;

}

void MPI_GUIRootWindow::initialiseOpenGL( void ) const
{

    // FIXME this stuff is hardcoded here...  should encapsulate graphics
    // (opengl/glut) and the drawing style (color scheme, etc.)

    // set clear colour to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // set fill colour to white
    glColor3f(1.0, 1.0, 1.0);

    // set up standard orthogonal clipping
    // these are actually the default values
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

}

void MPI_GUIRootWindow::initialiseGLUT( void ) const
{
    // FIXME we're bypassing arguments to glut here...
    int argc = 0;
    char **argv = NULL;

    glutInit(&argc, argv); // should this be here?  in main?
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
}

void MPI_GUIRootWindow::registerCallbacks( void ) const
{
    glutDisplayFunc(MPI_GUICallbacks::displayCallback);
    glutReshapeFunc(MPI_GUICallbacks::reshapeCallback);
    glutMouseFunc(MPI_GUICallbacks::mouseCallback);
    glutMotionFunc(MPI_GUICallbacks::motionCallback);
    glutIdleFunc(MPI_GUICallbacks::idleCallback);
    glutKeyboardFunc(MPI_GUICallbacks::keyboardCallback);
}

void MPI_GUIRootWindow::createWindow( void ) const
{
#if 0
    glutInitWindowSize(windowWidth, windowHeight);
    // FIXME hardcoded pos, name here
    glutInitWindowPosition(0, 0);
    glutCreateWindow("ds");
glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
#else

    // see http://www.nullterminator.net/glut.html
    glutEnterGameMode();

    // see http://www.opengl.org/resources/libraries/glut/glut-3.spec.pdf
    // see man 3 glutSetCursor as well
    // FIXME can't figure out where to call this -- it gets clobbered at some point
    // works if you cross the window boundary
    // if you start the window with the cursor in the middle of it, it flashes to the new shape and then back to the normal cursor
    // maybe it has something to do with the way that the osx implements glut
    // maybe it warps the cursor off the window and then teleports it back on,
    // not letting it dectect when it's crossed the boundary
    // the glutSetCursor() call sticks if you do it right after the glut window is created
    // is it possible to make our own cursor?  it might be best if it was a
    // really small dot or something.  you do need some kind of positional
    // feedback, though.
    // you can make your own cursor, too, that follows the mouse position and
    // animates or whatever in an arbitrary way.
    glutSetCursor(GLUT_CURSOR_DESTROY);

#endif
}

// vim:sw=4:et:cindent:
