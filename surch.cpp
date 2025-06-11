#include "surch.h"
#include <iostream>
#include <irrKlang.h>
#include <iomanip>
#include <conio.h>
#include <fstream>
surah::surah() : head(nullptr), tail(nullptr), size(0) {
    engine = irrklang::createIrrKlangDevice();
}
void surah::addsurah(std::string name, std::string type, std::string path)
{
    Node_surah* new_node = new Node_surah(name, type, path);
    if (size==0)
    {
        head = tail = new_node;
    }
    else {
        new_node->prev = tail;
        new_node->next = nullptr;
        tail->next = new_node;
        tail = new_node;
    }
    size++;
} 
Node_surah* surah::search_name_surah(std::string name)
{
    if (head == nullptr)
    {
        std::cout << "list is empty \n";
        return nullptr;
    }
    Node_surah* curr = head;
    while (curr)
    {
        if (curr->name_surah == name)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}
void surah::Rmove_surah(std::string name)
{
    Node_surah* curr = search_name_surah(name);
    if (curr != nullptr) {
        std::cout << "Delete surah \'" << name << "\'...\n";
        if (curr->prev == nullptr && curr->next == nullptr)
        {
            delete curr;
            head = tail = nullptr;
        }
        else if (curr->prev == nullptr)
        {
            Node_surah* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        else if (curr->next == nullptr)
        {
            Node_surah* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        else
        {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            delete curr;
        }
        size--;
    }
    else
    {
        std::cout << "surah \'" << name << "\' Not found \n";
    }
}
void surah::insert_at_pos(std::string name, std::string type, std::string path, int position)
{
    if (position < 1 || position > size + 1)
    {
        std::cout << "out of range \n";
        return;
    }
    Node_surah* new_node = new Node_surah(name, type, path);
    if (position == 1)
    {
        if (head == nullptr) {
            head = tail = new_node;
        }
        else
        {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }
    else if (position - 1 == size)
    {
        new_node->prev = tail;
        new_node->next = nullptr;
        tail->next = new_node;
        tail = new_node;
    }
    else {
        Node_surah* curr = head;
        for (size_t i = 1; i < position - 1; i++)
            curr = curr->next;
        new_node->next = curr->next;
        new_node->prev = curr;
        curr->next->prev = new_node;
        curr->next = new_node;
    }
    size++;
}
void surah::update_order(std::string name, int position)
{
    Node_surah* curr = search_name_surah(name);
    if (curr != nullptr)
    {
        if (position < 1 || position > size)
        {
            std::cout << "out of range \n";
            return;
        }
        if (size == 1 && position == 1)
        {
            std::cout << "surah currnet position equal new position \n";
            return;
        }
        Node_surah* temp = head;
        if (curr->next == nullptr && curr->prev == nullptr)
        {
            temp = curr;
            head = tail = nullptr;
        }
        else if (curr->prev == nullptr)
        {
            temp = head;
            head = head->next;
            head->prev = nullptr;
        }
        else if (curr->next == nullptr)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            temp = curr;
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        size--;
        std::cout << "Surah \'" << temp->name_surah << "\' Moved to position : " << position << std::endl;
        insert_at_pos(temp->name_surah, temp->type_surah, temp->path_surah, position);
        delete temp;
    }
    else
    {
        std::cout << "surah \'" << name << "\' Not found \n";
    }
}
bool surah::Display()
{
    if (head == nullptr)
    {
        std::cout << "list is empty \n";
        return false;
    }
    int id = 1;
    Node_surah* curr = head;
    while (curr) {
        std::cout<<id << ".\t" <<
            std::setw(15) << curr->name_surah
            << std::setw(15) << curr->type_surah
            << curr->path_surah << std::endl;
        curr = curr->next;
        id++;
    }
    std::cout << std::endl;
    return true;
}
surah::~surah()
{
    Node_surah* temp = head;
    while (head) {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    engine->drop();
}
void surah::Runsound()
{
    if (head == nullptr)
    {
        std::cout << "list is empty\n";
        return;
    }
    if (!engine) {
       std::cout<< "Error: Could not initialize sound engine!" << std::endl;
       return;
    }
    Node_surah* curr = head;
    std::string playfile = curr->type_surah + "/" + curr->name_surah + "/" + curr->path_surah;
    std::cout << "Playing:" << curr->name_surah << "...\n";
    irrklang::ISound* sounds = engine->play2D(playfile.c_str(), true, false, true);
    if (!sounds)
    {
        std::cout << "Error : Could not initialize sound \n";
        return;
    }
    bool f1 = 1;
    while (f1) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'q':
            {
                engine->stopAllSounds();
                std::cout << "You Stop current Playlist.\n";
                f1 = 0;
            }
            break;
            case 72://top
            {
                std::cout << "Sound paused.\n";
                sounds->setIsPaused(true);
            }
            break;
            case 80://bottom
            {
                std::cout << "Sound Resumed.\n";
                sounds->setIsPaused(false);
            }
            break;
            case 75://left
            {
                if (curr->prev != nullptr) {
                    curr = curr->prev;
                    sounds->stop();
                    playfile = curr->type_surah + "/" + curr->name_surah + "/" + curr->path_surah;
                    std::cout << "Now Playing:" << curr->name_surah << "...\n";
                    sounds = engine->play2D(playfile.c_str(), true, false, true);
                }
                else {
                    std::cout << "Start of playlist reached.\n";
                }
            }
            break;
            case 77://right
            {
                if (curr->next != nullptr) {
                    sounds->stop();
                    curr = curr->next;
                    playfile = curr->type_surah + "/" + curr->name_surah + "/" + curr->path_surah;
                    std::cout << "Now Playing:" << curr->name_surah << "...\n";
                    sounds = engine->play2D(playfile.c_str(), true, false, true);
                }
                else
                    std::cout << "End of play list reached.\n";
            }
            break;
            }
        }
    }
}
void surah::Savetofile(std::ofstream* out)
{
    if (out->is_open()) {
        Node_surah* temp = head;
        while (temp)
        {
            *out << temp->name_surah << "|" << temp->type_surah << "|" << temp->path_surah << "\n";
            temp = temp->next;
        }
        *out << "END\n";
    }
    else {
        std::cout << "file not open \n";
    }
}
