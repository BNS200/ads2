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
using std::ios;
using std::fstream;


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
        outFile << randomNumber << " ";
    }

    if (!outFile.good()) {  
        return false;    
    }  

    return true;  
}  

bool isFileContainsSortedArray(const std::string &fileName) {
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    int previous, cur;
    if (!(file >> previous)) {
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

void initialization_ip_ms(int countFile, std::vector<int>& ip, std::vector<int>& ms) {    
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
    for (int i = 0; i < countFile - 1; ++i) {
        ms[i] = ip[i + 1] - ip[i] + ip0;
        ip[i] = ip[i + 1] + ip0;
    }
    ms[countFile - 1] = 0; 
    ip[countFile - 1] = 0; 
}

void fileSplitting(const std::string &fileName, std::vector<std::string>& fileNames, int countFile, std::vector<int>& ip, std::vector<int>& ms, int& L, int& countSequences) {
    
    std::ifstream inputFile(fileName);
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
            outputFile[i] << "\n";
            countSequences++;
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
        
        if (prev != INT_MIN && current >= prev) { 
            outputFile[i] << " ";
        }
           
        outputFile[i] << current;
        prev = current;
    }

    outputFile[i] << "\n";
    countSequences++;
    ms[i]--;
    
    for (int i = 0; i < countFile; ++i) {
        outputFile[i].close();
    }
}

bool mergeFiles(int countFile, std::vector<std::string>& fileNames, std::vector<int>& ms, std::vector<int>& ip, int& L, const std::string& fileNameResult, int& countSequences) {
    std::vector<std::fstream> mainFiles(countFile);

    for (int i = 0; i < countFile - 1; i++) {
        mainFiles[i].open(fileNames[i], std::fstream::in);
    }

    mainFiles[countFile - 1].open(fileNames[countFile - 1], std::fstream::out);

    for (int i = 0; i < countFile; i++) {
        if (!mainFiles[i].is_open()) {
            return false;
        }
    }

    while (L > 0) {
        int minMs = ip[0];
        for (int i = 0; i < countFile - 1; i++) {
            if (ms[i] <= minMs) {
                minMs = ms[i];
            }
        }

        ms[countFile - 1] += minMs;
        ip[countFile - 1] += minMs;

        for (int i = 0; i < countFile - 1; i++) {
            ms[i] -= minMs;
            ip[i] -= minMs;
        }

        while (ip[countFile - 2] > 0) {
            std::vector<bool> boolSequences(countFile - 1, false);
            std::vector<int> elemsOfSequences(countFile - 1);
            bool hasSequences = false;

            for (int i = 0; i < countFile - 1; i++) {
                if (ms[i] == 0) {
                    mainFiles[i] >> elemsOfSequences[i];
                    boolSequences[i] = true;
                    hasSequences = true;
                } else {
                    ms[i]--;
                    ip[i]--;
                }
            }

            while (hasSequences) {
                int minElemInSequence = INT_MAX;
                int posOfMin = -1;
                for (int i = 0; i < countFile - 1; i++) {
                    if (boolSequences[i]) {
                        if (minElemInSequence >= elemsOfSequences[i]) {
                            minElemInSequence = elemsOfSequences[i];
                            posOfMin = i;
                        }
                    }
                }
                if (posOfMin == -1) {
                    std::cerr << "error";
                    return false;
                }
                mainFiles[countFile - 1] << elemsOfSequences[posOfMin];
                if (mainFiles[posOfMin].peek() != '\n') {
                    mainFiles[posOfMin] >> elemsOfSequences[posOfMin];
                } else {
                    boolSequences[posOfMin] = false;
                    ip[posOfMin]--;
                }

                hasSequences = false;
                for (int i = 0; i < countFile - 1; i++) {
                    if (boolSequences[i]) {
                        hasSequences = true;
                    }
                }

                if (hasSequences) {
                    mainFiles[countFile - 1] << ' ';
                } else {
                    mainFiles[countFile - 1] << '\n';
                    countSequences--;
                    
                }
            }
            ip[countFile - 1]++;
        }

        L--;

        mainFiles[countFile - 2].close();
        mainFiles[countFile - 1].close();
        mainFiles[countFile - 1].open(fileNames[countFile - 1], std::fstream::in);
        mainFiles[countFile - 2].open(fileNames[countFile - 2], std::fstream::out);
        if (!mainFiles[countFile - 1].is_open() || !mainFiles[countFile - 2].is_open()) {
            return false;
        }

        for (int i = countFile - 1; i > 0; i--) {
            std::swap(mainFiles[i], mainFiles[i - 1]);
            std::swap(fileNames[i], fileNames[i - 1]);
            std::swap(ms[i], ms[i - 1]);
            std::swap(ip[i], ip[i - 1]);
        }
    }

    for (int i = 0; i < countFile; i++) {
        mainFiles[i].close();
    }

    std::ifstream inputFile(fileNames[0]);
    if (!inputFile.is_open()) {
        cerr << "error" << endl;
        return false;
    }
    std::ofstream sortedFile(fileNameResult);
    if (!sortedFile.is_open()) {
        cerr << "error" << endl;
        return false;
    }
    int elem;

    while (inputFile >> elem) {
        sortedFile << elem << " ";
    }

    return true;
}

void sortFile(const std::string &fileName, int countFile, const std::string &fileNameResult){
    
    std::vector<std::string> fileNames;
    std::vector<int> ip (countFile); 
    std::vector<int> ms (countFile);

    initialization_ip_ms(countFile, ip, ms);
    int countSequences;
    int L = 1;

    fileSplitting(fileName, fileNames, countFile, ip, ms, L, countSequences);
    mergeFiles(countFile, fileNames, ms, ip, L, fileNameResult, countSequences);
}

int createAndSortFile(const std::string &fileName, const int numbersCount, const int maxNumberValue, int countFile, const std::string &fileNameResult)
{
    //if (!createFileWithRandomNumbers(fileName, numbersCount, maxNumberValue)) {
      //  return -1;
    //}

    sortFile(fileName, countFile, fileNameResult);
    if (!isFileContainsSortedArray(fileNameResult)) {
        return -2;
    }

    return 1;
}

int main()
{
    std::string fileNameResult = "fileResult.txt";
    std::string fileName = "file.txt";
    const int numbersCount = 10;
    const int maxNumberValue = 100;

    
    int countFile;
    cout << "Count files: " << endl;
    cin >> countFile;

    for (int i = 0; i < 3; i++) {
        switch (createAndSortFile(fileName, numbersCount, maxNumberValue, countFile, fileNameResult)) {
            case 1:
                std::cout << "Test passed." << std::endl;
            break;

            //case -1:
                //std::cout << "Test failed: can't create file." << std::endl;
            //break;

            case -2:
                std::cout << "Test failed: file isn't sorted." << std::endl;
            break;
        }
    }

    return 0;
}