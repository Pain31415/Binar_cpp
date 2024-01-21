#ifndef DAIDATABASE_H
#define DAIDATABASE_H

#include <string>

class DAIDatabase {
private:
    struct Node {
        std::string licensePlate;
        std::string violations;
        Node* left;
        Node* right;

        explicit Node(const std::string& plate);
    };

    Node* root;

    void insert(Node*& node, const std::string& plate, const std::string& violation);
    Node* findMinNode(Node* node);
    Node* deleteNode(Node* node, const std::string& plate);

    void printDatabase(Node* node) const;

public:
    DAIDatabase();
    ~DAIDatabase();

    void addViolation(const std::string& plate, const std::string& violation);
    void insertNewRecord(const std::string& plate, const std::string& violation);
    void deleteRecord(const std::string& plate);

    void printFullDatabase() const;
    void printDataByPlate(const std::string& plate) const;
    void printDataInRange(const std::string& startPlate, const std::string& endPlate) const;

    void printDataByPlate(Node* node, const std::string& plate) const;
    void printDataInRange(Node* node, const std::string& startPlate, const std::string& endPlate) const;
};

#endif // DAIDATABASE_H