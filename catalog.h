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
    bool matches(const string& t) const {
        return title == t;
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
        auto it = find_if(mediaList.begin(), mediaList.end(), 
                          [&title](const Media& media) { return media.matches(title); });
        if (it != mediaList.end()) {
            mediaList.erase(it);
            return true;  // Media was found and removed
        }
        return false;  // Media not found
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
};


string user_choice();
void add_media_to_catalog(Catalog& catalog, const string& filename);
string add_extension_and_lowercase(const string& filename);
string remove_extension_and_capitalize(const string& filename);
void loadMediaList(const string& filename, vector<Media>& mediaList);
void view_catalog(Catalog& my_catalog, string filename);
void add_to_catalog(Catalog& my_catalog, string filename);
void remove_from_catalog(Catalog& my_catalog, string filename);
void filter_catalog(Catalog& my_catalog, string filename);

#endif