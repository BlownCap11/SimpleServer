/* October 5th 2024 15:50 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "Source/Server/Server.h"
#include "Source/Util/Util.h"
#include "Source/Http/Http.h"

int main()
{
    Webserver_t srv;
    webserver_setup(&srv, 2233);
    printf("Listening on port: %d\n", srv.port);
    char reqd[BUFFSIZE*4];
    HttpRequest hreq;
    char* fdata;
    /* routes */
    webserver_route_add(&srv, "/", "Web/Index.html");
    webserver_route_add(&srv, "/about", "Web/About.html");
    while (1)
    {
        webserver_conn(&srv);
        recv(srv.cln.cfd, reqd, BUFFSIZE*4, 0);
        http_request_parse(&hreq, reqd);
        const char* f = webserver_route_get(&srv, hreq.route);
        printf("Route: %s\n", f);
        if (f == NULL)
        {
            char* err = http_response(RESPNOTFOUND, 3, "404");
            send(srv.cln.cfd, err, BUFFSIZE*4, 0);
        }
        else
        {
            fdata = util_read_file(f);
            char* resp = http_response(RESPOK, strlen(fdata), fdata);
            send(srv.cln.cfd, resp, BUFFSIZE*4, 0);
        }
        close(srv.cln.cfd);
    }
    return 0;
}
