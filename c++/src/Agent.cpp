#include "Agent.h"

Agent::Agent() {}
Agent::~Agent() {}

Agent::Agent(unsigned int x, unsigned int y) : x(x), y(y) {}

unsigned int Agent::getX() const {return x;}
unsigned int Agent::getY() const{return y;}

void Agent::setX(unsigned int new_x){x = new_x;}
void Agent::setY(unsigned int new_y){y = new_y;}

bool Agent::operator==(const Agent & rhs) const{return (x == rhs.x) && (y == rhs.y);}


