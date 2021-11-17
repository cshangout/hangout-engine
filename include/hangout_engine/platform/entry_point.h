//
// Created by Paul Mauviel on 2021-11-08.
//

#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <hangout_engine/service_locator.h>

// Keep headers
#include <hangout_engine/platform/game.h>

int main(int argc, char **argv) {
    // Create the game
    auto* theGame = HE::CreateGame();

    // Run the game
    theGame->Run();

    // once it's done, delete the game
    delete theGame;
}