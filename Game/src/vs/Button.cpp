#include "Button.h"
namespace game {
	Button::Button(const std::string& S, const int& x, const int& y, sf::Font& font) {
		sprite.setSize(sf::Vector2f(120, 80));
		sprite.setOutlineThickness(1);
		sprite.setOutlineColor(sf::Color::Black);
		sprite.setPosition(x, y);
		text.setString(S);
		text.setFont(font);
		text.setPosition(x + 10, y + 5);
		text.setCharacterSize(25);
		text.setFillColor(sf::Color::Black);
		is_pressed = false;
		if (S == "Simple")
			type = SimpleTower::TypeOfLevel::Simple;
		if (S == "Middle")
			type = SimpleTower::TypeOfLevel::Middle;
		if (S == "Strong")
			type = SimpleTower::TypeOfLevel::Strong;
		if (S == "Location")
			strat = SimpleTower::TypeOfStrategy::Location;
		if (S == "Location\nto castle")
			strat = SimpleTower::TypeOfStrategy::LocationFromCastle;
		if (S == "Health \n  up")
			strat = SimpleTower::TypeOfStrategy::HealthUp;
		if (S == "Health \n down")
			strat = SimpleTower::TypeOfStrategy::HealthDown;
		if (S == "Speed \n  up")
			strat = SimpleTower::TypeOfStrategy::Speed;
	}
	Button::Button(Button&& B) {
		sprite = std::move(B.sprite);
		text = std::move(B.text);
		is_pressed = B.is_pressed;
	}

	void Button::setx(int x) {
		sf::Vector2f p = sprite.getPosition();
		text.setPosition(x + 10, p.y + 5);
		sprite.setPosition(x, p.y);
	}

	void Button::press() {
		if (is_pressed)
			text.setStyle(sf::Text::Regular);
		else
			text.setStyle(sf::Text::Bold);
		is_pressed = !is_pressed;
	}
	bool Button::is_being_pressed(const int& x, const int& y) {
		return sprite.getGlobalBounds().contains(x, y);
	}

	void Button::draw(sf::RenderWindow& window) {
		window.draw(sprite);
		window.draw(text);
	}
}