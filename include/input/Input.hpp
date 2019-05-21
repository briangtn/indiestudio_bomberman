/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Input.hpp
*/

/* Created the 21/05/2019 at 19:38 by brian */

#ifndef INDIESTUDIO_INPUT_HPP
#define INDIESTUDIO_INPUT_HPP

#include <map>
#include <string>
#include <irrlicht/Keycodes.h>
#include <irrlicht/IEventReceiver.h>

namespace indie {

    struct Axis {
        unsigned int positive = 0;
        unsigned int negative = 0;
        unsigned int joystickID = 0;
    };

    class Input {
    public:
        explicit Input(std::map<std::string, Axis> axes);

    private:
        std::map<std::string, Axis> _axes;
    };
}

#endif //INDIESTUDIO_INPUT_HPP
