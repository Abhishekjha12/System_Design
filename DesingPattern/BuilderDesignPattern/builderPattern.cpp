#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

using namespace std;

class HttpRequest {
private:
    string url;
    string method;
    map<string, string> headers;
    map<string,string> queryParams;
    string body;
    int timeout; // in seconds

    // Private constructor - can only be accessed by the Builder
    HttpRequest() { }

public:
    friend class HttpRequestBuilder;

    // Method to execute the HTTP request
    void execute() {
        cout << "Executing " << method << " request to " << url << endl;
        
        if (!queryParams.empty()) {
            cout << "Query Parameters:" << endl;
            for (const auto& param : queryParams) {
                cout << "  " << param.first << "=" << param.second << endl;
            }
        }

        cout << "Headers:" << endl;
        for (const auto& header : headers) {
            cout << "  " << header.first << ": " << header.second << endl;
        }
        
        if (!body.empty()) {
            cout << "Body: " << body << endl;
        }
        
        cout << "Timeout: " << timeout << " seconds" << endl;
        cout << "Request executed successfully!" << endl;
    }
};

class HttpRequestBuilder {
private:    
    HttpRequest req;

public:    
    // Method chaining
    HttpRequestBuilder& withUrl(const string& u) {
        req.url = u; 
        return *this;
    }

    HttpRequestBuilder& withMethod(string method) {
        req.method = method;
        return *this;
    }
    
    HttpRequestBuilder& withHeader(const string& key, const string& value) {
        req.headers[key] = value;
        return *this;
    }

    HttpRequestBuilder& withQueryParams(const string& key, const string& value) {
        req.queryParams[key] = value;
        return *this;
    }
    
    HttpRequestBuilder& withBody(const string& body) {
        req.body = body;
        return *this;
    }
    
    HttpRequestBuilder& withTimeout(int timeout) {
        req.timeout = timeout;
        return *this;
    }
    
    // Build method to create the immutable HttpRequest object
    HttpRequest build() {
        // Validation logic can be added here
        if (req.url.empty()) {
            throw runtime_error("URL cannot be empty");
        }
        return req;
    }
};


int main() {
    // Using Builder Pattern (nested class)
    HttpRequest request = HttpRequestBuilder()
        .withUrl("https://api.example.com")
        .withMethod("POST")
        .withHeader("Content-Type", "application/json")
        .withHeader("Accept", "application/json")
        .withQueryParams("key", "12345")
        .withBody("{\"name\": \"Aditya\"}")
        .withTimeout(60)
        .build();

        // HttpRequestBuilder *builder = new HttpRequestBuilder();
        // // builder->withUrl("https://www.google.com");
        // // builder->withBody("Sadsa");
        // HttpRequest request2 = builder->withUrl("https://www.example.com").build(); //.build helps to convert httpRequest to builder request
        // i.e .build Stimulate the same effect as HttpBuilderRequest but within a mew builder 

        // the code base above is immutable, meaning it generate unique API's every single time, 
        // as we are not allowed to make changes in segments, the entire configuration needs to be set up 
    request.execute(); // Guaranteed to be in a consistent state
}