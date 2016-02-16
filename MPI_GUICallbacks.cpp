
//
// MPI_GUICallbacks.cpp
//

#include "MPI_GUICallbacks.h"

#include "MPI_GUIRootWindow.h"
#include "MPI_ParticleFactory.h"
#include "MPI_Application.h"
#include <stdlib.h>

void MPI_GUICallbacks::displayCallback( void )
{
    MPI_Application::getInstance().getGUIRootWindow().displayCallback();
}

void MPI_GUICallbacks::reshapeCallback( int w, int h )
{
    MPI_Application::getInstance().getGUIRootWindow().reshapeCallback( w, h );
}

void MPI_GUICallbacks::idleCallback( void )
{
    MPI_Application::getInstance().getGUIRootWindow().idleCallback();
}

void MPI_GUICallbacks::mouseCallback( int button, int state, int x, int y )
{
    MPI_Application::getInstance().getGUIRootWindow().mouseCallback( button, state, x, y );
}

void MPI_GUICallbacks::motionCallback( int x, int y )
{
    MPI_Application::getInstance().getGUIRootWindow().motionCallback( x, y );
}

void MPI_GUICallbacks::keyboardCallback( unsigned char key, int x, int y )
{
    // quit the application if you see the q key
    if ( key == 'q' ) {
        MPI_Application::destroyInstance();
        exit(0);
    }
    else if ( key == '0' ) {
        MPI_Application::getInstance().getParticleFactory().setStateParticleStroke();
    }
    else if ( key == '1' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 0 );
    }
    else if ( key == '2' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 1 );
    }
    else if ( key == '3' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 2 );
    }
    else if ( key == '4' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 3 );
    }
    else if ( key == '5' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 4 );
    }
    else if ( key == '6' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 5 );
    }
    else if ( key == '7' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 6 );
    }
    else if ( key == '8' ) {
        MPI_Application::getInstance().getParticleFactory().setStatePlayheadStroke( 7 );
    }
    else if ( key == 'r' || key == 'R' ) {
        MPI_Application::getInstance().getParticleFactory().setStateRemovalStroke();
    }
    // FIXME figure out where this should really go -- there should be a layer
    // between this and the function that has the keyboard mapping.  should be
    // able to change it on the fly (not because I'd want to, but more because
    // it'd keep things modular).
}

MPI_GUICallbacks::MPI_GUICallbacks()
{
    // empty
}

MPI_GUICallbacks::~MPI_GUICallbacks()
{
    // empty
}

// vim:sw=4:et:cindent:
