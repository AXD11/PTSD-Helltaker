#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <memory>
#include <string>

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Logger.hpp"


class Background : public Util::GameObject {

public:
    Background(const std::string image);

    void SetImage(std::string image) { m_Drawable = std::make_shared<Util::Image>(image); }
};

#endif
