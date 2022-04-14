#define L 1
#include <stdio.h>

#define DEBUG(args...) printf(args...)

%%{
    machine soap_tasting_fsm;

    action on_begin
    {
        p_begin = p;
        DEBUG(L, 10, "[%p]: SOAP tasting: `on_begin` action: [*p = '%.*s...']",
              d_http, decoder_soap::view_length(p, pe), p);
    }

    action on_match_tag
    {
        DEBUG(L, 10, "[%p]: SOAP tasting: `on_match_tag` action: [*p = '%.*s...']",
              d_http, decoder_soap::view_length(p, pe), p);
        DEBUG(L, 0, "[%p]: SOAP tasting: tasted SOAP", d_http);
        return TASTING_STATUS::SUCCESS;
    }

    action on_eof
    {
        if (p_begin != nullptr)
        {
            DEBUG(L, 10, "[%p]: SOAP tasting: `on_eof` action: caching: [*p = '%.*s...']",
                  d_http, decoder_soap::view_length(p_begin, pe), p_begin);

            cache.add(p_begin, pe - p_begin);
            cache.save();
        }
        else
        {
            DEBUG(L, 10, "[%p]: SOAP tasting: `on_eof` action: nothing to cache", d_http);
        }

        DEBUG(L, 0, "[%p] SOAP tasting: waiting new chunk"
        return TASTING_STATUS::WAITING_NEW_CHUNK;
    }

    action on_scanner_error
    {
        fret;
    }

    tag_scanner := |*
        'Envelope'i >on_begin       => on_match_tag;
        'Upgrade'i >on_begin        => on_match_tag;
        'NotUnderstood'i >on_begin  => on_match_tag;
        any => on_scanner_error;
    *|;

    main := ((any -- '<')* '<' %{ fcall tag_scanner; })+;

}%%

%% write data;

void soap_signature_tasting::init_fsm()
{
    %% write init;
    cache.clear();
}

soap_signature_tasting::TASTING_STATUS soap_signature_tasting::taste(
                                            const char* data, size_t length, const void* d_http,
                                            uint32_t max_soap_tasting_view_length,
                                            uint32_t max_soap_tasting_tryings)
{
    const char          *p = data,
                        *pe = data + ((length > max_soap_tasting_view_length)
                                            ? max_soap_tasting_view_length : length);
    const char          *eof = pe; // = finish ? pe : nullptr;
    const char          *p_begin = nullptr;

    if (tryings > max_soap_tasting_tryings)
    {
        DEBUG(L, 0, "[%p] Tasting SOAP: exceeded taste tryings limit [limit = %u]",
              d_http, max_soap_tasting_tryings);
        return TASTING_STATUS::TRYINGS_OVER;
    }

    %% write data;

    // unused variables
    UNUSED_VAR(soap_tasting_fsm_start);
    UNUSED_VAR(soap_tasting_fsm_error);
    UNUSED_VAR(soap_tasting_fsm_en_main);
    UNUSED_VAR(soap_tasting_fsm_first_final);
    UNUSED_VAR(soap_tasting_fsm_en_tag_scanner);

    %% write exec;

    ++tryings;
    return TASTING_STATUS::FAILED;
}
