/*
** EPITECH PROJECT, 2018
** indiestudio
** File description:
** LeaderBoard.cpp
*/

/* Created the 14/06/2019 at 16:47 by jfrabel */

#include "Events.hpp"
#include "components/LeaderBoard.hpp"

indie::components::LeaderBoard::LeaderBoard(jf::entities::Entity &entity)
    : Component(entity), _playerLeaderboard()
{
    EMIT_CREATE(LeaderBoard);
}

indie::components::LeaderBoard::~LeaderBoard()
{
    EMIT_DELETE(LeaderBoard);
}

const indie::components::LeaderBoard::PlayerLeaderBoard &indie::components::LeaderBoard::getPlayerLeaderboard() const
{
    return _playerLeaderboard;
}

void indie::components::LeaderBoard::setPlayerLeaderboard(const PlayerLeaderBoard &playerLeaderboard)
{
    _playerLeaderboard = playerLeaderboard;
}

void indie::components::LeaderBoard::addPlayerToLeaderBoard(int playerRanking, int id)
{
    _playerLeaderboard.emplace_back(id, playerRanking);
}

indie::components::LeaderBoard &indie::components::LeaderBoard::operator>>(std::ostream &file)
{
    file << R"(        <component type="LeaderBoard">)" << std::endl;
    for (auto &it : _playerLeaderboard) {
        file << R"(            <player id=")" << it.first << R"(" ranking=")" << it.second << "/>" << std::endl;
    }
    file << "        </component>" << std::endl;
    return *this;
}