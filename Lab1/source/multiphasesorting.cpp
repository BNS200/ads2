#include <iostream> 
#include <fstream>
#include <random>
#include <string>

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

