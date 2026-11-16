#include <iostream>
#include <string>
#include <vector>
#include <cassert>

std::vector<std::string> extractErrors(const std::vector<std::string>& logs)
{
    std::vector<std::string> result = {};
    std::string error_flag = ("[ERROR] ");

    for (const std::string& s : logs)
    {
        std::size_t found = s.find(error_flag);
        if (found == 0)
        {
            result.push_back(s.substr(error_flag.length()));
        }
    }

    return result;
}

void testExtractErrors()
{
    assert((extractErrors({
        "[ERROR] Sensor timeout"
    }) == std::vector<std::string>{
        "Sensor timeout"
    }));

    assert((extractErrors({
        "[INFO] [ERROR] Hidden message"
    }) == std::vector<std::string>{}));

    assert((extractErrors({
        "[ERROR] "
    }) == std::vector<std::string>{""}));

    assert((extractErrors({}) ==
            std::vector<std::string>{}));
}

int main()
{
    const std::vector<std::string> logs = {
        "[INFO] System started",
        "[ERROR] Sensor timeout",
        "[WARN] Battery low",
        "[ERROR] I2C bus busy",
        "[ERROR] ",
        "Malformed log"
    };

    std::vector<std::string> errors =
        extractErrors(logs);

    for (const std::string& error : errors)
    {
        std::cout << "[" << error << "]\n";
    }

    testExtractErrors();

    return 0;
}