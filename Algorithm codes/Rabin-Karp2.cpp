#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

const unsigned long long prime = 1000000007; // larger prime number used in Rabin-Karp algorithm

vector<int> rabin_karp_match(string text, string pattern, unsigned long long prime)
{
    int n = text.length();
    int m = pattern.length();
    unsigned long long pattern_hash = 0; // hash value of pattern
    unsigned long long text_hash = 0;    // hash value of current window of text
    unsigned long long h = 1;            // pow(prime, m-1)
    vector<int> indices;

    // calculate h
    for (int i = 0; i < m - 1; i++)
    {
        h = (h * prime) % prime;
    }

    // calculate the hash value of pattern and first window of text
    for (int i = 0; i < m; i++)
    {
        pattern_hash = (prime * pattern_hash + pattern[i]) % prime;
        text_hash = (prime * text_hash + text[i]) % prime;
    }

    // slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++)
    {
        // check if hash values match
        if (pattern_hash == text_hash)
        {
            int j;
            for (j = 0; j < m; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
            {
                indices.push_back(i);
            }
        }
        // calculate hash value for next window of text
        if (i < n - m)
        {
            text_hash = (prime * (text_hash - text[i] * h) + text[i + m]) % prime;
            // make sure text_hash is positive
            if (text_hash < 0)
            {
                text_hash += prime;
            }
        }
    }

    return indices;
}

int main()
{
    string filename, pattern_file;

    // prompt the user to enter the filename and read it from standard input
    cout << "Enter the filename: ";
    getline(cin, filename);

    // attempt to open the file with the given filename
    ifstream file(filename);
    if (!file)
    {
        cout << "Unable to open file." << endl;
        return 1;
    }

    // read the entire contents of the file into a string variable
    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // prompt the user to enter the pattern file name and read it from standard input
    cout << "Enter the pattern file name: ";
    getline(cin, pattern_file);

    // attempt to open the pattern file with the given filename
    ifstream pattern(pattern_file);
    if (!pattern)
    {
        cout << "Unable to open pattern file." << endl;
        return 1;
    }

    // read the pattern from the pattern file
    string pattern_string((istreambuf_iterator<char>(pattern)), istreambuf_iterator<char>());

    int num_runs = 1000;
    vector<int> indices;
    auto start = chrono::high_resolution_clock::now(); // start the chrono
    double total_duration = 0;

    // run the rabin_karp_match function num_runs times, and compute the total duration
    for (int i = 0; i < num_runs; i++)
    {
        indices = rabin_karp_match(text, pattern_string, prime);
    }

    auto stop = chrono::high_resolution_clock::now(); // stop the chrono
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    total_duration += duration.count();

    double avg_duration = total_duration / num_runs;

    // if the pattern was found, print the indices where it occurs
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

    // print the average time taken to run the function
    cout << "Average time taken by function over "
         << num_runs << " runs: "
         << avg_duration << " microseconds" << endl;

    // return 0 to indicate successful program execution
    return 0;
}
