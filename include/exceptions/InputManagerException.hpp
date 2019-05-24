/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** InputManagerException.hpp
*/

/* Created the 21/05/2019 at 21:06 by brian */

#ifndef INDIESTUDIO_INPUTMANAGEREXCEPTION_HPP
#define INDIESTUDIO_INPUTMANAGEREXCEPTION_HPP

#include <exception>
#include <string>

namespace indie {
    class InputManagerException : public std::exception {
    public:
        InputManagerException(const std::string &what);

        const char *what() const noexcept override;

    protected:
        std::string _what;
    };

    class AxisNotFoundException : public InputManagerException {
    public:
        AxisNotFoundException(const std::string &inputName);

        std::string getInputName() const;

    protected:
        std::string _inputName;
    };

    class AxisAlreadyExistException : public InputManagerException {
    public:
        AxisAlreadyExistException(const std::string &inputName);

        std::string getInputName() const;

    protected:
        std::string _inputName;
    };
}


#endif //INDIESTUDIO_INPUTMANAGEREXCEPTION_HPP
