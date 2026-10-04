#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>

sf::Vector2f readMovementDirection()
{
    sf::Vector2f direction{ 0.f, 0.f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        direction.x -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        direction.x += 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        direction.y -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        direction.y += 1.f;
    }

    const float length = std::sqrt(
        direction.x * direction.x
        + direction.y * direction.y
    );

    if (length > 0.f)
    {
        direction.x /= length;
        direction.y /= length;
    }

    return direction;
}

void updatePlayer(
    sf::RectangleShape& player,
    sf::Vector2f direction,
    float speed,
    float deltaTime,
    sf::Vector2u windowSize
)
{
    sf::Vector2f position = player.getPosition();

    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;

    const sf::Vector2f playerSize = player.getSize();

    const float maximumX =
        static_cast<float>(windowSize.x) - playerSize.x;

    const float maximumY =
        static_cast<float>(windowSize.y) - playerSize.y;

    position.x = std::clamp(position.x, 0.f, maximumX);
    position.y = std::clamp(position.y, 0.f, maximumY);

    player.setPosition(position);
}

int main()
{
    constexpr unsigned int windowWidth = 800;
    constexpr unsigned int windowHeight = 600;

    constexpr float playerWidth = 50.f;
    constexpr float playerHeight = 50.f;
    constexpr float playerSpeed = 240.f;
    constexpr float maximumDeltaTime = 0.05f;

    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "Chapter 4 | Arrows: Move | R: Reset | Esc: Exit",
        sf::Style::Titlebar | sf::Style::Close
    );

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::RectangleShape player({ playerWidth, playerHeight });
    player.setFillColor(sf::Color(70, 190, 240));

    const sf::Vector2f startPosition{
        (static_cast<float>(windowWidth) - playerWidth) / 2.f,
        (static_cast<float>(windowHeight) - playerHeight) / 2.f
    };

    player.setPosition(startPosition);

    sf::Clock frameClock;

    while (window.isOpen())
    {
        const float deltaTime = std::min(
            frameClock.restart().asSeconds(),
            maximumDeltaTime
        );

        bool resetRequested = false;

        // 1. Process events.
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto* key =
                event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
                else if (key->code == sf::Keyboard::Key::R)
                {
                    resetRequested = true;
                }
            }
        }

        if (!window.isOpen())
        {
            break;
        }

        // 2. Update.
        if (window.hasFocus())
        {
            if (resetRequested)
            {
                player.setPosition(startPosition);
            }
            else
            {
                updatePlayer(
                    player,
                    readMovementDirection(),
                    playerSpeed,
                    deltaTime,
                    window.getSize()
                );
            }
        }

        // 3. Render.
        window.clear(sf::Color(20, 30, 45));
        window.draw(player);
        window.display();
    }

    return 0;
}
