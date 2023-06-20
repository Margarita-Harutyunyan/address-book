#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "addressbook.hpp"

// class Contact {
// private:
//     std::string fullName;
//     std::string phoneNumber;
//     std::string email;


// setter methods
void Contact::setFullName(const std::string& name) {
    this->fullName = name; 
}

void Contact::setPhoneNumber(const std::string& number) {
    this->phoneNumber = number;
}

void Contact::setEmail(const std::string& email) {
    this->email = email;
}

// getter methods
std::string Contact::getFullName() const {
    return this->fullName;
}

std::string Contact::getPhoneNumber() const {
    return this->phoneNumber;
}

std::string Contact::getEmail() const {
    return this->email;
}

void Contact::displayContact() const {
    std::cout << fullName + "; " + phoneNumber + "; " + email << std::endl;
}

std::string Contact::getContactForFile() const {
    return (fullName + ";" + phoneNumber + ";" + email);
}

////////////////

// class AddressBook {
// private:
//     std::vector<Contact> contacts;
//     std::string user;

// private helper function
int AddressBook::searchHelper(const std::string& name) {
    // auto it = std::__find_if(contacts.begin(), contacts.end(), [&](Contact& contact){return contact.getFullName() == name;});
    // return it;
    for (int i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getFullName() == name) {
            return i;
        }
    }

    return -1;
}
// getter method
std::vector<Contact> AddressBook::getContacts() const {
    return this->contacts;
}

// setter method

void AddressBook::setContacts(std::vector<Contact> contacts) {
    this->contacts = contacts;
}

// modifier methods
void AddressBook::addContact(Contact& contact) {
    this->contacts.push_back(contact);
}

bool AddressBook::removeContact(const std::string& name) {
    int index = searchHelper(name);
    if (index != -1) {
        contacts.erase(contacts.begin() + index);
        return true;
    } else { 
        return false;
    }
}

bool AddressBook::updateContactName(const std::string& name, const std::string& newName) {
    int index = searchHelper(name);
    if (index != -1) {
        (contacts.begin() + index)->setFullName(newName);
        return true;
    } else {
        return false;
    }
}

bool AddressBook::updateContactNumber(const std::string& name, const std::string& number) {
    int index = searchHelper(name);
    if (index != -1) {
        (contacts.begin() + index)->setPhoneNumber(number);
        return true;
    } else {
        return false;
    }
}

bool AddressBook::updateContactEmail(const std::string& name, const std::string& email) {
    int index = searchHelper(name);
    if (index != -1) {
        (contacts.begin() + index)->setEmail(email);
        return true;
    } else {
        return false;
    }
}

bool AddressBook::findContact(const std::string& name) {
    int index = searchHelper(name);
    if (index != -1) {
        std::cout << "Here is the contact you are searching:\n";
        (contacts.begin() + index)->displayContact();
        return true;
    } else {
        return false;
    }
}

//////////

// class AddressBookController {
// private:
//     AddressBook addressBook;
//    std::string userFile;

// private helper methods
void AddressBookController::openBook() {
// asks the user their name and makes a string with the name + '.txt'. if the file exists, it reads the contents
// and stores in addressBook, otherwise makes a new file to add the new addressbook and store it
    // Ask the user for their name
    std::cout << "Welcome! Enter you name (Make sure you enter the same name everytime to see you address book!): ";
    std::cin >> userFile;
    userFile += ".txt";

    // Check if the file exists
    std::ifstream inputFile(userFile);
    if (inputFile) {
        // If file exists, load the contents into the addressBook
        loadFromFile(userFile);
        std::cout << "Address book opened successfully!" << std::endl;
    } else {
        // If the file does not exist, create a new one
        std::ofstream outputFile(userFile);
        if(outputFile) {
            std::cout << "New adress book created successfully!" << std::endl;
        }   else {
            std::cout << "Failed to create a new address book :(" << std::endl;
            std::cout << "Close the program and try to run it again" << std::endl;
        }
        outputFile.close();
    }
    inputFile.close();
}

void AddressBookController::loadFromFile(const std::string& fileName) {
// A helper function for the openBook
    std::ifstream inputFile(fileName);
    std::string line;
    // Get each line and split it 
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string name, number, email;
        if (std::getline(iss, name, ';') && std::getline(iss, number, ';') && std::getline(iss, email)) {
            // Make a new contact objext and add it to addressBook
            Contact contact;
            contact.setFullName(name);
            contact.setPhoneNumber(number);
            contact.setEmail(email);
            addressBook.addContact(contact);
        }
    }
    inputFile.close();
}


void AddressBookController::displayContacts() const {
// displays the addressbook
    std::vector<Contact> contacts = addressBook.getContacts();
    std::cout << "Displaying address book contacts...\n";
    for (const Contact& contact : contacts) {
        contact.displayContact();
    }
    std::cout << '\n';
}

void AddressBookController::addContact() {
// asks the name, the phone number, and the email, checks if the phone number is valid and if the email has '@' and makes the new contact
// if a user has a mistake, it warns and waits for new input
    std::string name, number, email;

    std::cout << "Enter the full name: ";
    std::cin >> name;
    std::cout << '\n';
    
    std::cout << "Enter the phone number: ";
    std::cin >> number;
    std::cout << '\n';
    while(!isValidPhNum(number)) {
        std::cout << "Invalid number. Please try again: ";
        std::cin >> number;
    }
    std::cout << '\n';

    std::cout << "Enter the email: ";
    std::cin >> email;
    while (!isValidEmail(email)) {
        std::cout << "Invalid email. Please try again: ";
        std::cin >> email;
    }
    std::cout << '\n';
    Contact contact;
    contact.setFullName(name);
    contact.setPhoneNumber(number);
    contact.setEmail(email);

    addressBook.addContact(contact);
    
    std::cout << "New contact created successfully!" << std::endl;
}

void AddressBookController::removeContact() {
// asks for the name and tries removing, if the result is false, it warns the user
    std::string name;
    std::cout << "Enter the full name of the contact you want to remove: ";
    std::cin >> name;
    std::cout << '\n';

    bool removed = addressBook.removeContact(name);
    if (removed) {
        std::cout << "Contact removed successfully" << std::endl;
    } else {
        std::cout << "Contact not found" << std::endl;
    }

}
void AddressBookController::updateContact() {
// asks for the name and finds the contact, then asks the user what exactly they want to update, checks the input and does the operation
    std::string name;
    std::cout << "Please enter the name of the contact you want to update: ";
    std::cin >> name;
    std::cout << '\n';

    std::string newName, newNumber, newEmail;
    std::cout << "Enter new name (leave * to keep the current name): ";
    std::cin >> newName;
    std::cout << '\n';

    std::cout << "Enter new phone number (leave * to keep the current name): ";
    std::cin >> newNumber;
    std::cout << '\n';

    std::cout << "Enter new email (leave * to keep the current name): ";
    std::cin >> newEmail;
    std::cout << '\n';

    bool updatedName = false;
    bool updatedNumber = false;
    bool updatedEmail = false;

    if (newName != "*") {
        updatedName = addressBook.updateContactName(name, newName);
        if (updatedName) {
            std::cout << "Contact name updated successfully!" << std::endl;
        }
    }

    if (newNumber != "*") {
        while(!isValidPhNum(newNumber)) {
            std::cout << "Invalid phone number. Please try again: ";
                std::cin >> newNumber;
                std::cout << '\n';
        }
        if(updatedName) {
            name = newName;
        }
        updatedNumber = addressBook.updateContactNumber(name, newNumber);
        if (updatedNumber) {
            std::cout << "Contact phone number updated successfully!" << std::endl;
        }
    }

    if (newEmail != "*") {
        while (!isValidEmail(newEmail)) {
            std::cout << "Invalid email. Please try again: ";
                std::cin >> newEmail;
                std::cout << '\n';
        }
        if(updatedName) {
            name = newName;
        }
        updatedEmail = addressBook.updateContactEmail(name, newEmail);
        if (updatedEmail) {
            std::cout << "Contact email updated successfully!" << std::endl;
        }
    } 

    if(!updatedName && !updatedNumber && !updatedEmail) {
        std::cout << "Contact not found" << std::endl;
    }
    
}


bool AddressBookController::isValidPhNum(const std::string& number) {
    return std::all_of(number.begin(), number.end(), ::isdigit);
}

bool AddressBookController::isValidEmail(const std::string& email) {
    return email.find('@') != std::string::npos;
}
void AddressBookController::searchContact() {
// searches for a contact by name and displays it if found
    std::string name;
    std::cout << "Enter the full name of the contact you want to find: ";
        std::cin >> name;
        std::cout << '\n';
    bool found = addressBook.findContact(name);
    if (!found) {
        std::cout << "Contact not found" << std::endl;
    }

}
void AddressBookController::saveChanges() {
// this function is called after the user quits, it saves the addressBook in the userFile, overwrites the file if changes are made
    std::ofstream outputFile(userFile);
    if (outputFile) {
        std::vector<Contact> contacts = addressBook.getContacts();
        for (const Contact& contact : contacts) {
            outputFile << contact.getContactForFile() << std::endl;
        }
        std::cout << "Changes saved successfully!" << std::endl;
    } else {
        std::cout << "Failed to save changes :(" << std::endl;
    }
}
void AddressBookController::displayMenu() {
// an interactive menu to ask the user what they want to do
    std::cout << "------------ Address Book Menu ------------" << std::endl;
    std::cout << "1. Display contacts" << std::endl;
    std::cout << "2. Add contact" << std::endl;
    std::cout << "3. Remove contact" << std::endl;
    std::cout << "4. Update contact" << std::endl;
    std::cout << "5. Search contact" << std::endl;
    std::cout << "6. Quit" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
}

//public method
void AddressBookController::start() {
// the only public method
// starts by asking for the users name and executing the openBook method
// displays the menu, asks an imput from the user until they want to quit
// calls all the methods needed
// calls saveChanges in the end to save the addressBook in a file
    openBook();

    int choice;
    bool quit = false;
    while (!quit) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayContacts();
                break;
            case 2:
                addContact();
                break;
            case 3:
                removeContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                searchContact();
                break;
            case 6:
                saveChanges();
                quit = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again:\n";
                std::cout << '\n';
                std::cin.clear();
                break;
        }
    }
}

