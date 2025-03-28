#ifndef BOX_HPP
#define BOX_HPP

#include <memory>

#include "Hero.hpp"
#include "Tile.hpp"
#include "Wall.hpp"


class Box : public Tile {

public:
    Box();


    bool IsColliding(const std::shared_ptr<Wall>& other, int position) const;

    bool IsColliding(const std::shared_ptr<Box>& other, int position) const;

    void Move(int moveStep, int position) { 
        switch (position) {
            case 1:
                m_Transform.translation.y += moveStep;
                break;
            case 2:
                m_Transform.translation.y -= moveStep;
                break;
            case 3:
                m_Transform.translation.x -= moveStep;
                break;
            case 4:
                m_Transform.translation.x += moveStep;
                break;
            default:
                break;
        
        }
        SetCenter();
    }

    bool CanMove(Direction position, const std::vector<std::shared_ptr<Tile>>& tiles);
};

#endif
