#include <iostream>
#include "Actor.h"

Actor::Actor()
{
	*this = Actor(0, 0, 0, true, false, false);
}

Actor::Actor(int id, float x_pos, float y_pos, bool isAlive, bool isBullet, bool touched)
{
	m_id = id;
	m_x_pos = x_pos;
	m_y_pos = y_pos;
	m_isAlive = isAlive;
	m_isBullet = isBullet;
	m_touchedActor = touched;
}

void Actor::setLife()
{
	m_isAlive = !m_isAlive;
}

bool Actor::isEqual(const Actor a)//this is probably better of as a =operator overload -R 
{
	return m_id==a.m_id;
}

bool Actor::isEmpty()
{
	return m_id==0;
}

std::ostream& operator<<(std::ostream& os, const Actor& a)
{
	return os << "This is an actor:" << a.m_id << "\n"
	<<((a.m_isAlive) ? "I am alive" : "I am dead") << std::endl;
	
}
