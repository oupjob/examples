#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>
#include "error_messages.h"

typedef std::vector<double>     DataArray;
typedef unsigned int            uint;
typedef unsigned long           ulong;

#define MB_TO_BYTES( n ) \
n * 1048576

#define BYTES_TO_MB( n ) \
n / 1048576

#define CELL_SIZE sizeof( double )

#define MAX_CHUNK_SIZE MB_TO_BYTES( 25 )

#define MIN_CHUNK_SIZE 512

#define OUT_COL_WIDTH 12

size_t calculateChunkSizeInBytes( size_t file_size );

uint generateInputFile( const std::string& out_file_name, size_t file_size );
uint checkFileSize( const std::string& file_name );
uint checkFileIsSorted( const std::string& file_name );
uint checkChunksInFileIsSorted( const std::string& file_name, size_t chunk_size );

size_t parseSizeT( const std::string& s );
std::string sizeTToStr( size_t n );

#endif // INPUTFILEGENERATOR_H
