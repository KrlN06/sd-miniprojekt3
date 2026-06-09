#include "Interface.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <stdexcept>

Interface::Interface() : firstRun(true) {

    srand(static_cast<unsigned int>(time(nullptr)));
}

void Interface::clearScreen() {
#ifdef _WIN32
    system("cls");
#elif __APPLE__ || __linux__
    for (int i = 0; i < 50; i++) {
        std::cout << '\n';
    }
#endif
}

void Interface::waitForUser() {
    std::cout << "\nPress ENTER to continue...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Interface::run() {
    int choice = 0;
    while (true) {
        clearScreen();
        displayMainMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            waitForUser();
            continue;
        }

        handleMainMenuChoice(choice);
    }
}

void Interface::displayMainMenu() {
    if (firstRun) {
        std::cout << "PROJECT DATA STRUCTURES - HASH TABLES\n"
                  << "KAROL NALEPA MICHAŁ MARSZAŁEK\n\n";
        firstRun = false;
    }
    std::cout << "Select mode:\n"
              << "Hash Table Chaining AVL      [1]\n"
              << "Hash Table Chaining List     [2]\n"
              << "Hash Table Open Addressing   [3]\n"
              << "Benchmark                    [4]\n"
              << "Quit                         [5]\n"
              << "Your choice: ";
}

void Interface::handleMainMenuChoice(int choice) {
    switch (choice) {
        case 1:
            displayStructureMenu("HASH TABLE CHAINING AVL");
            break;
        case 2:
            displayStructureMenu("HASH TABLE CHAINING LIST");
            break;
        case 3:
            displayStructureMenu("HASH TABLE OPEN ADDRESSING");
            break;
        case 4:
            displayBenchmarkMenu();
            break;
        case 5:
            clearScreen();
            std::cout << "Exiting program. Goodbye!\n";
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again.\n";
            waitForUser();
    }
}

void Interface::displayStructureMenu(const std::string& structureName) {
    int choice = 0;
    int structureType = 0;

    if (structureName == "HASH TABLE CHAINING AVL") structureType = 1;
    else if (structureName == "HASH TABLE CHAINING LIST") structureType = 2;
    else if (structureName == "HASH TABLE OPEN ADDRESSING") structureType = 3;

    while (true) {
        clearScreen();
        std::cout << "--- " << structureName << " MENU ---\n"
                  << "Select operation:\n"
                  << "Insert key-value pair     [1]\n"
                  << "Remove key                [2]\n"
                  << "Generate random structure [3]\n"
                  << "Load structure from file  [4]\n"
                  << "Clear structure           [5]\n"
                  << "Return to main menu       [6]\n"
                  << "Your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            waitForUser();
            continue;
        }

        if (choice == 6) break;
        handleStructureMenuChoice(choice, structureType);
    }
}

void Interface::handleStructureMenuChoice(int choice, int structureType) {
    switch (choice) {
        case 1:
            handleInsertOperation(structureType);
            waitForUser();
            break;
        case 2:
            handleRemoveOperation(structureType);
            waitForUser();
            break;
        case 3:
            handleGenerateRandomOperation(structureType);
            waitForUser();
            break;
        case 4:
            handleLoadFromFileOperation(structureType);
            waitForUser();
            break;
        case 5:
            handleClearOperation(structureType);
            waitForUser();
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            waitForUser();
    }
}

void Interface::handleInsertOperation(int structureType) {
    clearScreen();
    int key, value;
    std::cout << "--- INSERT KEY-VALUE PAIR ---\n";
    std::cout << "Enter key: ";
    std::cin >> key;
    std::cout << "Enter value: ";
    std::cin >> value;

    if (structureType == 1) {
        hashTableAVL.insert(key, value);
    } else if (structureType == 2) {
        hashTableList.insert(key, value);
    } else {
        hashTableOpen.insert(key, value);
    }
    std::cout << "Key-value pair inserted successfully.\n";
}

void Interface::handleRemoveOperation(int structureType) {
    clearScreen();
    int key;
    std::cout << "--- REMOVE KEY ---\n";
    std::cout << "Enter key to remove: ";
    std::cin >> key;

    try {
        if (structureType == 1) {
            hashTableAVL.remove(key);
        } else if (structureType == 2) {
            hashTableList.remove(key);
        } else {
            hashTableOpen.remove(key);
        }
        std::cout << "Key removed successfully.\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Interface::handleGenerateRandomOperation(int structureType) {
    clearScreen();
    int count;
    std::cout << "--- GENERATE RANDOM STRUCTURE ---\n";
    std::cout << "Enter the number of elements to generate: ";
    std::cin >> count;

    handleClearOperation(structureType);

    for (int i = 0; i < count; i++) {
        int randomKey = rand() % 10000;
        int randomValue = rand() % 10000;
        if (structureType == 1) hashTableAVL.insert(randomKey, randomValue);
        else if (structureType == 2) hashTableList.insert(randomKey, randomValue);
        else hashTableOpen.insert(randomKey, randomValue);
    }
    std::cout << "Generated " << count << " random key-value pairs.\n";
}

void Interface::handleLoadFromFileOperation(int structureType) {
    clearScreen();
    std::string filename;
    std::cout << "--- LOAD FROM FILE ---\n";
    std::cout << "Enter text file name: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
        return;
    }

    handleClearOperation(structureType);

    int key, value;
    int count = 0;

    while (file >> key >> value) {
        if (structureType == 1) hashTableAVL.insert(key, value);
        else if (structureType == 2) hashTableList.insert(key, value);
        else hashTableOpen.insert(key, value);
        count++;
    }

    file.close();
    std::cout << "Successfully loaded " << count << " key-value pairs from file.\n";
}

void Interface::handleClearOperation(int structureType) {
    std::cout << "Clear operation not implemented for hash tables yet.\n";
}

void Interface::displayBenchmarkMenu() {
    int choice = 0;
    while (true) {
        clearScreen();
        std::cout << "--- BENCHMARK MENU ---\n"
                  << "Select benchmark option:\n"
                  << "Run full benchmark  [1]\n"
                  << "Return to main menu [2]\n"
                  << "Your choice: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            waitForUser();
            continue;
        }

        if (choice == 1) {
            clearScreen();
            runFullBenchmark();
            waitForUser();
        } else if (choice == 2) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
            waitForUser();
        }
    }
}

void Interface::runFullBenchmark() {
    std::cout << "Starting automatic benchmark...\n";
    Benchmark benchmark;
    benchmark.run();
    std::cout << "\nBenchmark finished!\n";
}