// Entity.cpp
#include "Entity.h"

#include <iostream>

#include "Champion.h"

Entity::Entity(std::string name, const Stats &stats)
    : name(std::move(name)), entity_stats(stats) {}

float Entity::getHP() const {return entity_stats.max_HP;}
float Entity::getCurrHP() const {return entity_stats.current_HP;}
float Entity::getBaseAD() const {return entity_stats.base_AD;}
float Entity::getBonusAD() const {return entity_stats.bonus_AD;}
float Entity::getAP() const {return entity_stats.AP;}
float Entity::getArmor() const {return entity_stats.base_armor;}
float Entity::getMR() const {return entity_stats.base_MR;}
float Entity::getAS() const {return entity_stats.attack_speed;}
float Entity::getAH() const {return entity_stats.ability_haste;}
float Entity::getCrit() const {return entity_stats.crit_chance;}
float Entity::getMS() const {return entity_stats.MS;}
int Entity::getLevel() const {return entity_stats.level;}
const Stats& Entity::getStats() const {return entity_stats;}

float Entity::computeArmorReduction(const Entity& Source) const {
    float temp_armor = this->getArmor();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_armor >= 0) {
            temp_armor *= 1.0f - champSource->getArmorPen();
            temp_armor -= champSource->getLethality();
        }
    }
    float reduction;
    if (temp_armor >= 0.0f) {
        reduction = 100.0f / (100.0f + temp_armor);
    }else {
        reduction = 2.0f - 100.0f / (100.0f - temp_armor);
    }
    return reduction;
}

float Entity::computeMagicReduction(const Entity& Source) const {
    float temp_mr = this->getMR();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_mr >= 0) {
            temp_mr *= 1.0f - champSource->getMagicPen();
            temp_mr -= champSource->getMagicPenFlat();
        }
    }
    float reduction;
    if (temp_mr >= 0.0f) {
        reduction = 100.0f / (100.0f + temp_mr);
    }else {
        reduction = 2.0f - 100.0f / (100.0f - temp_mr);
    }
    return reduction;
}
