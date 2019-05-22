/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** Sound2DComponent.cpp
*/

/* Created the 22/05/2019 at 23:48 by jbulteau */

#include "Sound2DComponent.hpp"

indie::components::Sound2DComponent::Sound2DComponent(jf::entities::Entity &entity, const std::string &sourceFile,
                                                      indie::components::ASoundComponent::SoundType soundType)
        : ASoundComponent(entity, sourceFile, soundType)
{

}
