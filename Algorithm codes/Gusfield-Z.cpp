#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

vector<int> gusfield_z_match(string text, string pattern)
{
    string s = pattern + "#" + text;
    int n = s.length();
    int m = pattern.length();

    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++)
    {
        if (i <= r)
        {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            z[i]++;
        }
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }

    vector<int> indices;
    for (int i = 0; i < n; i++)
    {
        if (z[i] == m)
        {
            indices.push_back(i - m - 1);
        }
    }

    return indices;
}
int main()
{
    string filename, text, pattern;
    cout << "Enter the filename: ";
    getline(cin, filename);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    ifstream infile(filename);
    text.assign((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());

    int num_runs = 1000;
    double total_duration = 0;
    vector<int> indices;
    auto start = chrono::high_resolution_clock::now(); // Start the chrono
    for (int i = 0; i < num_runs; i++)
    {
        indices = gusfield_z_match(text, pattern);
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