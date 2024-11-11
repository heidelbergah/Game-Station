#include "UserSnake.h"

UserSnake::UserSnake(Segment h)
: outline(sf::TriangleStrip)
{
    head = h;
    velocity = 3.5f;
    color = head.color;
    head.shape.setFillColor(color);
    head.shape.setRadius(head.radius);
    head.shape.setOrigin(head.radius, head.radius);
    head.shape.setPosition(head.pos);
    head.shape.setRotation(head.rotation);

    lEye.setRadius(4);
    lEye.setOrigin(lEye.getRadius(), lEye.getRadius());
    lEye.setPosition(head.lSide);
    lEye.setFillColor(sf::Color::Black);
    lEye.setOutlineThickness(2);
    lEye.setOutlineColor(sf::Color::White);
    
    rEye.setRadius(4);
    rEye.setOrigin(lEye.getRadius(), lEye.getRadius());
    rEye.setPosition(head.lSide);
    rEye.setFillColor(sf::Color::Black);
    rEye.setOutlineThickness(2);
    rEye.setOutlineColor(sf::Color::White);
}

void UserSnake::connectSegments(int i, float xDiff, float yDiff, float difference)
{
    float angle = std::atan2(-yDiff, xDiff);

    body[i].rotation = angle;
    body[i].pos.x += cos(angle) * (difference);
    body[i].pos.y -= sin(angle) * (difference);
}

void UserSnake::addSegment(int radius)
{
    Segment segment;
    segment.radius = radius;
    segment.color = color;
    segment.shape.setFillColor(color);
    segment.shape.setRadius(radius);
    segment.shape.setOrigin(radius, radius);

    sf::Vector2f pos;
    float rotation = 0;
    if(body.size() == 0)
    {
        rotation = head.rotation;
        pos = sf::Vector2f(head.pos.x - cos(rotation) * radius * 2, head.pos.y + sin(rotation) * radius * 2);
    }
    else
    {
        rotation = body[body.size()-1].rotation;
        pos = sf::Vector2f(body[body.size()-1].pos.x - cos(rotation) * radius, body[body.size()-1].pos.y + sin(rotation) * radius);
    }

    segment.rotation = rotation;
    segment.pos = pos;
    segment.shape.setPosition(segment.pos);
    segment.shape.setRotation(segment.rotation);

    body.push_back(segment);

    sf::Vector2f lSide(pos.x + cos(rotation + PI/2) * radius, pos.y - sin(rotation + PI/2) * radius);
    sf::Vector2f rSide(pos.x + cos(rotation + PI/2) * radius, pos.y - sin(rotation + PI/2) * radius);
    segment.lSide = lSide;
    segment.rSide = rSide;
}

bool UserSnake::collisionWithBody()
{
    for(int i = 2; i < body.size(); ++i)
    {
        float diffX = head.pos.x - body[i].pos.x;
        float diffY = head.pos.y - body[i].pos.y;
        float distance = std::sqrt(diffX * diffX + diffY * diffY);
        if(distance < head.radius + body[i].radius)
            return true;
    }
    return false;
}

Segment UserSnake::getHead()
{
    return head;
}

std::vector<Segment> UserSnake::getBody()
{
    return body;
}

Segment UserSnake::getLastSegment()
{
    return body[body.size()-1];
}

sf::CircleShape UserSnake::getLeftEye()
{
    return lEye;
}

sf::CircleShape UserSnake::getRightEye()
{
    return rEye;
}

sf::VertexArray UserSnake::getOutline()
{
    return outline;
}

bool UserSnake::isAlive()
{
    return alive;
}

void UserSnake::kill()
{
    alive = false;
}

void UserSnake::updateRotation(float rotationAdjustment)
{
    head.rotation += rotationAdjustment;
}

void UserSnake::update()
{
    // Position, rotation, etc. updating
    head.pos.x += cos(head.rotation) * velocity;
    head.pos.y -= sin(head.rotation) * velocity;

    float xDiff = head.pos.x - body[0].pos.x;
    float yDiff = head.pos.y - body[0].pos.y;
    float distance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
    if(distance > head.radius)
    {
        float difference = distance - (head.radius);
        connectSegments(0, xDiff, yDiff, difference);
    }

    for(int i = 0; i < body.size()-1; ++i)
    {
        float xDiff = body[i].pos.x - body[i+1].pos.x;
        float yDiff = body[i].pos.y - body[i+1].pos.y;
        float distance = std::sqrt(xDiff * xDiff + yDiff * yDiff);
        if(distance > body[i].radius)
        {
            float difference = distance - (body[i].radius);
            connectSegments(i+1, xDiff, yDiff, difference);
        }
    }

    if(collisionWithBody())
    {
        alive = false;
    }

    head.shape.setPosition(head.pos);
    for(int i = 0; i < body.size(); ++i)
    {
        body[i].shape.setPosition(body[i].pos);
        body[i].shape.setRotation(body[i].rotation);
    }

    // Body side updating
    sf::VertexArray newOutline(sf::TriangleStrip);

    head.lSide = sf::Vector2f(head.pos.x + cos(head.rotation + PI/2) * head.radius, head.pos.y - sin(head.rotation + PI/2) * head.radius);
    head.rSide = sf::Vector2f(head.pos.x + cos(head.rotation - PI/2) * head.radius, head.pos.y - sin(head.rotation - PI/2) * head.radius);
    for(int i = 0; i < body.size(); ++i)
    {
        body[i].lSide = sf::Vector2f(body[i].pos.x + cos(body[i].rotation + PI/2) * body[i].radius, body[i].pos.y - sin(body[i].rotation + PI/2) * body[i].radius);
        body[i].rSide = sf::Vector2f(body[i].pos.x + cos(body[i].rotation - PI/2) * body[i].radius, body[i].pos.y - sin(body[i].rotation - PI/2) * body[i].radius);
    }

    float eyeAngle = PI/4;
    lEye.setPosition(sf::Vector2f(head.pos.x + cos(head.rotation + eyeAngle) * head.radius, head.pos.y - sin(head.rotation + eyeAngle) * head.radius));
    rEye.setPosition(sf::Vector2f(head.pos.x + cos(head.rotation - eyeAngle) * head.radius, head.pos.y - sin(head.rotation - eyeAngle) * head.radius));

    newOutline.append(sf::Vertex(head.lSide, color));
    newOutline.append(sf::Vertex(head.rSide, color));

    for(int i = 0; i < body.size(); ++i)
    {
        newOutline.append(sf::Vertex(body[i].lSide, color));
        newOutline.append(sf::Vertex(body[i].rSide, color));
    }

    outline = newOutline;
}

