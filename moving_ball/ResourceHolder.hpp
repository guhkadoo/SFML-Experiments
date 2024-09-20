#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <SFML/Graphics.hpp>
#include <memory>

template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void        load(Identifier ID, const std::string& filename);
        template    <typename Parameter>
        void        load(Identifier ID, const std::string& filename, const Parameter& secondParam);
        Resource&   get(Identifier ID);
        const Resource& get(Identifier ID) const;

    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

#endif //RESOURCEHOLDER_HPP
