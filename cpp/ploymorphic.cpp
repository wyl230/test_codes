
#include <iostream>
#include <string>

class Shape {
public:
  Shape(const std::string &name) : name(name) {}

  virtual double area() const = 0;
  virtual void printInfo() const {
    std::cout << "Shape: " << name << std::endl;
  }

private:
  std::string name;

protected:
  const std::string &getName() const { return name; }
};

class Circle : public Shape {
public:
  Circle(const std::string &name, double radius)
      : Shape(name), radius(radius) {}

  double area() const override { return 3.14159 * radius * radius; }

  void printInfo() const override {
    std::cout << "Circle: " << Shape::getName() << ", Radius: " << radius
              << ", Area: " << area() << std::endl;
  }

private:
  double radius;
};

class Rectangle : public Shape {
public:
  Rectangle(const std::string &name, double length, double width)
      : Shape(name), length(length), width(width) {}

  double area() const override { return length * width; }

  void printInfo() const override {
    std::cout << "Rectangle: " << Shape::getName() << ", Length: " << length
              << ", Width: " << width << ", Area: " << area() << std::endl;
  }

private:
  double length;
  double width;
};

int main() {
  Circle circle("Circle 1", 5.0);
  Rectangle rectangle("Rectangle 1", 4.0, 6.0);

  Shape *shape1 = &circle;
  Shape *shape2 = &rectangle;

  shape1->printInfo();
  shape2->printInfo();

  return 0;
}
