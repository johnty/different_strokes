
//
// MPI_Application.h
//
// Description:
//   Top level application.  Intialises/frees all of the global
//   program resources in a controlled manner.
//

#ifndef __MPI_APPLICATION_H__
#define __MPI_APPLICATION_H__

class MPI_Audio;
class MPI_Scheduler;
class MPI_ParticleFactory;
class MPI_Workspace;
class MPI_GUIRootWindow;

class MPI_Application
{

  public:

    static MPI_Application& getInstance( void );
    static void destroyInstance( void );

    void start( void ) const;

    MPI_Audio& getAudio( void ) const;
    MPI_GUIRootWindow& getGUIRootWindow( void ) const;
    MPI_ParticleFactory& getParticleFactory( void ) const;

  private:

    MPI_Application();
    ~MPI_Application();
    MPI_Application( MPI_Application& );

    static MPI_Application* singletoninstance_;

    MPI_Audio* audio_;
    MPI_Scheduler *scheduler_;
    MPI_ParticleFactory *factory_;
    MPI_Workspace *workspace_;
    MPI_GUIRootWindow* guirootwindow_;

};

#endif

// vim:sw=4:et:cindent:
