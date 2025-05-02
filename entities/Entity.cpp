// Entity.cpp
#include "Entity.h"
#include "Champion.h"

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
int Entity::getLevel() const {return entity_stats.level;}
float Entity::getAttackRange() const {return entity_stats.attackRange;}
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
