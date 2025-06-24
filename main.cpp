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

int main() {
    crow::SimpleApp app;

    std::string path = "static/index.html";
    if (!std::filesystem::exists(path)) {
        std::cout << "File not found: " << path << std::endl;
    } else {
        std::cout << "File exists: " << path << std::endl;
    }

    CROW_ROUTE(app, "/")([] {
        return crow::response(readFile("static/index.html"));
    });
    
    app.port(8080).multithreaded().run();
}
