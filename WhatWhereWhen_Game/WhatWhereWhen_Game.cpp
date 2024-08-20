#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>

bool lookForSector(int offset, int& currentSector, std::vector<bool>& usedSectors, int& newSector) {
    newSector = (currentSector - 1 + offset) % 13;
    int originalSector = newSector;

    while (usedSectors[newSector]) {
        newSector = (newSector + 1) % 13;
        if (newSector == originalSector) {
            return false;
        }
    }

    usedSectors[newSector] = true;
    currentSector = newSector;
    return  true;
}

int main()
{
    std::vector<bool> usedSectors(13, false);
    int currentSector = 0;
    int offset = 0;
    int newSector = 0;

    int playerScore = 0;
    int audienceScore = 0;

    std::cout << "Welcome to the game what? where? when?" << std::endl;


    while (playerScore < 6 && audienceScore < 6) {
        std::cout << "Please spin the top!And enter nums from 1 to 13" << std::endl;
        std::cin >> offset;
        std::cin.ignore();


        lookForSector(offset, currentSector, usedSectors, newSector);

        std::string questionFileName = "WhatWhere/question" + std::to_string(newSector) + ".txt";
        std::string answerFileName = "WhatWhere/answer" + std::to_string(newSector) + ".txt";



        std::ifstream questionFile(questionFileName);
        std::ifstream answerFile(answerFileName);
        if (!questionFile.is_open() || !answerFile.is_open()) {
            std::cout << "Error opening question or answer file" << std::endl;
            return 1;
        }


        std::string question;
        std::string correctAnswer;
        std::getline(questionFile, question);
        std::getline(answerFile, correctAnswer);

        std::cout << "Question: " << question << std::endl;
        std::string playerAnswer;
        std::getline(std::cin, playerAnswer);

        if (playerAnswer == correctAnswer) {
            playerScore++;
            std::cout << "Correct!" << std::endl;
        }
        else {
            audienceScore++;
            std::cout << "Incorrect. The correct answer was: " << correctAnswer << std::endl;
        }

    }

    if (playerScore == 6) {
        std::cout << "Congratulations, player win!" << std::endl;
    }
    else {
        std::cout << "Sorry, but audience win!" << std::endl;
    }

    return  0;
}
