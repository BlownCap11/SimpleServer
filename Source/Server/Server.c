#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "Server.h"

void webserver_setup(Webserver_t* ws, int32_t port)
{
    ws->sck = socket(AF_INET, SOCK_STREAM, 0);
    ws->port = port;
    ws->nroutes = 0;

    struct sockaddr_in addrin;
    addrin.sin_port = htons(ws->port);
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = INADDR_ANY;
    socklen_t _addrlen = (socklen_t)sizeof(addrin);

    int _bnd = bind(ws->sck, (struct sockaddr*)&addrin, _addrlen);
    if (_bnd < 0)
    {
        perror("bind()");
        exit(EXIT_FAILURE);
    }
    
    int _ln = listen(ws->sck, 5);
    if (_ln < 0)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
}

void webserver_conn(Webserver_t* ws)
{
    socklen_t clnaddrlen = (socklen_t)sizeof(ws->cln.cln);
    ws->cln.cfd = accept(ws->sck, (struct sockaddr*)&ws->cln.cln, &clnaddrlen);
    if (ws->cln.cfd < 0)
    {
        perror("accept()");
        exit(EXIT_FAILURE);
    }
}

void webserver_route_add(Webserver_t* ws, char* route, char* file)
{
    ws->routes[ws->nroutes].route = route;
    ws->routes[ws->nroutes].file = file;
    ws->nroutes += 1;
}

char* webserver_route_get(Webserver_t *ws, char *route)
{
    Route r;
    for (int i = 0; i < ws->nroutes; i++)
    {
        r = ws->routes[i];
        if (!strcmp(route, r.route))
            return r.file;
    }
    return NULL;
}
