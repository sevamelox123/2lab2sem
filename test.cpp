#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include <iomanip>
#include <sstream>
#include <vector>

class DateTimeParser {
private:
    static const std::map<char, std::pair<int, int>> formatSpecifiers;

    static std::vector<int> extractComponents(const std::string& input, const std::string& format) {
        std::vector<int> components(7, 0); // Y,y,m,d,H,M,S
        size_t inputPos = 0;
        size_t formatPos = 0;

        while (formatPos < format.size() && inputPos < input.size()) {
            if (format[formatPos] == '%') {
                if (formatPos + 1 < format.size()) {
                    char specifier = format[formatPos + 1];
                    if (formatSpecifiers.count(specifier)) {
                        const auto& spec = formatSpecifiers.at(specifier);
                        int value = 0;
                        int digitsRead = 0;
                        
                        while (digitsRead < spec.second && inputPos < input.size() && isdigit(input[inputPos])) {
                            value = value * 10 + (input[inputPos] - '0');
                            inputPos++;
                            digitsRead++;
                        }
                        
                        if (digitsRead != spec.second) {
                            throw std::runtime_error("Insufficient digits for format specifier");
                        }
                        
                        components[spec.first] = value;
                        formatPos += 2;
                        continue;
                    }
                }
            }
            
            if (input[inputPos] != format[formatPos]) {
                throw std::runtime_error("Format delimiter mismatch");
            }
            inputPos++;
            formatPos++;
        }

        return components;
    }

public:
    static std::tm parse(const std::string& input, const std::string& format) {
        auto components = extractComponents(input, format);
        std::tm result = {0};

        // Заполняем структуру tm
        if (components[0] != 0) { // 4-digit year
            result.tm_year = components[0] - 1900;
        } else if (components[1] != 0) { // 2-digit year
            result.tm_year = (components[1] >= 70 ? components[1] : components[1] + 100) - 1900;
        }

        result.tm_mon = components[2] - 1;
        result.tm_mday = components[3];
        result.tm_hour = components[4];
        result.tm_min = components[5];
        result.tm_sec = components[6];
        result.tm_isdst = -1;

        // Validate date/time
        if (mktime(&result) == -1) {
            throw std::runtime_error("Invalid date/time values");
        }

        return result;
    }
};

// Инициализация статической map
const std::map<char, std::pair<int, int>> DateTimeParser::formatSpecifiers = {
    {'Y', {0, 4}}, {'y', {1, 2}}, {'m', {2, 2}},
    {'d', {3, 2}}, {'H', {4, 2}}, {'M', {5, 2}},
    {'S', {6, 2}}
};

int main() {
    try {
        // Пример использования
        std::tm time1 = DateTimeParser::parse("2023-12-31 23:59:59", "%Y-%m-%d %H:%M:%S");
        std::tm time2 = DateTimeParser::parse("31.12.23", "%d.%m.%y");
        
        auto printTime = [](const std::tm& tm) {
            std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << std::endl;
        };

        std::cout << "Parsed time 1: ";
        printTime(time1);
        
        std::cout << "Parsed time 2: ";
        printTime(time2);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}