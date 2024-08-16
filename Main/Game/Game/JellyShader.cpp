#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

// JellyVertex class for physics simulation
class JellyVertex {
public:
    int ID;
    sf::Vector2f Position, Velocity, Force;

    JellyVertex(int _id, sf::Vector2f _pos) : ID(_id), Position(_pos) {}

    void Shake(const sf::Vector2f& target, float m, float s, float d) {
        Force = (target - Position) * s;
        Velocity = (Velocity + Force / m) * d;
        Position += Velocity;
        if ((Velocity + Force + Force / m).length() < 0.001f)
            Position = target;
    }
};

// JellyMesh class for managing jelly effect on sprite
class JellyMesh {
public:
    float Intensity = 1.f;
    float Mass = 1.f;
    float Stiffness = 1.f;
    float Damping = 0.75f;

    sf::VertexArray MeshClone;
    std::vector<JellyVertex> jv;
    bool enabled = false;
    std::chrono::steady_clock::time_point disableTime;

    JellyMesh(const sf::Texture& texture) {
        // Initialize vertex array for the sprite
        MeshClone.setPrimitiveType(sf::TrianglesFan);
        MeshClone.resize(4); 

        sf::Vector2f size(texture.getSize().x, texture.getSize().y);
        // Define vertices for a rectangle
        MeshClone[0].position = sf::Vector2f(0, 0);
        MeshClone[1].position = sf::Vector2f(size.x, 0);
        MeshClone[2].position = sf::Vector2f(size.x, size.y);
        MeshClone[3].position = sf::Vector2f(0, size.y);

        // Set texture coordinates
        MeshClone[0].texCoords = sf::Vector2f(0, 0);
        MeshClone[1].texCoords = sf::Vector2f(size.x, 0);
        MeshClone[2].texCoords = sf::Vector2f(size.x, size.y);
        MeshClone[3].texCoords = sf::Vector2f(0, size.y);

        // Initialize JellyVertex array
        for (size_t i = 0; i < MeshClone.getVertexCount(); i++) {
            jv.emplace_back(i, MeshClone[i].position);
        }

        DisableJellyMesh();
    }

    void EnableJellyMesh() {
        enabled = true;
    }

    void DisableJellyMesh() {
        enabled = false;
        disableTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(900);
    }

    void Update() {
        if (!enabled) {
            auto now = std::chrono::steady_clock::now();
            if (now < disableTime) return;
            DisableJellyMesh();
        }

        // Apply jelly effect
        for (auto& vertex : jv) {
            sf::Vector2f target = MeshClone[vertex.ID].position;
            float intensity = (1 - (target.y / MeshClone[2].position.y)) * Intensity;
            vertex.Shake(target, Mass, Stiffness, Damping);
            target = vertex.Position;
            MeshClone[vertex.ID].position = lerp(MeshClone[vertex.ID].position, target, intensity);
        }
    }

private:
    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
        return start + (end - start) * t;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jelly Sprite Example");

    sf::Texture texture;
    if (!texture.loadFromFile("#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

// JellyVertex class for physics simulation
class JellyVertex {
public:
    int ID;
    sf::Vector2f Position, Velocity, Force;

    JellyVertex(int _id, sf::Vector2f _pos) : ID(_id), Position(_pos) {}

    void Shake(const sf::Vector2f& target, float m, float s, float d) {
        Force = (target - Position) * s;
        Velocity = (Velocity + Force / m) * d;
        Position += Velocity;
        if ((Velocity + Force + Force / m).length() < 0.001f)
            Position = target;
    }
};

// JellyMesh class for managing jelly effect on sprite
class JellyMesh {
public:
    float Intensity = 1.f;
    float Mass = 1.f;
    float Stiffness = 1.f;
    float Damping = 0.75f;

    sf::VertexArray MeshClone;
    std::vector<JellyVertex> jv;
    bool enabled = false;
    std::chrono::steady_clock::time_point disableTime;

    JellyMesh(const sf::Texture& texture) {
        // Initialize vertex array for the sprite
        MeshClone.setPrimitiveType(sf::TrianglesFan);
        MeshClone.resize(4); // Assume a quad (rectangle) for the sprite
        
        sf::Vector2f size(texture.getSize().x, texture.getSize().y);
        // Define vertices for a rectangle
        MeshClone[0].position = sf::Vector2f(0, 0);
        MeshClone[1].position = sf::Vector2f(size.x, 0);
        MeshClone[2].position = sf::Vector2f(size.x, size.y);
        MeshClone[3].position = sf::Vector2f(0, size.y);

        // Set texture coordinates
        MeshClone[0].texCoords = sf::Vector2f(0, 0);
        MeshClone[1].texCoords = sf::Vector2f(size.x, 0);
        MeshClone[2].texCoords = sf::Vector2f(size.x, size.y);
        MeshClone[3].texCoords = sf::Vector2f(0, size.y);

        // Initialize JellyVertex array
        for (size_t i = 0; i < MeshClone.getVertexCount(); i++) {
            jv.emplace_back(i, MeshClone[i].position);
        }

        DisableJellyMesh();
    }

    void EnableJellyMesh() {
        enabled = true;
    }

    void DisableJellyMesh() {
        enabled = false;
        disableTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(900);
    }

    void Update() {
        if (!enabled) {
            auto now = std::chrono::steady_clock::now();
            if (now < disableTime) return;
            DisableJellyMesh();
        }

        // Apply jelly effect
        for (auto& vertex : jv) {
            sf::Vector2f target = MeshClone[vertex.ID].position;
            float intensity = (1 - (target.y / MeshClone[2].position.y)) * Intensity;
            vertex.Shake(target, Mass, Stiffness, Damping);
            target = vertex.Position;
            MeshClone[vertex.ID].position = lerp(MeshClone[vertex.ID].position, target, intensity);
        }
    }

private:
    sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
        return start + (end - start) * t;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jelly Sprite Example");

    sf::Texture texture;
    if (!texture.loadFromFile("images/NewNodes/Mod/Ice.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    sf::Sprite sprite(texture);
    JellyMesh jellyMesh(texture);
    jellyMesh.EnableJellyMesh();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        jellyMesh.Update();

        window.clear();
        window.draw(sprite); // Draw the original sprite
        window.draw(jellyMesh.MeshClone); // Draw the jelly effect mesh
        window.display();
    }

    return 0;
}
")) {
        std::cerr << "Error loading texture" << std::endl;
        return -1;
    }

    sf::Sprite sprite(texture);
    JellyMesh jellyMesh(texture);
    jellyMesh.EnableJellyMesh();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        jellyMesh.Update();

        window.clear();
        window.draw(sprite);
        window.draw(jellyMesh.MeshClone);
        window.display();
    }

    return 0;
}
