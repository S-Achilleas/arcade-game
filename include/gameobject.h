#pragma once
#include <string>

class GameObject {
    static int next_id;
protected:
    class GameState* state;
    std::string name;
    int id=0;
    bool active=true;

public:
    GameObject(const std::string& Name = "");
    virtual void update(float dt){}
    virtual void init(){}
    virtual void draw(){}
    virtual ~GameObject(){}
    bool isActive(){ return active; }
    void setActive(bool Active){ active = Active; }
};
