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
The program is a command-line tool and should be used as follows:
```bash
$ ./cipher <option> <key> <message>
```
where:

`<option>` is 0 for encryption and 1 for decryption.

`<key>` is an integer from 1 to 16, each number corresponds to the keys listed above.

`<message>` is the string to be encrypted or decrypted. If the message contains spaces, it should be enclosed in quotes.

## Example
To encrypt the phrase "hello world" using the "Elvish" key, you would run:
```bash
$ ./cipher 0 2 "hello world"
```
This would return the message: "hshch eodpm"

To decrypt the message using the same key, you would run:
```bash
$ ./cipher 1 2 "hshch eodpm"
```
This would then once again be translated to "hello world"

## Important Notes
The program is case-sensitive, meaning it treats uppercase and lowercase letters separately.

The program ignores spaces and special characters while encrypting or decrypting, only alphabetic characters are processed.

When using decryption, make sure to use the same key (i.e., the same language) that was used to encrypt the message.

The translation method alternates shifting right and left across the alphabet for each character.

## Build
The program is written in C and can be compiled using any standard C compiler. For example, to compile the program with gcc, use the following command:
```bash
$ gcc -o cipher cipher.c
```

## Limitations
The program does not currently support error handling for situations where the user inputs invalid arguments.

The program uses simple ASCII arithmetic for character manipulation. Non-ASCII or special characters may not be processed correctly.


