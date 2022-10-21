#pragma once

#include <map>
#include <string>

namespace dotenv
{

/*
 * The fn `parse` silently ignores all lines that don't contain the '=' character.
 * In case of duplicate variables, only the first declaration will be considered valid.
 */
std::map<const std::string, const std::string> parse();

}; // namespace dotenv
