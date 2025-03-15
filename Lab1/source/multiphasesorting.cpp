#include <iostream> 
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <climits>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

const int endElement = -1;
int L = 1;

bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue) { 
    if (numbersCount <= 0 || maxNumberValue <= 0) { 
        return false;
    }

    std::ofstream outFile(fileName);
    if (!outFile.is_open())
        return false;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, maxNumberValue);
    
    for (int i = 0; i < numbersCount; i++) {
        int randomNumber = distribution(generator);
        outFile << randomNumber << "\n";
    }

    if (!outFile.good()) {
        outFile.close();
        return false;    
    }

    outFile.close();
    return true;
}

bool isFileSorted(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    int previous, cur;
    if (!file >> previous) {
        cerr << "file read error" << endl;
        return false;
    }

    while (file >> cur) {
        if (previous > cur) {
            return false;
        }
        previous = cur;
    }
    return true;
}

std::string nameFile(int i) {
    return "f" + std::to_string(i) + ".txt";
}

void initialization_ip_ms(std::vector<int>& ip, std::vector<int>& ms, int countFile) {
    for (int i = 0; i < countFile - 1; i++) {
        ip[i] = 1;
        ms[i] = 1;
    }
    ip[countFile - 1] = 0;
    ms[countFile - 1] = 0;
}

void recalculate_ip_ms(std::vector<int>& ip, std::vector<int>& ms, int& L, int countFile) {
    L++; 
    int ip0 = ip[0];
    for (int k = 0; k < countFile - 1; ++k) {
        ms[k] = ip[k + 1] - ip[k] + ip0;
        ip[k] = ip[k + 1] + ip0;
    }
    ms[countFile - 1] = 0; 
    ip[countFile - 1] = 0; 
}

void fileSplitting(const std::string &mainFile, int countFile, std::vector<int>& ms, std::vector<int>& ip, std::vector<std::string>& fileNames, int& L) {
    std::ifstream inputFile(mainFile);
    if (!inputFile.is_open()) {
        cerr << "error" << endl;
        return;
    }
    std::vector<std::ofstream> outputFile(countFile);
    
    for (int i = 0; i < countFile; ++i) {
        std::string fileName = nameFile(i);
        fileNames.push_back(fileName);
        outputFile[i].open(fileName);
        if (!outputFile[i].is_open()) {
            cerr << "error" << endl;
            return;
        }
    }
    
    int i = 0;
    int prev = INT_MIN;
    int current;

    while (inputFile >> current) {
        if (current < prev) {
            outputFile[i] << endElement << " ";
            ms[i]--;
            if (i + 1 < ms.size() && ms[i] < ms[i + 1]) {
                i++;
            } else if (ms[i] == 0) {
                recalculate_ip_ms(ip, ms, L, countFile);
                i = 0;
            } else {
                i = 0;
            }
        }       
        outputFile[i] << current << " ";
        prev = current;
    }

    outputFile[i] << endElement << " ";

    for (int i = 0; i < countFile; ++i) {
        outputFile[i].close();
    }

    for (int i = 0; i < fileNames.size(); ++i) {
        cout << "file:" << fileNames[i] << endl;
    }
}

/*void mergeFiles(vector<string>& fileNames, vector<int>& ms, vector<int>& ip, int& L, int countFile) {
    while (L > 0) {
        vector<ifstream> inputFiles(countFile - 1);
        for (int i = 0; i < countFile - 1; ++i) {
            inputFiles[i].open(fileNames[i]);
            if (!inputFiles[i].is_open()) {
                cerr << "error" << fileNames[i] << endl;
                return;
            }
        }
        ofstream outputFile(fileNames[countFile - 1]);
        if (!outputFile.is_open()) {
            cerr << "error"<< endl;
            return;
        }

        while (true) {
            bool allMsZero = true;
            for (int i = 0; i < countFile - 1; ++i) {
                if (ms[i] > 0) {
                    ms[i]--;
                    ms[countFile - 1]++;
                    allMsZero = false;
                }
            }

            for (int i = 0; i < countFile - 1; ++i) {
                if (ms[i] == 0) {
                    int value;
                    while (inputFiles[i] >> value && value != -1) {
                        outputFile << value << " ";
                    }
                    outputFile << endElement << " ";
                    ms[i]--;
                }
            }

            if (allMsZero) {
                break;
            }
        }

        for (int i = 0; i < countFile - 1; ++i) {
            inputFiles[i].close();
        }
        outputFile.close();

        L--;
        string lastFileName = fileNames[countFile - 1];
        for (int i = countFile - 1; i > 0; --i) {
            fileNames[i] = fileNames[i - 1];
        }
        fileNames[0] = lastFileName;

        int lastIp = ip[countFile - 1];
        int lastMs = ms[countFile - 1];
        for (int i = countFile - 1; i > 0; --i) {
            ip[i] = ip[i - 1];
            ms[i] = ms[i - 1];
        }
        ip[0] = lastIp;
        ms[0] = lastMs;
    }
}*/

int main() {
    int countFile;
    cout << "Count:" << endl;
    cin >> countFile;

    std::string mainFile = "mainFile.txt";
    createFileWithRandomNumbers(mainFile, 10, 50);
    
    std::vector<std::string> fileNames;

    std::vector<int> ms(countFile);
    std::vector<int> ip(countFile);
    initialization_ip_ms(ip, ms, countFile);

    fileSplitting(mainFile, countFile, ms, ip, fileNames, L);
    //mergeFiles(fileNames, ms, ip, L, countFile);

    return 0;
}