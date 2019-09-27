#ifndef FKBD_STRUCTS_H
#define FKBD_STRUCTS_H

#include <linux/types.h>

struct fkbd_timeval32 {
    __u32 			seconds;
    __u32			null_fld_1;
    __u32			mseconds;
    __u32			null_fld_2;
};

struct fkbd_timeval64 {
    __u64 			seconds;
    __u64			mseconds;
};

typedef struct fkbd_timeval64 fkbd_timeval;

struct ev_code {
    fkbd_timeval	time;
    __u32			fld_262148; // ever 262148
    __u32			code;
};

struct ev_type {
    fkbd_timeval	time;
    // __u32			code_mult_pow_2_16; // code * 2 ^ 16
    __u16           code_prefix;
    __u16           code;
    __u32			type; // 0 - press | 1 - unpress
};

struct ev_end {
    fkbd_timeval	time;
    __u32			null_fld1; // allways null
    __u32			null_fld2; // allways null
};

struct fkbd_symbol_event {
    ev_code			event_code;
    ev_type			event_type;
    ev_end			event_end;
};

#endif // FKBD_STRUCTS_H
