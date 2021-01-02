#pragma once

class ShellEntity
{
public:
    ShellEntity();
    virtual ~ShellEntity(); // TODO: Is VIRTUAL needed?
    ShellEntity(const ShellEntity &other) = default;
    ShellEntity(ShellEntity &&other) = default;
    ShellEntity &operator=(const ShellEntity &other) = default;
    ShellEntity &operator=(ShellEntity &&other) = default;

private:
    // Members
};
