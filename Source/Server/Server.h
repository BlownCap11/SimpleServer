#ifndef SERVER_INC
#define SERVER_INC

#include <stdint.h>
#include <netinet/in.h>

#include "../Util/Util.h"

typedef struct _Client
{
    struct sockaddr_in cln;
    int cfd;
} Client;

typedef struct _Route
{
    char* route;
    char* file;
} Route;

typedef struct _WebServer
{
    int port;
    int sck;
    Client cln;
    Route routes[MAX_N];
    int nroutes;
} Webserver_t;

void webserver_setup(Webserver_t* ws, int32_t port);

void webserver_conn(Webserver_t* ws);

void webserver_route_add(Webserver_t* ws, char* route, char* file);

char* webserver_route_get(Webserver_t *ws, char *route);

#endif
