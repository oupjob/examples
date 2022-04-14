#include <stack>
#include <string>

enum class TAG_TYPE : uint8_t
{
    ANY,
    BODY,
    CODE,
    CODE_VALUE,
    ENVELOPE,
    FAULT,
    FAULTACTOR,
    FAULTCODE,
    FAULTSTRING,
    HEADER,
    NODE,
    NOT_UNDERSTOOD,
    REASON,
    REASON_TEXT,
    ROLE,
    SUBCODE,
    SUBCODE_VALUE,
    SUPPORTED_ENVELOPE,
    UPGRADE
};
using tag_type_stack_t = std::stack<TAG_TYPE>;

enum class ATTR_TYPE : uint8_t
{
    ANY,
    ACTOR,
    MUST_UNDERSTAND,
    QNAME,
    RELAY,
    ROLE,
    SOAP_ENCODING_STYLE,
};

struct parser_vars_t
{
    const char*             p_tag_name_begin;
    const char*             p_tag_name_end;
    const char*             p_tag_val_begin;
    const char*             p_tag_val_end;
    const char*             p_attr_name_begin;
    const char*             p_attr_name_end;
    const char*             p_attr_val_begin;
    const char*             p_attr_val_end;

    ntdec_soap_tag_base                 lining_tag;
    ntdec_soap_supported_envelope_tag   current_supported_envelope_tag;
    ntdec_soap_str_value_tag            current_str_value_tag;
    bool                                lining_tag_moved = false;

    ntdec_soap_tag_base     *p_current_tag = static_cast<ntdec_soap_tag_base*>(&lining_tag);
    void                    *p_current_attr = nullptr;

    tag_type_stack_t        tag_type_stack;
    ATTR_TYPE               current_attr_type = ATTR_TYPE::ANY;

    parser_vars_t(const char* data) :
        p_tag_name_begin (data), p_tag_name_end (data),
        p_tag_val_begin (data), p_tag_val_end (data),
        p_attr_name_begin (data), p_attr_name_end (data),
        p_attr_val_begin (data), p_attr_val_end (data),
        lining_tag_moved(false),
        p_current_tag(static_cast<ntdec_soap_tag_base*>(&lining_tag)),
        p_current_attr(nullptr),
        current_attr_type(ATTR_TYPE::ANY)
    {}
};
