#include "Config.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>

std::unordered_map<std::string, std::string> Config::values_;

bool Config::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        trim(line);

        if (line.empty() || line[0] == '#') {
            continue;
        }

        const auto pos = line.find('=');
        if (pos == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        trim(key);
        trim(value);

        values_[key] = value;

#ifdef _WIN32
        _putenv_s(key.c_str(), value.c_str());
#else
        setenv(key.c_str(), value.c_str(), 1);
#endif
    }

    return true;
}

std::string Config::get(const std::string& key, const std::string& fallback) {
    const auto it = values_.find(key);
    return it != values_.end() ? it->second : fallback;
}

void Config::trim(std::string& s) {
    auto notSpace = [](unsigned char ch) {
        return !std::isspace(ch);
    };

    s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
    s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
}