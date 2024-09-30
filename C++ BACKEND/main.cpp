#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <iostream>
#include "Database.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

Database db("realestate.db");

void handle_get(http_request request) {
    ucout << "GET request received" << std::endl;

    db.get_properties(); // Retrieve and display properties

    json::value response_data;
    response_data[U("message")] = json::value::string(U("Properties listed in console"));

    request.reply(status_codes::OK, response_data);
}

void handle_post(http_request request) {
    ucout << "POST request received" << std::endl;

    request.extract_json().then([=](json::value request_data) {
        ucout << "Received data: " << request_data.serialize() << std::endl;

        std::string name = request_data[U("name")].as_string();
        double price = request_data[U("price")].as_double();

        if (db.insert_property(name, price)) {
            json::value response_data;
            response_data[U("status")] = json::value::string(U("Property added successfully"));
            request.reply(status_codes::OK, response_data);
        }
        else {
            request.reply(status_codes::InternalError, U("Failed to add property"));
        }
        }).wait();
}

int main() {
    db.create_table(); // Create the properties table

    http_listener listener(U("http://localhost:8080"));

    listener.support(methods::GET, handle_get);
    listener.support(methods::POST, handle_post);

    try {
        listener
            .open()
            .then([&listener]() { ucout << "Starting server at: " << listener.uri().to_string() << std::endl; })
            .wait();

        while (true);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
