#ifndef PROPERTY_CONTROLLER_H
#define PROPERTY_CONTROLLER_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "Database.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

class PropertyController {
public:
    PropertyController(const std::string& url, Database& db);
    void start();

private:
    void handleGet(http_request request);
    void handlePost(http_request request);
    void handlePut(http_request request);
    void handleDelete(http_request request);

    http_listener listener;
    Database& database;
};

#endif // PROPERTY_CONTROLLER_H
