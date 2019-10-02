#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include <set>
#include <memory>

typedef unsigned int uint;

struct SharedPtrInfo {
    void*   ptr;
    uint    count;

//    ~SharedPtrInfo() {
//        delete ptr;
//    }
};

struct SharedPtrInfoLess {
    bool operator () ( const SharedPtrInfo& a, const SharedPtrInfo& b ) {
        return a.ptr < b.ptr;
    }
};
template <
    typename T,
    typename PtrT       = T*,
    typename RefT       = T&
> class SharedPtr;

class SharedPtrTable {
//    friend class SharedPtr;
public:
    template <
        typename T,
        typename PtrT,
        typename RefT
    > friend class SharedPtr;
    typedef std::set<SharedPtrInfo, SharedPtrInfoLess> Table;
private:
    static Table            table_;

    static SharedPtrInfo*   getInfoByPtr( void* ptr );
    static SharedPtrInfo*   insertInfoByPtr( void* ptr );
public:
    static Table::iterator  begin() { return table_.begin(); }
    static Table::iterator  end()   { return table_.end(); }
    static const Table&     table() { return table_; }

};

template <
    typename T,
    typename PtrT,
    typename RefT
> class SharedPtr
{
private:
    SharedPtrInfo*  info_;
    inline void releaseIfNeed() {
        if ( info_ && !( info_->count ) ) {
            delete static_cast<PtrT>( info_->ptr );
            SharedPtrTable::table_.erase( *info_ );
        }
    }

    inline void increaseRefCount() { if( info_) info_->count++; }
    inline void decreaseRefCount() {
        if( info_ ) info_->count--;
        releaseIfNeed();
    }

public:
    SharedPtr() : info_( 0 ) {}

//    SharedPtr( const SharedPtr<T>& src ) {
//        info_ = SharedPtrTable::getInfoByPtr( src.getPtr() );
//    }

    SharedPtr( PtrT ptr ) {
        SharedPtrInfo* info = SharedPtrTable::getInfoByPtr( ptr );
        if ( info ) {
            info_->count += ( info_ == info ) ? 1: -1;
            releaseIfNeed();
            info_ = info;
        } else {
            info_ = SharedPtrTable::insertInfoByPtr( ptr );
        }
    }

    SharedPtr( const  SharedPtr<T, PtrT, RefT>& src ) {
        info_ = src.info_;
        increaseRefCount();
    }

    ~SharedPtr() {
        if ( !info_ ) return;
        decreaseRefCount();
    }


    SharedPtr<T, PtrT, RefT>& operator = ( PtrT ptr ) {
        if ( !ptr ) {
            decreaseRefCount();
            info_ = 0;
            return *this;
        }
        if ( !info_ ) {
            info_ = SharedPtrTable::insertInfoByPtr( ptr );
            return *this;
        }

        if ( info_->ptr != ptr ) {
            decreaseRefCount();
            info_ = SharedPtrTable::insertInfoByPtr( ptr );
        } else {
            info_ = SharedPtrTable::getInfoByPtr( ptr );
            increaseRefCount();
        }

        return *this;
    }

    SharedPtr<T, PtrT, RefT>&
    operator = ( const  SharedPtr<T, PtrT, RefT>& src ) {
        if ( !src.info_ ) {
            decreaseRefCount();
            info_ = 0;
        } else if ( info_ != src.info_ ) {
            decreaseRefCount();
            info_ = src.info_;
            increaseRefCount();
        }

        return *this;
    }

    RefT operator *  () { return *( info_->ptr ); }
    PtrT operator -> () { return info_->ptr; }
    RefT getRef()       { return static_cast<RefT>( *( info_->ptr ) ); }
    PtrT getPtr()       { return static_cast<PtrT>( info_->ptr );  }
    SharedPtrInfo* getInfo() { return info_; }

    uint useCount() { return info_->count; }
    operator bool() { return info_->ptr; }
};

#endif // SHAREDPTR_H
