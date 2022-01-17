#include <iostream>
#include <string>


class Toy {
public:
    Toy(std::string inName_toy) : name_toy(inName_toy) {}

    Toy(const Toy& other) {
        name_toy = other.name_toy;
    }

    Toy() : Toy("SomeToy") {}

private:
    std::string name_toy;
};


class Shared_ptr_toy {
public:
    Shared_ptr_toy() : Shared_ptr_toy("SomeToy") {}

    Shared_ptr_toy(std::string name) {
        obj = new Toy(name);
        counter = new int(0);
    }
    
    Shared_ptr_toy(Toy& other_toy) {
        obj = new Toy(other_toy);
        counter = new int(0);
    }
    
    Shared_ptr_toy(const Shared_ptr_toy& other_toy) {
        obj = new Toy(*other_toy.obj);
        counter = new int(0);
        *other_toy.counter = *other_toy.counter + 1;
    }

    Shared_ptr_toy& operator=(const Shared_ptr_toy& other_toy) {
        if (this == &other_toy) return *this;
        if (obj != nullptr) delete obj;
        
        obj = new Toy(*other_toy.obj);
        counter = new int(0);
        *other_toy.counter = *other_toy.counter + 1;
    }

    ~Shared_ptr_toy() {
        if (*counter == 0) {
            delete obj;
            delete counter;
        }
        else *counter = *counter - 1;
    }

private:
    Toy* obj = nullptr;
    int* counter = nullptr;
};

Toy make_shared_toy(std::string name) {
    Toy toy(name);
    return toy;
}

Toy make_shared_toy(const Toy& other) {
    Toy toy(other);
    return toy;
}

int main() {
    Toy toy_ball = make_shared_toy("Ball");
    Toy toy_ball_copy = make_shared_toy(toy_ball);

    Shared_ptr_toy ptr_cube = Shared_ptr_toy("Cube");

    Shared_ptr_toy ptr_ball = Shared_ptr_toy(toy_ball);
    Shared_ptr_toy ptr_ball_1 = Shared_ptr_toy(ptr_ball);
    Shared_ptr_toy ptr_ball_2 = ptr_ball_1;
    
    return 0;
}