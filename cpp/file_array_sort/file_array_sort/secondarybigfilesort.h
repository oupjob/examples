#ifndef SECONDARYFILESORTING_H
#define SECONDARYFILESORTING_H

#include <string>
#include <iostream>
#include <fstream>

#include "tools.h"

using namespace std;

class SecondaryBigFileSort
{
public:
    SecondaryBigFileSort( const std::string& file_name, size_t chunk_size_in_bytes );
    ~SecondaryBigFileSort();

    enum Error {
        eOk,
        eInvalidChunk
    };

private:
    string          file_name_;
    fstream         io_fstream_;

    size_t          chunk_size_in_bytes_;
    size_t          file_size_;

    DataArray       data1_;
    DataArray       data2_;
    DataArray       sorted_data_;

public:
    uint            sort();
    inline void     clearDataArrays();

private:
    uint            loadChunk( uint i, DataArray& data );
    uint            writeChunk( uint i, uint begin, uint end );

    uint            chunkCount() const;
};

#endif // SECONDARYFILESORTING_H
