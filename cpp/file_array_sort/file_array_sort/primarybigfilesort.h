#ifndef PRIMARYBIGFILESORT_H
#define PRIMARYBIGFILESORT_H

#include <string>
#include <fstream>
#include <iosfwd>
#include <vector>
#include <iostream>
#include "tools.h"

//#define MAX_CHUNK_SIZE_MB MB_TO_BYTES( 50 )

using namespace std;

class PrimaryBigFileSort
{
public:
    PrimaryBigFileSort(
        const std::string&  in_file_name,
        const std::string&  out_file_name,
        size_t              chunk_size_in_bytes = MAX_CHUNK_SIZE
    );
    ~PrimaryBigFileSort();

    enum Error {
        eOk,
        eInvalidChunk
    };

private:
    std::string             in_file_name_;
    std::string             out_file_name_;

    ifstream                in_fstream_;
    ofstream                out_fstream_;

    size_t                  chunk_size_in_bytes_;
    size_t                  in_file_size_;

    DataArray               data_;

public:
    uint                    sort();
    size_t                  inputFileSize() { return in_file_size_; }
    inline void             clearDataArray() { data_.clear(); data_.shrink_to_fit(); }

private:
    uint                    loadChunk( uint i );
    uint                    writeChunk( uint i );
    std::sting              chunkFileName( uint i );
    uint                    chunkCount();
};

#endif // PRIMARYBIGFILESORT_H
