#include "ATextBox.h"

ATextBox::ATextBox(sf::Font& pFont)
{
    m_pFont = &pFont;
}

ATextBox::~ATextBox() = default;

void ATextBox::initialize()
{
    setPosition(0.0f, 0.0f);
    text.setFont(*m_pFont);
    text.setString(content);
    text.setFillColor(sf::Color::White);
    text.setPosition(getPosition());
    text.setStyle(sf::Text::Regular);
    text.setCharacterSize(charSize);
}

void ATextBox::update(float deltaTime)
{
/*    //TODO Update position
    if (isActive)
    {
        elapsed += deltaTime;
        if (elapsed >= duration)
        {
            isActive = false;
            elapsed = 0.0f;
            return;
        }
    }
*/
}

// Draws Text without Wrapping it
void ATextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isActive)
    {  
        target.draw(text);
    }
}

void ATextBox::activate()
{
    if (!isActive)
        isActive = true;
}

void ATextBox::setString(const std::string& str)
{
    content = str;
    text.setString(content);
}

void    ATextBox::setTextOffsets(float x, float y)
{
    offsetX = x;
    offsetY = y;
}

void    ATextBox::setDuration(float a_duration)
{
    if (a_duration < 0.0f)
        duration = 0.0f;
    else
        duration = a_duration;
}

std::string ATextBox::wrapText(const std::string& str)
{
    std::string result = "";
    size_t count = 0;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (count == lineLength)
        {
            result += '\n';
            result += str[i];
            count = 0;
        }
        else
        {
            result += str[i];
            count++;
        }
    }
    return (result);
}

void    ATextBox::setLineLength(size_t num)
{
    if (num == 0)
        throw std::out_of_range("The line length is too small: " + num);
    else if (num >= 100)
        throw std::out_of_range("The line length is too big (max size: 99): " + num);
    else   
        lineLength = num;
}