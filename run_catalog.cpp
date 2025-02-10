/*
    Author: Brady Hanna
    Description: Main for catalog
*/
#include "catalog.h"

#include <iostream>
#include <fstream>

using namespace std;

string get_file(){
	string filename;
	bool valid = false;

    // Run until a valid filename is entered
    while (!valid) {
        // Get the users input
        cout << "\nPlease enter Catalog or Wishlist: " << endl;
        getline(cin, filename);

        // Check if the filename is valid
        if (filename == "Catalog" || filename == "Wishlist" || filename == "10") {
            valid = true;  // Filename is valid, exit loop
        } else{
            cout << "Invalid input. Please enter either Catalog or Wishlist" << endl;
        }
    }

    return filename;
}

void help(){
    // Output help for the user
    cout << "\nHelp Page:" << endl;
    cout << "\n1. When prompted for Wishlist or Catalog, enter which you would like to interact with." << endl;
    cout << "2. To add to your catalog or wishlist, select 2 and enter the title and type of media you wish to add." << endl;
    cout << "3. To remove an item from your catalog or wishlist, select 3 and enter the title of the media you wish to remove." << endl;
    cout << "4. To filter for items in your catalog or wishlist, select 4 and enter the type of media you would like to view." << endl
        << "Your options are Movie, Book, TV, or Music." << endl;
    cout << "\n To return to the option selection state, enter 10 at any point." << endl;
    cout << "\n Contact Email: hannabra@oregonstate.edu" << endl;
}

int main(){
// System introduction and explanation.
cout << "Welcome to Media Storage" << endl;
cout << "\nThis system allows you to keep track of movies, books, tv, and music that you have interacted with or wish to interact with." << endl;


Catalog my_catalog;

// Run until the user chooses to quit the program
while(1){
    // Get the users choice of acton
    string choice_s = user_choice();
    int choice = stoi(choice_s);
    
    // If the user chooses to quit, then return from main.
    if (choice == 6) {
        cout << "Exiting program." << endl;
        return 0;
    } else if (choice == 5){ // If the user needs help, output help and reprompt for user choice
        help();
        continue;
    }

    // Make sure media information is clear
    my_catalog.clearMediaList();
    // Get the file the user wants to interact with
    string filename = get_file();
    if (filename == "10"){ // Return home
        continue;
    }
    filename = add_extension_and_lowercase(filename);
    // Load media information
    load_media_list(filename, my_catalog);
    // Go to the users choice
    switch (choice) {
        case 1:
            view_catalog(my_catalog, filename);
            break;
        case 2:
            add_to_catalog(my_catalog, filename);
            break;
        case 3:
            remove_from_catalog(my_catalog, filename);
            break;
        case 4:
            filter_catalog(my_catalog, filename);
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
    }
} }