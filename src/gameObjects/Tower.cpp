#include "Tower.hpp"

Tower::Tower()
    : property_t()
    , property_s()
{
}

Tower::Tower(const TowerProperty& property_t, const ElementsMeshGl* mesh_t,
    const ShellProperty& property_s, const ElementsMeshGl* mesh_s)
{
    init(property_t, mesh_t, property_s, mesh_s);
}

void Tower::init(const TowerProperty& property_t, const ElementsMeshGl* mesh_t,
    const ShellProperty& property_s, const ElementsMeshGl* mesh_s)
{
    this->property_t = property_t;
    this->mesh_t = mesh_t;
    this->property_s = property_s;
    this->mesh_s = mesh_s;
}

Tower::~Tower()
{
}

Tower::Tower(const Tower& other)
    : property_t(other.property_t)
    , property_s(other.property_s)
{
    this->property_t = other.property_t;
    this->mesh_t = other.mesh_t;
    this->property_s = other.property_s;
    this->mesh_s = other.mesh_s;
}

Tower::Tower(Tower&& other)
    : property_t(other.property_t)
    , property_s(other.property_s)

{
    this->property_t = other.property_t;
    this->mesh_t = other.mesh_t;
    this->property_s = other.property_s;
    this->mesh_s = other.mesh_s;
}

Tower& Tower::operator=(const Tower& other)
{
    this->property_t = other.property_t;
    this->mesh_t = other.mesh_t;
    this->property_s = other.property_s;
    this->mesh_s = other.mesh_s;

    return *this;
}

Tower& Tower::operator=(Tower&& other)
{
    this->property_t = other.property_t;
    this->mesh_t = other.mesh_t;
    this->property_s = other.property_s;
    this->mesh_s = other.mesh_s;

    return *this;
}
