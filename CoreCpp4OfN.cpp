#include <memory>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

class Shape {
  public:
    Shape() {}
    virtual ~Shape() {}
    // NVI: Non-Virtual Interface.
    void draw(int x, int y) {
        cout << "non-virtual! Shape::draw(" << x << ", " << y << ")" << endl;
        do_draw(x, y);
        cout << "Shape::draw() says by!" << endl;
    }

  private:
    virtual void do_draw(int x, int y) = 0;
    Shape(const Shape&);
    Shape& operator=(const Shape&);
};

class Polygon : public Shape {
  private:
    virtual void do_draw(int x, int y) override {
        cout << "Polygon::do_draw(" << x << ", " << y << ")" << endl;
    }
};

class Evilgon : public Shape {
  public:
    virtual void draw(double x, double y) /*override*/ {
        cout << "Evilgon::draw(" << x << ", " << y << ")" << endl;
    }

  private:
    virtual void do_draw(int x, int y) override { draw(x, y); }
};

class Triangle /*final*/ : public Polygon {
  private:
    virtual void do_draw(int x, int y) /*final*/ override {
        cout << "Triangle::draw(" << x << ", " << y << ")" << endl;
    }
};

class BermudaTriangle : public Triangle {
  private:
    virtual void do_draw(int x, int y) override {
        cout << "BermudaTriangle::draw(" << x << ", " << y << ")" << endl;
    }
};

int main() {
    shared_ptr<Shape> shape = make_shared<Polygon>();
    shape->draw(11, 22);

    shape = make_shared<Evilgon>();
    // Calls Shape::draw(int, int)
    shape->draw(33, 44);

    return 0;
}
