#ifndef INTERFACE_H
#define INTERFACE_H
struct interface {
    /* fields */
    char *site;
    unsigned short port;
    const int type_of_market;
    struct ws *ws;

    /* functions */
    int (*subscribe) ( struct ws *ws );
    void (*read) ( struct ws *ws );
};

#define MARKET_HUOBI               0
#define MARKET_BINANCE             1

void init_market ( struct interface *market, const int type_of_market );
#endif