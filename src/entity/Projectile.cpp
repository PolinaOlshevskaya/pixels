#include "entity/Projectile.h"
#include "resource/DataTables.h"
#include "util/Utility.h"
#include "resource/ResourceHolder.h"
#include "nodes/EmitterNode.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <cmath>
#include <cassert>


namespace
{
	const std::vector<ProjectileData> Table = InitializeProjectileData();
}



Projectile::Projectile( SceneGrid* sceneGrid, Type_t type, const TextureHolder& textures )
: Entity( sceneGrid, 1 )
, m_type(type)
, m_sprite( textures.Get( Table[type].texture ), Table[type].textureRect )
, m_targetDirection()
{
	CenterOrigin(m_sprite);

	// Add particle system for missiles
	if ( IsGuided( ) )
	{
		m_sprite.setColor( sf::Color( 200, 200, 255 ) );
		std::unique_ptr<EmitterNode> smoke( new EmitterNode( Particle::Smoke ) );
		smoke->setPosition( 0.f, GetBoundingRect( ).height / 2.f );
		AttachChild( std::move( smoke ) );

		std::unique_ptr<EmitterNode> propellant( new EmitterNode( Particle::Propellant ) );
		propellant->setPosition( 0.f, GetBoundingRect( ).height / 2.f );
		AttachChild( std::move( propellant ) );
	}
}


void Projectile::GuideTowards(sf::Vector2f position)
{
	assert(IsGuided());
	m_targetDirection = VectorUnit(position - GetWorldPosition());
}

bool Projectile::IsGuided() const
{
	return m_type == Missile;
}

void Projectile::UpdateCurrent(sf::Time dt, CommandQueue& commands)
{
	const float approachRate = 200.f;
	if (IsGuided())
	{
		const float approachRate = 200.f;

		sf::Vector2f newVelocity = VectorUnit(approachRate * dt.asSeconds() * m_targetDirection + GetVelocity());
		newVelocity *= GetSpeed();
		float angle = std::atan2(newVelocity.y, newVelocity.x);

		setRotation(ToDegree(angle) + 90.f);
		SetVelocity(newVelocity);
	}


	Entity::UpdateCurrent(dt, commands);
}

void Projectile::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

Category::Type_t Projectile::GetCategory( ) const
{
	if (m_type == EnemyBullet)
		return Category::EnemyProjectile;
	else
		return Category::AlliedProjectile;
}

sf::FloatRect Projectile::GetBoundingRect() const
{
	return GetWorldTransform().transformRect(m_sprite.getGlobalBounds());
}

float Projectile::GetSpeed() const
{
	return Table[m_type].speed;
}

int Projectile::GetDamage() const
{
	return Table[m_type].damage;
}
