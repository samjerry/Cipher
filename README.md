# Encrypt/Decrypt Program

## 📑 Table Of Content
1. [Overview](#📜-Overview)
2. [Usage](#usage)
3. [Example](#example)
4. [Important Notes](#important-notes)
5. [Build](#build)
6. [Limitations](#limitations)

## 📜 Overview
This C program is a unique implementation of the **Vigenère cipher**, a method for encrypting alphabetic text using a series of different Caesar ciphers, where the shift is determined by the letters of a keyword. Unlike a standard Vigenère cipher, this program introduces a twist: the direction of the shift alternates for each character. This enhancement adds an extra layer of security, making it more resistant to standard cryptographic attacks.

### **How It Works**
In a **Caesar cipher**, each letter in the plaintext is shifted a set number of positions down the alphabet. For example, a shift of 1 would convert A to B, B to C, and so on. The **Vigenère cipher** extends this idea by using a keyword to determine the shifts. Each letter of the keyword corresponds to a numerical value (A=1, B=2, etc.), and this value is used for shifting the characters of the plaintext.

### **Unique Twist**
In this program:

- The first letter of the plaintext is shifted **right** based on the first letter of the keyword.
- The second letter is shifted **left** based on the second letter of the keyword.
- This pattern continues, alternating the direction of the shift.
  
The result is a more complex encryption pattern that enhances security.

### **User Authentication and Keys**
The program also features **user authentication**. Each user is assigned specific languages (acting as keys) from the **Dungeons & Dragons** universe. Only authenticated users can encrypt or decrypt messages using the languages available to them.

**Available Keys:**
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

## 🛠️ Usage
The program guides users through a series of interactive prompts:

1. **Authentication:** Enter your unique user ID to log in. Type `quit` to exit.
2. **Choose Action:** Select whether to **encrypt (write)** or **decrypt (read)** a message.
3. **Language Selection:** View the available languages (keys) assigned to you and pick one.
4. **Enter Text:** Input the text you want to encrypt or decrypt. The program processes your input and displays the result.
5. **Repeat or Change Language:** Decide whether to continue using the same language or return to the language selection.

## 📋 Example
Here is a sample interaction with the program:

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
After choosing `No`, the program returns to the language selection menu.

## ⚠️ Important Notes
- **Authentication Required:** Only authenticated users can access the encryption and decryption features. Usernames and accessible languages are predefined in the `cipher.h` file.
- **Language Access:** Users can only use the languages assigned to them.
- **Input Validation:** The program validates basic inputs (e.g., expecting numeric inputs where needed) but does not check for input length overflow.
- **Character Support:** The program operates using ASCII values, and only supports the English alphabet (A-Z, a-z). Special characters, numerals, and letters from other alphabets are not supported.

## 🔧 Build Instructions

To run the program, you need to compile it using the GNU Compiler Collection (GCC). Follow the steps below:

1. Open Terminal: Use Command Prompt or PowerShell on Windows, or Terminal on macOS/Linux.
2. Navigate to Project Directory: Use the `cd` command to go to the directory containing `cipher.c` and `cipher.h`. For example:
   - Windows: `cd C:\Users\YourUsername\Desktop\cipher_project`
   -  macOS/Linux: `cd /Users/YourUsername/Desktop/cipher_project`
3. Compile the Program:

```bash
$ gcc -o cipher cipher.c
```
`gcc`: Invokes the GCC compiler.

`-o cipher`: Names the compiled output file as "cipher".

`cipher.c`: The source code file to compile.

4. Run the Program:

```bash
$ ./cipher
```
If there are errors during compilation, check the terminal output for troubleshooting hints.

## 🚧 Limitations

- **Character Restrictions:** The program only supports the English alphabet. It cannot process numerals, special characters, or letters from non-English alphabets.
- **Hardcoded User Data:** User credentials and accessible keys are stored directly in the `cipher.h` file. This design is not ideal for scalability.
- **Lack of Error Handling:** There is no comprehensive error handling for input overflow or unexpected input types.
- **Simple Shift Logic:** The shift values are straightforward, which may not provide sufficient security for real-world encryption needs.
