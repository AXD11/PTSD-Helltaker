#ifndef BOX_HPP
#define BOX_HPP

#include <memory>

#include "Tile.hpp"
#include "Wall.hpp"


class Box : public Tile {

public:
    Box();


    bool IsColliding(const std::shared_ptr<Wall>& other, int position) const;


    void MoveUp(int moveStep) { 
        m_Transform.translation.y += moveStep;
        SetCenter();
    }

    void MoveDown(int moveStep) { 
        m_Transform.translation.y -= moveStep;
        SetCenter();
    }

    void MoveRight(int moveStep) {
        m_Transform.translation.x += moveStep;
        SetCenter();
    }

    void MoveLeft(int moveStep) { 
        m_Transform.translation.x -= moveStep;
        SetCenter();
    }
};

#endif
