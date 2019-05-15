#include <map>
#include <iostream>
#include <boost/function.hpp>

typedef boost::function<void (void)> FunctionPtr;


void hello_world() {
    std::cout << "Hello World!\n";
}

void goo_goo_ka_choo() {
    std::cout << "Goo goo ka choo!\n";
}



class Server {
public:
    Server();
    // Server(const Server&) = delete;
    // Server& operator=(const Server&) = delete;
    // ~Server();
    std::shared_ptr<std::map<std::string, FunctionPtr>> smart_ptr_;
    // std::map<std::string, FunctionPtr>* available_functions_;
    void AddFunction(std::string function_name, FunctionPtr ptr);
};

Server::Server() {
    smart_ptr_.reset(new std::map<std::string, FunctionPtr>);
    // available_functions_ = new std::map<std::string, FunctionPtr>;
}

// Server::~Server() {
//     delete available_functions_;
// }

void Server::AddFunction(std::string function_name, FunctionPtr ptr) {
    // (*available_functions_)[function_name] = ptr;
    (*smart_ptr_)[function_name] = ptr;
    std::cout << "Added Function: " << function_name << "\n";
}

class Client {
public:
    Client(std::shared_ptr<std::map<std::string, FunctionPtr>> available_functions);
    void CallFunction(std::string name);
    std::shared_ptr<std::map<std::string, FunctionPtr>> available_functions_;
};

Client::Client(std::shared_ptr<std::map<std::string, FunctionPtr>> available_functions) {
    available_functions_ = available_functions;
}

void Client::CallFunction(std::string name) {
    std::map<std::string, FunctionPtr>::iterator it = (*available_functions_).find(name);
    if(it != (*available_functions_).end()) {
        // element found
        (*available_functions_)[name]();
    } else {
        std::cout << "Cannot find function with name: " << name << "\n";
    }
}

int main() {
    Server s = Server();
    // std::map<std::string, FunctionPtr> *ptr;
    // ptr = s.smart_ptr_.get();

    Client c = Client(s.smart_ptr_);
    
    s.AddFunction("hello_world", &hello_world);
    s.AddFunction("goo_goo_ka_choo", &goo_goo_ka_choo);
    c.CallFunction("hello_world");
    return 0;
}