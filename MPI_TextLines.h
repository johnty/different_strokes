
//
// MPI_TextLines.h
//
// Description:
//   Read a text file and make its lines available
//

#ifndef __MPI_TEXTLINES_H__
#define __MPI_TEXTLINES_H__

#include <list>

class MPI_TextLines
{

  public:

    MPI_TextLines( std::string const filename );
    ~MPI_TextLines();

    bool openOk( void ) const;

    std::list<std::string> const& getFileLines( void ) const;

  private:

    void trimWhitespace( std::string &string ) const;

    bool openok_;
    std::list<std::string> filelines_;

};

#endif

// vim:sw=4:et:cindent:
