
///////////////////////////////////////////
/// Author: Alayna De Valk              ///
/// SNHU CS210 Programming Languages    ///
/// Corner Grocer Item Tracker          ///
/// Date: 2/25/2024                     ///
///////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

//class to create backup file
class FileBackup {

public:

    //constructor for the File Backup class
    FileBackup(const string& originalFilename, const string& backupFilename)
        : originalFileName(originalFilename), backupFileName(backupFilename) {}

    //function to process the original file, write to a map, and create a backup file
    void processAndBackup() {
        ifstream inFS(originalFileName);

        //print error if unable to open original file
        if (!inFS.is_open()) {
            cout << "Error opening original file: " << originalFileName << endl;
            return;
        }//end if

        //create a map to store the data
        map<string, int> grocerItemMap;
        string product;
        int quantity;

        //read from the original file and populate the map
        while (inFS >> product) {

            ++grocerItemMap[product];

        }//end while

        //close the original file
        inFS.close(); 

        //create a backup file
        ofstream outFS(backupFileName);

        //print an error if unable to open backup
        if (!outFS.is_open()) {
            cout << "Error opening backup file for writing: " << backupFileName << endl;
            return;
        }//end if

        //write the info to the map
        for (const auto& entry : grocerItemMap) {
            outFS << entry.first << " " << entry.second << endl;
        }//end for

        //close the backup file
        outFS.close(); 

        //print a success message
        cout << "Backup created successfully: " << backupFileName << endl << endl;

    }//end process and backup

    const string& getBackupFileName() const {
        return backupFileName;
    }

private:
    string originalFileName;
    string backupFileName;

}; //end FIleBackup

//class to create menu + options
class Menu {

public:

    //constructor to initialize fileBackup
    Menu(const FileBackup& fileBackup) : fileBackup(fileBackup) {}

    //show Menu method to display the Menu to the User
    void showMenu() {

        //Print a dividing line
        cout << setw(57) << setfill('=') << "" << endl;

        //Welcome Message
        cout << "|| Welcome to the Corner Grocer Item inventory system! ||" << endl;

        //Print a dividing line
        cout << setw(57) << setfill('=') << "" << endl;

        //Print menu options
        cout << "Please choose an option to continue:" << endl << endl;
        cout << "[1] Get the quantity of an item\n";
        cout << "[2] Print full item list with quantities\n";
        cout << "[3] Print a histogram showing item quantities\n";
        cout << "[4] End the Program\n";

        //Print a dividing line
        cout << setw(55) << setfill('=') << "" << endl;

        //Prompt for choice
        cout << "Enter your choice (1-4): ";

    }//end showmenu

    //option 1 method
    void Option1() {

        //get user input for the product name
        cout << "Enter the name of an item: ";

        //declare variable to store User input
        string userInput;
        cin >> userInput;

        //open the backup file
        ifstream backupFile(fileBackup.getBackupFileName());

        //check if the backup file is opened successfully
        if (!backupFile.is_open()) {
            cout << "Error opening backup file: " << fileBackup.getBackupFileName() << endl;
            return;
        }//end if

        //variables to store data from the backup file
        string product;
        int quantity;

        //read the backup file and search for the corresponding item
        while (backupFile >> product >> quantity) {

            if (product == userInput) {

                //display the result
                cout << "The quantity of " << userInput << " in stock is: " << quantity << endl << endl;
                backupFile.close();
                return;

            }//end if

        }//end while

        // If the item is not found in the backup file (in stock)
        cout << "Item not found in stock." << endl;

        // Close the backup file
        backupFile.close();
    }//end option1

    //option 2 method
    void Option2() {
        // Open the backup file
        ifstream backupFile(fileBackup.getBackupFileName());

        // Check if the backup file is opened successfully
        if (!backupFile.is_open()) {
            cout << "Error opening backup file: " << fileBackup.getBackupFileName() << endl;
            return;
        }//end if

        // Display header
        cout << "Item List with Quantities:\n";

        // Variables to store data from the backup file
        string product;
        int quantity;

        // Read the backup file and print item list with quantities
        while (backupFile >> product >> quantity) {
            cout << product << ": " << quantity << endl;
        }//end while
        
        // Close the backup file
        backupFile.close();

        cout << endl;

    }//end option 2

    //option 3 method
    void Option3() {
        //Open the backup file
        ifstream backupFile(fileBackup.getBackupFileName());

        //Check if the backup file is opened successfully
        if (!backupFile.is_open()) {
            cout << "Error opening backup file: " << fileBackup.getBackupFileName() << endl;
            return;
        }//end if

        

        // Display header
        cout << "Item List with Histogram:\n";

            //Variables to store data from the backup file
        string product;
        int quantity;

        // Set the width for product names to create a more uniform Histogram look
        int productNameWidth = 12;

        //Read the backup file and print item list with quantities
        //Align the data to display the histogram better
        while (backupFile >> product >> quantity) {
            cout << setw(productNameWidth) << setfill(' ') << left << product << ": " << printAsterisks(quantity) << endl;
        }//end while

        cout << endl;

        //Close the backup file
        backupFile.close();

    }//end option 3

    //print asterisks based on quantity
    string printAsterisks(int quantity) {
        string asterisks;
        for (int i = 0; i < quantity; ++i) {
            asterisks += '*';
        }//end for
        return asterisks;
    }//end print asterisks

private:
    const FileBackup& fileBackup;
};//end menu class

int main() {

    //Specify the original and backup file names to be used in the processAndBackup method
    string originalFileName = "CS210_Project_Three_Input_File.txt";
    string backupFileName = "frequency.dat";

    //Create an instance of FileBackup and use it to process and create the backup file
    FileBackup fileBackup(originalFileName, backupFileName);
    fileBackup.processAndBackup();

    //Create an instance of Menu and a variable to hold the Users input
    Menu choiceMenu(fileBackup);
    int userChoice;

    //Use a do-while loop to run the program while the User inputs a valid 
    //number choice (between 1 & 4, inclusive)
    do {

        //show the menu to the user and accept their choice
        choiceMenu.showMenu();
        cin >> userChoice;

        //perform different actions based on user input (case)
        switch (userChoice) {

        case 1:
            cout << endl << "[ You selected Option 1 ]\n" << endl;
            choiceMenu.Option1();
            break;

        case 2:
            cout << endl << "[ You selected Option 2 ]\n" << endl;
            choiceMenu.Option2();
            break;

        case 3:
            cout << endl << "[ You selected Option 3 ]\n" << endl;
            choiceMenu.Option3();
            break;

        case 4:
            cout << endl << "[ You selected Option 4 ]\n" << endl;
            cout << "Exiting program....\n";
            return 0;

            //Print an error if input fails
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }

    } while (userChoice >= 1 && userChoice <= 4);

    return 0;


}//end main
