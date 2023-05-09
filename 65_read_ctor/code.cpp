#include "code.h"

#include <stdio.h>
#include <stdlib.h>

Pet::Pet(const char * n, const char * s) : name(n), species(s), hungerLevel(0) {
}

void Pet::feed(unsigned food) {
  if (food > hungerLevel) {
    hungerLevel = 0;
  }
  else {
    hungerLevel -= food;
  }
}

void Pet::getHungrier(unsigned howMuch) {
  hungerLevel += howMuch;
}

void Pet::describe(void) {
  printf("  %s the %s (who is ", name, species);
  if (hungerLevel < 5) {
    printf("satiated)\n");
  }
  else if (hungerLevel < 20) {
    printf("a bit hungry)\n");
  }
  else if (hungerLevel < 50) {
    printf("hungry)\n");
  }
  else if (hungerLevel < 100) {
    printf("very hungry)\n");
  }
  else {
    printf("STARVING!)\n");
  }
}

Person::Person(const char * n) : name(n), myPet(NULL) {
}

void Person::describe(void) {
  if (!havePet()) {
    printf("%s has no pet\n", name);
  }
  else {
    printf("%s has the pet:\n", name);
    myPet->describe();
  }
}

void Person::feedPet(unsigned food) {
  if (havePet()) {
    myPet->feed(food);
  }
}

bool Person::havePet(void) {
  return myPet != NULL;
}

void Person::setPet(Pet * p) {
  myPet = p;
}

int main(void) {
  Person ** people = new Person *[3];
  Pet ** pets = new Pet *[2];
  people[0] = new Person("Hades");
  people[1] = new Person("Perseus");
  people[2] = new Person("Zeus");
  pets[0] = new Pet("Cerberus", "3-headed dog");
  pets[1] = new Pet("Pegasus", "flying horse");
  people[0]->setPet(pets[0]);
  people[1]->setPet(pets[1]);
  for (int i = 0; i < 2; i++) {
    pets[i]->getHungrier(20 * i + 60);
  }
  for (int i = 0; i < 3; i++) {
    people[i]->feedPet(50 - 10 * i);
    people[i]->describe();
  }
  for (int i = 0; i < 3; i++) {
    delete people[i];
  }
  for (int i = 0; i < 2; i++) {
    delete pets[i];
  }
  delete[] people;
  delete[] pets;
  return EXIT_SUCCESS;
}
