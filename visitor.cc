#include <iostream>
#include <vector>

class Widget;
class Gadget;

struct ObjectVisitor
{
    virtual void visit(Widget &) const = 0;
    virtual void visit(Gadget &) const = 0;
    virtual~ObjectVisitor() {}
};

struct Object
{
    virtual void accept(const ObjectVisitor &) = 0;
    virtual ~Object() {}
};

class Widget: public Object
{
public:
    explicit Widget(int serial) : serial_(serial) {}
    int get_serial()
    {
        return serial_;
    }

    void accept(const ObjectVisitor &visitor)
    {
        visitor.visit(*this);
    }

private:
    int serial_;
};

class Gadget: public Object
{
public:
    explicit Gadget(std::string name): name_(name) {}
    std::string get_name()
    {
        return name_;
    }

    void accept(const ObjectVisitor &visitor)
    {
        visitor.visit(*this);
    }

private:
    std::string name_;
};

class ObjectCollection
{
public:
    std::vector<Object*>& get_objects()
    {
        return objects_;
    }

    ObjectCollection(): objects_{new Widget(42), new Gadget("foo")}
    {
    }

    ~ObjectCollection()
    {
        while(!objects_.empty()) {
            objects_.erase(objects_.begin());
        }
    }
private:
    std::vector<Object*> objects_;
};

struct PrintVisitor: public ObjectVisitor
{
    void visit(Widget &w) const
    {
        std::cout << "serial: "  << w.get_serial() << std::endl;
    }

    void visit(Gadget &g) const
    {
        std::cout << "name: " << g.get_name() << std::endl;
    }

    void visit_objects(ObjectCollection &o) const
    {
        std::cout << "Visiting object collection" << std::endl;
        for(auto &obj: o.get_objects()) {
            obj->accept(*this);
        }
        std::cout << "All objects in collection have been visited" << std::endl;
    }
};

struct L33tVisitor: public ObjectVisitor
{
    void visit(Widget &w) const
    {
        std::cout << "S3R14L: "  << w.get_serial() << std::endl;
    }

    void visit(Gadget &g) const
    {
        std::cout << "N4M3: " << g.get_name() << std::endl;
    }

    void visit_objects(ObjectCollection &o) const
    {
        std::cout << "All ur objects r belong to us" << std::endl;
        for(auto &obj: o.get_objects()) {
            obj->accept(*this);
        }
        std::cout << "w00t!" << std::endl;
    }
};

int main()
{
    ObjectCollection o;
    PrintVisitor p;
    L33tVisitor l;
    p.visit_objects(o);
    l.visit_objects(o);
}

