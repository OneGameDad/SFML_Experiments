#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

#include "HUDComponent.hpp"

/*NOTE: HUD Manager must be initialized last so it can grab all the necessary items*/
class HUDManager
{
private:
    std::vector<AHUDComponent> components;
public:
    HUDManager();
    ~HUDManager();

    void    init();
    void    update();
};