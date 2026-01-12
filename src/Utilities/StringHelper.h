#ifndef MOD_PYTHON_ENGINE_STRING_HELPER_H
#define MOD_PYTHON_ENGINE_STRING_HELPER_H

#include <string_view>
#include <string>
#include <vector>

namespace PyEng::Utilities
{
    /**
     * @brief Generic string manipulation utilities
     */
    class StringHelper
    {
    public:
        /**
         * @brief Trim whitespace from the left (start) of string
         */
        [[nodiscard]] static std::string_view TrimLeft(std::string_view str) noexcept
        {
            if (str.empty())
                return str;

            size_t start = str.find_first_not_of(" \t\r\n");
            if (start == std::string_view::npos)
                return "";

            return str.substr(start);
        }

        /**
         * @brief Trim whitespace from the right (end) of string
         */
        [[nodiscard]] static std::string_view TrimRight(std::string_view str) noexcept
        {
            if (str.empty())
                return str;

            size_t end = str.find_last_not_of(" \t\r\n");
            if (end == std::string_view::npos)
                return "";

            return str.substr(0, end + 1);
        }

        /**
         * @brief Trim whitespace from both sides of string
         */
        [[nodiscard]] static std::string_view Trim(std::string_view str) noexcept
        {
            return TrimRight(TrimLeft(str));
        }

        /**
         * @brief Remove matching quotes from string
         */
        [[nodiscard]] static std::string_view Unquote(std::string_view str) noexcept
        {
            if (str.length() < 2)
                return str;

            char first = str.front();
            char last = str.back();

            if ((first == '"' && last == '"') || (first == '\'' && last == '\''))
                return str.substr(1, str.length() - 2);

            return str;
        }

        /**
         * @brief Split string into lines with optional max length per line
         *
         * @param str String to split
         * @param maxLength Maximum line length (0 = unlimited)
         * @return Vector of trimmed, non-empty lines
         */
        [[nodiscard]] static std::vector<std::string> SplitLines(std::string_view str, size_t maxLength = 0)
        {
            std::vector<std::string> result;
            if (str.empty())
                return result;

            size_t pos = 0;

            while (pos < str.length())
            {
                size_t newlinePos = str.find('\n', pos);
                size_t lineEnd = (newlinePos != std::string_view::npos) ? newlinePos : str.length();

                std::string line(Trim(str.substr(pos, lineEnd - pos)));

                line = Truncate(line, maxLength);
                if (!line.empty())
                    result.push_back(std::move(line));

                pos = (newlinePos != std::string_view::npos) ? newlinePos + 1 : str.length();
            }

            return result;
        }

        /**
         * @brief Truncate string to maximum length with suffix
         */
        [[nodiscard]] static std::string Truncate(std::string_view str, size_t maxLength, std::string_view suffix = "...")
        {
            if (str.length() <= maxLength)
                return std::string(str);

            if (maxLength <= suffix.length())
                return std::string(str.substr(0, maxLength));

            return std::string(str.substr(0, maxLength - suffix.length())) + std::string(suffix);
        }

    private:
        StringHelper() = delete;
    };

} // namespace PyEng::Utilities

#endif // MOD_PYTHON_ENGINE_STRING_HELPER_H
