#include <iostream>
#include <cstring>
#include <windows.h>
#include <unordered_map>
#include <string>

using namespace std;

const int maxWordCount = 50;
const int maxWordLenght = 10;
const int maxStringLenght = maxWordCount * (maxWordLenght + 1);
const int MAX_LENGTH = 1000;

void preprocessBadChar(const char* pattern, unordered_map<char, int>& badChar) {
    int patternLength = strlen(pattern);
    for (int i = 0; i < patternLength; i++) {
        badChar[pattern[i]] = i;
    }
}

void removeExtraSpaces(char* text)
{
    char cleanedText[maxStringLenght];
    int cleanedIndex = 0;
    bool lastCharWasSpace = true;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            if (!lastCharWasSpace)
            {
                cleanedText[cleanedIndex++] = ' ';
                lastCharWasSpace = true;
            }
        }
        else
        {
            cleanedText[cleanedIndex++] = text[i];
            lastCharWasSpace = false;

        }
    }
    cleanedText[cleanedIndex] = '\0';
    strcpy_s(text, maxStringLenght, cleanedText);

}

void removeExtraPunctuation(char* text)
{
    char cleanedText[maxStringLenght];
    int cleanedIndex = 0;
    bool lastCharWasPunct = false;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (ispunct(text[i]))
        {
            if (!lastCharWasPunct)
            {
                cleanedText[cleanedIndex++] = text[i];
                lastCharWasPunct = true;
            }
        }
        else
        {
            cleanedText[cleanedIndex++] = text[i];
            lastCharWasPunct = false;
        }
    }

    cleanedText[cleanedIndex] = '\0';
    strcpy_s(text, maxStringLenght, cleanedText);
}

void registerCorrection(char* text) {
    char cleanedText[maxStringLenght];
    int cleanedIndex = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (i == 0)
        {
            cleanedText[cleanedIndex++] = toupper(text[i]);
        }
        else
        {
            cleanedText[cleanedIndex++] = tolower(text[i]);
        }
    }

    cleanedText[cleanedIndex] = '\0';
    strcpy_s(text, maxStringLenght, cleanedText);
}

void printWordsWithoutDigits(char* text)
{
    char copyText[maxStringLenght];
    strcpy_s(copyText, maxStringLenght, text);

    char word[maxWordLenght];
    int wordIndex = 0;
    bool inWord = false;

    cout << "\n[3.3] Слова, не содержащие цифры:" << endl;

    for (int i = 0; copyText[i] != '\0'; i++) {
        if (copyText[i] == ' ') {
            if (inWord) {
                word[wordIndex] = '\0';
                bool hasDigit = false;

                for (int j = 0; word[j] != '\0'; j++) {
                    if (isdigit(word[j])) {
                        hasDigit = true;
                        break;
                    }
                }

                if (!hasDigit) {
                    cout << word << endl;
                }
                wordIndex = 0;
            }
            inWord = false;
        }
        else {
            if (wordIndex < maxWordLenght - 1) {
                word[wordIndex++] = copyText[i];
            }
            inWord = true;
        }
    }

    if (inWord) {
        word[wordIndex] = '\0';
        bool hasDigit = false;

        for (int j = 0; word[j] != '\0'; j++) {
            if (isdigit(word[j])) {
                hasDigit = true;
                break;
            }
        }

        if (!hasDigit) {
            cout << word << endl;
        }
    }
}

void countCharactersInWords(const char* text) {
    char copyText[maxStringLenght];
    strcpy_s(copyText, maxStringLenght, text);

    char word[maxWordLenght];
    int wordIndex = 0;
    bool inWord = false;

    cout << "[4.2] Количество символов в каждом слове:" << endl;


    for (int i = 0; copyText[i] != '\0'; i++) {
        if (copyText[i] == ' ') {
            if (inWord) {
                word[wordIndex] = '\0';
                cout << wordIndex << " символов в слове: " << word << endl;
                wordIndex = 0;
                inWord = false;
            }
        }
        else {
            if (wordIndex < maxStringLenght - 1) {
                word[wordIndex++] = copyText[i];
            }
            inWord = true;
        }
    }

    if (inWord) {
        word[wordIndex] = '\0';
        cout << wordIndex << " символов в слове: " << word << endl;
    }
}
void linearSearch(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    bool found = false;

    for (int i = 0; i <= textLength - patternLength; i++) {
        int j;
        for (j = 0; j < patternLength; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == patternLength) {
            cout << i << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "Не найдено";
    }
    cout << endl;
}

void boyerMoore(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    int badChar[256];

    for (int i = 0; i < 256; i++) {
        badChar[i] = -1;
    }
    for (int i = 0; i < patternLength; i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }

    int s = 0;
    bool found = false;

    while (s <= textLength - patternLength) {
        int j = patternLength - 1;

        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        if (j < 0) {
            cout << s << " ";
            found = true;
            s += (s + patternLength < textLength) ? patternLength - badChar[(unsigned char)text[s + patternLength]] : 1;
        }
        else {
            s += max(1, j - badChar[(unsigned char)text[s + j]]);
        }
    }
    if (!found) {
        cout << "Не найдено";
    }
    cout << endl;
}

int searchAllSubstrings(const char* text, const char* pattern, int* positions) {
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == m) {
            if (count < maxWordCount) {
                positions[count++] = i;
            }
        }
    }
    return count;
}

void KMPSearch(const string& text, const string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();
    int lps[MAX_LENGTH];

    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < patternLength) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    int j = 0;
    bool found = false;

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == patternLength) {
            cout << i - j << " ";
            found = true;
            j = lps[j - 1];
        }
        else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    if (!found) {
        cout << "Не найдено";
    }
    cout << endl;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "RU");
    char inputText[maxStringLenght];

    cout << "[1] Введите последовательность слов (от 1 до 50 слов, каждое до 10 символов и заканчивается точкой): ";
    cin.getline(inputText, maxStringLenght);

    removeExtraSpaces(inputText);
    removeExtraPunctuation(inputText);
    registerCorrection(inputText);

    cout << "\n[2] Отредактированный текст: " << inputText << endl;

    printWordsWithoutDigits(inputText);

    countCharactersInWords(inputText);

    string text, pattern;

    cout << "[5] Введите строку: ";
    getline(cin, text);
    cout << "Введите подстроку для поиска: ";
    getline(cin, pattern);

    cout << "Результаты линейного поиска: ";
    linearSearch(text, pattern);

    cout << "Результаты алгоритма Бойера-Мура: ";
    boyerMoore(text, pattern);

    cout << "Результаты алгоритма КМП: ";
    KMPSearch(text, pattern);
    return 0;
}