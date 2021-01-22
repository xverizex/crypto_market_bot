#ifndef IMPLEMENT_BINANCE
#define IMPLEMENT_BINANCE
#include "interface.h"
#include <ws.h>

int binance_subscribe ( struct ws *ws );
void binance_read ( struct ws *ws );
#endif