using uint32_t = unsigned int;

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
    attrmask0_t() :
        supported_attrs(false), type(false), fh_expire_type(false), change(false),
        size(false), link_support(false), symlink_support(false), named_attr(false),
        fsid(false), unique_handles(false), lease_time(false), rdattr_error(false), acl(false),
        aclsupport(false), archive(false), cansettime(false), case_insensitive(false),
        case_preserving(false), chown_restricted(false), filehandle(false), fileid(false),
        files_avail(false), files_free(false), files_total(false), fs_locations(false), hidden(false),
        homogeneous(false), maxfilesize(false), maxlink(false), maxname(false), maxread(false),
        maxwrite(false)
    {}
};

int main()
{
    attrmask0_t attrmask;
}
