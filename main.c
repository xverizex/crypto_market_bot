#include "interface.h"
#include <pthread.h>

struct interface market[] = {
    { "wss://api.huobi.pro/ws", 443, MARKET_HUOBI },
    { "wss://stream.binance.com/ws", 9443, MARKET_BINANCE }
};

const int size_market = 2;

static void *separate_stream ( void *data ) {
    struct interface *market = ( struct interface * ) data;
    int ret = market->subscribe ( market->ws );
    if (ret == -1) return NULL;
    while ( 1 ) {
        market->read ( market->ws );
    }
}

int main ( int argc, char **argv ) {

    pthread_t t[size_market];

    for ( int i = 0; i < size_market; i++ ) {
        init_market ( &market[i], market[i].type_of_market );
        pthread_create(&t[i], NULL, separate_stream, &market[i] );
    }

    for ( int i = 0; i < size_market; i++ ) {
        int *ret = NULL;
        pthread_join ( t[i], (void *) &ret );
    }
}