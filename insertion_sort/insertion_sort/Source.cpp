#include<SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
const int weidth = 1000; 
const int height = 800; 
const int barWeidth = 3;

void fillBars(std::vector<sf::RectangleShape> &bars) {
	int xOffset = 0; 
	while (xOffset <= weidth) {
		float barHeight = rand() % (height - 50) + 5; 
		sf::RectangleShape bar(sf::Vector2f(barWeidth,barHeight));
		bar.setFillColor(sf::Color::Blue);
		bar.setPosition(sf::Vector2f(xOffset,height-barHeight));
		bars.push_back(bar);
		xOffset += barWeidth + 3; 
	}
}
int main() {
	sf::RenderWindow window(sf::VideoMode(weidth,height), "Insertion Sort");
	sf::Event event; 

	srand(time(NULL));
	std::vector<sf::RectangleShape> bars;

	bool isSort = false; 
	sf::Clock clock; 

	int i = 1; 
	int j = i; 

	fillBars(bars);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			isSort = true; 
			std::cout << "Sorting Start\n"; 
		}
		if (isSort&&clock.getElapsedTime().asMilliseconds()>=1.f) {
			if (i < bars.size()) {
				if (j > 0) {
					if (bars[j].getSize().y < bars[j - 1].getSize().y) {
						float tempX = bars[j].getPosition().x;
						bars[j].setPosition(sf::Vector2f(bars[j-1].getPosition().x, bars[j].getPosition().y));
						bars[j-1].setPosition(sf::Vector2f(tempX, bars[j-1].getPosition().y));
						std::swap(bars[j],bars[j-1]);
					}
					j--;
				}
				else {
					i++;
					j = i;
				}
			}
			else {
				isSort = false; 
				std::cout << "Sorted\n";
			}
			clock.restart();
		}

		window.clear(sf::Color::White); 
		for (auto& bar : bars) window.draw(bar);
		window.display();
	}
}