#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

#define EC_OK 0

#define USAGE \
"\nfile_array_sort -- sorting big files.\n" \
"OPTIONS:\n" \
"-g file_name n -- generate array of `n` bytes size into `file_name`\n"\
"-s in_file_name out_file_name max_chunk_mb \n"\
"  sort array stored in `in_file_name` and write result to `out_file_name`" \
"  use max chunk size specified in `max_chunk_mb`\n" \
"-c sort|chunks|size file_name [size in MB] -- check input\output file\n" \
"  -c sort file_name -- check result file of secondary sort is sorted.\n" \
"  -c chunks file_name -- check result file of primary sort is sorted.\n" \
"  -c size file_name [size] -- check generated input file size\n" \
"-h -- show this help\n"

#define EC_ARG_VALUE_EXPECTED 129
#define E_ARG_VALUE_EXPECTED( arg_key )\
std::string( arg_key ) + std::string( " : Missing argument value" )

#define E_INVALID_CHUNK_IDX "Invalid chunk index"

#define EC_OPEN_FILE 1
#define EC_READ_FILE 2
#define EC_WRITE_FILE 4

#define E_OPEN_FILE( name ) \
std::string( "Cannot open file: " ) + name;

#define E_READ_FILE( name ) \
std::string( "Cannot read file: " ) + name;

#define E_WRITE_FILE( name ) \
std::string( "Cannot write to file: " ) + name;

#define E_UNEXPECTED_EOF( name ) \
std::string( "Unexpected EOF in file: " ) + name;

#define E_NON_REPETITIVE_FILE_SIZE( str_size ) \
std::string( "File size is not repetitive to double type size = " ) + str_size
#define EC_SIZES_NOT_MATCH 131
#define EC_INVALID_SUBOPTION 132
#define EC_NOT_SORTED 133
#define EC_FAILED_PRIMARY_SORT 134
#define EC_FAILED_SECONDARY_SORT 135
#define EC_NON_REPETITIVE_FILE_SIZE 136
#define EC_UNEXPECTED_EOF 137

#endif // ERROR_MESSAGES_H

