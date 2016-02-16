
//
// MPI_Application.cpp
//

#include "MPI_Application.h"

#include "MPI_Audio.h"
#include "MPI_Scheduler.h"
#include "MPI_AudioParticleFactory.h"
#include "MPI_Workspace.h"
#include "MPI_GUIRootWindow.h"

MPI_Application* MPI_Application::singletoninstance_ = NULL;

MPI_Application& MPI_Application::getInstance( void )
{
    if ( !singletoninstance_ )
        singletoninstance_ = new MPI_Application;
    return *singletoninstance_;
}

void MPI_Application::destroyInstance( void )
{
    // technically, this shouldn't be allowed, but this singleton needs to be
    // destroyed somehow.
    // FIXME try to find a nicer way to handle this
    delete singletoninstance_;
    singletoninstance_ = NULL;
}

void MPI_Application::start( void ) const
{
    // Start up the application
    // These calls may access MPI_Application::getInstance()
    audio_->start();
    guirootwindow_->start();
    // this hangs here -- guirootwindow_->start() calls
    // glutMainLoop(), which doesn't return.
}

MPI_Audio& MPI_Application::getAudio( void ) const
{
    return *audio_;
}

MPI_GUIRootWindow& MPI_Application::getGUIRootWindow( void ) const
{
    return *guirootwindow_;
}

MPI_ParticleFactory& MPI_Application::getParticleFactory( void ) const
{
    return *factory_;
}

MPI_Application::MPI_Application()
{

    // allocate all of the objects

    // These calls may NOT access MPI_Application::getInstance()!
    // It'll be undefined if they do, and chaos will ensue.

    audio_ = new MPI_Audio;
    scheduler_ = new MPI_Scheduler;

    workspace_ = new MPI_Workspace;
    factory_ = new MPI_AudioParticleFactory( *audio_, *workspace_, *scheduler_ );
    workspace_->setFactory( factory_ );

    factory_->setStateParticleStroke();

    guirootwindow_ = new MPI_GUIRootWindow( *workspace_, *scheduler_ );

}

MPI_Application::~MPI_Application()
{
    // destroy all of the objects in reverse order

    delete guirootwindow_;
    delete workspace_;
    delete factory_;
    delete scheduler_;
    delete audio_;
}

// vim:sw=4:et:cindent:
