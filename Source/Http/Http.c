#include "Http.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Util/Util.h"

char* http_response(const char* code, uint len, const char* content)
{
    char fdata[BUFFSIZE];
    strncpy(fdata, RESPONSETMP, BUFFSIZE);
    /* crafting response */
    char* resp = malloc(BUFFSIZE * sizeof(char) * 4);
    snprintf(resp, BUFFSIZE*4, fdata, code, len, content);
    resp[BUFFSIZE*4] = '\0';
    return resp;
}

void http_request_parse(HttpRequest* request, char* httpreq) {
    char* line = strtok(httpreq, "\r\n");

    // Parse the request line
    if (line) {
        sscanf(line, "%s %s %s", request->method, request->route, request->version);
        line = strtok(NULL, "\r\n");
    }

    // Parse headers
    request->header_count = 0;
    while (line != NULL && request->header_count < MAX_N) {
        // Check for an empty line to stop headers
        if (strlen(line) == 0) break;

        // Split into key-value pairs
        char* separator = strchr(line, ':');
        if (separator) {
            *separator = '\0'; // Split the line into key and value
            strcpy(request->headers[request->header_count][0], line); // Key
            strcpy(request->headers[request->header_count][1], separator + 2); // Value (skip the space)
            request->header_count++;
        }

        line = strtok(NULL, "\r\n");
    }
}

// Function to search for a specific header
const char* http_request_header(const HttpRequest* request, const char* key) {
    for (int i = 0; i < request->header_count; i++) {
        if (strcasecmp(request->headers[i][0], key) == 0) { // Case-insensitive comparison
            return request->headers[i][1]; // Return the value
        }
    }
    return NULL; // Header not found
}
