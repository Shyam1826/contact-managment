#include <iostream>
#include <string>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
    Contact(string n, string p, string e) : name(n), phone(p), email(e) {}
};

struct Node {
    Contact contact;
    Node* left;
    Node* right;
    Node(Contact c) : contact(c), left(nullptr), right(nullptr) {}
};

class ContactBST {
private:
    Node* root;
    Node* insert(Node* root, Contact contact) {
        if (root == nullptr) {
            return new Node(contact);
        }
        if (contact.name < root->contact.name) {
            root->left = insert(root->left, contact);
        } else if (contact.name > root->contact.name) {
            root->right = insert(root->right, contact);
        }
        return root;
    }
    
    Node* search(Node* root, string name) {
        if (root == nullptr || root->contact.name == name) {
            return root;
        }
        if (name < root->contact.name) {
            return search(root->left, name);
        } else {
            return search(root->right, name);
        }
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << "Name: " << root->contact.name << ", Phone: " << root->contact.phone
                 << ", Email: " << root->contact.email << endl;
            inorder(root->right);
        }
    }

    Node* deleteNode(Node* root, string name) {
        if (root == nullptr) return root;
        if (name < root->contact.name) {
            root->left = deleteNode(root->left, name);
        } else if (name > root->contact.name) {
            root->right = deleteNode(root->right, name);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->contact = temp->contact;
            root->right = deleteNode(root->right, temp->contact.name);
        }
        return root;
    }

    Node* minValueNode(Node* root) {
        Node* current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

public:
    ContactBST() : root(nullptr) {}

    void insertContact(Contact contact) {
        root = insert(root, contact);
    }

    void searchContact(string name) {
        Node* result = search(root, name);
        if (result != nullptr) {
            cout << "Contact found: Name: " << result->contact.name
                 << ", Phone: " << result->contact.phone
                 << ", Email: " << result->contact.email << endl;
        } else {
            cout << "Contact not found!" << endl;
        }
    }

    void deleteContact(string name) {
        root = deleteNode(root, name);
    }

    void displayContacts() {
        cout << "Contact List:" << endl;
        inorder(root);
    }
};

void takeInput(string &name, string &phone, string &email) {
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Phone: ";
    getline(cin, phone);
    cout << "Enter Email: ";
    getline(cin, email);
}

void menu(ContactBST &contactSystem) {
    int choice;
    string name, phone, email;

    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display All Contacts\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                takeInput(name, phone, email);
                contactSystem.insertContact(Contact(name, phone, email));
                cout << "Contact added successfully!" << endl;
                break;
            case 2:
                cout << "Enter name to search: ";
                getline(cin, name);
                contactSystem.searchContact(name);
                break;
            case 3:
                cout << "Enter name to delete: ";
                getline(cin, name);
                contactSystem.deleteContact(name);
                cout << "Contact deleted (if it existed)!" << endl;
                break;
            case 4:
                contactSystem.displayContacts();
                break;
            case 5:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 5);
}

int main() {
    ContactBST contactSystem;
    menu(contactSystem);
    return 0;
}
