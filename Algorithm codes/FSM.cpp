#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

vector<int> fsm_match(string text, string pattern)
{
    int n = text.length();
    int m = pattern.length();

    vector<int> indices;

    vector<vector<int>> fsm(m + 1, vector<int>(256, 0));
    int j = 0;
    fsm[0][pattern[0]] = 1;
    for (int i = 1; i <= m; i++) //
    {
        for (int c = 0; c < 256; c++)
        {
            fsm[i][c] = fsm[j][c];
        }
        fsm[i][pattern[i]] = i + 1;
        if (i < m)
        {
            j = fsm[j][pattern[i]];
        }
    }

    int state = 0;
    for (int i = 0; i < n; i++)
    {
        state = fsm[state][text[i]];
        if (state == m)
        {
            indices.push_back(i - m + 1);
        }
    }

    return indices;
}
int main()
{
    string filename, text, pattern;
    cout << "Enter the filename: ";
    cin >> filename;

    // Open the file for reading
    ifstream fin(filename);

    // Read the entire contents of the file into the text string
    text.assign((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>()));

    cout << "Enter the pattern: ";
    cin >> pattern;

    int num_runs = 1000;
    double total_duration = 0;
    vector<int> indices;
    auto start = chrono::high_resolution_clock::now(); // Start the chrono
    for (int i = 0; i < num_runs; i++)
    {
        indices = fsm_match(text, pattern);
    }
    auto stop = chrono::high_resolution_clock::now(); // Stop the chrono
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    total_duration += duration.count();
    double avg_duration = total_duration / num_runs;

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

    cout << "Average time taken by function over "
         << num_runs << " runs: "
         << avg_duration << " microseconds" << endl;

    return 0;
}