// Entity.cpp
#include "Entity.h"

#include <iostream>
#include <sstream>

#include "Champion.h"

Entity::Entity(std::string name, const Stats &stats)
    : name(std::move(name)), entity_stats(stats) {}

std::string Entity::getName() const noexcept { return name; }
std::string Entity::toString() const {
    std::ostringstream output;
    output << name
           << "\n  HP: " << entity_stats.current_HP << "/" << entity_stats.max_HP
           << "\n  AD: " << getAD()
           << "\n  AP: " << getAP()
           << "\n  Armor: " << getArmor()
           << "\n  MR: " << getMR()
           << "\n  Attack speed: " << getAS()
           << "\n  Ability haste: " << getAH();
    return output.str();
}
float Entity::getMaxHP() const noexcept {return entity_stats.max_HP; }
float Entity::getCurrentHP() const noexcept { return entity_stats.current_HP; }
float Entity::getBaseAD() const noexcept {return entity_stats.base_AD; }
float Entity::getBonusAD() const noexcept {return entity_stats.bonus_AD; }
float Entity::getAD() const noexcept { return entity_stats.base_AD + entity_stats.bonus_AD; }
float Entity::getAP() const noexcept {return entity_stats.AP; }
float Entity::getArmor() const noexcept {return entity_stats.base_armor + entity_stats.bonus_armor; }
float Entity::getMR() const noexcept {return entity_stats.base_MR + entity_stats.bonus_MR; }
float Entity::getAS() const {return entity_stats.attack_speed; }
float Entity::getAH() const noexcept {return entity_stats.ability_haste; }
float Entity::getCritChance() const noexcept {return entity_stats.crit_chance; }
float Entity::getMS() const noexcept {return entity_stats.MS; }
int Entity::getLevel() const noexcept {return entity_stats.level; }
const Stats& Entity::getStats() const {return entity_stats; }

/**
 * Get the adaptive damage type of the entity. Either the biggest between bonus AD and AP, or the default adaptive damage type.
 * @return 0 if AD, 1 if AP
 */
uint8_t Entity::getAdaptiveType() const {
    if (entity_stats.bonus_AD > entity_stats.AP)
    {
        return 0;
    }
    if (entity_stats.bonus_AD > entity_stats.AP) {
        return 1;
    }
    return entity_stats.default_adaptive_damage;
}



bool Entity::removeCurrentHP(const float HP) noexcept {
    entity_stats.current_HP -= HP;
    return entity_stats.current_HP <= 0;
}
void Entity::addCurrentHP(const float HP) noexcept {
    if (entity_stats.current_HP + HP < entity_stats.max_HP) {
        entity_stats.current_HP += HP;
    } else {
        entity_stats.current_HP = entity_stats.max_HP;
    }
}
void Entity::addBonusAD(const float bonus_AD) noexcept { entity_stats.bonus_AD += bonus_AD; }
void Entity::addBonusArmor(const float bonus_armor) noexcept { entity_stats.bonus_armor += bonus_armor; }
void Entity::addBonusMR(const float bonus_MR) noexcept { entity_stats.bonus_MR += bonus_MR; }
void Entity::addAS(const float AS) noexcept { entity_stats.attack_speed += AS; }
void Entity::addAP(const float AP) noexcept { entity_stats.AP += AP; }
void Entity::addBonusHealth(const float bonus_health) noexcept { entity_stats.max_HP += bonus_health; }
void Entity::addBonusMana(const float bonus_mana) noexcept { entity_stats.bonus_resource += bonus_mana; }
void Entity::addAH(const float ability_haste) noexcept { entity_stats.ability_haste += ability_haste; }

/**
 * Computes the damage done to the entity after applying armor, armor pen and lethality of a given amount.
 * @param Source Entity source of the damage reference
 * @return The damage reduction multiplier after armor is applied
 */
float Entity::computeArmorReduction(const Entity& Source) const {
    float temp_armor = this->getArmor();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_armor >= 0) {
            temp_armor *= 1.0f - champSource->getArmorPen()/100;
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

/**
 * Computes the damage done to the entity after applying mr, magic pen and flat magic pen of a given amount.
 * @param Source Entity source of the damage reference
 * @return The damage reduction multiplier after mr is applied
 */
float Entity::computeMagicReduction(const Entity& Source) const {
    float temp_mr = this->getMR();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_mr >= 0) {
            temp_mr *= 1.0f - champSource->getMagicPen()/100;
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
