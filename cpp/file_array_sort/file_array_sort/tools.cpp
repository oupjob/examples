#include "tools.h"

//InputFileGenerator::InputFileGenerator()
//{

//}

#include <limits>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

size_t parseSizeT( const std::string& s ) {
    size_t size;
    istringstream is( s );
    is >> size;
    return size;
}

std::string sizeTToStr( size_t n ) {
    ostringstream os;
    os << n;
    return os.str();
}

size_t calculateChunkSizeInBytes( size_t file_size ) {
    if ( file_size < MIN_CHUNK_SIZE * 2 )
        return 0;

    if ( file_size > MB_TO_BYTES( 2048 ) )
        return 1;

    if ( file_size < MAX_CHUNK_SIZE * 2 )
        return MIN_CHUNK_SIZE;
    else
        return MAX_CHUNK_SIZE;
}

uint generateInputFile( const std::string &out_file_name, size_t file_size ) {
    std::ofstream of;
    if ( ! file_size % CELL_SIZE ) {
        cout << E_NON_REPETITIVE_FILE_SIZE( sizeTToStr( CELL_SIZE ) ) << endl;
        return EC_NON_REPETITIVE_FILE_SIZE;
    }

    try {
        of.open( out_file_name );
    } catch (std::ios_base::failure& e) {
        cerr << e.what() << endl;
        return EC_OPEN_FILE;
    }

    double lower_bound = std::numeric_limits<double>::min();
    double upper_bound = std::numeric_limits<double>::max();

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::default_random_engine re;

    cout << "Start generating input file: " << out_file_name
         << ", size: " << file_size << " bytes." << endl;

    do {
        of << unif( re ) << endl;
    } while( of.tellp() < file_size - 20 );


    cout << "Generating completed. File: " << out_file_name
         << ", generated size: " << of.tellp() << " bytes." << endl;

    of.close();
    return EC_OK;
}

uint checkFileSize( const std::string& file_name ) {
    std::ifstream ifs;
    try {
       ifs.open( file_name, ios_base::in | ios_base::ate );
       size_t size = ifs.tellg();
       return size;
    } catch (std::ios_base::failure& e) {
        cerr << e.what() << endl;
        return 0;
    }
    return 0;
}

uint checkFileIsSorted( const std::string& file_name ) {
    std::ifstream ifs;
    try {
        ifs.open( file_name );
    } catch (std::ios_base::failure& e) {
        cerr << e.what() << endl;
        return 0;
    }

    double d_prev, d_cur;
    ifs >> d_prev;
    while ( ifs ) {
        ifs >> d_cur;
        if ( d_cur < d_prev )
            return EC_NOT_SORTED;
        d_prev = d_cur;
    }

    return EC_OK;
}

uint checkChunksInFileIsSorted( const std::string& file_name, size_t chunk_size ) {
    std::ifstream ifs;
    try {
        ifs.open( file_name );
    } catch (std::ios_base::failure& e) {
        cerr << e.what() << endl;
        return EC_OPEN_FILE;
    }

    double d_prev, d_cur;
    size_t n = chunk_size / CELL_SIZE, i;
    while( ifs ) {
        ifs >> d_prev;
        i = CELL_SIZE;
        while( i < n ) {
            ifs >> d_cur;
            if ( d_cur > d_prev )
                return EC_NOT_SORTED;
            d_prev = d_cur;
        }
    }

    return EC_OK;
}
