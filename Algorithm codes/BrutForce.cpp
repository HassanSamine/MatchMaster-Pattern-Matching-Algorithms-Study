#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>

using namespace std;

vector<int> brute_force_match(string text, string pattern)
{
    vector<int> indices;
    int n = text.length(); 
    int m = pattern.length();

    for (int i = 0; i <= n - m; i++) 
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) // If j is equal to m that means the for loop didn't break for the whole length of the pattern which means we found a match.
        {
            indices.push_back(i); 
        }
    }
    return indices;
}

int main()
{
    string filename, text, pattern;
    cout << "Enter the filename: ";
    cin >> filename;

    // open the file for reading
    ifstream fin(filename);

    // read the entire contents of the file into the text string
    text.assign((istreambuf_iterator<char>(fin)), (istreambuf_iterator<char>())); //

    cout << "Enter the pattern: ";
    cin >> pattern;

    int num_runs = 1000;
    double total_duration = 0;
    vector<int> indices;
    auto start = chrono::high_resolution_clock::now(); // start the chrono
    for (int i = 0; i < num_runs; i++)
    {

        indices = brute_force_match(text, pattern);
    }
    auto stop = chrono::high_resolution_clock::now(); // stop the chrono
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
