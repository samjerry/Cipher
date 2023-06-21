# Encrypt/Decrypt Program

## Table Of Content
1. [Overview](#overview)
2. [Usage](#usage)
3. [Example](#example)
4. [Important Notes](#important-notes)
5. [Build](#build)
6. [Limitations](#limitations)

## Overview
This C program is a unique implementation of a Vigenère cipher, a method of encrypting alphabetic text by using a series of different Caesar ciphers based on the letters of a keyword. Vigenère cipher is a form of polyalphabetic substitution cipher.
In a Caesar cipher, each letter in the plaintext is 'shifted' a certain number of places down the alphabet. For example, with a shift of 1, A would be replaced by B, B would become C, and so on.

In the traditional Vigenère cipher, a keyword is used to determine the shift. Each letter of the keyword is converted to its numerical equivalent (A=1, B=2, etc.), and the resulting number is used to determine the shift for a particular letter in the plaintext.

However, this program features an unique twist on the Vigenère cipher. The direction of the shift for each character alternates depending on its position. The first letter of the keyword results in a right shift of the first letter of the plaintext, the second letter of the keyword leads to a left shift of the second letter of the plaintext, the third letter of the keyword results in a right shift of the third letter of the plaintext, and so forth. This adds an extra layer of security to the encrypted message, making it even more resistant to standard frequency analysis attacks.

The program also includes a user authentication feature. Each user is assigned a set of languages, which act as keys for the Vigenère cipher. Once authenticated, users can only encrypt or decrypt messages using the languages (keys) from the dungeons and dragons universe that are available to them.

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
This program guides users through a sequence of interactions:

Initially, users are prompted to input their unique ID for authentication purposes. Should they wish to exit the program, they simply have to type 'quit'.
Once their identity is authenticated, users will be presented with a choice to either write, which entails encrypting a message, or read, which involves decrypting a message.

Following their selection, the program displays all the available languages (acting as keys) that the user has access to, and prompts them to pick one.
Upon choosing their preferred language, users are then able to enter the text they wish to encrypt or decrypt. The program then carries out the specified operation and displays the outcome.

Finally, the user is given the option to continue with the same language. If they opt to proceed, they are invited to input more text for processing. Conversely, if they decide against it, they are redirected back to the language selection stage.

## Example
Let's say we have a user "Pim" who has access to the languages 1,4,5,7,8,12,14,16. Here is how an interaction with the program might look:

```yaml
Enter User ID (or 'quit' to exit): Pim
Enter option (0 to Write, 1 to Read, 2 to Logout): 0
Available languages are:
1 (Dwarvish)
4 (Gnomish)
5 (Goblin)
7 (Orc)
8 (Abyssal)
12 (DeepSpeech)
14 (Sylvan)
16 (Druidic)
Enter language number or -1 to go back: 1
Enter your message: hello world
Translated message: ifmmp xpsme
Do you want to continue in this language? (1 for Yes, 0 for No): 1
Enter your message: goodbye
Translated message: tifnqcf
Do you want to continue in this language? (1 for Yes, 0 for No): 0
```
The program would then go back to the language selection step.

## Important Notes
Only authenticated users can access the program. Usernames and accessible languages are predefined in the cipher.h file.

The languages (keys) for each user are also predefined. A user cannot access a language that is not assigned to them.

The program performs basic input validation, checking for numeric inputs where required. It does not, however, check for input length overflow.

The program uses ASCII values for the lower and upper case letters, meaning it only works with the English alphabet and does not support special characters or letters from other alphabets.

## Build

Before you can run the program, it needs to be compiled into an executable format. This is done using a compiler - in this case, we're using the GNU Compiler Collection (GCC).

GCC is a powerful tool that can compile code written in C, C++, and other languages. The primary command to use GCC to compile C code is gcc. In our specific use case, we're going to use it to compile our cipher.c file into an executable that we can run.

Here's the process:

Open Terminal: To run GCC commands, you need to open your terminal. On Windows, you can use Command Prompt or PowerShell. On macOS or Linux, just open the Terminal application.

Navigate to the Project Directory: Use the cd (change directory) command in the terminal to navigate to the directory where your cipher.c and cipher.h files are located. If your files are in a directory named "cipher_project" on your Desktop, the command might look like this:

On Windows: cd C:\Users\YourUsername\Desktop\cipher_project

On macOS or Linux: cd /Users/YourUsername/Desktop/cipher_project

Compile the Code: Once you're in the correct directory, you can compile your code using the gcc command:

```bash
$ gcc -o cipher cipher.c
```
Here's a quick breakdown of what the command does:

`gcc`: calls the GCC compiler

`-o cipher`: tells the compiler to output the compiled code into a file named "cipher". If you want the output file to have a different name, you can replace "cipher" with your desired name.

`cipher.c`: this is the C source file that you want to compile.

Run the Program: If the code compiled successfully, you can now run your program with the following command:

`./cipher`

If you run into any issues during compilation, make sure to check the error message in the terminal. It will often give you a clue as to what went wrong.

## Limitations

The program currently does not support special characters, numerals, or letters from non-English alphabets.

The list of users and their respective keys are hardcoded in the cipher.h header file, which might not be the most flexible design for a larger, scalable application.

There is no error handling mechanism for input length overflow.

The 'shift' value for each key is determined by its position in the alphabet, which may not provide sufficient complexity for a real-world encryption scenario.
