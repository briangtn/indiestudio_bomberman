/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManager.hpp
*/

/* Created the 21/05/2019 at 19:35 by brian */

#ifndef INDIESTUDIO_INPUTMANAGER_HPP
#define INDIESTUDIO_INPUTMANAGER_HPP

#include <vector>
#include "input/Input.hpp"

namespace indie {
    class InputManager {
        static InputManager *instance;

    private:
        InputManager();

    public:
        static InputManager *get();

    public:
        Input getInput(const std::string &inputName) const;
        float getAxis(const std::string &inputName, const std::string &axisName) const;

        void registerInput(const std::string &inputName, const Input &input);

    private:
        std::map<std::string, Input> _inputs;

    };
}

#endif //INDIESTUDIO_INPUTMANAGER_HPP
