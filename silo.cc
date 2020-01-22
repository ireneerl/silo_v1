#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::memory_order_relaxed
#include <thread>         // std::thread

std::atomic_int foo (0);
int foo2=0;

void set_foo(int x) {
  foo.store(x,std::memory_order_relaxed);     // set value atomically
}

void print_foo() {
  int x;

  do {
    x = foo.load(std::memory_order_relaxed);  // get value atomically
  } while (x==0);
  std::cout << "foo: " << x << '\n';
}
void set_foo_non_atomic(int x) {
  foo2 = x;     // set value atomically
}
void print_foo_non_atomic(){
  int y;
  do{
    y = foo2;
  }while(y==0);
    std::cout << "foo-2: " << y << '\n';

}

int main ()
{
  std::thread first (print_foo);
  std::thread second (set_foo,10);
    std::thread third (print_foo_non_atomic);
    std::thread fourth (set_foo_non_atomic,10);
  first.join();
  second.join();
  third.join();
  fourth.join();
  return 0;
}
//output: foo: 10
//running -> g++ silo.cc -std=c++0x -lpthread -o silo
