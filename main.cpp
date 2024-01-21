#include "DAIDatabase.h"
#include <iostream>
#include <string>

int main() {
    DAIDatabase database;

    std::string choice;
    do {
        std::cout << "1. Add a new record\n";
        std::cout << "2. Delete a record\n";
        std::cout << "3. Print the full database\n";
        std::cout << "4. Print data by license plate\n";
        std::cout << "5. Print data in range of license plates\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == "1") {
            std::string plate, violation;
            std::cout << "Enter license plate: ";
            std::cin >> plate;
            std::cout << "Enter violation: ";
            std::cin.ignore();
            std::getline(std::cin, violation);
            database.insertNewRecord(plate, violation);
            std::cout << "Record successfully added!\n";
        }
        else if (choice == "2") {
            std::string plate;
            std::cout << "Enter license plate to delete: ";
            std::cin >> plate;
            database.deleteRecord(plate);
            std::cout << "Record successfully deleted!\n";
        }
        else if (choice == "3") {
            database.printFullDatabase();
        }
        else if (choice == "4") {
            std::string plate;
            std::cout << "Enter license plate to print data: ";
            std::cin >> plate;
            database.printDataByPlate(plate);
        }
        else if (choice == "5") {
            std::string startPlate, endPlate;
            std::cout << "Enter start license plate: ";
            std::cin >> startPlate;
            std::cout << "Enter end license plate: ";
            std::cin >> endPlate;
            database.printDataInRange(startPlate, endPlate);
        }
        else if (choice != "6") {
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != "6");

    return 0;
}