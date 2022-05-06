#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>

// ~/proj/nt-dec/tests/functional/result/test-nfs/04_nfsv4_basic.flow=proto
// ntdec_onc_rpc_msg_reply.xid: 530677601

// Маска атрибутов по индексу 0
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
    attrmask0_t() { memset(this, 0, sizeof(*this)); }
};

#define PRT_FLAG(p, field) printf("p->" #field ": %u\n", p->field); 

int main()
{
    // uint8_t a[] = { 0x00, 0x10, 0x01, 0x1A };   // 436277248 in network byte order
    uint8_t a[] = { 0x1A, 0x01, 0x10, 0x00 };   // 436277248 in host byte order (1048858)
    
    uint32_t* pi = (uint32_t*)a;
    attrmask0_t* pa = (attrmask0_t*)a;

    printf("uint32_t: %u\n", *pi);

    PRT_FLAG(pa, supported_attrs);
    PRT_FLAG(pa, type);
    PRT_FLAG(pa, fh_expire_type);
    PRT_FLAG(pa, change);
    PRT_FLAG(pa, size);
    PRT_FLAG(pa, link_support);
    PRT_FLAG(pa, symlink_support);
    PRT_FLAG(pa, named_attr);
    
    PRT_FLAG(pa, fsid);
    PRT_FLAG(pa, unique_handles);
    PRT_FLAG(pa, lease_time);
    PRT_FLAG(pa, rdattr_error);
    PRT_FLAG(pa, acl);
    PRT_FLAG(pa, aclsupport);
    PRT_FLAG(pa, archive);
    PRT_FLAG(pa, cansettime);
    
    PRT_FLAG(pa, case_insensitive);
    PRT_FLAG(pa, case_preserving);
    PRT_FLAG(pa, chown_restricted);
    PRT_FLAG(pa, filehandle);
    PRT_FLAG(pa, fileid);
    PRT_FLAG(pa, files_avail);
    PRT_FLAG(pa, files_free);
    PRT_FLAG(pa, files_total);
    
    PRT_FLAG(pa, fs_locations);
    PRT_FLAG(pa, hidden);
    PRT_FLAG(pa, homogeneous);
    PRT_FLAG(pa, maxfilesize);
    PRT_FLAG(pa, maxlink);
    PRT_FLAG(pa, maxname);
    PRT_FLAG(pa, maxread);
    PRT_FLAG(pa, maxwrite);

    return 0;
}
