#include <SFML/Graphics.hpp>
#include <vector>
int main()
{ sf::RenderWindow window(sf::VideoMode({800,600}),"platform oyunu");
window.setFramerateLimit(60);
float speed=5.f;
float velocityY=0.f;
float gravity=0.5f;
float jumpPower=-12.f;
bool isOnGround=false;
sf::RectangleShape ground({800.f,50.f});
ground.setFillColor(sf::Color::Blue);
ground.setPosition({0.f,550.f});
std::vector<sf::RectangleShape>platforms;
platforms.push_back(ground);
sf::RectangleShape platform1({30.f,200.f});
platform1.setFillColor(sf::Color::Red);
platform1.setPosition({250.f,400.f});
platforms.push_back(platform1);

sf::RectangleShape platform2({30.f,200.f});
platform2.setFillColor(sf::Color::Magenta);
platform2.setPosition({500.f,300.f});
platforms.push_back(platform2);

//oyuncu
  sf::RectangleShape player({50.f,70.f});
  player.setFillColor(sf::Color::Green);
  player.setPosition({100.f,50.f});
  //coin
  sf::CircleShape coin(15.f);
  coin.setFillColor(sf::Color::Yellow);
  coin.setPosition({560.f,260.f});
  bool coinCollected=false;

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
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)&&isOnGround)
{
velocityY=jumpPower;
isOnGround=false;
}
velocityY+=gravity;
player.move({0.f,velocityY});
if(player.getPosition().x<0)
{
player.setPosition({0.f,player.getPosition().y});
}
if(player.getPosition().x+player.getSize().x>800)
{
 player.setPosition({800.f-player.getSize().x,player.getPosition().y});
}

isOnGround=false;
for(auto& plaform:platforms)
{
if(player.getGlobalBounds().findIntersection(plaform.getGlobalBounds())&&velocityY>0)
{
player.setPosition({

player.getPosition().x,plaform.getPosition().y-player.getSize().y});
velocityY=0.f;
isOnGround=true;
}
}
if(!coinCollected&&player.getGlobalBounds().findIntersection(coin.getGlobalBounds()))
{
coinCollected=true;
}

window.clear();
for(auto&platform:platforms)
{
 window.draw(platform);
}
if(!coinCollected)
{
window.draw(coin);
}
window.draw(player);
window.display();

}










return 0;
}