#include "interface.h"
#include "implement_huobi.h"
#include "implement_binance.h"
#include <stdio.h>
#include <ws.h>

void init_market ( struct interface *market, const int type_of_market ) {
    char *error = NULL;
    market->ws = ws_init ( market->site, market->port, &error );
    if ( error ) {
        printf ( "%s\n", error );
        return;
    }

    switch (type_of_market) {
        case MARKET_HUOBI:
                market->subscribe = huobi_subscribe;
                market->read = huobi_read;
                break;
        case MARKET_BINANCE:
                market->subscribe = binance_subscribe;
                market->read = binance_read;
                break;
    }
    
}