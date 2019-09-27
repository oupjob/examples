#include <algorithm>
#include <iomanip>
#include <cmath>
#include <sstream>

#include "primarybigfilesort.h"
#include "error_messages.h"


PrimaryBigFileSort::PrimaryBigFileSort(
    const std::string&  in_file_name,
    const std::string&  out_file_name,
    size_t              chunk_size_in_bytes
)
    :
      in_file_name_( in_file_name ),
      out_file_name_( out_file_name ),
      chunk_size_in_bytes_( chunk_size_in_bytes )
{
    try {
        in_fstream_.open( in_file_name_, ios_base::in | ios_base::ate );
        in_file_size_ = in_fstream_.tellg();
        in_fstream_.seekg( 0, in_fstream_.beg );
    } catch ( std::ios_base::failure& e ) {
        cerr << e.what() << endl;
        return;
    }
}

PrimaryBigFileSort::~PrimaryBigFileSort() {
    in_fstream_.close();
    out_fstream_.close();
}

uint PrimaryBigFileSort::loadChunk( uint i ) {
    uint chunk_size = chunk_size_in_bytes_;
    uint i_chunk = i * chunk_size;

    if ( i_chunk >= in_file_size_ )
        return eInvalidChunk;

    clearDataArray();
    int n =  chunk_size / CELL_SIZE;
    data_.reserve( n );

    double d;
    in_fstream_.seekg( i_chunk, in_fstream_.beg );
    for( uint k = 0; k < n; ++k ) {
        in_fstream_ >> d;
        data_.push_back( d );
        if ( !in_fstream_ )
            break;
    }

    cout << " Loaded chunk: index=" << i
         << ", offset = " << setw( OUT_COL_WIDTH ) << i_chunk
         << ", size  = " << setw( OUT_COL_WIDTH ) << chunk_size << " bytes.\n";

    return eOk;
}

uint PrimaryBigFileSort::writeChunk( uint i ) {
    std::string file_name = chunkFileName( i );

    try {
        out_fstream_.open( file_name, ios_base::binary );
    } catch (std::ios_base::failure& e) {
        cerr << e.what() << endl;
        return E_OPEN_FILE;
    }

    int n = 0;
    for( DataArray::iterator it = data_.begin(); it != data_.end(); ++it, ++n ) {
        out_fstream_ << *it << endl;
    }

    cout << " " << n << " numbers written to output temp file: "
         << file_name << ", "
         << out_fstream_.tellp()
         << " bytes written, chunk_index = " << i_chunk << endl;

    out_fstream_.close();
}

std::string PrimaryBigFileSort::chunkFileName( uint i ) {
    std::string file_name;
    std::ostringstream os( file_name );
    os << out_file_name_ << "_" << i << ".chunk";
    return file_name;
}

uint PrimaryBigFileSort::chunkCount() {
    return std::ceil( ( (double)in_file_size_ ) / chunk_size_in_bytes_ );
}

uint PrimaryBigFileSort::sort() {
    uint chunk_count = chunkCount();
    uint err;
    cout << "Start primary sorting: " << endl
         << " Input file size:  " << setw( OUT_COL_WIDTH ) << in_file_size_ << " bytes\n"
         << " Chunk size:       " << setw( OUT_COL_WIDTH ) << MB_TO_BYTES( chunk_size_in_bytes_ ) << " bytes\n"
         << " Chunk count:      " << setw( 6 ) << chunk_count << endl << endl;

    for( int i_chunk = 0; i_chunk < chunk_count; ++i_chunk ) {
        err = loadChunk( i_chunk );

        if ( err & eInvalidChunk ) {
            cout << endl << E_INVALID_CHUNK_IDX << ": " << i_chunk << endl;
            return eInvalidChunk;
        }

        std::sort( data_.begin(), data_.end() );

        writeChunk( i_chunk );
    }

    cout << "Primary sorting completed.\n";
    return EC_OK;
}

#undef OUT_COL_WIDTH
