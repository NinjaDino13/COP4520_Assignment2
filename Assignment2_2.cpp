#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable guest;

bool available = true;

void viewVase (int id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (!available) guest.wait(lck);
  available = false;
  std::cout << "Guest " << id << " is currently viewing the vase " << std::endl;
  available = true;
  guest.notify_one();
}

int main ()
{
  std::thread viewers[10];

  for (int i=0; i<10; ++i) {
    viewers[i] = std::thread(viewVase, i+1);
  }

  for (std::thread &vi : viewers) vi.join();

  std::cout << "\nAll guests have viewed the vase" << std::endl;
  return 0;
}