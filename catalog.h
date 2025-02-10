#ifndef CATALOG_H
#define CATALOG_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


class Media {
private:
    string title;
    string type;  // e.g., Movie, Book, Music, TV
public:
    Media(string title, string type) : title(title), type(type){} // Constructor
    // Getter functions
    string getTitle() const { return title; }
    string getType() const { return type; }
    /*
    * Function: display
    * Description: Displays the media title and type
    */
    void display() const {
        cout << "Title: " << title << endl << "Type: " << type << endl << endl;
    }
};

class Catalog {
private:
    vector<Media> mediaList;
public:
    /*
    * Function: addMedia
    * Description: Adds a media item to the mediaList
    * Parameters: 
    *   (const Media&) media: the media object to add
    */
    void addMedia(const Media &media) {
        mediaList.push_back(media);
    }
    /*
    * Function: displayCatalog
    * Description: Displays the media title and type for every item in the Catalog
    */
    void displayCatalog() const {
        for (const auto &media : mediaList) {
            media.display();
        }
    }
    /*
    * Function: removeMedia
    * Description: Removes a media item from the mediaList
    * Parameters: 
    *   (const string&) title: the title of the media to remove
    * Returns (bool): A boolean identifying whether a media item was sucessfully removed
    */
    bool removeMedia(const string& title) {
        // Use std::remove_if to move matching elements to the end of the vector
        auto it = remove_if(mediaList.begin(), mediaList.end(),[&title](const Media& media) {
            return media.getTitle() == title;
        });

        // Check if any elements were found to be removed
        bool found = (it != mediaList.end());

        // Erase the "removed" elements from the vector
        mediaList.erase(it, mediaList.end());

        return found;
    }
    /*
    * Function: filterByType
    * Description: Filters the mediaList by type and displays its information
    * Parameters: 
    *   (const string&) type: the type of media to filter for
    */
    void filterByType(const string& type) const {
        cout << "\nMedia of type '" << type << "':" << endl;
        bool found = false;

        // Loop through all media and match the correct type
        for (const auto& media : mediaList) {
            if (media.getType() == type) {
                cout << "- " << media.getTitle() << endl;
                found = true;
            }
        }

        // If there is no media of that type, inform the user
        if (!found) {
            cout << "\nNo media found of type '" << type << "'." << endl;
        }
    }
    /*
    * Function: saveToFile
    * Description: Saves a media item to the catalog file
    * Parameters: 
    *   (const string&) filename: the name of the file containing the media information
    *   (Media&) media: The media object
    */
    void saveToFile(const string& filename, Media& media) const {
        ofstream outFile(filename, ios::app);  // Open in append mode to not overwrite
        if (outFile) {
            outFile << media.getTitle() << endl;
            outFile << media.getType() << endl;
            
            outFile.close();
        } else {
            cout << "Error opening file for saving." << endl;
        }
    }
    // Get the media list (for file writing)
    const vector<Media>& getMediaList() const {
        return mediaList;
    }
    // Clear the media list
    vector<Media>& clearMediaList() {
        mediaList.clear();
        return mediaList;
    }
};

string user_choice();
string add_extension_and_lowercase(const string& filename);
string remove_extension_and_capitalize(const string& filename);
void load_media_list(const string& filename, Catalog& catalog);
void view_catalog(Catalog& my_catalog, string filename);
void add_to_catalog(Catalog& my_catalog, string filename);
void remove_from_catalog(Catalog& my_catalog, string filename);
void filter_catalog(Catalog& my_catalog, string filename);

#endif