#include <iostream>
#include <string>

class Toy {
public:
    static int ptr_counter;

    Toy(std::string inName) : name(inName) {};

    Toy(const Toy& other_toy) {
        name = other_toy.name;
        ptr_counter++;
    }

private:
    std::string name;

};

int Toy::ptr_counter = 0;

class Shared_toy_ptr {
public:
    Shared_toy_ptr() : Shared_toy_ptr("SomeToy") {};

    Shared_toy_ptr(std::string inName) {
        toy_ptr = new Toy(inName);
    }

    Shared_toy_ptr(const Toy& other) {
        toy_ptr = new Toy(other);
    }

    Shared_toy_ptr(const Shared_toy_ptr& other) {
        toy_ptr = new Toy(*other.toy_ptr);
    }

    Shared_toy_ptr& operator = (const Shared_toy_ptr& other) {
        if (this == &other) return *this;
        if (toy_ptr != nullptr) delete toy_ptr;
        toy_ptr = new Toy(*other.toy_ptr);
        return *this;
    }

    ~Shared_toy_ptr() {
        if (toy_ptr->ptr_counter != 0) toy_ptr->ptr_counter--;
        else delete toy_ptr;
    }

private:
    Toy* toy_ptr = nullptr;
};

Toy& make_shared_toy(std::string name) {
    Toy* toy = new Toy(name);
    return *toy;
}

Toy& make_shared_toy(const Toy& other_toy) {
    Toy* toy = new Toy(other_toy);
    return *toy;
}

int main() {
    Toy ball = make_shared_toy("Ball");
    Toy ball_1 = make_shared_toy(ball);

    Shared_toy_ptr ptr("Stick");

    Shared_toy_ptr ptr_ball_1(ball);
    Shared_toy_ptr ptr_ball_2(ptr_ball_1);

    Shared_toy_ptr ptr_ball_3("SomeToy");
    ptr_ball_3 = ptr_ball_2;

    return 0;
}