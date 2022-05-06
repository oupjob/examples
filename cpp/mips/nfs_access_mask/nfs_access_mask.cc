// Example program
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <cstring>
#include <type_traits>

using namespace std;

// Приведение численного типа к структуре с битовыми полями
template <class STRUCT_T, typename T>
static STRUCT_T struct_cast(const T n)
{
    static_assert(std::is_integral_v<T>, "Integral type required as T");
    static_assert(std::is_class_v<STRUCT_T>, 
                  "class or struct type required as STRUCT_T");
    static_assert(std::is_trivially_copyable_v<STRUCT_T>, 
                  "Trivially copyable type required as STRUCT_T");
    static_assert(sizeof(T) == sizeof(STRUCT_T), "Incompatible types passed");

    STRUCT_T result;
    memcpy(reinterpret_cast<void*>(&result), reinterpret_cast<const void*>(&n), sizeof(STRUCT_T));

    return result;
}

// Приведение структур с битовыми полями к численному типу
template <typename T, class STRUCT_T>
static T integral_cast(const STRUCT_T& s)
{
    static_assert(std::is_integral_v<T>, "Integral type required as T");
    static_assert(std::is_class_v<STRUCT_T>,
                  "class or struct type required as STRUCT_T");
    static_assert(std::is_trivially_copyable_v<STRUCT_T>,
                  "Trivially copyable type required as STRUCT_T");
    static_assert(sizeof(T) == sizeof(STRUCT_T), "Incompatible types passed");

    T result;
    memcpy(reinterpret_cast<void*>(&result), reinterpret_cast<const void*>(&s), sizeof(T));

    return result;
}

struct attrmask0_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint32_t        supported_attrs:1;      // id: 0  0x00000001
    uint32_t        type:1;                 // id: 1  0x00000002
    uint32_t        fh_expire_type:1;       // id: 2  0x00000004
    uint32_t        change:1;               // id: 3  0x00000008
    uint32_t        size:1;                 // id: 4  0x00000010
    uint32_t        link_support:1;         // id: 5  0x00000020
    uint32_t        symlink_support:1;      // id: 6  0x00000040
    uint32_t        named_attr:1;           // id: 7  0x00000080

    uint32_t        fsid:1;                 // id: 8  0x00000100
    uint32_t        unique_handles:1;       // id: 9  0x00000200
    uint32_t        lease_time:1;           // id: 10 0x00000400
    uint32_t        rdattr_error:1;         // id: 11 0x00000800
    uint32_t        acl:1;                  // id: 12 0x00001000
    uint32_t        aclsupport:1;           // id: 13 0x00002000
    uint32_t        archive:1;              // id: 14 0x00004000
    uint32_t        cansettime:1;           // id: 15 0x00008000

    uint32_t        case_insensitive:1;     // id: 16 0x00010000
    uint32_t        case_preserving:1;      // id: 17 0x00020000
    uint32_t        chown_restricted:1;     // id: 18 0x00040000
    uint32_t        filehandle:1;           // id: 19 0x00080000
    uint32_t        fileid:1;               // id: 20 0x00100000
    uint32_t        files_avail:1;          // id: 21 0x00200000
    uint32_t        files_free:1;           // id: 22 0x00400000
    uint32_t        files_total:1;          // id: 23 0x00800000

    uint32_t        fs_locations:1;         // id: 24 0x01000000
    uint32_t        hidden:1;               // id: 25 0x02000000
    uint32_t        homogeneous:1;          // id: 26 0x04000000
    uint32_t        maxfilesize:1;          // id: 27 0x08000000
    uint32_t        maxlink:1;              // id: 28 0x10000000
    uint32_t        maxname:1;              // id: 29 0x20000000
    uint32_t        maxread:1;              // id: 30 0x40000000
    uint32_t        maxwrite:1;             // id: 31 0x80000000
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint32_t        named_attr:1;           // id: 7  0x00000080
    uint32_t        symlink_support:1;      // id: 6  0x00000040
    uint32_t        link_support:1;         // id: 5  0x00000020
    uint32_t        size:1;                 // id: 4  0x00000010
    uint32_t        change:1;               // id: 3  0x00000008
    uint32_t        fh_expire_type:1;       // id: 2  0x00000004
    uint32_t        type:1;                 // id: 1  0x00000002
    uint32_t        supported_attrs:1;      // id: 0  0x00000001

    uint32_t        cansettime:1;           // id: 15 0x00008000
    uint32_t        archive:1;              // id: 14 0x00004000
    uint32_t        aclsupport:1;           // id: 13 0x00002000
    uint32_t        acl:1;                  // id: 12 0x00001000
    uint32_t        rdattr_error:1;         // id: 11 0x00000800
    uint32_t        lease_time:1;           // id: 10 0x00000400
    uint32_t        unique_handles:1;       // id: 9  0x00000200
    uint32_t        fsid:1;                 // id: 8  0x00000100

    uint32_t        files_total:1;          // id: 23 0x00800000
    uint32_t        files_free:1;           // id: 22 0x00400000
    uint32_t        files_avail:1;          // id: 21 0x00200000
    uint32_t        fileid:1;               // id: 20 0x00100000
    uint32_t        filehandle:1;           // id: 19 0x00080000
    uint32_t        chown_restricted:1;     // id: 18 0x00040000
    uint32_t        case_preserving:1;      // id: 17 0x00020000
    uint32_t        case_insensitive:1;     // id: 16 0x00010000

    uint32_t        maxwrite:1;             // id: 31 0x80000000
    uint32_t        maxread:1;              // id: 30 0x40000000
    uint32_t        maxname:1;              // id: 29 0x20000000
    uint32_t        maxlink:1;              // id: 28 0x10000000
    uint32_t        maxfilesize:1;          // id: 27 0x08000000
    uint32_t        homogeneous:1;          // id: 26 0x04000000
    uint32_t        hidden:1;               // id: 25 0x02000000
    uint32_t        fs_locations:1;         // id: 24 0x01000000
#else
#error "Unspecified host byte order, please fix 'nfsv4.proto'"
#endif
};

struct attrmask1_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint32_t        mimetype:1;             // id: 32 0x00000001
    uint32_t        mode:1;                 // id: 33 0x00000002
    uint32_t        no_trunc:1;             // id: 34 0x00000004
    uint32_t        numlinks:1;             // id: 35 0x00000008
    uint32_t        owner:1;                // id: 36 0x00000010
    uint32_t        owner_group:1;          // id: 37 0x00000020
    uint32_t        quota_avail_hard:1;     // id: 38 0x00000040
    uint32_t        quota_avail_soft:1;     // id: 39 0x00000080

    uint32_t        quota_used:1;           // id: 40 0x00000100
    uint32_t        rawdev:1;               // id: 41 0x00000200
    uint32_t        space_avail:1;          // id: 42 0x00000400
    uint32_t        space_free:1;           // id: 43 0x00000800
    uint32_t        space_total:1;          // id: 44 0x00001000
    uint32_t        space_used:1;           // id: 45 0x00002000
    uint32_t        system:1;               // id: 46 0x00004000
    uint32_t        time_attr:1;          // id: 47 0x00008000

    uint32_t        time_attr_set:1;      // id: 48 0x00010000
    uint32_t        time_backup:1;          // id: 49 0x00020000
    uint32_t        time_create:1;          // id: 50 0x00040000
    uint32_t        time_delta:1;           // id: 51 0x00080000
    uint32_t        time_metadata:1;        // id: 52 0x00100000
    uint32_t        time_modify:1;          // id: 53 0x00200000
    uint32_t        time_modify_set:1;      // id: 54 0x00400000
    uint32_t        mounted_on_fileid:1;    // id: 55 0x00800000

    uint32_t        dir_notif_delay:1;      // id: 56 0x01000000
    uint32_t        dirent_notif_delay:1;   // id: 57 0x02000000
    uint32_t        dacl:1;                 // id: 58 0x04000000
    uint32_t        sacl:1;                 // id: 59 0x08000000
    uint32_t        change_policy:1;        // id: 60 0x10000000
    uint32_t        fs_status:1;            // id: 61 0x20000000
    uint32_t        fs_layout_type:1;       // id: 62 0x40000000
    uint32_t        layout_hint:1;          // id: 63 0x80000000
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint32_t        quota_avail_soft:1;     // id: 39 0x00000080
    uint32_t        quota_avail_hard:1;     // id: 38 0x00000040
    uint32_t        owner_group:1;          // id: 37 0x00000020
    uint32_t        owner:1;                // id: 36 0x00000010
    uint32_t        numlinks:1;             // id: 35 0x00000008
    uint32_t        no_trunc:1;             // id: 34 0x00000004
    uint32_t        mode:1;                 // id: 33 0x00000002
    uint32_t        mimetype:1;             // id: 32 0x00000001

    uint32_t        time_attr:1;          // id: 47 0x00008000
    uint32_t        system:1;               // id: 46 0x00004000
    uint32_t        space_used:1;           // id: 45 0x00002000
    uint32_t        space_total:1;          // id: 44 0x00001000
    uint32_t        space_free:1;           // id: 43 0x00000800
    uint32_t        space_avail:1;          // id: 42 0x00000400
    uint32_t        rawdev:1;               // id: 41 0x00000200
    uint32_t        quota_used:1;           // id: 40 0x00000100

    uint32_t        mounted_on_fileid:1;    // id: 55 0x00800000
    uint32_t        time_modify_set:1;      // id: 54 0x00400000
    uint32_t        time_modify:1;          // id: 53 0x00200000
    uint32_t        time_metadata:1;        // id: 52 0x00100000
    uint32_t        time_delta:1;           // id: 51 0x00080000
    uint32_t        time_create:1;          // id: 50 0x00040000
    uint32_t        time_backup:1;          // id: 49 0x00020000
    uint32_t        time_attr_set:1;      // id: 48 0x00010000

    uint32_t        layout_hint:1;          // id: 63 0x80000000
    uint32_t        fs_layout_type:1;       // id: 62 0x40000000
    uint32_t        fs_status:1;            // id: 61 0x20000000
    uint32_t        change_policy:1;        // id: 60 0x10000000
    uint32_t        sacl:1;                 // id: 59 0x08000000
    uint32_t        dacl:1;                 // id: 58 0x04000000
    uint32_t        dirent_notif_delay:1;   // id: 57 0x02000000
    uint32_t        dir_notif_delay:1;      // id: 56 0x01000000
#else
#error "Unspecified host byte order, please fix 'nfsv4.proto'"
#endif
};

struct attrmask2_t
{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    uint32_t        layout_type:1;          // id: 64 0x00000000
    uint32_t        layout_blksize:1;       // id: 65 0x00000000
    uint32_t        layout_alignment:1;     // id: 66 0x00000000
    uint32_t        fs_locations_info:1;    // id: 67 0x00000000
    uint32_t        mdsthreshold:1;         // id: 68 0x00000000
    uint32_t        retention_get:1;        // id: 69 0x00000000
    uint32_t        retention_set:1;        // id: 70 0x00000000
    uint32_t        retentevt_get:1;        // id: 71 0x00000000

    uint32_t        retentevt_set:1;        // id: 72 0x00000000
    uint32_t        retention_hold:1;       // id: 73 0x00000000
    uint32_t        mode_setmasked:1;      // id: 74 0x00000000
    uint32_t        suppattr_exclcreat:1;   // id: 75 0x00000000
    uint32_t        fs_charset_cap:1;       // id: 76 0x00000000
    uint32_t        clone_blksize:1;        // id: 77 0x00000000
    uint32_t        space_freed:1;          // id: 78 0x00000000
    uint32_t        change_attr_type:1;     // id: 79 0x00000000

    uint32_t        sec_label:1;            // id: 80 0x00000000
    uint32_t        reserved1:7;

    uint32_t        reserved2:8;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint32_t        retentevt_get:1;        // id: 71 0x00000000
    uint32_t        retention_set:1;        // id: 70 0x00000000
    uint32_t        retention_get:1;        // id: 69 0x00000000
    uint32_t        mdsthreshold:1;         // id: 68 0x00000000
    uint32_t        fs_locations_info:1;    // id: 67 0x00000000
    uint32_t        layout_alignment:1;     // id: 66 0x00000000
    uint32_t        layout_blksize:1;       // id: 65 0x00000000
    uint32_t        layout_type:1;          // id: 64 0x00000000

    uint32_t        change_attr_type:1;     // id: 79 0x00000000
    uint32_t        space_freed:1;          // id: 78 0x00000000
    uint32_t        clone_blksize:1;        // id: 77 0x00000000
    uint32_t        fs_charset_cap:1;       // id: 76 0x00000000
    uint32_t        suppattr_exclcreat:1;   // id: 75 0x00000000
    uint32_t        mode_setmasked:1;      // id: 74 0x00000000
    uint32_t        retention_hold:1;       // id: 73 0x00000000
    uint32_t        retentevt_set:1;        // id: 72 0x00000000

    uint32_t        reserved1:7;
    uint32_t        sec_label:1;            // id: 80 0x00000000

    uint32_t        reserved2:8;
#else
#error "Unspecified host byte order, please fix 'nfsv4.proto'"
#endif
};

enum class ATTR_MASK_FIELD_ID : uint16_t
{
    SUPPORTED_ATTRS     = 0,
    TYPE                = 1,
    FH_EXPIRE_TYPE      = 2,
    CHANGE              = 3,
    SIZE                = 4,
    LINK_SUPPORT        = 5,
    SYMLINK_SUPPORT     = 6,
    NAMED_ATTR          = 7,
    FSID                = 8,
    UNIQUE_HANDLES      = 9,
    LEASE_TIME          = 10,
    RDATTR_ERROR        = 11,
    ACL                 = 12,
    ACLSUPPORT          = 13,
    ARCHIVE             = 14,
    CANSETTIME          = 15,
    CASE_INSENSITIVE    = 16,
    CASE_PRESERVING     = 17,
    CHOWN_RESTRICTED    = 18,
    FILEHANDLE          = 19,
    FILEID              = 20,
    FILES_AVAIL         = 21,
    FILES_FREE          = 22,
    FILES_TOTAL         = 23,
    FS_LOCATIONS        = 24,
    HIDDEN              = 25,
    HOMOGENEOUS         = 26,
    MAXFILESIZE         = 27,
    MAXLINK             = 28,
    MAXNAME             = 29,
    MAXREAD             = 30,
    MAXWRITE            = 31,
    MIMETYPE            = 32,
    MODE                = 33,
    NO_TRUNC            = 34,
    NUMLINKS            = 35,
    OWNER               = 36,
    OWNER_GROUP         = 37,
    QUOTA_AVAIL_HARD    = 38,
    QUOTA_AVAIL_SOFT    = 39,
    QUOTA_USED          = 40,
    RAWDEV              = 41,
    SPACE_AVAIL         = 42,
    SPACE_FREE          = 43,
    SPACE_TOTAL         = 44,
    SPACE_USED          = 45,
    SYSTEM              = 46,
    TIME_ATTR         = 47,
    TIME_ATTR_SET     = 48,
    TIME_BACKUP         = 49,
    TIME_CREATE         = 50,
    TIME_DELTA          = 51,
    TIME_METADATA       = 52,
    TIME_MODIFY         = 53,
    TIME_MODIFY_SET     = 54,
    MOUNTED_ON_FILEID   = 55,
    DIR_NOTIF_DELAY     = 56,
    DIRENT_NOTIF_DELAY  = 57,
    DACL                = 58,
    SACL                = 59,
    CHANGE_POLICY       = 60,
    FS_STATUS           = 61,
    FS_LAYOUT_TYPE      = 62,
    LAYOUT_HINT         = 63,
    LAYOUT_TYPE         = 64,
    LAYOUT_BLKSIZE      = 65,
    LAYOUT_ALIGNMENT    = 66,
    FS_LOCATIONS_INFO   = 67,
    MDSTHRESHOLD        = 68,
    RETENTION_GET       = 69,
    RETENTION_SET       = 70,
    RETENTEVT_GET       = 71,
    RETENTEVT_SET       = 72,
    RETENTION_HOLD      = 73,
    MODE_SET_MASKED     = 74,
    SUPPATTR_EXCLCREAT  = 75,
    FS_CHARSET_CAP      = 76,
    CLONE_BLKSIZE       = 77,
    SPACE_FREED         = 78,
    CHANGE_ATTR_TYPE    = 79,
    SEC_LABEL           = 80
};

// traits для получения типа маски по индексу
template <uint16_t N>
struct attrmask_type { using type = void; };
template <uint16_t N>
using attrmask_t = typename attrmask_type<N>::type;

template<>
struct attrmask_type<0> { using type = attrmask0_t; };
template<>
struct attrmask_type<1> { using type = attrmask1_t; };
template<>
struct attrmask_type<2> { using type = attrmask2_t; };

bool attrmask_val_by_id(const std::vector<uint32_t>& v_attrmask, ATTR_MASK_FIELD_ID field_id)
{
    size_t index = static_cast<uint16_t>(field_id) / 32;
    assert(index < v_attrmask.size());
    return v_attrmask[index] & (0x1 << ((static_cast<uint16_t>(field_id) % 32)));
}   

void check_attrmask_val_by_id(const std::vector<uint32_t>& v_attrmask, ATTR_MASK_FIELD_ID field_id)
{
    cout << "attrmask_val_by_id(" << static_cast<uint16_t>(field_id) << ") == " << attrmask_val_by_id(v_attrmask, field_id) 
         <<  endl;
}

#define CHECK_ATTRMASK_TRAIT(v_attrmask, N, fld_name) \
cout << #fld_name " == " << struct_cast<attrmask_t<N>>(v_attrmask[N]).fld_name << endl;

int main()
{
    std::vector<uint32_t> v_attrmask = { 1, 2, 7, 8 };
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::SUPPORTED_ATTRS);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::MODE);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::LAYOUT_TYPE);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::LAYOUT_BLKSIZE);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::LAYOUT_ALIGNMENT);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::FS_LOCATIONS_INFO);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::RETENTION_GET);
    check_attrmask_val_by_id(v_attrmask, ATTR_MASK_FIELD_ID::SEC_LABEL);

    CHECK_ATTRMASK_TRAIT(v_attrmask, 0, supported_attrs);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 1, mode);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 2, layout_type);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 2, layout_blksize);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 2, layout_alignment);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 2, fs_locations_info);
    CHECK_ATTRMASK_TRAIT(v_attrmask, 2, sec_label); 
}

