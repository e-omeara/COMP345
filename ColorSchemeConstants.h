#include <SFML/Graphics.hpp>

class ColorSchemeConstants {

     public:
          static const sf::Color TEXT_COLOR;
          static const sf::Color BACKGROUND_COLOR;
          static const sf::Color PRIMARY_COLOR;
          static const sf::Color SECONDARY_COLOR;
          static const sf::Color ACCENT_COLOR;


};

//color scheme for the program / main menu
const sf::Color ColorSchemeConstants::TEXT_COLOR(224, 226, 219); // soft white
const sf::Color ColorSchemeConstants::BACKGROUND_COLOR(46, 53, 50); // soft black
const sf::Color ColorSchemeConstants::PRIMARY_COLOR(139, 38, 53); // dark red
const sf::Color ColorSchemeConstants::SECONDARY_COLOR( 240, 162, 2); // light sienna
const sf::Color ColorSchemeConstants::ACCENT_COLOR( 105, 143, 63); // sage green