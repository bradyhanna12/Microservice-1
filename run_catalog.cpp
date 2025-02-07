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

    while (!valid) {
        cout << "Please enter Catalog or Wishlist: " << endl;
        getline(cin, filename);

        // Check if the filename is valid
        if (filename == "Catalog" || filename == "Wishlist") {
            valid = true;  // Filename is valid, exit loop
        } else {
            cout << "Invalid input. Please enter either Catalog or Wishlist" << endl;
        }
    }

    return filename;
}

int main(){
Catalog my_catalog;

while(1){
    string choice_s = user_choice();
    int choice = stoi(choice_s);

    if (choice == 5) {
         cout << "Exiting program." << endl;
         return 0;
    }

    string filename = get_file();
    filename = add_extension_and_lowercase(filename);

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