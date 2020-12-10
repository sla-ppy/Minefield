#include "stdafx.h"

#ifdef __linux
#include <math.h>
#endif
#include "Mine.h"

#include "ObjectManager.h"

Mine::Mine()
{
	m_position = new float[3];
	m_team = 0;
	m_destructiveRadius = 0.0f;
	m_health = 100.0f;
	m_explosiveYield = 500;
}

Mine::~Mine()
{
	printf("Mine destroyed\n");
	Explode();
	delete m_position;
}

void Mine::SetPosition(float* aPosition)
{
	for (int i = 0; i < 3; i++)
		m_position[i] = aPosition[i];
}

float Mine::GetDistance(float aPositionA[3], float aPositionB[3])
{
	float distance = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		// FIXED: powf instead of pow, compiler warning for possible loss of data from double to float conversaion
		distance += powf((aPositionA[i] - aPositionB[i]), 2.0f);
	}

	// FIXED: sqrtf instead of pow, compiler warning for possible loss of data from double to float conversaion
	return sqrtf(distance);
}

// Invulnerable mines do not take damage, but can be manually exploded if they are active
void Mine::FindCurrentTargets()
{
	//If not active, it cant find the current targets
	if (!GetActive())
	{
		return;
	}

	m_targetList.clear();

	for (int i = 0; i < ObjectManager::GetSingleton().GetNumberOfObjects(); ++i)
	{
		Object* pObject = ObjectManager::GetSingleton().GetObject(i);

		float distance = GetDistance(GetPosition(), pObject->GetPosition());

		if (distance > m_destructiveRadius)
		{
			break;
		}

		// Invulnerable mines aren't targetable
		if (GetInvulnerable())
		{
			break;
		}

		//TODO: Any other reasons to not add this object?

		m_targetList.push_back(pObject);
	}
}

int Mine::GetNumberOfEnemyTargets()
{
	int numberOfEnemyTargets = 0;
	for (unsigned int i = 0; i < m_targetList.size(); ++i)
	{
		if (static_cast<Mine*>(m_targetList[i])->GetTeam() != GetTeam())
		{
			numberOfEnemyTargets++;
		}
	}

	return numberOfEnemyTargets;
}

void Mine::Explode()
{

	for (unsigned int i = 0; i < m_targetList.size(); ++i)
	{
		// Inactive mines cannot be triggered to explode. They can only explode from taking too much damage
		if (!GetActive())
		{
			break;
		}

		float distance = GetDistance(GetPosition(), m_targetList[i]->GetPosition());

		// damage is inverse-squared of distance
		float factor = 1.0f - (distance / m_destructiveRadius);
		float damage = (factor * factor) * m_explosiveYield;
		static_cast<Mine*>(m_targetList[i])->TakeDamage(damage);
	}


	// Destroy self
	TakeDamage(m_health);
}

void Mine::TakeDamage(float aDamage)
{

	// FIXED: If an object is invulnerable, then TakeDamage wont happen to it
	if (GetInvulnerable())
	{
		return;
	}

	m_health -= aDamage;
	if (m_health < 0.0f)
	{
		ObjectManager::GetSingleton().RemoveObject(GetObjectId());
	}
}
