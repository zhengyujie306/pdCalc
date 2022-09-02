//
// Created by 郑育杰 on 2022/8/28.
//

#ifndef BASE_BUTTON_H
#define BASE_BUTTON_H

#include <SFML/Graphics.hpp>
#include <utility>

namespace sf {

    class Button : public sf::Drawable, public sf::Transformable {
    public:
        explicit Button(sf::RectangleShape _rect, sf::Text _text)
                : rect{std::move(_rect)}, text{std::move(_text)} {}

        void setPosition(const sf::Vector2f &position);
        void setSize(const sf::Vector2f& size);
        void setShapeColor(const sf::Color& color);
        void setTextColor(const sf::Color& color);
        void setFont(const sf::Font& font);
        void setString(const std::string& str);

        Vector2f getPosition() const;
        Vector2f getSize() const;
        std::string getString() const;

    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void central();

    private:
        sf::RectangleShape rect;
        sf::Text text;

    };
}

#endif //BASE_BUTTON_H
