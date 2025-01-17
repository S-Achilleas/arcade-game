#include "gameobject.h"
#include "gamestate.h"

GameObject::GameObject(const std::string &Name)
    :name(Name) , state(GameState::getInstance()),id(next_id++){}

GameObject::~GameObject() {
}

int GameObject::next_id = 1;
