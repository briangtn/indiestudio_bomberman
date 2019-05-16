/*
** EPITECH PROJECT, 2019
** indiestudio
** File description:
** MeshExceptions
*/

#ifndef MESHEXCEPTIONS_HPP_
#define MESHEXCEPTIONS_HPP_

#include <exception>
#include <string>
#include "Exceptions.hpp"

namespace jf {

    namespace exceptions {

        class MeshExceptions : public ECSException {
            public:
                explicit MeshExceptions(const std::string &err, const std::string &where = "");
        };
    }
}

#endif /* !MESHEXCEPTIONS_HPP_ */
