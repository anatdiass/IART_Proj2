#ifndef AGENT_H
#define AGENT_H

class Agent {
	unsigned int x, y;
	
public:
	Agent();
	Agent(unsigned int x, unsigned int y);

	unsigned int getX() const;
	void setX(unsigned int new_x);

	unsigned int getY() const;
	void setY(unsigned int new_y);

	bool operator==(const Agent& rhs)const;

	~Agent();
};
#endif
