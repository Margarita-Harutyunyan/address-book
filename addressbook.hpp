#ifndef ADDRESS_BOOK
#define ADDRESS_BOOK

#include <string>
#include <vector>

class Contact {
private:
    std::string fullName;
    std::string phoneNumber;
    std::string email;

public:
    // setter methods
    void setFullName(const std::string& name);
    void setPhoneNumber(const std::string& number);
    void setEmail(const std::string& email);

    // getter methods
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;

    void displayContact() const;
    std::string getContactForFile() const;
};

class AddressBook {
private:
    std::vector<Contact> contacts;

    // private helper function
    int searchHelper(const std::string& name);

public:
    // getter method
    std::vector<Contact> getContacts() const;

    // setter method
    void setContacts(std::vector<Contact> contacts);

    // modifier methods
    void addContact(Contact& contact);
    bool removeContact(const std::string& name); 
    bool updateContactName(const std::string& name, const std::string& newName);
    bool updateContactNumber(const std::string& name, const std::string& number);
    bool updateContactEmail(const std::string& name, const std::string& email);
    bool findContact(const std::string& name);
    
};

class AddressBookController {
public:
    AddressBook addressBook;
    std::string userFile;

    void openBook();
    void displayContacts() const;
    void addContact();
    void removeContact();
    void updateContact();
    bool isValidPhNum(const std::string& number);
    bool isValidEmail(const std::string& email);
    void searchContact();
    void saveChanges();
    void loadFromFile(const std::string& fileName);
    void displayMenu();

public:
    void start();
};



#endif

