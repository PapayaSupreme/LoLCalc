// Entity.cpp
#include "Entity.h"

#include <iostream>

#include "Champion.h"

Entity::Entity(std::string name, const Stats &stats)
    : name(std::move(name)), entity_stats(stats) {}

std::string Entity::get_name() const noexcept { return name; }
float Entity::get_max_HP() const noexcept { return entity_stats.max_HP; }
float Entity::get_current_HP() const noexcept { return entity_stats.current_HP; }
float Entity::get_base_AD() const noexcept {return entity_stats.base_AD;}
float Entity::get_bonus_AD() const noexcept {return entity_stats.bonus_AD;}
float Entity::get_AP() const noexcept {return entity_stats.AP;}
float Entity::get_armor() const noexcept {return entity_stats.base_armor + entity_stats.bonus_armor;}
float Entity::get_MR() const noexcept {return entity_stats.base_MR + entity_stats.bonus_MR;}
float Entity::get_AS() const {return entity_stats.attack_speed;}
float Entity::get_AH() const noexcept {return entity_stats.ability_haste;}
float Entity::get_crit_chance() const noexcept {return entity_stats.crit_chance;}
float Entity::get_MS() const noexcept {return entity_stats.MS;}
int Entity::get_level() const noexcept {return entity_stats.level;}
const Stats& Entity::getStats() const {return entity_stats;}

uint8_t Entity::get_adaptive_type() const {
    if (entity_stats.bonus_AD > entity_stats.AP)
    {
        return 0;
    }
    if (entity_stats.bonus_AD > entity_stats.AP) {
        return 1;
    }
    return entity_stats.default_adaptive_damage;
}

void Entity::add_HP(const float HP) noexcept {
    if (entity_stats.current_HP + HP < entity_stats.max_HP) {
        entity_stats.current_HP += HP;
    } else {
        entity_stats.current_HP = entity_stats.max_HP;
    }
}

bool Entity::remove_HP(const float HP) noexcept {
    entity_stats.current_HP -= HP;
    return entity_stats.current_HP <= 0;
}

void Entity::add_bonus_AD(const float bonus_AD) noexcept { entity_stats.bonus_AD += bonus_AD; }
void Entity::add_bonus_armor(const float bonus_armor) noexcept { entity_stats.bonus_armor += bonus_armor; }
void Entity::add_bonus_MR(const float bonus_MR) noexcept { entity_stats.bonus_MR += bonus_MR; }
void Entity::add_AS(const float AS) noexcept { entity_stats.attack_speed += AS; }
void Entity::add_AP(const float AP) noexcept { entity_stats.AP += AP; }
void Entity::add_bonus_health(const float bonus_health) noexcept { entity_stats.max_HP += bonus_health; }
void Entity::add_bonus_mana(const float bonus_mana) noexcept { entity_stats.bonus_resource += bonus_mana; }



float Entity::computeArmorReduction(const Entity& Source) const {
    float temp_armor = this->get_armor();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_armor >= 0) {
            temp_armor *= 1.0f - champSource->get_armor_pen()/100;
            temp_armor -= champSource->get_lethality();
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
    float temp_mr = this->get_MR();
    if (const auto* champSource = dynamic_cast<const Champion*>(&Source)) {
        if (temp_mr >= 0) {
            temp_mr *= 1.0f - champSource->get_magic_pen()/100;
            temp_mr -= champSource->get_magic_pen_flat();
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
