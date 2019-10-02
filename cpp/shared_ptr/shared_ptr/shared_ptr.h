//#ifndef SHARED_PTR_H
//#define SHARED_PTR_H

//#include <memory>

//typedef unsigned int uint;

//template <
//    typename T,
//    typename ptr_t,
//    typename ref_t
//> class shared_ptr
//{
//private:
//    ptr_t   ptr_;
//    uint*   count_;

//public:
//    shared_ptr() : ptr_( 0 ), count_( 0 ) {}

////    shared_ptr( const shared_ptr<T>& src ) {
////        info_ = shared_ptr_table::getInfoByPtr( src.getPtr() );
////    }

//    shared_ptr( ptr_t ptr ) {
//        if ( ptr_ ) {
//            --( *count_ );
//            ptr_ = ptr;
//        } else {
//            ptr     = new T;
//            count   = new uint( 1 );
//        }
//        ptr_ = ptr;
//    }

//    shared_ptr( const shared_ptr<T>& src ) {

//    }

//    ~shared_ptr() {
//        if ( !info_ ) return;
//        info_->count--;
//        if ( !info_->count ) {
//            delete static_cast<ptr_t>( info_->ptr );
//            shared_ptr_table::table_.erase( *info_ );
//        }
//    }

//    ref_t operator *  () { return *( info_->ptr ); }
//    ref_t operator -> () { return info_->ptr; }
//    ref_t getRef()       { return *( info_->ptr ); }
//    ptr_t getPtr()       { return info_->ptr;  }

//    uint useCount() { return info_->count; }
//    operator bool() { return info_->ptr; }
//};

//#endif // SHARED_PTR_H
