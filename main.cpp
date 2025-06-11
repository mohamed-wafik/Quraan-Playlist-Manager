#include <iostream>
#include "surch.h"
#include "Playlist.h"

void menu_main()
{
    std::cout << "\t\t\t\t\t\t\t\t\t+=====================================================================+\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|                  Quraan Playlist Manager Menu                       |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t=======================================================================\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 1. Add a new play list                                              |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 2. Add Shurah to an exisiting playlist                              |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 3. Remove Shurah from an exisiting playlist                         |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 4. Update the order of exisition playlist                           |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 5. Display All Current Playlists                                    |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 6. Display All Playlists Shurah                                     |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 7. Display Shurah from specific playlist                            |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 8. Play Shurah from specific playlist                               |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|    Use left arrow (<-) to play the previous shurah                  |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|    Use right arrow (->) to play the next shurah                     |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|    Use up arrow (^) to pause the current shurah                     |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|    Use down arrow (v) to resume the current shurah                  |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t|    Press q to exit current playlist 8 return back to menu           |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 9. Save an exisiting playlist to a file                             |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 10. Load an existion Playlist from a file                           |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 11. Remove an existing Playlist                                     |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t| 12. Exit                                                            |\n";
    std::cout << "\t\t\t\t\t\t\t\t\t+=====================================================================+\n";
}
int main() {
    std::cout << "\t\t\t\t\t\t\t\t\t\t      Quraan Playlist Manager Simulation System \n";
    std::cout << "\t\t\t\t\t\t\t\t\t\t            developed by Mohamed Wafik \n";
    Playlist* play = new Playlist();
    int choice;
    bool found;
    std::string name_play;
    do
    {
        menu_main();
        std::cout << "\t\t\t\t\t\t\t\t\tYour Choice : ";
        std::cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
        {
            std::cout << "Enter Playlist name: ";
            std::cin >> name_play;
            play->addplaylist(name_play);
        }
        break;
        case 2:
        {
            found = play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name: ";
                std::cin >> name_play;
                play->Add_surah(name_play);
            }
        }
        break;
        case 3:
        {
            found=play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name: ";
                std::cin >> name_play;
                play->Rmove_surah(name_play);
            }
        }
        break;
        case 4:
        {
            found=play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name : ";
                std::cin >> name_play;
                play->update_order_surah(name_play);
            }
        }
        break;
        case 5:
        {
            play->Display_name_play();
        }
        break;
        case 6:
        {
            play->Display_all_playlist();
        }
        break;
        case 7:
        {
            found= play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name: ";
                std::cin >> name_play;
                play->select_playlist(name_play);
            }
        }
        break;
        case 8:
        {
            found =play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name: ";
                std::cin >> name_play;
                play->Run_play(name_play);
            }
        }
        break;
        case 9:
        {
            play->savetofile();
        }
        break;
        case 10:
        {
            play->loadTofile();
        }
        break;
        case 11:
        {
            found=play->Display_name_play();
            if (found) {
                std::cout << "Enter Playlist name: ";
                std::cin >> name_play;
                play->Rmove_playlist(name_play);
            }
        }
        }
    } while (choice != 12);
    delete play;
    return 0;
}
