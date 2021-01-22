#include "interface.h"
#include <json-c/json.h>
#include <ws.h>
#include <string.h>
#include <stdlib.h>

int huobi_subscribe ( struct ws *ws ) {
    json_object *json_root = json_object_new_object ( );
    json_object *json_sub = json_object_new_string ( "market.btcusdt.kline.1min" );
    json_object *json_id = json_object_new_string ( "id1" );
    json_object_object_add ( json_root, "sub", json_sub );
    json_object_object_add ( json_root, "id", json_id );

    const char *data = json_object_to_json_string ( json_root );

    ws_write ( ws, data, strlen ( data ) );
    json_object_put ( json_root );

    size_t length = 4096;


    unsigned char *buffer = calloc ( length, 1 );
    unsigned char *out = calloc ( length, 1 );

    
    int ret = ws_read ( ws, buffer, length );
    
    ret = ws_gzip_decompress ( buffer, ret, out, length );
    
    json_root = json_tokener_parse ( out );
    json_object *json_status = json_object_object_get ( json_root, "status");
    const char *status = json_object_get_string ( json_status );

    free ( buffer );
    free ( out );

    
    if(!strncmp ( status, "ok", 3)) ret = 0;
    else ret = -1;

    json_object_put (json_root);

    if(!ret) {
        printf("huobi subscribe ok\n");
    }
    return ret;
}

void huobi_read ( struct ws *ws ) {

}