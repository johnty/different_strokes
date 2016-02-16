
//
// MPI_GUICallbacks.h
//
// Description:
//   A class which contains the global GUI callbacks.  Not meant
//   to be instantiated -- just being used as a namespace.
//

#ifndef __MPI_GUICALLBACKS_H__
#define __MPI_GUICALLBACKS_H__

class MPI_GUICallbacks
{

  public:

    static void displayCallback( void );
    static void reshapeCallback( int w, int h );
    static void idleCallback( void );
    static void mouseCallback( int button, int state, int x, int y );
    static void motionCallback( int x, int y );
    static void keyboardCallback( unsigned char key, int x, int y );

  private:

    MPI_GUICallbacks();
    ~MPI_GUICallbacks();

};

#endif

// vim:sw=4:et:cindent:
