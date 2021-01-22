#ifndef IMPLEMENT_HUOBI
#define IMPLEMENT_HUOBI
#include "interface.h"
#include <ws.h>

int huobi_subscribe ( struct ws *ws );
void huobi_read ( struct ws *ws );
#endif