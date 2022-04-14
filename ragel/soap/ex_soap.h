#pragma once

class decoder_soap
{
private:
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

    bool parse_data(const char* data, size_t length, bool finish, ntdec_soap_msg& soap_msg);

    bool determine_current_tag(parser_vars_t& parser_vars, ntdec_soap_msg& soap_msg);
    bool tag_name_is(const std::string_view& must_tag_name,
                     const char* p_tag_name_begin, const char* p_tag_name_end) const;

    bool set_tag_value(const char* p_tag_val_begin, const char* p_tag_val_end,
                       ntdec_soap_msg& soap_msg, TAG_TYPE ntproto_tag_type);
    bool set_attr_value(const char* p_attr_val_begin, const char* p_attr_val_end,
                        void* p_ntproto_tag, TAG_TYPE ntproto_tag_type,
                        void* p_ntproto_attr, ATTR_TYPE ntproto_attr_type);

    void move_tag_attrs(ntdec_soap_tag_base& src_tag, bool src_tag_moved,
                        ntdec_soap_tag_base& dst_tag) const;
    void tag_type_stack_push(tag_type_stack_t& tag_type_stack, TAG_TYPE tag_type,
                             const char* p_tag_name_begin, const char* p_tag_name_end) const;
    void tag_type_stack_pop(tag_type_stack_t& tag_type_stack,
                            const char* p_tag_name_begin, const char* p_tag_name_end) const;

    template <typename STR_T>
    typename STR_T::iterator find_str_ignore_case(const STR_T& haystack, const STR_T& needle) const;

    void push_tag_type_based_on_tag_name(const char *p_tag_name_begin, const char* p_tag_name_end);

    static constexpr int DEBUG_VIEW_LEN = 32;
    int view_length(const char* const p, const char* const pe)
    { return pe - p > DEBUG_VIEW_LEN ? DEBUG_VIEW_LEN : pe - p; }

};

template <typename STR_T>
typename STR_T::iterator decoder_soap::find_str_ignore_case(const STR_T& haystack, const STR_T& needle) const
{
    return std::search(
        haystack.begin(), haystack.end(),
        needle.begin(),   needle.end(),
        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );
}
