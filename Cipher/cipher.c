#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cipher.h"

int main()
{
    char user[50];
    int option;
    int keyIndex;

    // Prompt the user for their userID, option, and key index
    printf("Enter User ID: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = '\0'; // Remove trailing newline

    // Immediately check if the user exists
    if (!authenticateUser(user)) 
    {
        printf("Invalid User ID. Exiting.");
        return -1;
    }

    printf("Enter option (0 to Write, 1 to Read): ");
    scanf("%d", &option);

    printf("Available languages are:\n");
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        if (isKeyAvailableForUser(user, i + 1))
        {
            printf("%d (%s)\n", i + 1, keys[i]);
        }
    }
    printf("Enter language number: ");
    scanf("%d", &keyIndex);

    if (!isKeyAvailableForUser(user, keyIndex) || keyIndex < 1 || keyIndex > sizeof(keys) / sizeof(keys[0]))
    {
        printf("Invalid input!\n");
        return -1;
    }

    const char *key = keys[keyIndex - 1];

    // Determine the size of the alphabet
    int alphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);

    // Prompt the user for the message to encrypt/decrypt
    printf("Enter your message: ");
    getchar();          // Consume the '\n' from the previous input
    char message[1000]; // Choose an appropriate size for your use case
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; // Remove trailing newline

    int msgsize = strlen(message);
    TranslateMessage(message, msgsize, option, key);

    printf("Translated message: %s\n", message);

    return 0;
}

bool authenticateUser(const char *username)
{
    // Look for the user in the users array
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            // Found the user, check if the key is available
            return true;
        }
    }

    return false;
}

int isKeyAvailableForUser(const char *username, int keyIndex)
{
    // Look for the user in the users array
    for (int i = 0; i < sizeof(users) / sizeof(users[0]); i++)
    {
        if (strcmp(users[i].username, username) == 0)
        {
            // Found the user, check if the key is available
            for (int j = 0; j < sizeof(users[i].availableKeys) / sizeof(users[i].availableKeys[0]); j++)
            {
                if (users[i].availableKeys[j] == 0)
                    break; // End of list
                if (users[i].availableKeys[j] == keyIndex)
                    return 1; // Key is available
            }
        }
    }

    // User not found or key not available
    return 0;
}

// Function to encrypt or decrypt a message
char *TranslateMessage(char *msg, int length, int option, const char *key)
{
    char *translatedMsg = msg;
    int shiftcount = 0;
    int keyIndex = 0;
    int keyLength = strlen(key);
    const char *currentAlphabet; // Variable to hold the current alphabet (lowercase or uppercase)
    int currentAlphabetSize = 0; // Variable to hold the current alphabet size

    // Iterate over the message
    for (int i = 0; i < length; i++)
    {
        // If the current character is a space, skip it
        if (msg[i] == ' ')
            continue;

        // Determine which alphabet to use based on the case of the current character
        if (msg[i] >= 'a' && msg[i] <= 'z')
        {
            currentAlphabet = alphabet;
            currentAlphabetSize = sizeof(alphabet) / sizeof(alphabet[0]);
        }
        else if (msg[i] >= 'A' && msg[i] <= 'Z')
        {
            currentAlphabet = upperAlphabet;
            currentAlphabetSize = sizeof(upperAlphabet) / sizeof(upperAlphabet[0]);
        }
        else
            continue;

        shiftcount = 0;

        // Find the shift count for the current character
        for (int j = 0; j < currentAlphabetSize - 1; j++)
        { // Subtract one because of null character at the end
            shiftcount++;
            if (currentAlphabet[j] == key[keyIndex])
                break;
        }

        // Increment key index for the next character
        if (++keyIndex == keyLength)
            keyIndex = 0;

        // Encrypt or decrypt the current character based on the option
        if (option == 0)
            translatedMsg[i] = (i & 1) ? ShiftChar(msg[i], shiftcount, 'l', currentAlphabet) : ShiftChar(msg[i], shiftcount, 'r', currentAlphabet);
        else if (option == 1)
            translatedMsg[i] = (i & 1) ? ShiftChar(msg[i], shiftcount, 'r', currentAlphabet) : ShiftChar(msg[i], shiftcount, 'l', currentAlphabet);
    }
    return translatedMsg;
}

// Function to shift a character to the left or right
char ShiftChar(char c, int amount, char dir, const char *currentAlphabet)
{
    int minDecimal = currentAlphabet == alphabet ? MIN_LOWER_CIPHER_DECIMAL : MIN_UPPER_CIPHER_DECIMAL;
    amount = dir == 'l' ? -amount : amount; // Make amount negative for 'l'
    return (c + amount - minDecimal + ALPHABET_RANGE) % ALPHABET_RANGE + minDecimal;
}