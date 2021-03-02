#include <SFML/Graphics.hpp>

sf::Image frame;
sf::RenderWindow w;
sf::Texture t;
sf::Sprite s;
void Setup()
{
    w.create(sf::VideoMode(320, 320), "6502");
    srand(int(time(0)));
    s.scale(10, 10);
    frame.create(32, 32);
}
void DrawFrame(Memory& memory)
{
    sf::Event event;
    while(w.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) w.close();
        if(event.type == sf::Event::KeyPressed)
        {
            memory[0x00ff] = (uint8_t)event.key.code;
        }
    }
    memory[0x00fe] = rand() % (0xff + 1);
    uint16_t addr = 0x0200;
    for(int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            uint8_t byte = memory[addr + i + j];
            switch (byte)
            {
            case 0x00:
                frame.setPixel(j, i, sf::Color::Black);
                break;
            case 0x01:
                frame.setPixel(j, i, sf::Color::White);
                break;
            case 0x02:
                frame.setPixel(j, i, sf::Color::Red);
                break;
            case 0x03:
                frame.setPixel(j, i, sf::Color::Cyan);
                break;
            case 0x04:
                frame.setPixel(j, i, sf::Color::Magenta);
                break;
            case 0x05:
                frame.setPixel(j, i, sf::Color::Green);
                break;
            case 0x06:
                frame.setPixel(j, i, sf::Color::Blue);
                break;
            case 0x07:
                frame.setPixel(j, i, sf::Color::Yellow);
                break;
            case 0x08:
                frame.setPixel(j, i, sf::Color(153, 102, 51));
                break;
            case 0x09:
                frame.setPixel(j, i, sf::Color(255, 102, 102));
                break;
            case 0x0A:
                frame.setPixel(j, i, sf::Color(64, 64, 64));
                break;
            case 0x0B:
                frame.setPixel(j, i, sf::Color(89, 89, 89));
                break;
            default:
                break;
            }
        }
        addr += 31;
    }
    t.loadFromImage(frame);
    s.setTexture(t);
    w.clear();
    w.draw(s);
    w.display();
}