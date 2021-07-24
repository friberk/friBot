#include "../deps/HTTPRequest/include/HTTPRequest.hpp"
#include "../deps/json/single_include/nlohmann/json.hpp"
#include <iostream>

using json = nlohmann::json;

int main(int argc, char const *argv[]) {
  try {
    http::Request request("http://puango.net/api/hesaplama.php");
    std::map<std::string, std::string> parameters = {
        {"diploma", "50.5"}, {"kirikOBP", "true"}, {"ttd", "40"}, {"tmd", "40"},
        {"tsd", "20"},      {"tfd", "20"},        {"tty", "0"},  {"tmy", "0"},
        {"tsy", "0"},       {"tfy", "0"},         {"md", "40"},  {"fd", "14"},
        {"kd", "13"},       {"bd", "13"},         {"my", "0"},   {"fy", "0"},
        {"ky", "0"},        {"by", "0"}};

    const http::Response response =
        request.send("POST", parameters,
                     {"Content-Type: application/x-www-form-urlencoded"});

    json postReq{
        json::parse(std::string{response.body.begin(), response.body.end()})};

    std::cout << postReq.dump(4) << std::endl;
  } catch (const std::exception &e) {
    std::cerr << "Request failed, error: " << e.what() << std::endl;
  }
}
