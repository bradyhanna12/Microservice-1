#include "catalog.h"

#include <iostream>
#include <regex>
#include <cctype>
using namespace std;

/*
* Function: user_choice
* Description: Get the users input for how they want to use the catalog
* Returns (string): The users input
*/
string user_choice(){
	string choice;
    regex validChoice("[1-6]");
	do{
		// Ask user what they want to do
		cout << "\nWhat would you like to do?:" << endl << endl
			<< "1 - View a catalog" << endl 
			<< "2 - Add to a catalog" << endl
			<< "3 - Remove from a catalog" << endl
			<< "4 - Filter a catalog" << endl
            << "5 - I need Help" << endl
			<< "6 - Quit the program" << endl << endl;

		// Get user input
		getline(cin, choice);

		// Error handling
		if (!regex_match(choice, validChoice)){
			cout << "\nInvalid Choice. Please Try again." << endl;	
		}
	} while (!regex_match(choice, validChoice));
	
	return choice;
}

/*
* Function: load_media_list
* Description: Loads the mediaList vector with the information from a txt file
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
*   (Catalog&) catalog: The media catalog object
*/
void load_media_list(const string& filename, Catalog& catalog) {
    // Read the file
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string title, type;

    // Read each media item until the end of the file
    while (getline(inFile, title) && getline(inFile, type)) {
        // Create Media object and add it directly to the catalog
        catalog.addMedia(Media(title, type));
    }

    inFile.close();
}

/*
* Function: add_extension_and_lowercase
* Description: adds .txt to the filename
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
* Returns (string): filename.txt
*/
string add_extension_and_lowercase(const string& filename) {
    // Convert the entire filename to lowercase
    string lowercase_filename = filename;
    for (char& c : lowercase_filename) {
        c = tolower(c);  // Convert each character to lowercase
    }

    // Add the ".txt" extension if it doesn't already exist
    lowercase_filename += ".txt";

    return lowercase_filename;
}

/*
* Function: remove_extension_and_capitalize
* Description: removes .txt from the filename
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
* Returns (string): filename
*/
string remove_extension_and_capitalize(const string& filename) {
    // Find the position of ".txt"
    size_t pos = filename.find(".txt");

    // If ".txt" is found, return the substring excluding the ".txt" part
    string base_name = (pos != string::npos) ? filename.substr(0, pos) : filename;

    // Capitalize the first letter
    if (!base_name.empty()) {
        base_name[0] = toupper(base_name[0]);  // Capitalize the first character
    }

    return base_name;
}

/*
* Function: view_catalog
* Description: Displays the catalog contents
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
*   (Catalog&) catalog: The media catalog object
*/
void view_catalog(Catalog& my_catalog, string filename){
    // Print catalog contents
	cout << endl << remove_extension_and_capitalize(filename) << " Contents: " << endl << endl;
    my_catalog.displayCatalog();
}

/*
* Function: add_to_catalog
* Description: Adds a media item to the catalog based on the users input
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
*   (Catalog&) catalog: The media catalog object
*/
void add_to_catalog(Catalog& my_catalog, string filename){
	string title, type;

    // Ask the user for the title and type
    cout << endl << "Enter the title of the media: ";
    getline(cin, title);

    // Return home
    if (title == "10"){
        return;
    }

    const string validTypes[] = {"Book", "Movie", "TV", "Music"};
    bool valid = false;

    // Repeat until a valid type is entered
    while (!valid) {
        cout << endl << "Enter the type of the media (Book, Movie, TV, Music): ";
        getline(cin, type);

        // Check if the entered type is valid
        for (const string& validType : validTypes) {
            if (type == validType) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid type. Please enter one of the following: Book, Movie, TV, or Music." << endl;
        }
    }

    // Create Media object and add it to catalog
    Media newMedia(title, type);
    my_catalog.addMedia(newMedia);

    // Save to file
    my_catalog.saveToFile(filename, newMedia);

    cout << endl << "Media added successfully!" << endl;
}

/*
* Function: remove_from_catalog
* Description: Removes a media item from the catalog based on the users input
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
*   (Catalog&) catalog: The media catalog object
*/
void remove_from_catalog(Catalog& my_catalog, string filename){
    // Get the users input to remove a title
    string title_to_remove;
    cout << "\nEnter the title of the media you want to remove: ";
    getline(cin, title_to_remove);
    // Return home
    if (title_to_remove == "10"){
        return;
    }

    // Ensure the user wants to remove it
    string user_choice;
    while(1){
        cout << "\nAre you sure you want to remove " << title_to_remove << "? You can not undo this action." 
            << "\nEnter 1 if yes and 0 if no: " << endl;
        getline(cin, user_choice);
        int choice = stoi(user_choice);
        if (choice == 0 || choice == 10) {
            return;
        } else {
            break;
        }
    }


    // Remove the media from the catalog
    if (my_catalog.removeMedia(title_to_remove)) {
        cout << "Successfully removed " << title_to_remove << " from the catalog." << endl;

        // Rewrite the file with the updated catalog
        ofstream outFile(filename, ios::trunc);  // Open file for writing (overwrite the file)
        if (!outFile.is_open()) {
            cerr << "Unable to open file for updating." << endl;
            return;
        }

        // Write the updated catalog to the file
        const auto& mediaList = my_catalog.getMediaList();
        for (const auto& media : mediaList) {
            outFile << media.getTitle() << endl;
            outFile << media.getType() << endl;
        }

        outFile.close();
    } else {
        cout << "\nMedia item not found in the catalog." << endl;
    }
}

/*
* Function: filter_catalog
* Description: Displays specific media items in a catalog based on the users input
* Parameters: 
*   (const string&) filename: the name of the file containing the media information
*   (Catalog&) catalog: The media catalog object
*/
void filter_catalog(Catalog& my_catalog, string filename){
    string type;
    const string validTypes[] = {"Book", "Movie", "TV", "Music", "10"};
    bool valid = false;
    // Repeat until a valid type is entered
    while (!valid) {
        cout << endl << "\nEnter the type of the media (Book, Movie, TV, Music): ";
        getline(cin, type);

        // Check if the entered type is valid
        for (const string& validType : validTypes) {
            if (type == validType) {
                valid = true;
                break;
            }
        }

        if (!valid) {
            cout << "\nInvalid type. Please enter one of the following: Book, Movie, TV, or Music." << endl;
        }
    }

    // Return home
    if (type == "10"){
        return;
    }

    // Filter and display the media
    my_catalog.filterByType(type);
}