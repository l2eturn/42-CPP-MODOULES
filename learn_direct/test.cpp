#include <iostream>

class Widget {
public:
    static int count;
    Widget() {
        count++;
    }
    static int howMany() {
        return count;
    }
};

int Widget::count = 0;

int main()
{
    Widget a;
    Widget b;
    Widget c;
    (void)a; (void)b; (void)c;
    std::cout << Widget::howMany() << std::endl;
    return 0;
}
