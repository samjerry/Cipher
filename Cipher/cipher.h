// Define the ASCII values for the lower case letters 'a' and 'z'
#define MIN_LOWER_CIPHER_DECIMAL 97
#define MIN_UPPER_CIPHER_DECIMAL 65
#define ALPHABET_RANGE 26

// Define the alphabet and the keys for the cipher
static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
static const char upperAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static const char *keys[] = {"Dwarvish", 
                             "Elvish", 
                             "Giant", 
                             "Gnomish", 
                             "Goblin", 
                             "Halfling", 
                             "Orc", 
                             "Abyssal",
                             "Celestial", 
                             "Draconic", 
                             "DeepSpeech", 
                             "Infernal", 
                             "Primordial", 
                             "Sylvan", 
                             "Undercommon", 
                             "Druidic"
                            };

typedef struct {
    const char *username;
    int availableKeys[16];
} User;

// Function prototypes
char * TranslateMessage(char* msg, int length, int option, const char* key);
char ShiftChar(char c, int amount, char dir, const char* currentAlphabet);
int isKeyAvailableForUser(const char *username, int keyIndex);
