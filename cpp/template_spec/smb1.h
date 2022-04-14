#pragma once
#include <iostream>

struct smb1_close_request {};
struct smb1_find_close2_request {};

class smb1_subdecoder
{
public:
    static const uint16_t INVALID_FILE_ID       = 0xFFFF;
    static const uint16_t INVALID_SEARCH_ID     = 0;
    
    template<class END_OBJECT_T, uint16_t INVALID_ID>
    void send_subflow_premature_end_msg(
        uint64_t subflow_msg_id, uint8_t close_reason, uint64_t header_msg_id, 
        uint16_t file_id_or_search_id, uint8_t side);

    void send_msg();
    void send_tr_msg();
};

using namespace std;
template <class END_OBJECT_T, uint16_t INVALID_ID>
void smb1_subdecoder::send_subflow_premature_end_msg(
    uint64_t subflow_msg_id, uint8_t close_reason, uint64_t header_msg_id, 
    uint16_t file_id_or_search_id, uint8_t side)
{
    cout << "send_subflow_premature_end_msg<END_OBJECT_T, INVALID_ID>(...)" << endl;
}

template<>
inline void smb1_subdecoder::send_subflow_premature_end_msg<
    smb1_close_request, smb1_subdecoder::INVALID_FILE_ID>(
    uint64_t subflow_msg_id, uint8_t close_reason, uint64_t header_msg_id, 
    uint16_t file_id_or_search_id, uint8_t side)
{
    cout << "send_subflow_premature_end_msg<smb1_close_request, INVALID_FILE_ID>(...)" << endl;
}


template<>
inline void smb1_subdecoder::send_subflow_premature_end_msg<
    smb1_find_close2_request, smb1_subdecoder::INVALID_SEARCH_ID>(
    uint64_t subflow_msg_id, uint8_t close_reason, uint64_t header_msg_id, 
    uint16_t file_id_or_search_id, uint8_t side)

{
    cout << "send_subflow_premature_end_msg<smb1_find_close2_request, INVALID_SEARCH_ID>(...)" << endl;
}

