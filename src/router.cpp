#include "jet/router.hpp"
#include "jet/helper.hpp"

#include <iostream>

void Router::mount(const std::string& method, const std::string& path, handler handler){
    if(is_method_valid(method) == false){
        std::cout << method << " is not a valid method type." << std::endl;
        return;
    }

    str_to_lower(method);
    str_to_lower(path);
    routes[method][path] = handler;
    std::cout << "Mounted " << method << " " << path << std::endl;
}

void Router::unmount(const std::string& method, const std::string& path) {
    str_to_lower(method);
    str_to_lower(path);

    routes[method].erase(path);
    if (routes[method].empty()) {
        routes.erase(method);
    }
}

void Router::execute(Request& req, Response& res) {
    std::string method = req.get_method();
    std::string path = req.get_target();

    str_to_lower(method);
    str_to_lower(path);

    std::unordered_map<std::string, std::unordered_map<std::string, handler>>::iterator method_it = routes.find(method);
    if (method_it == routes.end()) {
        std::cerr << "No handlers for method: " << method << std::endl;
        res.set_status(404);
        return;
    }
    
    std::unordered_map<std::string, handler>::iterator handler_iterator = method_it->second.find(path);
    if (handler_iterator == method_it->second.end()) {
        std::cerr << "No handler for path: " << path << std::endl;
        res.set_status(404);
        return;
    }

    handler_iterator->second(req, res);
}