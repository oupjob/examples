#include "smb1.h"

using namespace std;

void smb1_subdecoder::send_tr_msg()
{
    cout << "send_tr_msg:" << endl;
    send_subflow_premature_end_msg<smb1_close_request, INVALID_FILE_ID>(0, 0, 0, 0, 0);
    send_subflow_premature_end_msg<smb1_find_close2_request, INVALID_SEARCH_ID>(0, 0, 0, 0, 0);
}
