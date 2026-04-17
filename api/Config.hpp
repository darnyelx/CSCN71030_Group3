/**
 * @file Config.hpp
 * @brief Simple `KEY=value` loader for `config.env` (database URL and other settings).
 */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <unordered_map>

/**
 * @brief In-memory key/value store populated by `load()` from a path next to the executable.
 * @details Lines are parsed as `KEY=value`; blank lines and `#` comments are skipped. Keys and values
 *          are trimmed of leading/trailing whitespace.
 */
class Config {
public:
    /**
     * @brief Reads and parses a configuration file into the static map.
     * @param path Filesystem path to a `.env`-style file.
     * @return false if the file cannot be read; on failure previous entries may remain unchanged.
     */
    static bool load(const std::string& path);

    /**
     * @brief Returns a configuration value by key.
     * @param key Setting name as written in the file (after trimming).
     * @param fallback Returned when the key is missing or was never loaded.
     * @return Stored value or `fallback`.
     */
    static std::string get(const std::string& key, const std::string& fallback = "");

private:
    /**
     * @brief Removes ASCII whitespace from both ends of `s` in place.
     * @param s String to trim.
     */
    static void trim(std::string& s);

    /** @brief Parsed key/value pairs from the last successful `load`. */
    static std::unordered_map<std::string, std::string> values_;
};

#endif // CONFIG_HPP
