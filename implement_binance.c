#include "interface.h"
#include <json-c/json.h>
#include <ws.h>
#include <string.h>
#include <stdlib.h>

int binance_subscribe ( struct ws *ws ) {
json_object *json_root = json_object_new_object ( );
    json_object *json_sub = json_object_new_string ( "SUBSCRIBE" );
    json_object *json_id = json_object_new_int ( 1 );
    json_object *json_params = json_object_new_array ( );
    json_object *json_kline = json_object_new_string ( "btcusdt@kline_1m");
    json_object_array_add ( json_params, json_kline );
    json_object_object_add ( json_root, "method", json_sub );
    json_object_object_add ( json_root, "params", json_params );
    json_object_object_add ( json_root, "id", json_id );

    const char *data = json_object_to_json_string ( json_root );
    ws_write ( ws, data, strlen ( data ) );
    json_object_put ( json_root );

    size_t length = 4096;

    unsigned char *buffer = calloc ( length, 1 );
    
    int ret = ws_read ( ws, buffer, length );
    buffer[ret] = 0;
   
    json_root = json_tokener_parse ( buffer );
    json_object *json_result = json_object_object_get ( json_root, "result");
    const char *result = json_object_get_string ( json_result );
    
    free ( buffer );
    
    if(result == NULL) ret = 0;
    else ret = -1;
    
    json_object_put (json_root);

    if(!ret) {
        printf("binance subscribe ok\n");
    }
    return ret;
}
void binance_read ( struct ws *ws ) {

}