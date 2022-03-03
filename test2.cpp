// condition_variable example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique
#include <condition_variable> // std::condition_variable
#include <time.h>
#include <chrono>

std::mutex minotaur_mtx;
std::mutex mtx[8];
std::condition_variable cv;
bool cupcake = true;
bool all_guests = false;
int current_guest = -1;
int n = 8;

void enterLabyrinth(int id)
{
    mtx[id].lock();
    if (cupcake && id == current_guest)
    {
        cupcake = false;
        std::cout << "guest " << id << " ate the cupcake." << std::endl;
    }
    //std::cout << "guest " << id << " has completed the labyrinth" << std::endl;
}

void minotaur()
{
    while(!all_guests)
    {
        int num = rand() % 8;
        current_guest = num;
        std::cout << "current guest " << current_guest << std::endl;
        mtx[current_guest].unlock();
        minotaur

        if(current_guest == 0)
        {
            break;
        }
    }
}

int main()
{
    srand(time(NULL));
    std::thread threads[8];
    // spawn 8 threads:
    for (int i=0; i<8; i++)
        //threads[i] = std::thread(enterLabyrinth, i);

    minotaur();
    
    for (auto& th: threads) th.join();

    return 0;
}