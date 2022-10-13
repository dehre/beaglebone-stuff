#include <cstdlib>
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE
#include <httplib.h>
#include <iostream>
#include <string>

int main()
{
    const char *iftttKey{std::getenv("IFTTT_KEY")};
    if (!iftttKey)
    {
        std::cerr << "Env variable $IFTTT_KEY not provided\n";
        return EXIT_FAILURE;
    }

    std::string iftttPath{"/trigger/high_temperature/json/with/key/"};
    iftttPath.append(iftttKey);

    httplib::Client cli("http://maker.ifttt.com");
    if (const auto res = cli.Post(iftttPath))
    {
        std::cout << "Response status: " << res.value().status << '\n';
        std::cout << "Response body: " << res.value().body << '\n';
    }
    else
    {
        const auto err = res.error();
        std::cerr << "HTTP error: " << httplib::to_string(err) << '\n';
    }
    return EXIT_SUCCESS;
}
