import secrets # For generating strong random passwords
import string # Give us access to ascii_letters and digits
import pwnedpasswords # Check if password has been leaked

specialChars = '!@#$%^&*' # List of special characters

alphabet = string.ascii_letters  + string.digits + specialChars # List of all characters

def getUserInput():
    # Ask to include special characters or not (since some sites still don't allow special chars somehow)
    while True:
        print("Include special characters? (y/n):")
        special = input()
        if special == 'y' or special == 'n':
            break
        else:
            print("Please enter 'y' or 'n':")
    

    # Ask for password length
    while True:
        print("Enter password length (10-32 characters):")
        length = int(input())
        if length >= 10 and length <= 32:
            break
        else:
            print("Please enter a number between 8 and 32:")
    return special, length



def generatePassword(length, special):
    # Generate password
    if special == 'y':
        password = ''.join(secrets.choice(alphabet) for i in range(length))
        
        # Check if password contains at least one special character
        while not any(char in specialChars for char in password):
            password = ''.join(secrets.choice(alphabet) for i in range(length))

    else:
        password = ''.join(secrets.choice(string.ascii_letters + string.digits) for i in range(length))

        # Make sure password contains at least one number
        while not any(digits in string.digits for digits in password):
            password = ''.join(secrets.choice(string.ascii_letters + string.digits) for i in range(length))

    return password


def checkPasswordForLeaks(password):
    # Check if password has been leaked
    if pwnedpasswords.check(password):
        print("Password has been leaked. Generating new password...")
        return True
    else:
        return False
    

def main():
    special, length = getUserInput()
    password = generatePassword(length, special)

    while checkPasswordForLeaks(password):
        password = generatePassword(length, special)

    print(password)
    

if __name__ == "__main__":
    main()