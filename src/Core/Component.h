#pragma once

namespace core
{

class Component
{
    public:
        Component();
        virtual ~Component();

        Component(Component const&) = delete;
        Component& operator=(Component const&) = delete;

};

} // namespace