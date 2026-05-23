#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

void resetGameElements(std::vector<sf::CircleShape>&coins,std::vector<sf::RectangleShape>&enemies)
{
coins.clear();
enemies.clear();
//coinleri ilk konumlariyla yeniden dolduruyorum
sf::CircleShape coin1(15.f);
coin1.setFillColor(sf::Color::Yellow);
coin1.setPosition({560.f,390.f});
coins.push_back(coin1);
sf::CircleShape coin2(15.f);
  coin2.setFillColor(sf::Color::Yellow);
  coin2.setPosition({300.f,360.f});
  coins.push_back(coin2);

  sf::CircleShape coin3(15.f);
  coin3.setFillColor(sf::Color::Yellow);
  coin3.setPosition({120.f,510.f});
  coins.push_back(coin3);

  //dusmanlari ilk konumlariyla yeniden dolduruyorum
  sf::RectangleShape enemy1({50.f,50.f});
enemy1.setFillColor(sf::Color::White);
enemy1.setPosition({700.f,500.f});
enemies.push_back(enemy1);

sf::RectangleShape enemy2({50.f,50.f});
enemy2.setFillColor(sf::Color::White);
enemy2.setPosition({1350.f,300.f});
enemies.push_back(enemy2);

sf::RectangleShape enemy3({50.f,50.f});
enemy3.setFillColor(sf::Color::White);
enemy3.setPosition({1700.f,500.f});
enemies.push_back(enemy3);

}

int main(){
  int level=1;
   sf::RenderWindow window(sf::VideoMode({800,600}),"platform oyunu");
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
sf::RectangleShape platform1({200.f,30.f});
platform1.setFillColor(sf::Color::Red);
platform1.setPosition({250.f,400.f});
platforms.push_back(platform1);

sf::RectangleShape platform2({200.f,30.f});
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
  player.setFillColor(sf::Color::Transparent);
  player.setPosition({100.f,50.f});
  sf::Texture playerTexture;
  if(!playerTexture.loadFromFile("player.png")){
    return -1;
  }
  sf::Sprite playerSprite(playerTexture);
  bool facingRight=true;
  
  //kamera olusturma
  sf::View view(sf::FloatRect({0.f,0.f},{800.f,600.f}));

  //coin
  std::vector<sf::CircleShape>coins;
  sf::CircleShape coin1(15.f);
  coin1.setFillColor(sf::Color::Yellow);
  coin1.setPosition({560.f,390.f});
  

  sf::CircleShape coin2(15.f);
  coin2.setFillColor(sf::Color::Yellow);
  coin2.setPosition({300.f,360.f});
  

  sf::CircleShape coin3(15.f);
  coin3.setFillColor(sf::Color::Yellow);
  coin3.setPosition({120.f,510.f});


//dusmanlar
std::vector<sf::RectangleShape> enemies;
sf::RectangleShape enemy1({50.f,50.f});
enemy1.setFillColor(sf::Color::White);
enemy1.setPosition({700.f,500.f});


sf::RectangleShape enemy2({50.f,50.f});
enemy2.setFillColor(sf::Color::White);
enemy2.setPosition({1350.f,300.f});


sf::RectangleShape enemy3({50.f,50.f});
enemy3.setFillColor(sf::Color::White);
enemy3.setPosition({1700.f,500.f});
resetGameElements(coins,enemies);
//dusmanlara hareket ekliyorumm
std::vector<float>enemyMovement;
enemyMovement.push_back(2.f);
enemyMovement.push_back(2.f);
enemyMovement.push_back(2.f);

sf::Texture enemyTexture;
if(!enemyTexture.loadFromFile("enemy.png"))
{
return -1;
}
sf::Sprite enemySprite(enemyTexture);
sf::Texture swordTexture;
if(!swordTexture.loadFromFile("sword.png"))
{
return -1;
}
sf::Sprite swordSprite(swordTexture);
sf::Texture heartTexture;
if(!heartTexture.loadFromFile("heart.png"))
{
return -1;
}
sf::Sprite heartSprite(heartTexture);
swordSprite.setOrigin({swordTexture.getSize().x/2.f,swordTexture.getSize().y/2.f});
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
  //level
  sf::Text levelText(font);
  levelText.setCharacterSize(24);
  levelText.setFillColor(sf::Color::White);
  levelText.setPosition({20.f,90.f});

sf::Text lifeText(font);
lifeText.setCharacterSize(24);
lifeText.setFillColor(sf::Color::White);
lifeText.setPosition({10.f,40.f});

//can hakki
int life=3;
bool isAttacking=false;
sf::Clock attackClock;
sf::Clock damageClock;

  sf::Clock animationClock;
while(window.isOpen())
{float animationTime=animationClock.getElapsedTime().asSeconds();
  bool isMoving=false;
  
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
 facingRight=false;
 isMoving=true;
}
//sag hareket icin
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
{
 player.move({speed,0.f});
 facingRight=true;
 isMoving=true;
}

//saldiri kontrolu
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
{ isAttacking=true;
  attackClock.restart();
}
if(isAttacking&&attackClock.getElapsedTime().asSeconds()>0.2f)
{
  isAttacking=false;
}

  float spriteScale=0.15f;
  if(isMoving)
  {
spriteScale=0.15f+std::sin(animationTime*10.f)*0.01f;
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
resetGameElements(coins,enemies);
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
//levelin bitis kismini ayarlama
if(player.getPosition().x>2900.f)
{ level++;
  player.setPosition({100.f,50.f});
  platforms.clear();
  enemies.clear();
  coins.clear();
  platforms.push_back(ground);
  if(level==2){
    sf::RectangleShape newPlatform1({250.f,30.f});
    newPlatform1.setFillColor(sf::Color::Green);
    newPlatform1.setPosition({400.f,450.f});
    platforms.push_back(newPlatform1);

    sf::RectangleShape newPlatform2({200.f,30.f});
    newPlatform2.setFillColor(sf::Color::Yellow);
    newPlatform2.setPosition({900.f,350.f});
    platforms.push_back(newPlatform2);

    sf::RectangleShape newEnemy({50.f,50.f});
     newEnemy.setPosition({1000.f,500.f});
     enemies.push_back(newEnemy);

     sf::CircleShape newCoin(15.f);
     newCoin.setFillColor({sf::Color::Yellow});
     newCoin.setPosition({950.f,300.f});
     coins.push_back(newCoin);
  }
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
//coin kontrolu
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
//dusman hareket 
for(int i=0;i<enemies.size();i++)
{
enemies[i].move({enemyMovement[i],0.f});
if(enemies[i].getPosition().x<600.f)
{
 enemyMovement[i]=2.f;
}
if(enemies[i].getPosition().x>900.f)
{
 enemyMovement[i]=-2.f;
}
}
//dusman kontrolu
sf::RectangleShape sword({20.f,40.f});
sword.setFillColor(sf::Color::White);
if(facingRight)
{
sword.setPosition({player.getPosition().x+100.f,player.getPosition().y+35.f});
}
else
{
sword.setPosition({player.getPosition().x-15.f,player.getPosition().y+35.f});
}
for(auto it=enemies.begin();it!=enemies.end();)
{
if(isAttacking&&sword.getGlobalBounds().findIntersection(it->getGlobalBounds()))
{
 it=enemies.erase(it);
 score+=2;
}
else { 
  if(player.getGlobalBounds().findIntersection(it->getGlobalBounds())&&damageClock.getElapsedTime().asSeconds()>1.f)
{
life--;
damageClock.restart();
player.setPosition({100.f,50.f});
velocityY=0.f;
resetGameElements(coins,enemies);
if(life<=0)
{
life=3;
score=0;
player.setPosition({100.f,50.f});
resetGameElements(coins,enemies);
}
}
it++;
}
}
scoreText.setString("score: "+std::to_string(score));
scoreText.setPosition({cameraX-390.f,10.f});

scoreText.setPosition({cameraX-390.f,10.f});

window.clear();
for(auto&platform:platforms)
{
 window.draw(platform);
}
for(auto&coin:coins)
{
window.draw(coin);
}
for(auto&enemy:enemies)
{
enemySprite.setPosition(enemy.getPosition());
enemySprite.setScale({0.12f,0.12f});
window.draw(enemySprite);
}
//level ana dongu ici
levelText.setString("Level: "+std::to_string(level));

if(facingRight)
{
playerSprite.setScale({spriteScale,spriteScale});
playerSprite.setPosition({player.getPosition().x+15.f,player.getPosition().y-45.f});
}
else
{
playerSprite.setScale({-spriteScale,spriteScale});
playerSprite.setPosition({player.getPosition().x+player.getSize().x+10.f,player.getPosition().y-45.f});
}
window.draw(playerSprite);

if(isAttacking)
{
swordSprite.setPosition(sword.getPosition());

if(facingRight)
{
swordSprite.setScale({0.12f,0.12f});
}
else
{
swordSprite.setScale({-0.12f,0.12f});
}
window.draw(swordSprite);
}
window.draw(scoreText);
for(int i=0;i<life;i++)
{
heartSprite.setScale({0.06f,0.06f});
heartSprite.setPosition({cameraX-390.f+(i*50.f),50.f});
window.draw(heartSprite);
}
window.draw(levelText);
window.display();
}
return 0;
}