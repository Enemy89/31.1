#include <iostream>
#include <memory>
#include <string>

class Toy {
std::string toyName;
public:
    Toy(std::string inName) : toyName(inName) {};
    Toy() : toyName("SomeToy") {};
    ~Toy() {
        std::cout << "Toy " << toyName << " was dropped " << std::endl;
    }
};

class Dog {
    std::string dogName;
    int age;
    std::shared_ptr<Toy> lovelyToy;
public:
    Dog(std::string inName, std::shared_ptr<Toy> inLovelyToy, int inAge) : dogName(inName), lovelyToy(inLovelyToy) {
        if (inAge>=0 && inAge<30) {
            age = inAge;
        }
    }
    Dog () : Dog("Snow", std::make_shared<Toy>("SomeToy"), 0) {};
    Dog(std::string inName, int inAge) : Dog(inName, std::make_shared<Toy>("SomeToy"), inAge) {};
    Dog (std::string inName) : Dog(inName, std::make_shared<Toy>("SomeToy"), 0) {};
    Dog (int inAge) : Dog ("Snow", std::make_shared<Toy>("SomeToy"), inAge) {};

    void getToy(const std::shared_ptr<Toy>& toy) {
        if (lovelyToy == toy) {
            std::cout << "I already have this toy." << std::endl;
        } else if (toy.use_count() > 1) {
            std::cout << "Another dog is playing with this toy." << std::endl;
        } else {
            lovelyToy=toy;
            std::cout << "My darling!" << std::endl;
        }
    }

    void dropToy () {
        if (lovelyToy.use_count() > 1) {
            lovelyToy.reset();
        } else {
            std::cout << "Nothing to drop." << std::endl;
        }
    }
};

int main() {
    std::shared_ptr<Toy> bone = std::make_shared<Toy>("Bone");
    std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");

    //std::cout<<bone.use_count()<<std::endl;

    Dog a("Bobik", bone, 12);
    Dog b("Richi", 7);
    Dog c("Mino", 2);
    Dog d("Princess", 5);

    a.getToy(bone);
    //std::cout<<bone.use_count()<<std::endl;
    b.getToy(bone);
    //std::cout<<bone.use_count()<<std::endl;
    a.dropToy();
    //std::cout<<bone.use_count()<<std::endl;
    b.getToy(bone);
    //std::cout<<bone.use_count()<<std::endl;
    c.getToy(bone);
    c.dropToy();
}