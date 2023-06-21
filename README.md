# Encrypt/Decrypt Program

## Table Of Content
1. [Overview](#overview)
2. [Usage](#usage)
3. [Example](#example)
4. [Important Notes](#important-notes)
5. [Build](#build)
6. [Limitations](#limitations)

## Overview
This program provides a simple encryption and decryption service based on the concept of Vigenère cipher but with added complexity. You can select different encryption/decryption keys, each corresponding to a certain language from the Dungeons & Dragons universe.

The keys available are:
| Key |   Language  |  | Key |   Language  |
| --- |:-----------:|--| --- |:-----------:|
| 1   |   Dwarvish  |  | 9   |  Celestial  |
| 2   |    Elvish   |  | 10  |   Draconic  | 
| 3   |    Giant    |  | 11  |  DeepSpeech | 
| 4   |   Gnomish   |  | 12  |   Infernal  |
| 5   |    Goblin   |  | 13  |  Primordial |
| 6   |   Halfling  |  | 14  |    Sylvan   |
| 7   |     Orc     |  | 15  | Undercommon |
| 8   |   Abyssal   |  | 16  |   Druidic   |

## Usage
The script prompts the user for the following inputs:

1. User ID

2. An option (0 to Write/Encode, 1 to Read/Decode)

3. Language number

After collecting these details, it checks whether the chosen language is available for the provided user. If the language is not available or if an invalid option is entered, the program terminates with an error message.
In the case of successful validation, the program then asks for a message from the user to encode or decode, based on the chosen option.

## Example
Here's an example of the program execution:

```javascript
Enter User ID: Uhbk
Enter option (0 to Write, 1 to Read): 0
Available languages are:
14 (Sylvan)
Enter language number: 14
Enter your message: Hello World!
Translated message: Bktlo Dmfie!
```

## Important Notes
The User ID, option, and language number are expected to be entered by the user manually when prompted.

The available languages for each user are predefined and cannot be changed during program execution.

The "option" should be either 0 (for Write/Encode) or 1 (for Read/Decode).

The message input by the user should not exceed 1000 characters.

## Build
The program is written in C and can be compiled using any standard C compiler. For example, to compile the program with gcc, use the following command:
```bash
$ gcc -o cipher cipher.c
```

## Limitations
The program only works with predefined users and their available languages. To modify this, you will need to manually change the code.

It only encodes and decodes alphabetic characters; numbers and special characters are not handled.

This program does not have error handling for non-numeric input for the option or language number.
