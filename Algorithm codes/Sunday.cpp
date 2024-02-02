#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>

using namespace std;

vector<int> sunday_match(string text, string pattern)
{
    vector<int> indices;
    int n = text.length();
    int m = pattern.length();
    unordered_map<char, int> shift_table;
    for (int i = 0; i < m; i++)
    {
        shift_table[pattern[i]] = m - i;
    }
    int i = 0;
    while (i <= n - m)
    {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            indices.push_back(i);
        }
        if (i + m >= n)
        {
            break;
        }
        char c = text[i + m];
        if (shift_table.count(c) == 0)
        {
            i += m + 1;
        }
        else
        {
            i += shift_table[c];
        }
    }
    return indices;
}

int main()
{
    string file_name, pattern;

    cout << "Enter the file name: ";
    getline(cin, file_name);

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    ifstream file_stream(file_name);
    if (!file_stream.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(file_stream)),
                istreambuf_iterator<char>());
    file_stream.close();

    int iterations = 1000;
    vector<int> indices;
    double total_duration = 0.0;
    auto start = chrono::high_resolution_clock::now(); // start the chrono
    for (int i = 0; i < iterations; i++)
    {
        indices = sunday_match(text, pattern);
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
