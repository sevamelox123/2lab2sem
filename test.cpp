#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>

class DateTimeParser {
private:
    static std::map<char, int> formatComponents;

    static void initializeFormatComponents() {
        formatComponents['Y'] = 0; // год (4 цифры)
        formatComponents['y'] = 1; // год (2 цифры)
        formatComponents['m'] = 2; // месяц (01-12)
        formatComponents['d'] = 3; // день (01-31)
        formatComponents['H'] = 4; // час (00-23)
        formatComponents['M'] = 5; // минуты (00-59)
        formatComponents['S'] = 6; // секунды (00-59)
    }

    static std::vector<int> extractDateTimeComponents(const std::string& input, const std::string& format) {
        std::vector<int> components(7, 0); // [год4, год2, месяц, день, час, минуты, секунды]

        size_t inputPos = 0;
        size_t formatPos = 0;

        while (formatPos < format.size() && inputPos < input.size()) {
            if (format[formatPos] == '%') {
                if (formatPos + 1 < format.size()) {
                    char specifier = format[formatPos + 1];
                    if (formatComponents.find(specifier) != formatComponents.end()) {
                        // Для числовых значений
                        if (isdigit(input[inputPos])) {
                            int value = 0;
                            while (inputPos < input.size() && isdigit(input[inputPos])) {
                                value = value * 10 + (input[inputPos] - '0');
                                inputPos++;
                            }
                            components[formatComponents[specifier]] = value;
                        }
                        formatPos += 2;
                        continue;
                    }
                }
            }
            // Пропускаем разделители
            if (input[inputPos] == format[formatPos]) {
                inputPos++;
                formatPos++;
            } else {
                throw std::runtime_error("Несоответствие формата");
            }
        }

        return components;
    }

public:
    static std::tm parseDateTime(const std::string& input, const std::string& format) {
        initializeFormatComponents();
        std::tm timeStruct = {0};
        auto components = extractDateTimeComponents(input, format);

        // Заполняем структуру tm
        if (components[0] != 0) { // 4-значный год
            timeStruct.tm_year = components[0] - 1900;
        } else if (components[1] != 0) { // 2-значный год
            timeStruct.tm_year = (components[1] >= 70 ? components[1] : components[1] + 100) + 1900 - 1900;
        }

        timeStruct.tm_mon = components[2] - 1;  // месяцы 0-11
        timeStruct.tm_mday = components[3];
        timeStruct.tm_hour = components[4];
        timeStruct.tm_min = components[5];
        timeStruct.tm_sec = components[6];
        timeStruct.tm_isdst = -1; // автоматическое определение летнего времени

        // Проверка корректности
        mktime(&timeStruct);
        if (timeStruct.tm_year < 0 || 
            timeStruct.tm_mon < 0 || timeStruct.tm_mon > 11 ||
            timeStruct.tm_mday < 1 || timeStruct.tm_mday > 31 ||
            timeStruct.tm_hour < 0 || timeStruct.tm_hour > 23 ||
            timeStruct.tm_min < 0 || timeStruct.tm_min > 59 ||
            timeStruct.tm_sec < 0 || timeStruct.tm_sec > 59) {
            throw std::runtime_error("Некорректная дата/время");
        }

        return timeStruct;
    }
};

// Инициализация статического члена
std::map<char, int> DateTimeParser::formatComponents;

int main() {
    try {
        // Примеры использования
        std::tm time1 = DateTimeParser::parseDateTime("2023-12-31 23:59:59", "%Y-%m-%d %H:%M:%S");
        std::tm time2 = DateTimeParser::parseDateTime("31.12.23 23:59", "%d.%m.%y %H:%M");
        std::tm time3 = DateTimeParser::parseDateTime("12/31/2023", "%m/%d/%Y");

        // Вывод результатов
        auto printTime = [](const std::tm& tm) {
            std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << std::endl;
        };

        printTime(time1);
        printTime(time2);
        printTime(time3);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}