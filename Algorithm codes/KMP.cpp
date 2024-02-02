#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

vector<int> kmp_match(string text, string pattern)
{
    vector<int> indices;
    int n = text.length();
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    //We make the lps table
    while (i < m)
    {
        if (pattern[i] == pattern[len]) //If we find a match we increment len put lps(i) equal to len and increment i and check again 
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    i = 0;
    int j = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == m)
        {
            indices.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return indices;
}

int main()
{
    string file_name, pattern;
    cout << "Enter the file name: ";
    cin >> file_name;
    cin.ignore(); // Ignore the newline character left in the input buffer
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    ifstream file(file_name);
    if (!file)
    {
        cerr << "Unable to open file!" << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    int iterations = 1000;

    vector<int> indices;
    double total_duration = 0.0;
    auto start = chrono::high_resolution_clock::now(); // start the chrono
    for (int i = 0; i < iterations; i++)
    {
        indices = kmp_match(text, pattern);
    }
    auto stop = chrono::high_resolution_clock::now(); // stop the chrono
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    total_duration += duration.count();

    if (indices.size() > 0)
    {
        cout << "Pattern found at indices: ";
        for (int i = 0; i < indices.size(); i++)
        {
            cout << indices[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Pattern not found" << endl;
    }
    double avg_duration = total_duration / iterations;
    cout << "Average time taken by function: "
         << avg_duration << " microseconds" << endl;

    return 0;
}