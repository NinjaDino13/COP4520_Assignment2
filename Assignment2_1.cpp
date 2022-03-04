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
    bool has_eaten = false; // Whether this guest has eaten a cupcake.
    while(!all_guests)
    {
        std::unique_lock<std::mutex> lck(mtx); // Locking the guest until they have been notified
        while (!may_enter[id]) cv[id].wait(lck);
        if (all_guests) break;
        if(output) std::cout << "guest " << id << " has entered the labyrinth";
        // Having the guest eat the cupcake if they haven't already.
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
                // Guest 0 counts how many cupcakes have been eaten and calls a new one.
                cupcake = true;
                guest_counted++;
                if(output) std::cout << ", counted " << guest_counted << " guests";
                if(output) std::cout << " and replaced the cupcake." << std::endl;
                if (guest_counted == 8)
                    all_guests = true;
            }
            else
            {
                // Guest 0 does nothing in this instance
                if(output) std::cout << ", but no one else has entered since the last entry." << std::endl;
            }
        }
        else
        {
            // Guest has already eaten or found no cupcake.
            if(output) std::cout << " and found no cupcake." << std::endl;
        }

        // Guest leaves the labyrinth and lets the minotaur know.
        may_enter[id] = false;
        guest_in = false;
        minotaur_cv.notify_one();
        if(output) std::cout << "guest " << id << " has left the labyrinth" << std::endl;
    }
}

void minotaur()
{
    while(!all_guests)
    {
        // Since the guests have not let the minotaur know they have all entered, he will keep calling in a random guest
        current_guest = rand() % 8;
        if(output) std::cout << "Guest " << current_guest << " has been chosen by the Minotaur." << std::endl;
        may_enter[current_guest] = true;
        guest_in = true;
        cv[current_guest].notify_one(); // Notifying the guest of being chosen.
        std::unique_lock<std::mutex> lck(mtx); // Locking the Minotaur until the guest in the labyrinth leaves.
        while (guest_in) minotaur_cv.wait(lck); 
    }
    std::cout << "\nAll guests have experienced the maze." << std::endl;
    // Waking up the threads one last time so that they may join.
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