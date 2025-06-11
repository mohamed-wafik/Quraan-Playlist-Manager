#include "Playlist.h"
#include "surch.h"
#include <iomanip>
#include <string>

Playlist::Playlist() :head(nullptr), tail(nullptr), size(0) {}
void Playlist::addplaylist(std::string name)
{
    Node_playlist* new_node = new Node_playlist(name);
    if (head == nullptr)
    {
        head = tail = new_node;
    }
    else
    {
        new_node->prev = tail;
        new_node->next = nullptr;
        tail->next = new_node;
        tail = new_node;
    }
    size++;
}
Node_playlist* Playlist::search_playlist(std::string name)
{
    if (head == nullptr)
    {
        std::cout << "list is empty \n";
        return nullptr;
    }
    Node_playlist* curr = head;
    while (curr)
    {
        if (curr->name_playlist == name)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}
bool Playlist::Display(Node_playlist* curr)
{
    if (curr != nullptr) {
        std::cout << "\tplaylist :: " << curr->name_playlist;
        std::cout << "\n---------------------------------------------------------\n";
        std::cout << "Id\t" <<
            std::setw(15) << std::left << "surah" <<
            std::setw(15) << "Type"
            << "path" << std::endl;
        std::cout << "---------------------------------------------------------\n";
        return curr->list->Display();
    }
    else {
        std::cout << "play list is not found \n";
        return false;
    }
}

void Playlist::Add_surah(std::string name_play)
{
        Node_playlist* curr = search_playlist(name_play);
        if (curr != nullptr)
        {
            std::string name, type, path;
            char press;
            do {
                std::cout << "Enter surah name : ";
                std::cin >> name;
                std::cout << "Enter surah type : ";
                std::cin >> type;
                std::cout << "Enter surah path : ";
                std::cin >> path;
                std::cout << "Add another surah to the current list? Press(y)";
                std::cin >> press;
                curr->list->addsurah(name, type, path);
            } while (press == 'y');
        }
        else
        {
            std::cout << "surah \'" << name_play << "\' Not found \n";
        }
    }
void Playlist::Rmove_surah(std::string name_play)
{
    Node_playlist* curr = search_playlist(name_play);
    if (curr != nullptr)
    {
        if (Display(curr)) {
            std::string name;
            std::cout << "Enter name : ";
            std::cin >> name;
            curr->list->Rmove_surah(name);
        }
    }
    else
    {
        std::cout << "playlist \'" << name_play << "\' Not found \n";
    }

}
void Playlist::update_order_surah(std::string name_play)
{
    Node_playlist* curr = search_playlist(name_play);
    if (curr != nullptr)
    {
        if (Display(curr)) {
            std::string name_surah;
            int pos;
            std::cout << "Enter name : ";
            std::cin >> name_surah;
            std::cout << "Enter now position : ";
            std::cin >> pos;
            curr->list->update_order(name_surah, pos);
        }
    }
    else
    {
        std::cout << "playlist \'" << name_play << "\' Not found \n";
    }
}
bool Playlist::Display_name_play()
{
    std::cout << "The current playlists are:\n";
    if (head == nullptr)
    {
        std::cout << "No playlists available \n";
        return false;
    }
    int id = 1;
    Node_playlist* curr = head;
    std::cout << "-------------------------------------\n";
    std::cout << std::setw(5) << std::left << "ID" << "Playlist\n";
    std::cout << "-------------------------------------\n";
    while (curr) {
        std::cout << std::setw(5) << std::left << id << curr->name_playlist << "\n";
        curr = curr->next;
        id++;
    }
    std::cout << "\n";
    return true;
}

void Playlist::select_playlist(std::string name)
{
    Node_playlist* curr = search_playlist(name);
    if (curr != nullptr)
    {
        Display(curr);
    }
    else
    {
        std::cout << "list is empty\n";
    }
}
    // Runplay => 8
void Playlist::Run_play(std::string name)
{
    Node_playlist* curr = search_playlist(name);
    if (curr != nullptr)
    {
        curr->list->Runsound();
    }
    else
    {
        std::cout << "Playlist : \'" << name << "\' Not found \n";
    }
}
    // Save To file
void Playlist::savetofile()
{
    Node_playlist* curr = head;
    std::ofstream out("playlist.txt", std::ios::app);
    if (out.is_open()) {
        while (curr)
        {
            out << "Playlist: " << curr->name_playlist << "\n";
            curr->list->Savetofile(&out);
            curr = curr->next;
        }
        out.close();
    }
    else
    {
        std::cout << "file Not open \n";
    }
}
void Playlist::loadTofile()
{
    std::string line, name, type, path;
    std::ifstream in("playlist.txt");
    if (in.is_open()) {
        while (getline(in, line)) {
            int pos = line.find(" ");
            std::string temp = line.substr(pos + 1);
            Node_playlist* new_node = new Node_playlist(temp);
            if (head == nullptr)
            {
                head = tail = new_node;
            }
            else {
                new_node->prev = tail;
                new_node->next = nullptr;
                tail->next = new_node;
                tail = new_node;
                size++;
            }

            while (getline(in, line)) {
                if (line == "END")
                {
                    break;
                }
                pos = line.find("|");
                name = line.substr(0, pos);
                line = line.substr(pos + 1);

                pos = line.find("|");
                type = line.substr(0, pos);
                line = line.substr(pos + 1);

                pos = line.find("|");
                path = line.substr(0, pos);
                line = line.substr(pos + 1);

                new_node->list->addsurah(name, type, path);
            }
        }
        in.close();
    }
    else
    {
        std::cout << "file Not open\n";
    }
}
void Playlist::Rmove_playlist(std::string name)
{
    Node_playlist* curr = search_playlist(name);
    if (curr != nullptr) {
        std::cout << "Delete playlist  \'" << name << "\'...\n";
        if (curr->next == nullptr && curr->prev ==nullptr)
        {
            delete curr;
            head = tail = nullptr;
        }
        else if (curr->prev == nullptr)
        {
            Node_playlist* temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
        else if (curr->next == nullptr)
        {
            Node_playlist* temp = tail;
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
        std::cout << "Playlist : \'" << name << "\' Not found \n";
    }
}
void Playlist::Display_all_playlist() 
{
    if (head == nullptr) {
        std::cout << "The playlist is empty.\n";
        return;
    }

    Node_playlist* curr = head;
    while (curr != nullptr) {
        Display(curr); 
        curr = curr->next;
    }
}
Playlist::~Playlist()
{
    Node_playlist* temp = head;
    while (head)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}