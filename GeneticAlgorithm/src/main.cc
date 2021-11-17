#include <iostream>
#include <Genetic.h>
#include <draw.h>
#include <chrono>




void printVector(std::vector<int> arr)
{
    for(int i = 0; i < arr.size(); i++)
    {
       std::cout << arr[i] << " ";
    }
}

int main()
{

    int fieldSize = 20; // 150 -> 30 (30sec); 200 - 30(77.8sec); 200 - 40(67.7sec); 200 - 50(63sec); 200 - 54(52.1701sec)
    Genetic genetic(20, fieldSize);

    // time
    double time = 0;
    auto begin = std::chrono::steady_clock::now();
    // genetic.run();
    genetic.run();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;
    time = elapsed_seconds.count();
    std::cout << "Time: " << time << "\n";

    std::vector<Agent*> population = genetic.getPopulation();


    std::vector<int> res = genetic.getPopulation()[0]->getChromo();

    std::cout << "\nThe best:\n";
    printVector(res);


    if (fieldSize > 40)
        return 0;
    // draw field

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