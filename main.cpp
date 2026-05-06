#include <SFML/Graphics.hpp>
int main()
{ sf::RenderWindow window(sf::VideoMode({800,600}),"platform oyunu");
window.setFramerateLimit(60);
//oyuncu
  sf::RectangleShape player({50.f,70.f});
  player.setFillColor(sf::Color::Green);
  player.setPosition({100.f,50.f});
  float speed=5.f;
while(window.isOpen())
{
 while(const std::optional event=window.pollEvent())
 {
  if(event->is<sf::Event::Closed>())
  {
   window.close();
  }
 }
//sol hareket icin
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
{
 player.move({-speed,0.f});
}
//sag hareket icin
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
{
 player.move({speed,0.f});
}
window.clear();
window.draw(player);
window.display();

}










return 0;
}