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
    string type;  // e.g., Movie, Book, Music
public:
    Media(string title, string type) : title(title), type(type){}
    string getTitle() const { return title; }
    string getType() const { return type; }
    void display() const {
        cout << "Title: " << title << endl << "Type: " << type << endl << endl;
    }
};

class Catalog {
private:
    vector<Media> mediaList;
public:
    void addMedia(const Media &media) {
        mediaList.push_back(media);
    }
    void displayCatalog() const {
        for (const auto &media : mediaList) {
            media.display();
        }
    }
    // Remove media by title
    bool removeMedia(const string& title) {
        // Use std::remove_if to move matching elements to the end of the vector
        auto it = std::remove_if(mediaList.begin(), mediaList.end(),[&title](const Media& media) {
            return media.getTitle() == title;
        });

        // Check if any elements were found to be removed
        bool found = (it != mediaList.end());

        // Erase the "removed" elements from the vector
        mediaList.erase(it, mediaList.end());

        return found;
    }
    // Filter and display Media objects by type
    void filterByType(const std::string& type) const {
        std::cout << "\nMedia of type '" << type << "':" << std::endl;
        bool found = false;

        for (const auto& media : mediaList) {
            if (media.getType() == type) {
                std::cout << "- " << media.getTitle() << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "\nNo media found of type '" << type << "'." << std::endl;
        }
    }
    // Save the catalog to a file
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
    vector<Media>& clearMediaList() {
        mediaList.clear();
        return mediaList;
    }
};

bool cancel(int input);
string user_choice();
string add_extension_and_lowercase(const string& filename);
string remove_extension_and_capitalize(const string& filename);
void load_media_list(const string& filename, Catalog& catalog);
void view_catalog(Catalog& my_catalog, string filename);
void add_to_catalog(Catalog& my_catalog, string filename);
void remove_from_catalog(Catalog& my_catalog, string filename);
void filter_catalog(Catalog& my_catalog, string filename);

#endif