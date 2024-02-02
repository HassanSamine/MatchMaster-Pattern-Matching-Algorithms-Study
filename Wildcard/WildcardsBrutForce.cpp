#include <iostream>
#include <string>
#include <vector>

#include <iostream>
#include <string>
#include <vector>

bool bruteForceMatch(const std::string& text, const std::string& pattern)
{
    int n = text.length();
    int m = pattern.length();
    int i = 0;
    int j = 0;
    int asteriskPos = -1;
    int textPos = -1;

    while (i < n && j < m)
    {
        if (pattern[j] == '\\')
        {
            if (j + 1 < m && (pattern[j + 1] == '?' || pattern[j + 1] == '*'))
            {
                i++;
                j += 2;
            }
            else if (i < n && text[i] == pattern[j + 1])
            {
                i++;
                j += 2;
            }
            else
            {
                j += 2;
            }
        }
        else if (pattern[j] == '?')
        {
            i++;
            j++;
        }
        else if (pattern[j] == '*')
        {
            asteriskPos = j;
            textPos = i;
            j++;
        }
        else if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            if (asteriskPos != -1)
            {
                j = asteriskPos + 1;
                i = ++textPos;
            }
            else
            {
                i++;
                j = 0; 
            }
        }
    }

    while (j < m && pattern[j] == '*')
    {
        j++;
    }

    return j == m;
}


int main()
{
    std::string text = "the text you need doesn't exist World!";
    std::string pattern = "the*ex";
    bool isMatch = bruteForceMatch(text, pattern);
    std::cout << "Brute-force Match: " << (isMatch ? "Found" : "Not Found") << std::endl;

    return 0;
}
