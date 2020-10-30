#include "GameEngine.h"

int GameEngine::mainGameLoop()
{
    return reinforcementPhase();
}
/**
 * Give players armies dependant of the number of territories they own
 * 
 * \return 
 */
int GameEngine::reinforcementPhase()
{
    for (Player* player : players)
    {
        int reinforcements = player->getTerritories()->size() / 3;
    }

    for (std::vector<Continent*>::const_iterator it = map->getContinents()->begin(); it != map->getContinents()->end(); it++) {
        Player* owner = (**it).getContinentOwner();
        if (owner != nullptr) {

        }
    }

    return 0;
}

int GameEngine::issueOrdersPhase()
{
    return 0;
}

int GameEngine::executeOrdersPhase()
{
    return 0;
}
