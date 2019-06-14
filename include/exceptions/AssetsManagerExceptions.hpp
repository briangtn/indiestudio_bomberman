/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** AssetsManagerExceptions.hpp
*/

//
// Created by romainfouyer on 6/4/19.
//

#ifndef INDIESTUDIO_ASSETSMANAGEREXCEPTIONS_HPP
#define INDIESTUDIO_ASSETSMANAGEREXCEPTIONS_HPP

#include <Exceptions.hpp>

namespace indie {

    namespace exceptions {

        class AssetsManagerExceptions : public jf::ECSException {
        public:
            explicit AssetsManagerExceptions(const std::string &err, const std::string &where = "");
        };

    }

}


#endif //INDIESTUDIO_ASSETSMANAGEREXCEPTIONS_HPP
