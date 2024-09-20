inline void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

inline void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

inline sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}
