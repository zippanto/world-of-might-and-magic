#include <SDL.h>

#include "Platform/Sdl2UserInputProvider.h"


extern std::map<SDL_Scancode, GameKey> scancode_lookup;

bool Sdl2UserInputProvider::IsKeyPressed(GameKey key) const {
    if (key != GameKey::None && key != GameKey::Char) {
        auto state = SDL_GetKeyboardState(nullptr);
        if (state != nullptr) {
            auto mappedKey = std::find_if(
                scancode_lookup.begin(),
                scancode_lookup.end()
                [key](const std::pair<SDL_Scancode, GameKey> &i) -> bool {
                    return key == i.second.x;
                }
            );
            if (mappedKey != scancode_lookup.end()) {
                return state[mappedKey->first] != 0;
            }
        }
    }
    return false;
}

bool Sdl2UserInputProvider::IsKeyHeld(GameKey key) const {
    return IsKeyPressed(key);
}