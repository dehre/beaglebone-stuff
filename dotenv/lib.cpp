#include "dotenv.hpp"
#include <cerrno>  // for errno
#include <cstring> // for strerror
#include <fstream>
#include <ios>
#include <map>
#include <string>

namespace dotenv
{
using map_t = std::map<const std::string, const std::string>;
static void parseline(const std::string &line, map_t &envs);

map_t parse()
{
    std::ifstream file(".env");
    if (file.fail())
    {
        std::string err{"Failed to open .env file: "};
        err.append(strerror(errno));
        throw std::ios::failure{err};
    }
    map_t envs{};
    std::string line{};
    while (!file.eof())
    {
        std::getline(file, line);
        parseline(line, envs);
    }
    return envs;
}

static void parseline(const std::string &line, map_t &envs)
{
    if (line.empty() || line.front() == '#')
    {
        return;
    }
    auto found_idx{line.find('=')};
    if (found_idx == std::string::npos)
    {
        return;
    }
    const auto env_name{line.substr(0, found_idx)};
    const auto env_value{line.substr(found_idx + 1)};
    envs.insert({env_name, env_value}); /* explicitly ignore insertion error */
}
}; // namespace dotenv
