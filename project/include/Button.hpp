#ifndef Button_HPP
#define Button_HPP

#include <SFML/Graphics.hpp>

using namespace std;

class Button
{
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text label;

public:
    Button(sf::Vector2f, sf::Vector2f, string, sf::Color = sf::Color(225, 225, 225));

    // void setClicked(bool);

    bool isHovered(sf::Vector2i);

    void draw(sf::RenderTarget *, sf::Color = sf::Color(0, 0, 0, 0));
};

#endif