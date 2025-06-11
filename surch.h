#pragma once
#include <iostream>
#include <irrKlang.h>
struct Node_surah
{
    std::string name_surah;
    std::string type_surah;
    std::string path_surah;
    Node_surah* prev;
    Node_surah* next;
    Node_surah(std::string name, std::string type, std::string path)
    {
        name_surah = name;
        type_surah = type;
        path_surah = path;
        prev = nullptr;
        next = nullptr;
    }
};
class surah
{
private:
    Node_surah* head;
    Node_surah* tail;
    int size;
    irrklang::ISoundEngine* engine;
    Node_surah* search_name_surah(std::string);
public:
    surah();
    void addsurah(std::string , std::string , std::string);
    void Rmove_surah(std::string);
    void insert_at_pos(std::string, std::string, std::string, int);
    void update_order(std::string ame, int );
    bool Display();
    ~surah();
    void Runsound();
    void Savetofile(std::ofstream*);
};

