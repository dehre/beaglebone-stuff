#include <httplib.h>
#include <iostream>

int main()
{
    httplib::Client cli("http://httpbin.org");
    if (const auto res = cli.Get("/ip"))
    {
        std::cout << "Status: " << res.value().status << '\n';
        std::cout << "Body: " << res.value().body;
    }
    else
    {
        const auto err = res.error();
        std::cout << "HTTP error: " << httplib::to_string(err) << '\n';
    }
    return 0;
}
