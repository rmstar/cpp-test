class Object
{

public:
    static Object create_gadget()
    {
        return Object(ObjectType::GADGET);
    }

    static Object create_widget()
    {
        return Object(ObjectType::WIDGET);
    }

private:
    enum class ObjectType {GADGET, WIDGET};
    Object(ObjectType) {}

};

int main()
{
    Object o1 = Object::create_gadget();
    Object o2 = Object::create_widget();
}
