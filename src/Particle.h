#pragma once

constexpr auto particle_id_empty = 0;
constexpr auto particle_id_spirit = 1;
constexpr auto particle_id_obstacle = 2;

struct Particle {
    

    int m_id{ 0 };
    int m_iColour{ 0x000000 };

    float m_fVelocityY{ 0.f };
    float m_fVelocityX{ 0.f };
};