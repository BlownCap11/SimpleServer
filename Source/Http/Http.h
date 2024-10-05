#ifndef HTTP_INC
#define HTTP_INC

#include "../Util/Util.h"

// http response template
#define RESPONSETMP "HTTP/1.1 %s\r\nServer: C_Webserver\r\nContent-Length: %d\r\nContent-Type: text/html;\r\n\r\n%s\r\n\r\n"

// response codes
#define RESPOK          "200 OK"
#define RESPNOTFOUND    "404 Not Found"

// http request
typedef struct {
    char method[10];      // e.g., GET, POST, etc.
    char route[BUFFSIZE]; // e.g., /index.html
    char version[10];     // e.g., HTTP/1.1
    char headers[MAX_N][2][BUFFSIZE]; // Array of headers: key-value pairs
    int header_count;     // Number of headers
} HttpRequest;

char* http_response(const char* code, unsigned int len, const char* content);

void http_request_parse(HttpRequest* request, char* httpreq);

const char* http_request_header(const HttpRequest* request, const char* key);
#endif
