#include "sharedptr.h"

extern SharedPtrTable::Table SharedPtrTable::table_;

SharedPtrInfo* SharedPtrTable::getInfoByPtr( void *ptr ) {
    SharedPtrInfo tmp = { ptr, 0 };
    Table::iterator t_it = SharedPtrTable::table_.find( tmp );
    return ( t_it == table_.end() ) ? 0 : const_cast<SharedPtrInfo*>( &( *t_it ) );
}

SharedPtrInfo* SharedPtrTable::insertInfoByPtr( void *ptr ) {
    if ( !ptr )
        return 0;

    SharedPtrInfo* info;
    info = getInfoByPtr( ptr );

    if ( info ) {
        info->count++;
        return info;
    } else {
        std::pair<Table::iterator, bool> ins_res = table_.insert( { ptr, 1 } );
        return const_cast<SharedPtrInfo*>( &( *( ins_res.first ) ) );
    }

    return info;
}
