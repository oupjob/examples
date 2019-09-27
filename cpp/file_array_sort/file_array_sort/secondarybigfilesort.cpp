#include "secondarybigfilesort.h"

#include <algorithm>
#include <iterator>
#include <cmath>
#include <iomanip>

#define RESERVE_MEM \
data1_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE ); \
data2_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE ); \
sorted_data_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE );

#define CLEAR_ARRAYS \
data1_.clear(); \
data2_.clear(); \
sorted_data_.clear();

SecondaryBigFileSort::SecondaryBigFileSort(
    const std::string&      file_name,
    size_t                  chunk_size_in_bytes
)
    : file_name_( file_name ), chunk_size_in_bytes_( chunk_size_in_bytes )
{
//    data1_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE );
//    data2_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE );
//    sorted_data_.reserve( MB_TO_BYTES( chunk_size_mb ) / CELL_SIZE );
    try {
        io_fstream_.open( file_name, ios_base::in | ios_base::out | ios_base::ate );
        file_size_ = io_fstream_.tellg();
        io_fstream_.seekg( 0, io_fstream_.beg );
    } catch ( std::ios_base::failure& e ) {
        cerr << e.what() << endl;
        return;
    }
}

SecondaryBigFileSort::~SecondaryBigFileSort() {
    io_fstream_.close();
}

void SecondaryBigFileSort::clearDataArrays() {
    data1_.clear();
    data1_.shrink_to_fit();
    data2_.clear();
    data2_.shrink_to_fit();
    sorted_data_.clear();
    sorted_data_.shrink_to_fit();
}

uint SecondaryBigFileSort::loadChunk( uint i, DataArray& data ) {
    uint chunk_size = MB_TO_BYTES( chunk_size_in_bytes_ );
    fstream::off_type i_chunk = i * chunk_size;

    if ( !data.capacity() )
        data.reserve( MB_TO_BYTES( chunk_size_in_bytes_ ) );
    else
        data.clear();

    io_fstream_.seekg( i_chunk, ios_base::beg );
    uint arr_size = chunk_size / CELL_SIZE;
    double d;
    for( uint k = 0; k < arr_size; ++k ) {
        io_fstream_ >> d;
        data.push_back( d );

        if ( !io_fstream_ ) {
            cout << " Loaded chunk: index=" << i
                 << ", offset = " << setw( OUT_COL_WIDTH ) << i_chunk
                 << ", size  = " << setw( OUT_COL_WIDTH ) << k << " bytes.\n";

            return EC_UNEXPECTED_EOF;
        }
    }
    cout << " Loaded chunk: index=" << i
         << ", offset = " << setw( OUT_COL_WIDTH ) << i_chunk
         << ", size  = " << setw( OUT_COL_WIDTH ) << chunk_size << " bytes.\n";

    return EC_OK;
}

uint SecondaryBigFileSort::writeChunk( uint i, uint begin, uint end ) {
    uint chunk_size = MB_TO_BYTES( chunk_size_in_bytes_ );
    fstream::off_type i_chunk = i * chunk_size;

    io_fstream_.seekg( i_chunk, ios_base::beg );
    for( uint k = begin; k <= end; ++k ) {
        io_fstream_ << sorted_data_[ k ];

        if ( !io_fstream_ ) {
            CLEAR_ARRAYS

            cout << " Secondary sort chunk write: "
                 << " i =" << i
                 << ", chunk offset: " << i_chunk
                 << E_WRITE_FILE( file_name_ );
            return EC_WRITE_FILE;
        }
    }

    CLEAR_ARRAYS
    return EC_OK;
}

std::string PrimaryBigFileSort::chunkFileName( uint i ) {
    std::string file_name;
    std::ostringstream os( file_name );
    os << out_file_name_ << "_" << i << ".chunk";
    return file_name;
}

uint SecondaryBigFileSort::chunkCount() const {
    return std::ceil( ( (double)file_size_ ) / MB_TO_BYTES( chunk_size_in_bytes_ ) );
}

uint SecondaryBigFileSort::sort() {
    uint chunk_count = chunkCount(),
         d1_size = chunk_size_in_bytes_ / CELL_SIZE,
         d2_size = chunk_size_in_bytes_ / CELL_SIZE;

    cout << endl << endl
         << "Start secondary sorting: " << endl
         << " Input file size:  " << setw( OUT_COL_WIDTH ) << file_size_ << " bytes\n"
         << " Chunk size:       " << setw( OUT_COL_WIDTH ) << MB_TO_BYTES( chunk_size_in_bytes_ ) << " bytes\n"
         << " Chunk count:      " << setw( 6 ) << chunk_count << endl << endl;

    for( uint i = 0; i < chunk_count - 1; ++i ) {
        uint ec_lc = loadChunk( i, data1_ );
        if ( ec_lc != EC_OK )
            return ec_lc;

        for( uint j = i + 1; j < chunk_count; ++j ) {
            ec_lc = loadChunk( j, data2_ );
            if ( ec_lc == EC_UNEXPECTED_EOF )
                d2_size = data2_.size();

            std::merge(
                data1_.begin(), data1_.end(),
                data2_.begin(), data2_.end(),
                std::back_inserter( sorted_data_ )
            );

            writeChunk( j, d1_size, d1_size + d2_size - 1 );
        }
        writeChunk( i, 0, d1_size - 1 );
    }
}


