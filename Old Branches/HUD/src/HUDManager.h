#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

#include "HUDComponent.h"

/*NOTE: HUD Manager must be initialized last so it can grab all the necessary items*/
class HUDManager
{
private:
    std::vector<HUDComponent> components;
public:
    HUDManager();
    ~HUDManager();

    void    initialize();
    void    update();
};