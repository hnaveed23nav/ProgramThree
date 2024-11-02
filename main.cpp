/*
   Program Three: HANGMAN
*/

#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class SecretWord {
private:
    vector<char> letters;
    vector<char> progress;

public:
    SecretWord(const string& input) {
        for (char c : input) {
            letters.push_back(c);
            progress.push_back('_');
        }
    }

    vector<char> getProgress() const {
        return progress;
    }

    void revealLetter(char ch) {
        for (size_t i = 0; i < letters.size(); ++i) {
            if (letters[i] == ch) {
                progress[i] = ch;
            }
        }
    }

    bool containsLetter(char ch) const {
        for (char c : letters) {
            if (c == ch) {
                return true;
            }
        }
        return false;
    }

    bool isComplete() const {
        return letters == progress;
    }
};

class HangmanState {
private:
    vector<string> stages = {"PLATFORM", "HEAD", "BODY", "LEFT_ARM", "RIGHT_ARM", "LEFT_LEG", "RIGHT_LEG"};
    int currentStage = 0;

public:
    string getCurrentStage() const {
        if (currentStage > 0) {
            return stages[currentStage - 1];
        }
        return "START";
    }

    void advanceStage() {
        if (currentStage < stages.size()) {
            currentStage++;
        }
    }

    bool isLost() const {
        return currentStage >= stages.size();
    }
};

class AttemptedLetters {
private:
    vector<char> attempts;

public:
    vector<char> getAttempts() const {
        return attempts;
    }

    void recordAttempt(char ch) {
        attempts.push_back(ch);
    }
};

int main() {
    string mysteryWord;
    cout << "Enter the secret word for Hangman: ";
    cin >> mysteryWord;

    for (char &c : mysteryWord) c = toupper(c);

    SecretWord word(mysteryWord);
    AttemptedLetters attemptedLetters;
    HangmanState hangman;
    char guess;

    do {
        cout << "\nCurrent state: " << hangman.getCurrentStage() << endl;
        cout << "Attempted letters: ";
        for (char c : attemptedLetters.getAttempts()) {
            cout << c << " ";
        }
        cout << "\nWord so far: ";
        for (char c : word.getProgress()) {
            cout << c << " ";
        }
        cout << "\nEnter a letter to guess: ";
        cin >> guess;
        guess = toupper(guess);

        if (word.containsLetter(guess)) {
            word.revealLetter(guess);
        } else {
            attemptedLetters.recordAttempt(guess);
            hangman.advanceStage();
        }
    } while (!hangman.isLost() && !word.isComplete());

    if (hangman.isLost()) {
        cout << "\nGame over! You've been hung." << endl;
        cout << "The correct word was: " << mysteryWord << endl;
    } else {
        cout << "\nCongratulations! You guessed the word: ";
        for (char c : word.getProgress()) {
            cout << c;
        }
        cout << endl;
    }

    return 0;
}
