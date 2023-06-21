#ifdef __unix__          /* __unix__ is usually defined by compilers targeting Unix systems */
    #define CLEAR_COMMAND "clear"
#elif defined(_WIN32)    /* _WIN32 is usually defined by compilers targeting 32 or 64 bit Windows systems */
    #define CLEAR_COMMAND "cls"
#elif defined(__APPLE__) && defined(__MACH__) /* Apple OSX and iOS (Darwin) */
    #define CLEAR_COMMAND "clear"
#else
    #define CLEAR_COMMAND ""
#endif

// Define the ASCII values for the lower case letters 'a' and 'z'
#define MIN_LOWER_CIPHER_DECIMAL 97
#define MIN_UPPER_CIPHER_DECIMAL 65
#define ALPHABET_RANGE 26
#define NUMBER_OF_KEYS 16


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
    const char *userID;
    const char *username;
    int availableKeys[17]; // Increased array size to 17 to accommodate the sentinel value
} User;

User users[] = {
    { "428", "Admin", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0} },
    { "Uhbk", "User 1", {14, 0} },
    { "Bndc", "User 2", {1, 2, 4, 6, 7, 0} },
    { "Rjtxoy", "User 3", {4, 11, 15, 0} },
    { "Iwnb", "User 4", {1, 4, 5, 6, 0} },
    { "Nrpap", "User 5", {1, 4, 5, 6, 0} },
    { "Pim", "Test User", {1, 4, 5, 7, 8, 12, 14, 16, 0}}
};

// Function prototypes
int isNumeric(const char* str);
int getNumericInput(int *num);
const User* authenticateUser(const char* userID);
char * TranslateMessage(char* msg, int length, int option, const char* key);
char ShiftChar(char c, int amount, char dir, const char* currentAlphabet);
int isKeyAvailableForUser(const User *user, int keyIndex);
