#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

// A new function to handle user input
int getInput(char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (!fgets(buffer, size, stdin)) {
        return 0;
    }

    // Check if the input string length exceeds the buffer size
    if (!strchr(buffer, '\n')) {
        // Clear the input buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } else {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove trailing newline
    }

    return 1;
}

int main()
{
    char user[50];
    int option;
    int keyIndex;

    // Prompt the user for their userID, option, and key index
    if (!getInput("Enter User ID: ", user, sizeof(user))) {
        printf("Error reading User ID. Exiting.");
        return -1;
    }

    // Immediately check if the user exists
    if (!authenticateUser(user)) 
    {
        printf("Invalid User ID. Exiting.");
        return -1;
    }

    // Get option from user and validate
    char option_str[3];
    if(!getInput("Enter option (0 to Write, 1 to Read): ", option_str, sizeof(option_str)) || 
                                                           sscanf(option_str, "%d", &option) != 1 || 
                                                           (option != 0 && option != 1)) {
        printf("Invalid option. Exiting.\n");
        return -1;
    }

    printf("Available languages are:\n");
    for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++) {
        if (isKeyAvailableForUser(user, i + 1)) {
            printf("%d (%s)\n", i + 1, keys[i]);
        }
    }

    // Get language number from user and validate
    char keyIndex_str[3];
    if(!getInput("Enter language number: ", keyIndex_str, sizeof(keyIndex_str)) || 
                                            sscanf(keyIndex_str, "%d", &keyIndex) != 1 || 
                                            !isKeyAvailableForUser(user, keyIndex) || 
                                            keyIndex < 1 || 
                                            keyIndex > sizeof(keys)/sizeof(keys[0])) {
        printf("Invalid input!\n");
        return -1;
    }

    const char* key = keys[keyIndex - 1];

    // Determine the size of the alphabet
    int alphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);

    // Prompt the user for the message to encrypt/decrypt
    char message[1000];  // Choose an appropriate size for your use case
    if (!getInput("Enter your message: ", message, sizeof(message))) {
        printf("Error reading message. Exiting.");
        return -1;
    }

    int msgsize = strlen(message);
    TranslateMessage(message, msgsize, option, key);

    printf("Translated message: %s\n", message);

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
