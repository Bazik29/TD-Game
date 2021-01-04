#pragma once

#include "../logicObjects/TowerProperty.hpp"
#include "../renderObjects/ElementsMeshGl.hpp"

class Tower {
public:
    Tower();
    Tower(const TowerProperty& property_t, const ElementsMeshGl* mesh_t,
        const ShellProperty& property_s, const ElementsMeshGl* mesh_s);
    ~Tower();
    Tower(const Tower& other);
    Tower(Tower&& other);
    Tower& operator=(const Tower& other);
    Tower& operator=(Tower&& other);

    void init(const TowerProperty& property_t, const ElementsMeshGl* mesh_t,
        const ShellProperty& property_s, const ElementsMeshGl* mesh_s);

    inline const TowerProperty& getPropsT() const;
    inline const ElementsMeshGl* getMeshT() const;

    inline const ShellProperty& getPropsS() const;
    inline const ElementsMeshGl* getMeshS() const;

private:
    TowerProperty property_t;
    const ElementsMeshGl* mesh_t;

    ShellProperty property_s;
    const ElementsMeshGl* mesh_s;
};

inline const TowerProperty& Tower::getPropsT() const
{
    return property_t;
}

inline const ElementsMeshGl* Tower::getMeshT() const
{
    return mesh_t;
}

inline const ShellProperty& Tower::getPropsS() const
{
    return property_s;
}

inline const ElementsMeshGl* Tower::getMeshS() const
{
    return mesh_s;
}
