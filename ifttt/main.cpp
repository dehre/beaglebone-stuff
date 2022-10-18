#include "RandomInt.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <httplib.h>
#include <iostream>
#include <stdexcept>
#include <string>

constexpr int g_i2cInstance{2};

int main()
{
    try
    {
        int temperature{RandomInt{}.generate(15, 40)};
        if (temperature < 30)
        {
            return EXIT_SUCCESS;
        }

        const char *iftttKey{std::getenv("IFTTT_KEY")};
        if (!iftttKey)
        {
            throw std::runtime_error("Env variable $IFTTT_KEY not provided");
        }
        std::string iftttPath{"/trigger/high_temperature/json/with/key/"};
        iftttPath.append(iftttKey);

        httplib::Client cli("http://maker.ifttt.com");
        const auto res = cli.Post(iftttPath);
        if (!res)
        {
            std::string err{"HTTP Error: " + httplib::to_string(res.error())};
            throw std::runtime_error(err);
        }

        std::cout << "Response status: " << res.value().status << '\n';
        std::cout << "Response body: " << res.value().body << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
