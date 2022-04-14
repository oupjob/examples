#include <stdio.h>
#include <stddef.h>

const char* align_ptr(const char* p_begin, const char* p, size_t align)
{
    if (p_begin > p)
        return p;


    size_t ptr_diff = p - p_begin;
    size_t offset_diff = (ptr_diff) % align;

    if (offset_diff == 0)
        return :

    return p + align - offset_diff;
}

int main()
{
    const char* p_begin = reinterpret_cast<const char*>(0x01);
    const char* p = reinterpret_cast<const char*>(0x02);

    printf("(%p, %p, %u) -> %p\n", p_begin, p, 2, align_ptr(p_begin, p, 2)); 
    printf("(%p, %p, %u) > %p\n", p_begin, p, 4, align_ptr(p_begin, p, 4));

    p_begin = reinterpret_cast<const char*>(0x02);
    p = reinterpret_cast<const char*>(0x02);

    printf("(%p, %p, %u) -> %p\n", p_begin, p, 2, align_ptr(p_begin, p, 2)); 
    printf("(%p, %p, %u) -> %p\n", p_begin, p, 4, align_ptr(p_begin, p, 4));

    return 0;
}
