/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** EndScene.hpp
*/

/* Created the 14/06/2019 at 16:39 by jbulteau */

#ifndef INDIESTUDIO_ENDSCENE_HPP
#define INDIESTUDIO_ENDSCENE_HPP

#include <vector>
#include "IScene.hpp"

namespace indie {
    namespace scenes {

        class EndScene : public IScene {
        public:
            void onStart() override;
            void onStop() override;

            SaveState save(bool override, bool saveShouldBeKeeped) override;
            SaveState save(const std::string &saveName, bool override, bool saveShouldBeKeeped) override;

            int getWinner(std::vector<std::pair<int, int>> &results) const;
            const std::string &getMaterial(int winnerId) const;
        };
    }
}

#endif //INDIESTUDIO_ENDSCENE_HPP
