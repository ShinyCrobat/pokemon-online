#ifndef TEAMDATA_H
#define TEAMDATA_H

#include "../PokemonInfo/battlestructs.h"

#include <memory>

class TeamData
{
public:
    TeamData(TeamBattle* team=NULL);
    ~TeamData();

    ShallowBattlePoke* poke(int slot);
    QString& name();

    void setPoke(int slot, ShallowBattlePoke* poke);
    void setPoke(int slot, PokeBattle* poke);
    void switchPokemons(int slot1, int slot2);
    void setTeam(TeamBattle *team);
protected:
    std::vector< ShallowBattlePoke* > pokemons;
    QString mName;
};

#endif // TEAMDATA_H
