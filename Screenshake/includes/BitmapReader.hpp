#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

class BitmapReader {
private:
    sf::Image image;
    bool loaded = false;

    BitmapReader() = default;

public:
    BitmapReader(const BitmapReader&) = delete;
    BitmapReader& operator=(const BitmapReader&) = delete;

    static BitmapReader& Instance()
    {
        static BitmapReader instance;
        return instance;
    }

    void Load(const std::string& filename)
    {
        if (!image.loadFromFile(filename))
            throw std::runtime_error("Failed to load image: " + filename);
        loaded = true;
        std::cout << "Loaded image: " << filename << " (" 
                  << image.getSize().x << "x" << image.getSize().y << ")\n";
    }

    float GetFloat(unsigned int x, unsigned int y) const
    {
        if (!loaded)
            throw std::runtime_error("No image loaded!");
        if (x >= image.getSize().x || y >= image.getSize().y)
            throw std::out_of_range("Pixel coordinates out of bounds");

        sf::Color color = image.getPixel(x, y);
        float gray = (0.299f * color.r + 0.587f * color.g + 0.114f * color.b) / 255.0f;
        return gray;
    }

    float GetPerlinNoise(float u, float v) const
    {
        if (!loaded)
            throw std::runtime_error("No image loaded!");
        unsigned int x = static_cast<unsigned int>(u * (image.getSize().x - 1));
        unsigned int y = static_cast<unsigned int>(v * (image.getSize().y - 1));
        return GetFloat(x, y);
    }

    unsigned int GetWidth() const { return image.getSize().x; }
    unsigned int GetHeight() const { return image.getSize().y; }
};
