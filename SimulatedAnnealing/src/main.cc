#include <iostream>
#include <simAnnealing.h>
#include <draw.h>
#include <chrono>


int main()
{
    int fieldSize = 20;
    SimAnnealing *alg = new SimAnnealing(fieldSize, 4000, 0.99);

    double time = 0;
    auto begin = std::chrono::steady_clock::now();

    std::vector<int> res = alg->run();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    time = elapsed_seconds.count();
    std::cout << "Time: " << time << "\n";

    for(int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " ";
    }
    std::cout << "\n";

    if (fieldSize > 40)
        return 0;

    const unsigned width = 1500;
    const unsigned height = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "Window");
    sf::RenderTexture rt;
    rt.create(width, height);

    std::vector <std::vector <bool> > M(fieldSize, std::vector<bool>(fieldSize));
    for(int i = 0; i < fieldSize; i++)
    {
        for(int j = 0; j < fieldSize; j++)
        {
            M[i][j] = false;
        }
    }
    for(int i = 0; i < fieldSize; i++)
    {
        M[res[i]][i] = true;
    }

    

    Field *field = new Field(fieldSize, sf::Vector2f(width / 2, height / 2), M, height / (fieldSize + 1 ));
    field->paint(&rt);  
    field->drawHorizontal(&rt);
    field->drawVertical(&rt);
  
    rt.display();
    sf::Sprite sprite(rt.getTexture());
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }




    return 0;
}