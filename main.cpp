#include "crow_all.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}
std::string getMimeType(const std::string& path) {
    if (endsWith(path, ".html")) return "text/html";
    if (endsWith(path, ".css")) return "text/css";
    if (endsWith(path, ".js")) return "application/javascript";
    if (endsWith(path, ".png")) return "image/png";
    if (endsWith(path, ".jpg") || endsWith(path, ".jpeg")) return "image/jpeg";
    return "text/plain";
}

int main() {
    crow::SimpleApp app;

    std::string path = "../../static/index.html";
    if (!std::filesystem::exists(path)) {
        std::cout << "File not found: " << path << std::endl;
    } else {
        std::cout << "File exists: " << path << std::endl;
    }

    CROW_ROUTE(app, "/")([] {
        return crow::response(readFile("../../static/index.html"));
    });

    CROW_ROUTE(app, "/static/<string>")
    ([](const std::string& filename) {
        std::string fullPath = "../../static/" + filename;
        if (!std::filesystem::exists(fullPath)) {
            return crow::response(404, "File not found");
        }
        crow::response res(readFile(fullPath));
        res.set_header("Content-Type", getMimeType(filename));
        return res;
    });


    CROW_ROUTE(app, "/api/hello")([] {
        crow::json::wvalue res;
        res["message"] = "Hello from Crow!";
        return res;
    });

    app.route_dynamic("/*").methods("GET"_method)
    ([](const crow::request& req) {
        return crow::response(404, "Custom 404: Page not found");
    });

    std::cout << "Crow server starting on http://localhost:8080" << std::endl;
    app.port(8080).multithreaded().run();
}