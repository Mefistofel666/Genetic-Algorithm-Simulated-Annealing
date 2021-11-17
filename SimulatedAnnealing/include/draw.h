#ifndef DRAW_H
#define DRAW_H

#include <SFML/Graphics.hpp>

class Field : public sf::CircleShape 
{
private:
    sf::Vector2f center;
    std::vector<std::vector<bool>> matrix;
    int size;
    sf::Color color;
    double sqSize;
public:
    Field(int n, sf::Vector2f c, std::vector<std::vector<bool>> m, double sq_size = 80, sf::Color color = sf::Color::Black);
    void drawHorizontal(sf::RenderTarget *rt);
    void drawVertical(sf::RenderTarget *rt);
    void draw(sf::RenderTarget *rt);
    void paint(sf::RenderTarget *rt);
    void insertPicture(sf::RenderTarget *rt, sf::Vector2f pos);

};


#endif