#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
int main()
{ sf::RenderWindow window(sf::VideoMode({800,600}),"platform oyunu");
window.setFramerateLimit(60);
float speed=5.f;
float velocityY=0.f;
float gravity=0.5f;
float jumpPower=-12.f;
bool isOnGround=false;
//oyun zemini
sf::RectangleShape ground({3000.f,50.f});
ground.setFillColor(sf::Color::Blue);
ground.setPosition({0.f,550.f});
std::vector<sf::RectangleShape>platforms;
platforms.push_back(ground);

//platformlar
sf::RectangleShape platform1({30.f,100.f});
platform1.setFillColor(sf::Color::Red);
platform1.setPosition({250.f,400.f});
platforms.push_back(platform1);

sf::RectangleShape platform2({30.f,100.f});
platform2.setFillColor(sf::Color::Magenta);
platform2.setPosition({500.f,430.f});
platforms.push_back(platform2);

sf::RectangleShape platform3({200.f,30.f});
platform3.setFillColor(sf::Color::Cyan);
platform3.setPosition({900.f,450.f});
platforms.push_back(platform3);

sf::RectangleShape platform4({150.f,30.f});
platform4.setFillColor(sf::Color::White);
platform4.setPosition({1250.f,350.f});
platforms.push_back(platform4);

sf::RectangleShape platform5({250.f,30.f});
platform5.setFillColor(sf::Color::Red);
platform5.setPosition({1500.f,400.f});
platforms.push_back(platform5);

//oyuncu
  sf::RectangleShape player({50.f,70.f});
  player.setFillColor(sf::Color::Green);
  player.setPosition({100.f,50.f});

  //kamera olusturma
  sf::View view(sf::FloatRect({0.f,0.f},{800.f,600.f}));

  //coin
  std::vector<sf::CircleShape>coins;
  sf::CircleShape coin1(15.f);
  coin1.setFillColor(sf::Color::Yellow);
  coin1.setPosition({560.f,260.f});
  coins.push_back(coin1);

  sf::CircleShape coin2(15.f);
  coin2.setFillColor(sf::Color::Yellow);
  coin2.setPosition({300.f,360.f});
  coins.push_back(coin2);

  sf::CircleShape coin3(15.f);
  coin3.setFillColor(sf::Color::Yellow);
  coin3.setPosition({120.f,510.f});
  coins.push_back(coin3);
  //score ayari
  int score=0;
  sf::Font font;
  if(!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf"))
{
    return -1;
}
  sf::Text scoreText(font);
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({10.f,10.f});

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
if(player.getPosition().y>700.f)
{
player.setPosition({100.f,50.f});
velocityY=0.f;
score=0;
}

float cameraX=player.getPosition().x+player.getSize().x/2;
if(cameraX<400.f)
{
cameraX=400.f;
}
if(cameraX>3000.f-400.f)
{
cameraX=3000.f-400.f;
}
view.setCenter({cameraX,300.f});
window.setView(view);
if(player.getPosition().x<0)
{
player.setPosition({0.f,player.getPosition().y});
}
if(player.getPosition().x+player.getSize().x>3000)
{
 player.setPosition({3000.f-player.getSize().x,player.getPosition().y});
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
for(auto it=coins.begin();it!=coins.end();)
{
if(player.getGlobalBounds().findIntersection(it->getGlobalBounds()))
{
 it=coins.erase(it);
 score++;
}
else{

  ++it;
}
}




scoreText.setString("score: "+std::to_string(score));
window.clear();
for(auto&platform:platforms)
{
 window.draw(platform);
}
for(auto&coin:coins)
{
window.draw(coin);
}
window.draw(player);
window.draw(scoreText);
window.display();

}










return 0;
}