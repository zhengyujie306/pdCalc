//
// Created by 郑育杰 on 2022/8/28.
//

#include <iostream>
#include "Button.h"


void sf::Button::setPosition(const sf::Vector2f &position) {
    rect.setPosition(position);
    text.setPosition(position);
    central();
}

void sf::Button::setShapeColor(const sf::Color& color) {
    rect.setFillColor(color);
}

void sf::Button::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}

void sf::Button::setFont(const sf::Font &font) {
    text.setFont(font);
    //central();
}

void sf::Button::setSize(const sf::Vector2f& size) {
    rect.setSize(size);
    //central();
}

void sf::Button::setString(const std::string &str) {
    text.setString(str);
    central();
}

sf::Vector2f sf::Button::getPosition() const {
    return rect.getPosition();
}

sf::Vector2f sf::Button::getSize() const{
    return rect.getSize();
}

std::string sf::Button::getString() const {
    return text.getString();
}

void sf::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(rect, states);
    target.draw(text, states);
}

void sf::Button::central() {
    auto groundRect = text.getGlobalBounds();
    text.setPosition((rect.getSize().x - groundRect.width)/2 + rect.getPosition().x, (rect.getSize().y - groundRect.height)/2 + rect.getPosition().y);
}
