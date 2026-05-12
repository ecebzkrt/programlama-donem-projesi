#include <SFML/Graphics.hpp>
int main()
{ sf::RenderWindow window(sf::VideoMode({800,600}),"platform oyunu");
window.setFramerateLimit(60);
//oyuncu
float speed=5.f;
float velocityY=0.f;
float gravity=0.5f;
float jumpPower=-12.f;
bool isOnGround=false;
sf::RectangleShape ground({800.f,50.f});
ground.setFillColor(sf::Color::Blue);
ground.setPosition({0.f,550.f});
  sf::RectangleShape player({50.f,70.f});
  player.setFillColor(sf::Color::Green);
  player.setPosition({100.f,50.f});

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
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&&isOnGround)
{
velocityY=jumpPower;
isOnGround=false;
}
velocityY+=gravity;
player.move({0.f,velocityY});
if(player.getGlobalBounds().findIntersection(ground.getGlobalBounds()))
{
player.setPosition({player.getPosition().x,ground.getPosition().y-player.getSize().y});
velocityY=0.f;
isOnGround=true;
}
window.clear();
window.draw(player);
window.draw(ground);
window.display();

}










return 0;
}