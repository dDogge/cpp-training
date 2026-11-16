
#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// TODO 1:
// Returnera alla felmeddelanden utan "[ERROR] ".
// Endast rader som BÖRJAR med prefixet får tas med.
std::vector<std::string> extractErrors(const std::vector<std::string>& logs)
{
    std::vector<std::string> result;
    const std::string prefix = "[ERROR] ";

    for (const std::string& log : logs)
    {
        if (log.find(prefix) == 0)
        {
            result.push_back(log.substr(prefix.size()));
        }
    }

    return result;
}

// TODO 2:
// Extrahera första mellanslagsavgränsade ordet
// som innehåller '@'.
// Returnera "" om det inte finns något '@'.
std::string extractEmail(const std::string& text)
{
    if (text.find('@') == std::string::npos) 
    {
        return "";
    }

    std::size_t at = text.find('@');

    std::size_t start = text.rfind(' ', at);

    if (start == std::string::npos) 
    {
        start = 0;
    } 
    else
    {
        start++;
    } 

    std::size_t end = text.find(' ', at);

    if (end == std::string::npos) 
    {
        end = text.length();
    }

    return text.substr(start, end - start);
}

// TODO 3:
// Infoga '\n' före varje stor bokstav,
// förutom den allra första.
std::string splitCamelCase(const std::string& text)
{
    std::string result = "";

    for (std::size_t i = 0; i < text.length(); ++i) 
    {
        char c = text[i];

        if ((i != 0) && std::isupper(static_cast<unsigned char>(c)))
        {
            result.push_back('\n');
        }

        result.push_back(c);
    }

    return result;
}

class LogAnalyzer
{
public:
    explicit LogAnalyzer(std::vector<std::string> lines) : lines_(std::move(lines))
    {
        std::cout << "Analyzer created\n";
    }

    ~LogAnalyzer()
    {
        std::cout << "Analyzer destroyed\n";
    }

    // TODO 4:
    // Extrahera fel, sortera och ta bort dubletter.
    std::vector<std::string> uniqueErrors() const
    {
        std::vector<std::string> result = extractErrors(lines_);

        std::sort(result.begin(), result.end());

        auto new_end = std::unique(result.begin(), result.end());

        result.erase(new_end, result.end());

        return result;
    }

    // TODO 5:
    // Använd std::count_if och en lambda.
    // Räkna unika fel som är LÄNGRE än threshold.
    std::size_t countLongErrors(std::size_t threshold) const
    {
        std::vector<std::string> errors = uniqueErrors();

        return static_cast<std::size_t>(
            std::count_if(errors.begin(), errors.end(), [threshold](const std::string& error)
            {
                return error.size() > threshold;
            })
        );
    }

    // TODO 6:
    // Hitta och returnera e-postadressen i loggarna.
    std::string supportEmail() const
    {
        std::string result = "";

        for (const std::string& line : lines_) 
        {
            if (result.empty())
            {
                result.append(extractEmail(line));    
            }
            else 
            {
                break;
            }
        }

        return result;
    }

private:
    std::vector<std::string> lines_;
};

int main()
{
    std::vector<std::string> logs = {
        "[INFO] SystemReady",
        "[ERROR] SensorTimeout",
        "[WARN] BatteryLow",
        "[ERROR] FanMotorOverheat",
        "[ERROR] SensorTimeout",
        "[INFO] Contact support@embedded.dev for help",
        "[INFO] Another [ERROR] FakeError",
        "[ERROR] "
    };

    {
        auto analyzer =
            std::make_unique<LogAnalyzer>(std::move(logs));

        const auto errors = analyzer->uniqueErrors();

        std::cout << "Unique errors ("
                  << errors.size() << "):\n";

        for (const std::string& error : errors)
        {
            std::cout << "[" << error << "]\n";
        }

        std::cout << "Long errors (> 13): "
                  << analyzer->countLongErrors(13)
                  << "\n";

        std::cout << "Support email: "
                  << analyzer->supportEmail()
                  << "\n";

        std::cout << "Split:\n"
                  << splitCamelCase("SensorTimeout")
                  << "\n";
    }

    std::cout << "Done\n";
}
