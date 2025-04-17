// Entity.cpp
#include "Entity.h"

Entity::Entity(const Stats& stats)
    : entity_stats(stats) {}

float Entity::getHP() const {return entity_stats.maxHP;}
float Entity::getCurrHP() const {return entity_stats.currentHP;}
float Entity::getAD() const {return entity_stats.AD;}
float Entity::getAP() const {return entity_stats.AP;}
float Entity::getArmor() const {return entity_stats.armor;}
float Entity::getMR() const {return entity_stats.magicResist;}
float Entity::getAS() const {return entity_stats.attackSpeed;}
float Entity::getAH() const {return entity_stats.abilityHaste;}
float Entity::getCrit() const {return entity_stats.critChance;}
float Entity::getMS() const {return entity_stats.movementSpeed;}

const Stats& Entity::getStats() const {return entity_stats;}
