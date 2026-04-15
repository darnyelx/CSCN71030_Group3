#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <unordered_map>

class Config {
public:
    // Load config file from path
    static bool load(const std::string& path);

    // Get value by key with optional fallback
    static std::string get(const std::string& key, const std::string& fallback = "");

private:
    // Helper to trim whitespace
    static void trim(std::string& s);

    // Storage for key-value pairs
    static std::unordered_map<std::string, std::string> values_;
};

#endif // CONFIG_HPP