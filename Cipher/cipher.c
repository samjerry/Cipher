#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void clearConsole() {
    if (CLEAR_COMMAND != "")
        system(CLEAR_COMMAND);
    else
        printf("\n"); // Fallback if the clear command is not defined
}

int main()
{
char user[50];
    int option;
    const User* authenticatedUser;
    int keyIndex;
    char message[1000];
    int continueProgram = 1;

    while (continueProgram)
    {
        clearConsole();
        // Prompt the user for their userID, option, and key index
        printf("Enter User ID (or 'quit' to exit): ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0';  // Remove trailing newline
        // If the user inputs 'quit', terminate the program
        if (strcmp(user, "quit") == 0)
        {
            printf("Exiting program.\n");
            return 0; // Exit with success
        }

        authenticatedUser = authenticateUser(user);
        if (authenticatedUser == NULL) 
        {
            printf("Invalid User ID. Try again.\n");
            continue;
        }
                printf("Welcome, %s!\n", authenticatedUser->username);


        while(1) // Option selection loop
        {
            clearConsole();

            printf("Welcome, %s! enter option (0 to Write, 1 to Read, 2 to Logout): ", authenticatedUser->username);
            if (getNumericInput(&option) != 0 || (option != 0 && option != 1 && option != 2))
            {
                printf("Invalid input! Please enter 0 to Write, 1 to Read or 2 to Logout.\n");
                continue;
            }

            if(option == 2) // Logout and go back to user selection
            {
                break;
            }

            while(1) // Language selection loop
            {
                clearConsole();

                printf("Available languages are:\n");
                for (int i = 0; i < NUMBER_OF_KEYS; i++) 
                {
                    if (isKeyAvailableForUser(authenticatedUser, i + 1)) 
                        printf("%d (%s)\n", i + 1, keys[i]);
                }
                printf("Enter language number or -1 to go back: ");
                
                if (getNumericInput(&keyIndex) != 0 || (!isKeyAvailableForUser(authenticatedUser, keyIndex) && keyIndex != -1) || keyIndex < -1 || keyIndex > NUMBER_OF_KEYS)
                {
                    printf("Invalid input! Please enter a valid language number or -1 to go back.\n");
                    continue;
                }

                if(keyIndex == -1) // Go back to option selection
                {
                    break;
                }

                while(1) // Message input and translation loop
                {
                    clearConsole();

                    const char* key = keys[keyIndex - 1];

                    printf("Enter your message or type 'BACK' to go back: ");
                    fgets(message, sizeof(message), stdin);
                    message[strcspn(message, "\n")] = '\0';  // Remove trailing newline

                    if(strcmp(message, "BACK") == 0) // Go back to language selection
                    {
                        break;
                    }

                    int msgsize = strlen(message);
                    TranslateMessage(message, msgsize, option, key);

                    printf("Translated message: %s\n", message);

                    char cont[50];
                    printf("Do you want to translate another message in this language? (yes/no): ");
                    fgets(cont, sizeof(cont), stdin);
                    cont[strcspn(cont, "\n")] = '\0';  // Remove trailing newline

                    if(strcmp(cont, "no") == 0) // Go back to language selection
                    {
                        break;
                    }
                }
            }
        }
    }
    return 0;
}


int isNumeric(const char* str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int getNumericInput(int *num)
{
    char buffer[50];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        char *endptr;
        long int val = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\n')
        {
            // Not a valid integer
            return -1;
        }
        else
        {
            *num = (int) val;
            return 0;
        }
    }
    else
    {
        // fgets failed
        return -1;
    }
}

const User* authenticateUser(const char* userID)
{
    for (int i = 0; i < sizeof(users) / sizeof(User); i++)
    {
        if (strcmp(userID, users[i].userID) == 0)
            return &users[i];  // return a pointer to the matched user
    }
    return NULL;  // return NULL if no match found
}

int isKeyAvailableForUser(const User *user, int keyIndex) 
{
    for (int i = 0; i < NUMBER_OF_KEYS; i++) 
    {
        if (user->availableKeys[i] == keyIndex) 
        {
            return 1;
        }
    }
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