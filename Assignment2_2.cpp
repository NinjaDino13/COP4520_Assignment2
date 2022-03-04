#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable guest;

// Used to show if the viewing room is open or not.
bool available = true;

// When a guest is viewing the vase, no other guest can enter the room.
void viewVase (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!available) guest.wait(lck); // Waiting for the room to be avoilable.
  available = false; // Viewing room is not available anymore.
  std::cout << "Guest " << id << " is currently viewing the vase " << std::endl;
  available = true; // Viewing room is now available again.
  guest.notify_one();
}

int main ()
{
  std::cout << "8 guests will begin viewing the vase, using strategy 2.\n" << std::endl;

  std::thread viewers[8];

  for (int i=0; i<8; ++i) {
    viewers[i] = std::thread(viewVase, i+1);
  }

  for (std::thread &vi : viewers) vi.join();

  std::cout << "\nAll guests have viewed the vase" << std::endl;
  return 0;
}