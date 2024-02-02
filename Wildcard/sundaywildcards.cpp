#include <iostream>
#include <string>
#include <vector>

std::vector<int> buildShiftTable(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> shiftTable(256, m + 1); // Initialize all entries with default shift value

    for (int i = 0; i < m; i++) {
        shiftTable[pattern[i]] = m - i; // Update shift value based on the rightmost occurrence of each character
    }

    return shiftTable;
}

bool sundayMatch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> shiftTable = buildShiftTable(pattern);
    int i = 0;

    while (i <= n - m) {
        int j = 0;
        while (j < m && (pattern[j] == text[i + j] || pattern[j] == '?')) {
            j++;
        }

        if (j == m) {
            return true; // Match found
        }

        if (i + m >= n) {
            break;
        }

        // Check if the next character in text matches the wildcard segment
        if (pattern[j] == '*') {
            int k = j + 1;
            while (k < m && pattern[k] == '*') {
                k++; // Skip consecutive '*' characters in the pattern
            }

            // Move the text pointer to the next position that matches the next segment
            while (i + m < n && text[i + m] != pattern[k]) {
                if (pattern[k] == '?') {
                    i++;
                } else {
                    i += shiftTable[text[i + m]];
                }
            }

            // Update the pattern pointer to the next segment
            j = k;
        }
        else {
            i += shiftTable[text[i + m]];
        }
    }

    return false; // No match found
}

int main() {
    std::string text = "the text you need deosnt exist World!";
    std::string pattern = "th?";
    bool isMatch = sundayMatch(text, pattern);
    std::cout << "Sunday Match: " << (isMatch ? "Found" : "Not Found") << std::endl;

    return 0;
}