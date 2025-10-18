#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "data.hpp"

/*NOTE: 1) Make sure the g_data is loaded and set. Then load this before creating and setting other objects, as they may reference it*/

class PerlinNoiseGenerator {
private:
    sf::Image image;
    bool loaded = false;
    unsigned int Width_ = 0;
    unsigned int Height_ = 0;

    PerlinNoiseGenerator() = default;

    float GetFloat(unsigned int x, unsigned int y) const
    {
        if (!loaded)
            throw std::runtime_error("No image loaded!");
        if (x >= Width_ || y >= Height_)
            throw std::out_of_range("Pixel coordinates out of bounds");

        sf::Color color = image.getPixel(x, y);
        float gray = (0.299f * color.r + 0.587f * color.g + 0.114f * color.b) / 255.0f;
        return (gray);
    }

    float GetFloatUV(float u, float v) const
    {
        if (!loaded)
            throw std::runtime_error("No image loaded!");
        unsigned int x = static_cast<unsigned int>(u * (Width_ - 1));
        unsigned int y = static_cast<unsigned int>(v * (Height_ - 1));
        return (GetFloat(x, y));
    }

   

public:
    PerlinNoiseGenerator(const PerlinNoiseGenerator&) = delete;
    PerlinNoiseGenerator& operator=(const PerlinNoiseGenerator&) = delete;

    static PerlinNoiseGenerator &Instance()
    {
        static PerlinNoiseGenerator instance;
        return instance;
    }

    void Load(const std::string &filename)
    {
        if (!image.loadFromFile(filename))
            throw std::runtime_error("Failed to load image: " + filename);
        loaded = true;
        Width_ = image.getSize().x;
        Height_ = image.getSize().y;
        std::cout << "Loaded image: " << filename << " (" << image.getSize().x << "x" << image.getSize().y << ")" << std::endl;
    }
    
    float getPerlinNoiseValue(double x, double y, double speedMultiplier)
    {
        static const double step = 0.01;
        // Convert time into x/y pixel coordinates
        float u = static_cast<float>(std::fmod(x * step * speedMultiplier, 1.0));
        float v = static_cast<float>(std::fmod(y * step * speedMultiplier, 1.0));
        
        float val = GetFloatUV(u, v);
        return (val);
    }
};
