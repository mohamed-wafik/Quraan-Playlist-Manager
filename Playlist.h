#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "surch.h"
struct Node_playlist
{
    surah* list;
    std::string name_playlist;
    Node_playlist* prev;
    Node_playlist* next;
    Node_playlist(std::string name)
    {
        name_playlist = name;
        list = new surah();
        prev = nullptr;
        next = nullptr;
    }
    ~Node_playlist()
    {
        delete list;
    }
};
class Playlist
{
private:
    Node_playlist* head;
    Node_playlist* tail;
    int size;
    Node_playlist* search_playlist(std::string name);
    bool Display(Node_playlist* curr);
public:
    Playlist();
    void addplaylist(std::string );
    void Add_surah(std::string );
    void update_order_surah(std::string );
    bool Display_name_play();
    void Rmove_surah(std::string);
    void select_playlist(std::string );
    // Runplay => 8
    void Run_play(std::string );
    // Save To file
    void savetofile();
    void loadTofile();
    void Rmove_playlist(std::string );
    void Display_all_playlist();
    ~Playlist();
};

