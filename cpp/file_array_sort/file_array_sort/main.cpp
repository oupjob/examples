#include <iostream>
#include <sstream>
#include <cstring>


#include "tools.h"
#include "error_messages.h"
#include "primarybigfilesort.h"
#include "secondarybigfilesort.h"

using namespace std;

#define ARG_PARSE( expected_key, received_key )\
if ( ! strncmp( expected_key, received_key, sizeof( expected_key ) ) )

#define CHECK_ARGV_INDEX( index, err_message, err_code ) \
if ( index >= argc ) { \
    cout << err_message; \
    return err_code; \
}

int main( int argc, char** argv ) {
    int i = 0;
    if ( argc  == 1 ) {
        cout << USAGE;
        return 0;
    }

    while( i < argc ) {
        ARG_PARSE( "-g", argv[ i ] ) {
            CHECK_ARGV_INDEX( i + 2, E_ARG_VALUE_EXPECTED( "-g" ), EC_ARG_VALUE_EXPECTED )

            size_t n_bytes;
            istringstream in( argv[ i + 2 ] );
            in >> n_bytes;
            n_bytes = MB_TO_BYTES( n_bytes );
            if ( ! in ) {
                cout << E_ARG_VALUE_EXPECTED( "-g" );
                return EC_ARG_VALUE_EXPECTED;
            }

            return generateInputFile( argv[ i + 1 ], n_bytes );
        } else ARG_PARSE( "-c", argv[ i ] ) {
            CHECK_ARGV_INDEX( i + 1, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
            ARG_PARSE( "size", argv[ i + 1 ] ) {
                CHECK_ARGV_INDEX( i + 2, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
                std::string file_name( argv[ i + 2 ] );

                CHECK_ARGV_INDEX( i + 3, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
                size_t in_size = parseSizeT( argv[ i + 2 ] ),
                       size = checkFileSize( file_name );

                cout << "Checked file size: " << ( MB_TO_BYTES( size ) ) << " MB ("
                     << size << " bytes)" << endl;
                if ( in_size ) {
                    cout << " " << ( size == in_size ? ": Matched" : ": Not matched" ) << endl;
                    return size == in_size ? EC_OK : EC_SIZES_NOT_MATCH;
                }
            }
            else ARG_PARSE( "chunks", argv[ i + 1 ] ) {
                CHECK_ARGV_INDEX( i + 2, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
                std::string file_name( argv[ i + 2 ] );

                CHECK_ARGV_INDEX( i + 3, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
                size_t chunk_size = parseSizeT( argv[ i + 3 ] );
                cout << "Start checking chunks for sorting\n";
                uint result = checkChunksInFileIsSorted( file_name, BYTES_TO_MB( chunk_size ) );

                std::string s_res = ( ( result == EC_OK ) ? "OK" : "Failed" );
                cout << "Checked chunks of size: " << chunk_size << " MB ("
                     << MB_TO_BYTES( chunk_size ) << " bytes), "
                     << "Result: " << s_res << endl;

                return result;
            }
            else ARG_PARSE( "sort", argv[ i + 1 ] ) {
                CHECK_ARGV_INDEX( i + 2, E_ARG_VALUE_EXPECTED( "-c" ), EC_ARG_VALUE_EXPECTED )
                uint result = checkFileIsSorted( argv[ i + 2 ] );
                if ( result == EC_OK ) {
                    cout << "File is sorted" << endl;
                    return EC_OK;
                } else {
                    cout << "File is not sorted" << endl;
                    return EC_NOT_SORTED;
                }
            } else {
                cout << "Invalid -c suboption" << endl;
                return EC_INVALID_SUBOPTION;
            }
        }
        else ARG_PARSE( "-s", argv[ i ] ) {
            CHECK_ARGV_INDEX( i + 3, E_ARG_VALUE_EXPECTED( "-s" ), EC_ARG_VALUE_EXPECTED )
            uint res;
            size_t chunk_sz_in_mbytes;
            istringstream in( argv[ i + 3 ] );
            in >> chunk_sz_in_mbytes;

            if ( !in ) {
                cout << E_ARG_VALUE_EXPECTED( "-s" );
                return EC_ARG_VALUE_EXPECTED;
            }

            // primary sort chunks
            PrimaryBigFileSort primary_sort(
                argv[ i + 1 ],
                argv[ i + 2 ],
                MB_TO_BYTES( chunk_sz_in_mbytes )
            );
            res = primary_sort.sort();
            primary_sort.clearDataArray();

            if ( res != EC_OK )
                 return EC_FAILED_PRIMARY_SORT;

            std::string answer;
            while( answer != "y" ) {
                cout << "File sorted by chunks (primary sort), continue to secondary sort (y\\n) ? ";
                cin >> answer;
                if ( answer == "n" )
                    return EC_OK;
            }
            cout << endl;

            SecondaryBigFileSort secondary_sort(
                argv[ i + 2 ],
                MB_TO_BYTES( chunk_sz_in_mbytes )
            );
            res = secondary_sort.sort();
            if ( res != EC_OK )
                return EC_FAILED_SECONDARY_SORT;
        }
        else ARG_PARSE( "-h", argv[ i ] ) {
            cout << USAGE;
            return 0;
        }
        ++i;
    }

    return 0;
}
