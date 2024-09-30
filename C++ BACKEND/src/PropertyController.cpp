#include "PropertyController.h"
#include <iostream>

PropertyController::PropertyController(const std::string& url, Database& db) : listener(url), database(db) {
    listener.support(methods::GET, std::bind(&PropertyController::handleGet, this, std::placeholders::_1));
    listener.support(methods::POST, std::bind(&PropertyController::handlePost, this, std::placeholders::_1));
    listener.support(methods::PUT, std::bind(&PropertyController::handlePut, this, std::placeholders::_1));
    listener.support(methods::DEL, std::bind(&PropertyController::handleDelete, this, std::placeholders::_1));
}

void PropertyController::start() {
    listener.open().then([&]() { std::cout << "Starting server at " << listener.uri().to_string() << std::endl; }).wait();
}

void PropertyController::handleGet(http_request request) {
    auto response = json::value::object();
    response["message"] = json::value::string("GET request received");
    request.reply(status_codes::OK, response);
}

void PropertyController::handlePost(http_request request) {
    auto response = json::value::object();
    response["message"] = json::value::string("POST request received");
    request.reply(status_codes::OK, response);
}

void PropertyController::handlePut(http_request request) {
    auto response = json::value::object();
    response["message"] = json::value::string("PUT request received");
    request.reply(status_codes::OK, response);
}

void PropertyController::handleDelete(http_request request) {
    auto response = json::value::object();
    response["message"] = json::value::string("DELETE request received");
    request.reply(status_codes::OK, response);
}
