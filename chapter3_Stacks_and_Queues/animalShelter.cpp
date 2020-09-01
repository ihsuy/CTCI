#include <time.h>

#include <iostream>
#include <list>
#include <random>
#include <string>

using namespace std;

struct animal {
    const string kind;
    int id;

    animal(const string& k) : kind(k), id(-1) {}
    void add_label(const int& ID) { id = ID; }
};

struct cat : public animal {
    cat() : animal("Cat") {}
};

struct dog : public animal {
    dog() : animal("Dog") {}
};

struct animalShelter {
    int order;

    list<animal> dogs;
    list<animal> cats;

    animalShelter() : order(0) {}

    void enqueue(animal& new_animal);
    void dequeueAny();
    void dequeueDog();
    void dequeueCat();

    void inspect() const;
};

void animalShelter::enqueue(animal& new_animal) {
    new_animal.add_label(order);
    order++;

    if (new_animal.kind == "Cat") {
        cats.push_back(new_animal);
    } else {
        dogs.push_back(new_animal);
    }
}

void animalShelter::dequeueAny() {
    if ((cats.size() == 0 or dogs.front().id < cats.front().id) and
        (dogs.size() != 0)) {
        dequeueDog();
    } else if ((dogs.size() == 0 or dogs.front().id > cats.front().id) and
               (cats.size() != 0)) {
        dequeueCat();
    } else if (dogs.size() == 0 and cats.size() == 0) {
        cout << "Animal Shelter is empty." << endl;
    } else {
        cout << "duplicated id, no two animals can have the same id." << endl;
    }
}

void animalShelter::dequeueCat() {
    cats.pop_front();
}

void animalShelter::dequeueDog() {
    dogs.pop_front();
}

void animalShelter::inspect() const {
    cout << "===inspection===" << endl;
    cout << "Dogs: ";
    for (auto dog : dogs) {
        cout << dog.id << " ";
    }
    cout << endl;
    cout << "Cats: ";
    for (auto cat : cats) {
        cout << cat.id << " ";
    }
    cout << endl;
}

int main() {
    // generate animals and put them into shelter
    auto seed = (int)chrono::system_clock::now().time_since_epoch().count();
    srand(seed);

    animalShelter home;
    const int nanimal = 30;

    animal* animals[nanimal];

    for (int i = 0; i < nanimal; ++i) {
        animals[i] = new animal("Cat");
        if (rand() % 2) {
            animals[i] = new animal("Cat");
        } else {
            animals[i] = new animal("Dog");
        }
    }

    for (int i = 0; i < nanimal; ++i) {
        home.enqueue(*animals[i]);
    }

    home.inspect();

    for (int i = 0; i < nanimal + 1; ++i) {
        home.dequeueAny();
        home.inspect();
    }

    return 0;
}