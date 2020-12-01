#include "Strategies.h";

NeutralPlayerStrategy::NeutralPlayerStrategy(): PlayerStrategy()
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other): PlayerStrategy(other)
{
}
NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& other)
{
	return *this;
}
const vector<Territory*>* NeutralPlayerStrategy::toDefend(Player* player)
{
	return player->getTerritories();
}
const vector<Territory*> NeutralPlayerStrategy::toAttack(Player* player)
{
	return *player->getTerritories();
}
bool NeutralPlayerStrategy::issueOrder(Player* player)
{
	return false;
}
BombOrder* NeutralPlayerStrategy::useBomb(Player* player)
{
	return nullptr;
}
NegotiateOrder* NeutralPlayerStrategy::useDiplomacy(Player* player)
{
	return nullptr;
}
AirliftOrder* NeutralPlayerStrategy::useAirlift(Player* player)
{
	return nullptr;
}
BlockadeOrder* NeutralPlayerStrategy::useBlockade(Player* player)
{
	return nullptr;
}
DeployOrder* NeutralPlayerStrategy::useReinforcement(Player* player)
{
	return nullptr;
}
ostream& operator<<(ostream& output, const NeutralPlayerStrategy& other)
{
	return output << "Neutral Strategy";
}