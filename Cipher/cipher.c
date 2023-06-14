#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

int main(int argc, char *argv[])
{
    // The first command line argument is the user
    const char* user = argv[1];

    // The second command line argument is the option (either "0" encrypt or "1" decrypt)
    int option = atoi(argv[2]);
    // The third command line argument is the key index (1-16)
    int keyIndex = atoi(argv[3]);
    
    if (!isKeyAvailableForUser(user, keyIndex) || keyIndex < 1 || keyIndex > sizeof(keys)/sizeof(keys[0])){
        printf("your character does not know that language.\n");
        return -1;
    }
    const char* key = keys[keyIndex - 1];

    // Determine the size of the alphabet
    int alphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);


    // Combine all remaining command line arguments into a single string message
    int totalLength = 0;
    for (int i = 3; i < argc; i++) {
        totalLength += strlen(argv[i]) + (i < argc - 1);  // Add space for all but last word
    }

    // Create a Variable Length Array (VLA) for the message
    char message[totalLength + 1];  // +1 for the null terminator
    message[0] = '\0';  // Initialize the string


    // Concatenate arguments into message
    for (int i = 3; i < argc; i++) {
        strcat(message, argv[i]);
    
        if (i < argc - 1)  strcat(message, " ");  // Add space between words
    }

    //printf("option: %i\nkey: %s\nmessage: %s\n", option, key, message);

    int msgsize = strlen(message);
    TranslateMessage(message, totalLength, option, key);
    
    printf("translated message: %s\n", message);

    return 0;
}

int isKeyAvailableForUser(const char *username, int keyIndex) {
    // Look for the user in the users array
    for (int i = 0; i < sizeof(users)/sizeof(users[0]); i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Found the user, check if the key is available
            for (int j = 0; j < sizeof(users[i].availableKeys)/sizeof(users[i].availableKeys[0]); j++) {
                if (users[i].availableKeys[j] == 0) break;  // End of list
                if (users[i].availableKeys[j] == keyIndex) return 1;  // Key is available
            }
        }
    }
    
    // User not found or key not available
    return 0;
}

// Function to encrypt or decrypt a message
char * TranslateMessage(char* msg, int length, int option, const char* key) {
    char * translatedMsg = msg;
    int shiftcount = 0;
    int keyIndex = 0;
    int keyLength = strlen(key);
    const char *currentAlphabet;  // Variable to hold the current alphabet (lowercase or uppercase)
    int currentAlphabetSize = 0; // Variable to hold the current alphabet size

    // Iterate over the message
    for (int i = 0; i < length; i++) {
        // If the current character is a space, skip it
        if (msg[i] == ' ')  continue;

        // Determine which alphabet to use based on the case of the current character
        if (msg[i] >= 'a' && msg[i] <= 'z') {
            currentAlphabet = alphabet;
            currentAlphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);
        }
        else if (msg[i] >= 'A' && msg[i] <= 'Z') {
            currentAlphabet = upperAlphabet;
            currentAlphabetSize = sizeof(upperAlphabet) / sizeof(upperAlphabet[0]);
        }
        else continue;

        shiftcount = 0;

        // Find the shift count for the current character
        for (int j = 0; j < currentAlphabetSize - 1; j++) { // Subtract one because of null character at the end
            shiftcount++;
            if (currentAlphabet[j] == key[keyIndex]) break;
        }

        // Increment key index for the next character
        if (++keyIndex == keyLength) keyIndex = 0;

        // Encrypt or decrypt the current character based on the option
        if (option == 0)
            translatedMsg[i] = (i & 1) ? ShiftChar(msg[i], shiftcount, 'l', currentAlphabet) : ShiftChar(msg[i], shiftcount, 'r', currentAlphabet);
        else if (option == 1)
            translatedMsg[i] = (i & 1) ? ShiftChar(msg[i], shiftcount, 'r', currentAlphabet) : ShiftChar(msg[i], shiftcount, 'l', currentAlphabet);
    }
    return translatedMsg;
}

// Function to shift a character to the left or right
char ShiftChar(char c, int amount, char dir, const char* currentAlphabet) {
    int minDecimal = currentAlphabet == alphabet ? MIN_LOWER_CIPHER_DECIMAL : MIN_UPPER_CIPHER_DECIMAL;
    amount = dir == 'l' ? -amount : amount;  // Make amount negative for 'l'
    return (c + amount - minDecimal + ALPHABET_RANGE) % ALPHABET_RANGE + minDecimal;
}