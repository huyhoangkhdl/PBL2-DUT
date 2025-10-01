#include <SFML/Graphics.hpp>

int main() {
    // Bật khử răng cưa
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    // Tạo cửa sổ theo cú pháp SFML 3.0.0
    sf::RenderWindow window(
        sf::VideoMode({1000, 1050}),
        "ChinaChess",
        sf::State::Windowed,
        settings
    );
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("banco.png")) return -1;

    // SFML 3.0.0: Sprite phải khởi tạo với texture
    sf::Sprite backgroundSprite(backgroundTexture);

    // Scale background vừa với cửa sổ
    sf::Vector2u winSize = window.getSize();
    sf::Vector2u texSize = backgroundTexture.getSize();
    backgroundSprite.setScale(
        sf::Vector2f(
            static_cast<float>(winSize.x) / texSize.x,
            static_cast<float>(winSize.y) / texSize.y
        )
    );
    sf::VertexArray grid(sf::PrimitiveType::Lines);

    // Vẽ đường ngang
    for (int i = 0; i <= 10; i++) {
        grid.append(sf::Vertex{sf::Vector2f(100.f, 100.f + i * 100.f), sf::Color::Black});
        grid.append(sf::Vertex{sf::Vector2f(900.f, 100.f + i * 100.f), sf::Color::Black});
    }

    // Vẽ đường dọc
    for (int i = 0; i <= 10; i++) {
        grid.append(sf::Vertex{sf::Vector2f(100.f + i * 100.f, 100.f), sf::Color::Black});
        grid.append(sf::Vertex{sf::Vector2f(100.f + i * 100.f, 500.f), sf::Color::Black});
        grid.append(sf::Vertex{sf::Vector2f(100.f + i * 100.f, 600.f), sf::Color::Black});
        grid.append(sf::Vertex{sf::Vector2f(100.f + i * 100.f, 1000.f), sf::Color::Black});
    }
    grid.append(sf::Vertex{sf::Vector2f(100.f, 100.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(100.f, 1000.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(900.f, 100.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(900.f, 1000.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(100.f, 500.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(900.f, 600.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(900.f, 500.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(100.f, 600.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(400.f, 100.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(600.f, 300.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(600.f, 100.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(400.f, 300.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(400.f, 1000.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(600.f, 800.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(100.f, 500.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(900.f, 600.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(600.f, 1000.f), sf::Color::Black});
    grid.append(sf::Vertex{sf::Vector2f(400.f, 800.f), sf::Color::Black});


    // Vẽ quân cờ
    std::vector<sf::CircleShape> pieces;
    for (int i = 0; i < 9; i++) {
        sf::CircleShape piece(40.f);  // bán kính = 25 -> đường kính = 50
        piece.setFillColor(sf::Color::White);
        piece.setOutlineColor(sf::Color::Black);
        piece.setOutlineThickness(3.f);
        piece.setOrigin({40, 40});
        piece.setPosition({100.f + i * 100.f, 100.f}); // xê dịch để không đè nhau
        pieces.push_back(piece);
    }

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::Cyan);
        window.draw(backgroundSprite);
        window.draw(grid);
        for (auto& piece : pieces){
            window.draw(piece);
        }
        window.display();
    }
    return 0;
}
