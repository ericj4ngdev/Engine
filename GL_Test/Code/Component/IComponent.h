#pragma once
class IComponent
{
public:
    IComponent() = default;

    IComponent(const IComponent& src) = default;

    virtual ~IComponent() = default;

    virtual void Start() = 0;

    virtual void Init() = 0;

    virtual void Tick(float elapsedTime) = 0;
};

