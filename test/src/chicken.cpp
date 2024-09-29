#include <iostream>
#include <cstring>

class Chicken {
private:
    int age;
    char *name;

public:

    Chicken() : age(24), name(nullptr) {}

    explicit Chicken(int _age) : age(_age), name(nullptr) {}

    Chicken(int _age, const char *_name) : age(_age), name(nullptr) {
        if (_name) {
            name = new char[strlen(_name) + 1];
            strcpy(name, _name);
        }
    }

    Chicken(const Chicken &other) : age(other.age), name(nullptr) {
        if (other.name) {
            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
        }
    }

    Chicken& operator=(const Chicken &other) {
        if (this != &other) { 
            delete[] name;
            age = other.age;
            if (other.name) {
                name = new char[strlen(other.name) + 1];
                strcpy(name, other.name);
            } else {
                name = nullptr;
            }
        }
        return *this;
    }

    ~Chicken() {
        delete[] name;
    }

    void setName(const char *_name) {
        if (name) {
            delete[] name;
        }
        if (_name) {
            name = new char[strlen(_name) + 1];
            strcpy(name, _name);
        } else {
            name = nullptr;
        }
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }
};

int main() {
    auto print = [](const Chicken &c) {
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old." << std::endl;
    };
    Chicken c(24, "Kunkun");
    print(c);
    Chicken d;
    d = c;
    print(d); // 测试【赋值运算符】是否正确
    Chicken a = c;
    print(a); // 测试【复制构造函数】是否正确
    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d); // 测试是否为【深度复制】
    Chicken b;
    b = d = c;
    print(b);
    print(d); // 测试【连续赋值】功能
    return 0;
}
