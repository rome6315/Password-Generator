#include <iostream>


//defining constant variables
#define ALPHABET_SIZE 64 //all possible characters
#define PASSWORD_SIZE 10 //size of the password, always

//global variables
int specialCheck = 0;
int digitCheck = 0;
int upperCheck = 0;
int lowerCheck = 0;

void printPassword(char password[]); //print the password
void generatePassword(char password[]); //create a password
void checkIndividualDependencies(char password[]); //check if the password has the individual criterion, adding value to the global variables
bool checkWholePassword(char password[]); //check the entire password at once to see if it meets the criteria
void finalizePassword(char password[]); //this function checks the boolean value of the above function^, if true, it will print the password


int main(void) {
    srand((unsigned)time(0)); //seed rand
    char randomPassword[10]; //declare password variable/array

    
        generatePassword(randomPassword); //generate a password
        checkIndividualDependencies(randomPassword); //check the characters in the password for password strength
        checkWholePassword(randomPassword); //check the password as a whole
        finalizePassword(randomPassword); //prints password, or performs the above 3 steps on repeat until we get an acceptable password to print
        
    return 0;
}

//create password
void generatePassword(char password[]) {
    char possibleCharacters[] = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!." }; //declaring an array of all the acceptable characters

    for (int i = 0; i < PASSWORD_SIZE; i++) {
        password[i] = possibleCharacters[rand() % ALPHABET_SIZE]; //password at each indice will get a random char from the possibleCharacters, a char from the indice of 0-64
    }  
}

//check the individual criteria
void checkIndividualDependencies(char password[]) {
    for (int i = 0; i < PASSWORD_SIZE; i++) {
        if(password[i] == '!' || password[i] == '.') specialCheck++;
        if(isdigit(password[i])) digitCheck++;
        if(isupper(password[i])) upperCheck++;
        if(islower(password[i])) lowerCheck++;
    }
}

//see if the criteria has been met
bool checkWholePassword(char password[]) {
    if(specialCheck >= 1 && digitCheck >= 1 && upperCheck >= 1 && lowerCheck >= 1) {
        return true;
    }

    return false;
}

//print the password if the criteria is met
void finalizePassword(char password[]) {
    if(checkWholePassword(password)) printPassword(password);

    //while the password does not qualify/meet criterion
    while(!checkWholePassword(password)) {
        //have to reset the gloabl variables each time we go through the loop or else they will already have values from a previous password
        specialCheck = 0;
        lowerCheck = 0;
        upperCheck = 0;
        digitCheck = 0;
        //run the below functions again
        generatePassword(password);
        checkIndividualDependencies(password);
        checkWholePassword(password);
        //if the password is good this time around it will print and then we break, if not, go again until it is 
        if(checkWholePassword(password)) {
            printPassword(password);
            break;
        }
    }
}

//print password to screen ONLY if the check passes
void printPassword(char password[]) {
        for (int i = 0; i < PASSWORD_SIZE; i++) { //print the password
            std::cout << password[i];
        }

        std::cout << "\n"; //whitespace
}