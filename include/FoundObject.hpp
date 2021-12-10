#pragma once

class FoundObject
{
private:
    std::tuple<float, float> location;
    std::tuple<float, float> size;//misschien los width height depth

public:
    FoundObject(/* args */);
    ~FoundObject();
};

