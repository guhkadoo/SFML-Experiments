#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <SFML/Graphics.hpp>

class Aircraft : public Entity
{
    public:
        enum Type
        {
            Eagle,
            Raptor,
        };

        explicit        Aircraft(Type type);

    private:
        Type    mType;
};

Aircraft::Aircraft(Type type)
: mType(type)
{
}

#endif //AIRCRAFT_HPP
