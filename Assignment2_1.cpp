#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <time.h>
#include <vector>
#include <cctype>

std::mutex mtx;
std::condition_variable cv[8];
std::condition_variable minotaur_cv;
bool cupcake = true;
bool all_guests = false;
bool may_enter[8];
bool guest_in = false;
int current_guest = -1;
int guest_counted = 1;
int n = 8;
bool output;

void enterLabyrinth(int id)
{
    bool has_eaten = false;
    while(!all_guests)
    {
        std::unique_lock<std::mutex> lck(mtx);
        while (!may_enter[id]) cv[id].wait(lck);
        if (all_guests) break;
        if(output) std::cout << "guest " << id << " has entered the labyrinth";
        if (cupcake && !has_eaten && id != 0)
        {
            has_eaten = true;
            cupcake = false;
            if(output) std::cout << " and ate the cupcake." << std::endl;
        }
        else if (id == 0)
        {
            if (!cupcake)
            {
                cupcake = true;
                guest_counted++;
                if(output) std::cout << ", counted " << guest_counted << " guests";
                if(output) std::cout << " and replaced the cupcake." << std::endl;
                if (guest_counted == 8)
                    all_guests = true;
            }
            else
            {
                if(output) std::cout << ", but no one else has entered since the last entry." << std::endl;
            }
        }
        else
        {
            if(output) std::cout << " and found no cupcake." << std::endl;
        }

        may_enter[id] = false;
        guest_in = false;
        minotaur_cv.notify_one();
        if(output) std::cout << "guest " << id << " has left the labyrinth" << std::endl;
    }
    //std::cout << "Thread " << id << " has finished" << std::endl;
}

void minotaur()
{
    while(!all_guests)
    {
        current_guest = rand() % 8;
        if(output) std::cout << "Guest " << current_guest << " has been chosen by the Minotaur." << std::endl;
        may_enter[current_guest] = true;
        guest_in = true;
        cv[current_guest].notify_one();
        std::unique_lock<std::mutex> lck(mtx);
        while (guest_in) minotaur_cv.wait(lck);
    }
    std::cout << "\nAll guests have experienced the maze." << std::endl;
    for (int i = 0; i < 8; i++) {
        may_enter[i] = true;
        cv[i].notify_one();
    }
}

int main()
{
    srand(time(NULL));
    bool valid = false;
    char to_output;
    std::cout << "Print output (y/n)?" << std::endl;
    std::cin >> to_output;
    do
    {
        if(tolower(to_output) != 'y' && tolower(to_output) != 'n')
        {
            std::cout << "Enter in either y or n." << std::endl;
            std::cin >> to_output;
            std::cout << to_output << std::endl;
        }
        else 
        {
            valid = true;
            if (tolower(to_output) == 'y') output = true;
            else output = false;
        }
    } while (!valid);
    std::cout << "Minotaur begins the party with 8 guests.\n" << std::endl;

    std::vector<std::thread> guests;
    for (int i = 0; i < 8; i++)
    {
        may_enter[i] = false;
        guests.push_back(std::thread(enterLabyrinth, i));
    }

    minotaur();
    
    for (std::thread &gu : guests) gu.join();

    return 0;
}