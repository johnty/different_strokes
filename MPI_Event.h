
//
// MPI_Event.h
//
// Description:
//   Encapsulates an event -- a message that will get passed to a particular
//   instance of an object.  This is the "command" pattern from the GoF book.
//   This is an abstract base class -- it needs to be subclassed for each
//   particular message.
//

#ifndef __MPI_EVENT_H__
#define __MPI_EVENT_H__

class MPI_Event
{

  public:

    virtual ~MPI_Event() {};

    virtual void execute( void ) = 0;

  protected:

    MPI_Event() {};

};

#endif

// vim:sw=4:et:cindent:
