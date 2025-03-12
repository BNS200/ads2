#include <iostream> 
#include <fstream>
#include <random>
#include <string>
#include <vector>


using std::cout;
using std::endl;



bool createFileWithRandomNumbers(const std::string &fileName, const int numbersCount, const int maxNumberValue){ 
    if (numbersCount <= 0 || maxNumberValue <= 0){ 
        return 0;
    }

    std::ofstream outFile(fileName);
    if (!outFile.is_open())
        return false;

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, maxNumberValue);
    
    for (int i = 0; i < numbersCount; i++){
        int randomNumber = distribution(generator);
        outFile << randomNumber << "\n";
    }

    if (!outFile.good()){
        outFile.close();
        return false;    
    }

    outFile.close();
    return true;
}

bool isFileSorted(const std::string &fileName){
    
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    int previous,current;
    if (!file >> previous){
        cout << "file read error" << endl;
        return false;
    }

    while(file >> current){
        if (previous > current){
            return false;
        }

        previous = current;
    }
    return true;
    
}
void splitIntoSequences(std::string &inputFile, std::string &outputFile){
    
    std::ifstream file1(inputFile);
    if(!file1.is_open())
        cout << "error" << endl;

    std::ofstream file2(outputFile);
    if(!file2.is_open())
        cout << "error" << endl;

    int previous = INT_MIN;
    int current;
    std::vector<int> sequence;

    while (input >> current){
        if (sequence.empty() || current >= previous){
            sequence.push_back(current);
        } else {
            for (size_t i = 0; i < sequence.size(); ++i){
                file2 << sequence[i];
                if (i != sequence.size() - 1) {
                    output << " ";
                }
            }
            file2 << "\n";
            sequence.clear();
            sequence.push_back(current);
            } 
            previous = current;
    }
        
    if (!sequence.empty()){
        for (size_t i = 0; i < sequence.size(); ++i){
            file2 << sequence[i];
            if (i != sequence.size() - 1){
                file2 << " "; 
            }
        }
        file2 << "\n";
    }

    file1.close();
    file2.close();
}



