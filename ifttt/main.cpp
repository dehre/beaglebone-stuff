#include "RandomInt.hpp"
#include "dotenv.hpp"
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <httplib.h>
#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
    try
    {
        int temperature{RandomInt{}.generate(15, 40)};
        if (temperature < 30)
        {
            std::cout << "Registered temperature: " << temperature << "°C (high_temperature event not triggered)\n";
            return EXIT_SUCCESS;
        }
        std::cout << "Registered temperature: " << temperature << "°C (high_temperature event triggered)\n";

        const auto envs{dotenv::parse()};
        auto ifttt_key_it{envs.find("IFTTT_KEY")};
        if (ifttt_key_it == envs.cend())
        {
            throw std::logic_error("Env variable IFTTT_KEY not provided");
        }
        std::string iftttPath{"/trigger/high_temperature/json/with/key/" + ifttt_key_it->second};

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
