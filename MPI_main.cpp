
//
// MPI_main.cpp
//
// Description:
//   main file
//

// TODO
//  - make a local todo database
//  - determine what you want the application to be called
//  - build up testing classes for each class, and run tests once in a while
//  - make a debugging message class, too, for adding debugging
//    - have a static flag to turn it on and off
//    - have different categories
//    - can use a macro to remove the calls altogether for the production
//      version of the code.
//  d make sure files are only included when they're needed
//    n implementation cpp files contain the includes they need
//    n h files contain the only includes they need
//  - figure out if you can import just one thing from std (std::list)
//    - using std::list; works,  but do you want to do it globally?
//    - doesn't work just inside the MPI_PolyLine class.
//    - is it just because it's a template?
//    - what if you used a typedef?  would that fix it?
//      - typedef blabla std::list<MPI_Point2D>
//      - do it inside MPI_PolyLine class to keep it in the namespace
//    - maybe have a segment iterator that you can return here, too.  do that
//      later, though...
//  - is there a better c++ equivalent than #include <cassert>?  can I do my
//    own?
//  - create a class that encapsulates the spatial view of the surface: between
//    the eye transformation and the projection
//    - does that make sense, though, since we're using an orthographic
//      projection?  moving the eye up and down won't matter...
//  - figure out how to get the guiworkspace to draw using the contents of the
//    workspace without having to downcast them to guipolylines.  sign of a bad
//    design...
//    - downcasting is a sign of a bad design!  shouldn't have to do this!  in
//      the python version, the redraw method was only called locally, and all
//      it did was update the corresponding data structure in tk.  tk took care
//      of the drawing itself.  the subclasses had the same interface as the
//      base classes...
//  - work out the dividing line between the MPI_GUIRootWindow and the
//    MPI_GUIWorkspace classes.
//    - the workspace shouldn't be a singleton and shouldn't know about other
//      workspaces
//    - the MPI_GUIWorkspace is a sepcialisation of the MPI_Workspace class
//    - MPI_GUIRootWindow needs to be a singleton so it can have the static
//      methods to register with glut.
//    - but should MPI_GUIWorkspace know about glut?  (It does -- swap buffers)
//    - could conceivably have just the lightweight MPI_GUIRootWindow wrapper
//      around the MPI_GUIWorkspace, and have the MPI_GUIWorkspace deal with
//      everything (or almost everything).
//  - figure out how to get glutMainLoop to return
//    - does it do it under linux?
//  d fix it so you don't have to declare all of the members of the root window
//    static.  Just have one singleton that holds all of the data members as
//    appropriate.  accessor methods would be static as appropriate.  the
//    callbacks would have to be global+static as well; would it make sense to
//    put these in a separate namespace for global callbacks?
//  - obviate the MPI_GUIPolyLine by using a visitor on a regular MPI_PolyLine
//    for drawing.  You pass in a callback (glVertex()), and it'll do it for
//    each point in turn.
//  - the gui workspace, for now, just has an initialisation method and a
//    display callback.  drawing could also be implemented using a visitor:
//    visit each of the polylines in the workspace with a second visitor that
//    draws each of the points...
//  d fix up the root window singleton; do it like audio singleton
//    - dynamic allocation, return reference
//    - figure out how to handle singleton destruction -- see Alexandrescu,
//      "modern c++ design"
//  - go through all the code and make sure it's const correct
//  d separate the application from the root window -- application should own
//    the root window
//    d application can instantiate the MPI_Audio object to start up the output
//  d use forward class declarations instead of full includes when you don't
//    need a full include -- it'll save in compilation time
//  - create a clock singleton for the program
//    - actually, don't make this global -- you only want objects to refer to
//      the current logical time
//  d make some notes about reducing the number of singletons -- just a
//    singleton application class?  if you have one root node that handles
//    everything, then you won't have to make all of these classes singletons
//  - implement drawing with visitors instead of subclassing
//  - implement an abstract factory for creating strokes
//  - implement a state for keeping track of the current type of stroke and for
//    creating the right ones when it's time to
//  - implement an audio subclass of the stroke which allocates a single voice
//    and drives it appropriately.  should be transparent from the simulation
//    part
//  - fix up all of the asterisks (*) so they go with the var name and not the
//    type
//  - try to minimise the references to MPI_Application.  If an object needs to
//    see a global object, try to pass it into the constructor or have some
//    other local way to reference it.  Keeps the direct dependencies under
//    control.
//  - change the names to go from general to specific: MPI_DrawPolyLineVisitor
//    should be MPI_GUIVisitorPolyLineDraw; MPI_StrokeBasicAudio, etc
//  - separate the audio bus that synths register themselves with and which
//    mixes their output from the code that deals with RtAudio.
//  - think about whether all workspaces should have a scheduler reference
//  - removed unused reverse iterators?
//  - think about making a general purpose subset iterator: pass in beginning,
//    end; have a reverse version as well (shouldn't just call it
//    MPI_PlaybackIterator)

#include "MPI_Application.h"

int main(int argc, char* argv[])
{
    // instantiate the application and start it up
    MPI_Application::getInstance().start();
}

// vim:sw=4:et:cindent:
