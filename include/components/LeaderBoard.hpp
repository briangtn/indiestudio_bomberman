/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LeaderBoard.hpp
*/

/* Created the 14/06/2019 at 16:47 by jfrabel */

#ifndef INDIESTUDIO_LEADERBOARD_HPP
#define INDIESTUDIO_LEADERBOARD_HPP

#include "Component.hpp"

namespace indie {

    namespace components {

        class LeaderBoard : public jf::components::Component {
        public:
            using PlayerLeaderBoard = std::vector<std::pair<int, int>>;

            LeaderBoard(jf::entities::Entity &entity);
            ~LeaderBoard() override;

            LeaderBoard &operator>>(std::ostream &file);

            const PlayerLeaderBoard &getPlayerLeaderboard() const;
            void setPlayerLeaderboard(const PlayerLeaderBoard &playerLeaderboard);

            void addPlayerToLeaderBoard(int playerRanking, int id);

        private:
            PlayerLeaderBoard _playerLeaderboard;
        };
    }
}

#endif //INDIESTUDIO_LEADERBOARD_HPP
