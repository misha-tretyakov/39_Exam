//
// Created by misha on 01.10.2026.
//

#include "header.h"
#include <iostream>
#include <fstream>

using namespace std;


void Task4::writeWords() {
    ofstream file("words.txt", ios::out | ios::trunc);

    if (file.is_open()) {
        file << "dbu\neph\nipvtf\nbqqmf\nubcmf";
        cout << "Words installed" << endl;
        file.close();
    }
}

bool Task4::loadWords() {
    ifstream file("words.txt");
    count = 0;

    while (count < 50 && file.getline(words[count], 30)) {
        if (words[count][0] != '\0') {
            count++;
        }
    }

    return count > 0;
}

void Task4::chooseWord() {
    int num_word = rand() % count;
    num_letter = 0;

    while (words[num_word][num_letter] != '\0') {
        word[num_letter] = words[num_word][num_letter] - 1;
        hidden[num_letter] = '_';
        num_letter++;
    }

    word[num_letter] = '\0';
    hidden[num_letter] = '\0';

    letters[0] = '\0';
    attempts = 0;
    errors = 0;
    remaining = num_letter;
}

void Task4::printInfo() {
    cout << "\nWord: " << hidden << endl;
    cout << "Mistakes out of 6: " << errors << endl;
    cout << "Letters used: " << letters << endl;
}

void Task4::inputLetter(const string& input) {
    if (input.length() != 1) {
        cout << "only one letter!" << endl;
        return;
    }

    char letter = input[0];

    if (letter < 'a' || letter > 'z') {
        cout << "lowercase only" << endl;
        return;
    }

    for (int i = 0; i < attempts; i++) {
        if (letters[i] == letter) {
            cout << "this letter was already used!" << endl;
            return;
        }
    }

    letters[attempts] = letter;
    attempts++;
    letters[attempts] = '\0';

    bool found = false;

    for (int i = 0; i < num_letter; i++) {
        if (word[i] == letter) {
            hidden[i] = letter;
            remaining--;
            found = true;
        }
    }

    if (!found) {
        errors++;
    }
}

void Task4::endGame(time_t start) {
    if (remaining == 0) {
        cout << "You won!" << endl;
    }
    else if (errors == 6) {
        cout << "You lost!" << endl;
    }
    else {
        cout << "Smth went wrong..." << endl;
    }

    cout << "Time: " << time(0) - start << " sec" << endl;
    cout << "Attempts: " << attempts << endl;
    cout << "Word: " << word << endl;
    cout << "Letters used: " << letters << endl;
}

void Task4::play() {

    writeWords();

    if (!loadWords()) {
        cout << "no words found" << endl;
        return;
    }

    cout << "words counted: " << count << endl;

    srand(time(0));
    chooseWord();

    time_t start = time(0);

    while (errors < 6 && remaining > 0) {
        printInfo();
        cout << "Enter letter >>>   ";

        string input;

        if (!(cin >> input)) {
            break;
        }

        inputLetter(input);
    }

    endGame(start);
}