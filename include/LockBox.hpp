#ifndef LOCKBOX_HPP
#define LOCKBOX_HPP

#include <Util/GameObject.hpp>
#include "Tile.hpp"
#include "Util/Image.hpp"
#include <string>
#include <memory>


class LockBox : public Tile{

public:
    LockBox():Tile(GA_RESOURCE_DIR"/Image/LockBox/lockbox.png"){
    }
};

#endif
