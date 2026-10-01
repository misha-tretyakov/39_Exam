//
// Created by misha on 01.10.2026.
//

#ifndef INC_39_EXAM_HEADER_H
#define INC_39_EXAM_HEADER_H

#endif //INC_39_EXAM_HEADER_H

#include <string>
using namespace std;

class Task4 {
private:
    char words[50][30];
    char word[30];
    char hidden[30];
    char letters[27];

    int count;
    int num_letter;
    int attempts;
    int errors;
    int remaining;

    void writeWords();
    bool loadWords();
    void chooseWord();
    void printInfo();
    void inputLetter(const string& input);
    void endGame(time_t start);

public:
    void play();
};