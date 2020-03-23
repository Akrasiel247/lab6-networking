#pragma once


struct Actor {
	int m_id; //Unique ID of this actor
	float  m_x_pos, m_y_pos;//Position of an Actor
	bool m_isAlive; //Still alive?
	bool m_isBullet; //Is this actor a bullet or a player?
	bool m_touchedActor; //If this Actor is collided with other Actor
	struct Direction {
		float d_x_dir;
		float d_y_dir;
	}direction;

	Actor();
	Actor(int id, float x_pos, float y_pos, bool isAlive, bool isBullet, bool touched,float x_dir,float y_dir);
	void setLife();

	friend std::ostream& operator<<(std::ostream& os, const Actor& a);
	bool isEqual(const Actor a);
	bool isEmpty();

};