#pragma once
#include "request.hpp"
#include "response.hpp"

#include <string>
#include <unordered_map>
#include <functional>

using handler = std::function<void(Request&, Response&)>;

class Router {
    public:
    static Router& get() {
        static Router instance;
        return instance;
    }

    Router(const Router&) = delete;
    Router& operator=(const Router&) = delete;

    std::unordered_map<std::string, std::unordered_map<std::string, handler>> routes;

    void mount(const std::string& method, const std::string& path, handler handler);
    void unmount(const std::string& method, const std::string& path);
    void execute(Request& req, Response& res);
    
    private:
    Router() {}
};