#include "catalog.h"

#include <iostream>
#include <regex>
#include <cctype>
using namespace std;

string user_choice(){
	string choice;
    regex validChoice("[1-5]");
	do{
		// Ask user what they want to do
		cout << "\nWhat would you like to do?:" << endl << endl
			<< "1 - View a catalog" << endl 
			<< "2 - Add to a catalog" << endl
			<< "3 - Remove from a catalog" << endl
			<< "4 - Filter a catalog" << endl
			<< "5 - Quit the program" << endl << endl;

		// Get user input
		getline(cin, choice);

		// Error handling
		if (!regex_match(choice, validChoice)){
			cout << "\nInvalid Choice. Please Try again." << endl;	
		}
	} while (!regex_match(choice, validChoice));
	
	return choice;
}

void load_media_list(const string& filename, Catalog& catalog) {
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

// Function to add media item to the catalog
void add_media_to_catalog(Catalog& catalog, const string& filename) {
    string title, type;

    // Ask the user for the title and type
    cout << endl << "Enter the title of the media: ";
    getline(cin, title);

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
    catalog.addMedia(newMedia);

    // Save to file
    catalog.saveToFile(filename, newMedia);

    cout << endl << "Media added successfully!" << endl;
}



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

void view_catalog(Catalog& my_catalog, string filename){
	load_media_list(filename, my_catalog);
	cout << endl << remove_extension_and_capitalize(filename) << " Contents: " << endl << endl;
    my_catalog.displayCatalog();
}

void add_to_catalog(Catalog& my_catalog, string filename){
	load_media_list(filename, my_catalog);
	add_media_to_catalog(my_catalog, filename);
}

void remove_from_catalog(Catalog& my_catalog, string filename){
    string title_to_remove;
    cout << "Enter the title of the media you want to remove: ";
    getline(cin, title_to_remove);

    // Remove the media from the catalog
    if (my_catalog.removeMedia(title_to_remove)) {
        cout << "Successfully removed " << title_to_remove << " from the catalog." << endl;

        // Now, we need to rewrite the file with the updated catalog
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

void filter_catalog(Catalog& my_catalog, string filename){

}