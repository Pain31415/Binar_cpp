#include "DAIDatabase.h"
#include <iostream>

DAIDatabase::Node::Node(const std::string& plate) : licensePlate(plate), left(nullptr), right(nullptr) {}

DAIDatabase::DAIDatabase() : root(nullptr) {}

DAIDatabase::~DAIDatabase() {
}

void DAIDatabase::insert(Node*& node, const std::string& plate, const std::string& violation) {
    if (node == nullptr) {
        node = new Node(plate);
        node->violations += violation + " ";
    }
    else if (plate < node->licensePlate) {
        insert(node->left, plate, violation);
    }
    else if (plate > node->licensePlate) {
        insert(node->right, plate, violation);
    }
    else {
        node->violations += violation + " ";
    }
}

void DAIDatabase::addViolation(const std::string& plate, const std::string& violation) {
    insert(root, plate, violation);
}

void DAIDatabase::insertNewRecord(const std::string& plate, const std::string& violation) {
    insert(root, plate, violation);
}

void DAIDatabase::deleteRecord(const std::string& plate) {
    root = deleteNode(root, plate);
}

DAIDatabase::Node* DAIDatabase::findMinNode(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

DAIDatabase::Node* DAIDatabase::deleteNode(Node* node, const std::string& plate) {
    if (node == nullptr) {
        return nullptr;
    }

    if (plate < node->licensePlate) {
        node->left = deleteNode(node->left, plate);
    }
    else if (plate > node->licensePlate) {
        node->right = deleteNode(node->right, plate);
    }
    else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMinNode(node->right);
        node->licensePlate = temp->licensePlate;
        node->violations = temp->violations;
        node->right = deleteNode(node->right, temp->licensePlate);
    }

    return node;
}

void DAIDatabase::printDatabase(Node* node) const {
    if (node != nullptr) {
        printDatabase(node->right);

        std::cout << "License Plate: " << node->licensePlate << "\n";
        std::cout << "Violations: " << node->violations << "\n";

        printDatabase(node->left);
    }
}

void DAIDatabase::printFullDatabase() const {
    std::cout << "Full Database:\n";
    printDatabase(root);
}

void DAIDatabase::printDataByPlate(const std::string& plate) const {
    printDataByPlate(root, plate);
}

void DAIDatabase::printDataInRange(const std::string& startPlate, const std::string& endPlate) const {
    printDataInRange(root, startPlate, endPlate);
}

void DAIDatabase::printDataByPlate(Node* node, const std::string& plate) const {
    while (node != nullptr) {
        if (plate == node->licensePlate) {
            std::cout << "License Plate: " << node->licensePlate << "\n";
            std::cout << "Violations: " << node->violations << "\n";
            return;
        }
        else if (plate < node->licensePlate) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    std::cout << "Record with license plate " << plate << " not found.\n";
}

void DAIDatabase::printDataInRange(Node* node, const std::string& startPlate, const std::string& endPlate) const {
    if (node != nullptr) {
        if (startPlate <= node->licensePlate && endPlate >= node->licensePlate) {
            std::cout << "License Plate: " << node->licensePlate << "\n";
            std::cout << "Violations: " << node->violations << "\n";
        }

        if (startPlate < node->licensePlate) {
            printDataInRange(node->left, startPlate, endPlate);
        }

        if (endPlate > node->licensePlate) {
            printDataInRange(node->right, startPlate, endPlate);
        }
    }
}