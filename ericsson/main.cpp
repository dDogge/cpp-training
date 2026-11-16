#include <iostream>
#include <string>
#include <cctype>

std::string splitCamelCase(const std::string& text)
{
    std::string result;

    for (std::size_t i = 0; i < text.length(); ++i)
    {
        char c = text[i];

        if (i > 0 &&
            std::isupper(static_cast<unsigned char>(c)))
        {
            result.push_back('\n');
        }

        result.push_back(c);
    }

    return result;
}

#include <string>

std::string extractEmail(const std::string& text)
{
    // Hitta @
    std::size_t at = text.find('@');

    if (at == std::string::npos)
    {
        return "";
    }

    // Hitta mellanslaget före @
    std::size_t start = text.rfind(' ', at);

    if (start == std::string::npos)
    {
        start = 0;
    }
    else
    {
        start++;
    }

    // Hitta mellanslaget efter @
    std::size_t end = text.find(' ', at);

    if (end == std::string::npos)
    {
        end = text.length();
    }

    // Plocka ut e-postadressen
    return text.substr(start, end - start);
}

int main()
{
    std::string camel = "YesYouAre";

    std::string sentence =
        "Please contact us lol@lolmail.com for further information";

    std::cout << "CamelCase:\n";
    std::cout << splitCamelCase(camel) << "\n\n";

    std::cout << "Email:\n";
    std::cout << extractEmail(sentence) << "\n";

    return 0;
}