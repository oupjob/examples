#include <cstdint>


struct bind_status_t
{
    uint8_t         bunch_found:1;
    uint8_t         bunch_can_be_stored:1;
    uint64_t        msg_id;
};

bind_status_t f() 
{ 
    return bind_status_t { .bunch_found = true, .bunch_can_be_stored = false, .msg_id = 2 };
}

int main()
{
    bind_status_t bind_status = f();
    bool bf = bind_status.bunch_found;
    bool bcbs = bind_status.bunch_can_be_stored;
    uint64_t msg_id = bind_status.msg_id;
}
