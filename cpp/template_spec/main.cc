#include "smb1.h"

int main()
{
    smb1_subdecoder sd;

    sd.send_msg();
    sd.send_tr_msg();

    return 0;
}
