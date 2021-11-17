#pragma once

#include <string>
#include <glm/glm.hpp>

namespace HE {
    class Game {
    public:
        Game();

        explicit Game(std::string windowTitle);
        ~Game();

        void Run();

    protected:
        virtual void Init() {};
        virtual void PhysicsUpdate(float deltaTime) {};
        virtual void Update(float deltaTime) {};
        virtual void Render() {};

    private:
        void initializeServices();
        void shutdownServices();

    public:
        // For public variables (probably none)
        static void gameLoop();

    protected:
        glm::vec4 _clearColor { 0.1f, 0.2f, 0.3f, 1.f };
    private:
        std::string _title;
        bool _running;

        static Game* _instance;
    };

    extern Game *CreateGame();
}

