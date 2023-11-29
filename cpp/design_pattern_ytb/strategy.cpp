#include <iostream>
#include <memory>

class Animal {
public:
  virtual ~Animal() = default;
  virtual void makeSound() = 0;
  virtual void tryFly() = 0;
};

class Dog : public Animal {
public:
  void makeSound() override { std::cout << "woof" << std::endl; }
  void tryFly() override { std::cout << "can fly" << std::endl; }
};

class Bird : public Animal {
public:
  void makeSound() override { std::cout << "chirp" << std::endl; }
  void tryFly() override { std::cout << "cannot fly" << std::endl; }
};

int main(int, char *[]) {
  std::unique_ptr<Animal> pDog = std::make_unique<Dog>();
  std::unique_ptr<Animal> pBird = std::make_unique<Bird>();

  pDog->makeSound();
  pBird->makeSound();

  pDog->tryFly();
  pBird->tryFly();

  return 0;
}
