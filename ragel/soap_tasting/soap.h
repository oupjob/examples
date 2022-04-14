

class soap_signature_tasting
{
public:
    enum class TASTING_STATUS : uint8_t { SUCCESS, FAILED, WAITING_NEW_CHUNK, TRYINGS_OVER, NONE };

    soap_signature_tasting() : tryings(0) { init_fsm(); }

    TASTING_STATUS taste(const char* data, size_t length, const void* d_http,
                         uint32_t max_soap_tasting_view_length, uint32_t max_soap_tasting_tryings);

private:
    void init_fsm();

private:
    uint32_t                tryings;    // Счетчик: Количество попыток тастинга
    message_cacher          cache;      // Кеш тегов

    // Ragel переменные
    int                     cs;
    int                     act;
    const char*             ts;
    const char*             te;
    int                     stack[3];
    int                     top;
};

