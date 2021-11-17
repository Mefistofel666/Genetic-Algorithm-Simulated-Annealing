#include <draw.h>
#include <cmath>

Field::Field(int n, sf::Vector2f c, std::vector<std::vector<bool>> m, double sq_size, sf::Color clr)
{
    size = n;
    center = c;
    matrix = m;
    color = clr;
    sqSize = sq_size;
}
void Field::drawHorizontal(sf::RenderTarget *rt)
{
    double length = sqSize * size;
    sf::RectangleShape line(sf::Vector2f(length, 4.f));
    line.setOrigin(length / 2.0, 2);
            
    line.setPosition(center - sf::Vector2f(0, length / 2));
    line.setFillColor(color);
    int tmp = size + 1;
    while(tmp != 0)
    {
        rt->draw(line);
        line.move(0, sqSize);
        tmp--;
    }

}
void Field::drawVertical(sf::RenderTarget *rt)
{
    double length = sqSize * size;
    sf::RectangleShape line(sf::Vector2f(length, 4.f));
    line.setOrigin(length / 2.0, 2);
    line.rotate(90);
            
    line.setPosition(center - sf::Vector2f(length / 2, 0));
    line.setFillColor(color);
    int tmp = size + 1;
    while(tmp != 0)
    {
        rt->draw(line);
        line.move(sqSize, 0);
        tmp--;
    }
    // // draw center of field
    // sf::CircleShape circle;
    // circle.setRadius(10);
    // circle.setOutlineColor(sf::Color::Red);
    // circle.setOutlineThickness(5);
    // circle.setOrigin(10,10);
    // circle.setPosition(center);
    // rt->draw(circle);
}



void Field::paint(sf::RenderTarget *rt)
{
    sf::Vector2f start = center - sf::Vector2f( (size - 1) * sqSize / 2.0, (size - 1) * sqSize / 2.0 );
    double rad = sqSize / sqrt(2);
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if (matrix[i][j])
            {   
                sf::Vector2f pos = start + sf::Vector2f(j * sqSize, i * sqSize );
                insertPicture(rt, pos);
            }
        }
    }
}


void Field::insertPicture(sf::RenderTarget *rt, sf::Vector2f pos)
{
    sf::Texture texture; 
    texture.loadFromFile("src/queen.png");
    sf::Vector2u size = texture.getSize();
    sf::Sprite sprite;
    sprite.setScale(sqSize / 80.0, sqSize / 80.0);
    sprite.setTexture(texture);
    sprite.setOrigin(size.x / 2.0, size.y / 2.0);
    sprite.setPosition(pos);
    rt->draw(sprite);
}