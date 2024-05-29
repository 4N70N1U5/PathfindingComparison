#include "../include/Button.hpp"

#include <iostream>

using namespace std;

Button::Button(sf::Vector2f size, sf::Vector2f position, string string, sf::Color backgroundColor)
{
    background.setSize(size);
    background.setFillColor(backgroundColor);
    background.setOutlineThickness(5);
    background.setOutlineColor(backgroundColor - sf::Color(30, 30, 30, 0));
    background.setPosition(position);

    font.loadFromFile("../fonts/NotoSansDisplay-SemiBold.ttf");

    int fontSize = 5 + (size.y / 15) * 5;

    label.setString(string);
    label.setFont(font);
    label.setCharacterSize(fontSize);
    label.setFillColor(sf::Color::Black);
    label.setPosition((int)position.x + (fontSize - 10), (int)position.y + (fontSize - 10));
}

// void Button::setSize(sf::Vector2f size)
// {
//     backgroundSize = size;
// }

// void Button::setClicked(bool clicked)
// {
//     // this->clicked = clicked;
//     backgroundColor = clicked ? backgroundColor - sf::Color(70, 70, 70, 0) : backgroundColor;
// }

bool Button::isHovered(sf::Vector2i mousePosition)
{
    return background.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
}

void Button::draw(sf::RenderTarget *target, sf::Color colorOffset)
{
    background.setFillColor(background.getFillColor() - colorOffset);
    background.setOutlineColor(background.getOutlineColor() - colorOffset);

    target->draw(background);
    target->draw(label);
}
