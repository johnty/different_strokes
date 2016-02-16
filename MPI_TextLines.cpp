
//
// MPI_TextLines.cpp
//

#include "MPI_TextLines.h"

#include <string>
#include <fstream>

MPI_TextLines::MPI_TextLines( std::string const filename ) :
    openok_( false )
{

    std::ifstream inputfile( filename.c_str() );
    openok_ = inputfile.is_open();

    if ( openok_ ) {

        std::string fileline;
        while( std::getline( inputfile, fileline ) ) {
            filelines_.push_back( fileline );
        }

        inputfile.close();

    }

}

MPI_TextLines::~MPI_TextLines()
{
    // empty
}

bool MPI_TextLines::openOk( void ) const
{
    return openok_;
}

std::list<std::string> const& MPI_TextLines::getFileLines( void ) const
{
    return filelines_;
}

void MPI_TextLines::trimWhitespace( std::string &string ) const
{
    // empty
    // FIXME fill this method in and use it when reading lines
}

// vim:sw=4:et:cindent:
