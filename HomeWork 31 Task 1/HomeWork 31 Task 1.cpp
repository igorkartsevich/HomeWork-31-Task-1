﻿#include <iostream>
#include <string>

class Toy {
public:
    Toy(std::string inName) : name(inName) {}
    Toy() : Toy("SomeToy") {}
    Toy(const Toy& other) {
        name = other.name;
    }

private:
    std::string name;
};

class shared_ptr_toy {
public:
    shared_ptr_toy() : shared_ptr_toy("SomeToy") {}
    shared_ptr_toy(std::string inName_toy) {
        ptr = new Toy(inName_toy);
        ptr_counter = new int(1);
    }
    shared_ptr_toy(const Toy& other_toy) {
        ptr = new Toy(other_toy);
        ptr_counter = new int(1);
    }
    shared_ptr_toy(const shared_ptr_toy& other_ptr) : ptr(other_ptr.ptr) {
        ptr_counter = new int(1);
        *other_ptr.ptr_counter = *other_ptr.ptr_counter + 1;
    }
    shared_ptr_toy& operator=(const shared_ptr_toy& other_ptr) {
        if (this == &other_ptr) return *this;
        if (ptr != nullptr) {
            if (*ptr_counter == 1) {
                delete ptr;
                delete ptr_counter;
            }
            else (*ptr_counter)--;
        }
        ptr = other_ptr.ptr;
        ptr_counter = new int(1);
        *other_ptr.ptr_counter = *other_ptr.ptr_counter + 1;
    }
    ~shared_ptr_toy() {
        if (ptr != nullptr) {
            if (*ptr_counter == 1) {
                delete ptr;
                delete ptr_counter;
            }
            else (*ptr_counter)--;
        }
    }

private:
    Toy* ptr = nullptr;
    int* ptr_counter = nullptr;
};

Toy make_shared_toy(std::string name) {
    Toy toy(name);
    return toy;
}

Toy make_shared_toy(const Toy& other_toy) {
    Toy toy(other_toy);
    return toy;
}

int main() {
    Toy ball = make_shared_toy("Ball");
    Toy ball_new = make_shared_toy(ball);

    shared_ptr_toy sometoy_ptr;
    shared_ptr_toy cube_ptr("Cube");
    shared_ptr_toy ball_ptr(ball);
    
    shared_ptr_toy ball_ptr_copy(ball_ptr);
    
    shared_ptr_toy ball_ptr_copy_1;
    ball_ptr_copy_1 = ball_ptr_copy;

    

    return 0;
}