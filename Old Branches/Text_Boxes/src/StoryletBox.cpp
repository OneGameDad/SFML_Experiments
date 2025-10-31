#include "StoryletBox.h"

StoryletBox::StoryletBox(sf::Font& pFont, const std::string& value)
    : ATextBox(pFont)
{
    content = value;
    content = wrapText(content);
    text.setString(content);
    std::cout << "Storylet Contructed, Content: " << content << std::endl;
}

StoryletBox::~StoryletBox() = default;

void    StoryletBox::initialize()
{
    text.setPosition(getPosition());
    text.setFont(*m_pFont);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(charSize);
    std::cout << "Storylet Initialized." << std::endl;
}

void    StoryletBox::initialize(sf::Vector2f a_position, unsigned int fontSize)
{
    setPosition(a_position);
    text.setPosition(getPosition());
    text.setFont(*m_pFont);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Italic);
    text.setCharacterSize(fontSize);
    std::cout << "Storylet Initialized." << std::endl;
}

void    StoryletBox::update(float deltatime)
{
    (void) deltatime;
    std::cout << "Storylet Updated." << std::endl;
}

void    StoryletBox::update(const std::string& str)
{
    content = str;
    content = wrapText(content);
    text.setString(content);
    std::cout << "Storylet Updated, Content Now: " << content << std::endl;
}

void    StoryletBox::activate()
{
    if (!isActive)
        isActive = true;
}

void    StoryletBox::deactivate()
{
    if (isActive)
        isActive = false;
}

void StoryletBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
