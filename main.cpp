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
coin1.setPosition({560.f,470.f});
coins.push_back(coin1);
sf::CircleShape coin2(15.f);
  coin2.setFillColor(sf::Color::Yellow);
  coin2.setPosition({300.f,370.f});
  coins.push_back(coin2);

  sf::CircleShape coin3(15.f);
  coin3.setFillColor(sf::Color::Yellow);
  coin3.setPosition({120.f,460.f});
  coins.push_back(coin3);

  //dusmanlari ilk konumlariyla yeniden dolduruyorum
  sf::RectangleShape enemy1({50.f,50.f});
enemy1.setFillColor(sf::Color::White);
enemy1.setPosition({700.f,450.f});
enemies.push_back(enemy1);

sf::RectangleShape enemy2({50.f,50.f});
enemy2.setFillColor(sf::Color::White);
enemy2.setPosition({1350.f,300.f});
enemies.push_back(enemy2);

sf::RectangleShape enemy3({50.f,50.f});
enemy3.setFillColor(sf::Color::White);
enemy3.setPosition({1700.f,350.f});
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
sf::RectangleShape ground({3000.f,140.f});
ground.setFillColor(sf::Color::Blue);
ground.setPosition({0.f,500.f});
std::vector<sf::RectangleShape>platforms;
platforms.push_back(ground);

//platformlar
sf::RectangleShape platform1({200.f,50.f});
platform1.setFillColor(sf::Color::Red);
platform1.setPosition({250.f,400.f});
platforms.push_back(platform1);

sf::RectangleShape platform2({200.f,50.f});
platform2.setFillColor(sf::Color::Magenta);
platform2.setPosition({500.f,430.f});
platforms.push_back(platform2);

sf::RectangleShape platform3({200.f,50.f});
platform3.setFillColor(sf::Color::Cyan);
platform3.setPosition({900.f,450.f});
platforms.push_back(platform3);

sf::RectangleShape platform4({150.f,50.f});
platform4.setFillColor(sf::Color::White);
platform4.setPosition({1250.f,350.f});
platforms.push_back(platform4);

sf::RectangleShape platform5({250.f,50.f});
platform5.setFillColor(sf::Color::Red);
platform5.setPosition({1500.f,400.f});
platforms.push_back(platform5);

//bolum sonu bayragi
sf::RectangleShape finishBox({80.f,160.f});
finishBox.setFillColor(sf::Color::Transparent);
finishBox.setPosition({2850.f,390.f});

//oyuncu
  sf::RectangleShape player({50.f,70.f});
  player.setFillColor(sf::Color::Transparent);
  player.setPosition({100.f,50.f});
  sf::Texture playerTexture;
  if(!playerTexture.loadFromFile("player.png")){
    return -1;
  }
  sf::Sprite playerSprite(playerTexture);
  //oyuncunun ayagini yere bastirma

playerSprite.setOrigin({playerTexture.getSize().x/2.f,(float)playerTexture.getSize().y-80.f});
  bool facingRight=true;
  
  //kamera olusturma
  sf::View view(sf::FloatRect({0.f,0.f},{800.f,600.f}));

  //coin
  std::vector<sf::CircleShape>coins;
  sf::CircleShape coin1(15.f);
  coin1.setFillColor(sf::Color::Yellow);
  coin1.setPosition({560.f,470.f});
  

  sf::CircleShape coin2(15.f);
  coin2.setFillColor(sf::Color::Yellow);
  coin2.setPosition({300.f,370.f});
  

  sf::CircleShape coin3(15.f);
  coin3.setFillColor(sf::Color::Yellow);
  coin3.setPosition({120.f,460.f});


//dusmanlar
std::vector<sf::RectangleShape> enemies;
sf::RectangleShape enemy1({50.f,50.f});
enemy1.setFillColor(sf::Color::White);
enemy1.setPosition({700.f,450.f});


sf::RectangleShape enemy2({50.f,50.f});
enemy2.setFillColor(sf::Color::White);
enemy2.setPosition({1350.f,300.f});


sf::RectangleShape enemy3({50.f,50.f});
enemy3.setFillColor(sf::Color::White);
enemy3.setPosition({1700.f,350.f});
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
  if(!font.openFromFile("arial.ttf"))
{
    return -1; 
}
//background texture 
sf::Texture backgroundTexture;
if(!backgroundTexture.loadFromFile("background.png"))
{
 return -1;
}
backgroundTexture.setRepeated(true);
sf::Sprite backgroundSprite(backgroundTexture);
backgroundSprite.setTextureRect(sf::IntRect({0,0},{6000,1000}));
backgroundSprite.setScale({0.4f,0.7f});
//zemin texture
sf::Texture groundTexture;
if(!groundTexture.loadFromFile("groundCover.png"))
{
  return -1;
}
groundTexture.setRepeated(true);
sf::Sprite groundSprite(groundTexture);
//platform texture
sf::Texture platformTexture;
if(!platformTexture.loadFromFile("platformCover.png"))
{
return -1;
}
platformTexture.setRepeated(true);
sf::Sprite platformSprite(platformTexture);
//score texture
  sf::Text scoreText(font);
  scoreText.setCharacterSize(18);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition({10.f,10.f});
  //level texture
  sf::Text levelText(font);
  levelText.setCharacterSize(18);
  levelText.setFillColor(sf::Color::White);
  levelText.setPosition({20.f,90.f});
//kalp texture kismi
sf::Text lifeText(font);
lifeText.setCharacterSize(22);
lifeText.setFillColor(sf::Color::White);
lifeText.setPosition({10.f,18.f});
//bayrak texture kismi
sf::Texture flagTexture;
 if(!flagTexture.loadFromFile("flag.png"))
 {
 return -1;
 }
 sf::Sprite flagSprite(flagTexture);
//oyun baslangic menusu
bool gameStart=false;
sf::Text titleText(font);
titleText.setCharacterSize(45);
titleText.setFillColor(sf::Color::White);
titleText.setString("VALKYRIE"); 
titleText.setPosition({210.f,180.f});
 //oyun bitis
 bool gameWon=false;
sf::Text startText(font);
startText.setCharacterSize(24);
startText.setFillColor(sf::Color::Red);
startText.setString("press ENTER to start warrior");
startText.setPosition({80.f,280.f});

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
 if(!gameStart)
 { if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
  {
    gameStart=true;
 }
  window.clear();
  window.setView(window.getDefaultView());
  window.draw(titleText);
  window.draw(startText);
  window.display();
  continue;
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
  if(isMoving&&isOnGround)
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
//level atlama kismi
if(player.getGlobalBounds().findIntersection(finishBox.getGlobalBounds()))
{ 
  level++;
  player.setPosition({100.f,50.f});
  platforms.clear();
  enemies.clear();
  coins.clear();
  platforms.push_back(ground);
  if(level==2){
    sf::RectangleShape l2Platform1({250.f,30.f});
    l2Platform1.setPosition({400.f,450.f});
    platforms.push_back(l2Platform1);

    sf::RectangleShape l2Platform2({200.f,30.f});
    l2Platform2.setPosition({800.f,350.f});
    platforms.push_back(l2Platform2);
    
    sf::RectangleShape l2PLatform3({150.f,30.f});
    l2PLatform3.setPosition({1200.f,400.f});
    platforms.push_back(l2PLatform3);

    sf::RectangleShape l2PLatform4({150.f,30.f});
    l2PLatform4.setPosition({1400.f,450.f});
    platforms.push_back(l2PLatform4);

    // level 2'de oyunun zorlasmasi icin dusman sayisini arttiriyorum.

    sf::RectangleShape l2Enemy1({50.f,50.f});
     l2Enemy1.setPosition({600.f,450.f});
     enemies.push_back(l2Enemy1); 
     enemyMovement.push_back(3.5f);  //hizlarini bilerek farkli ayarliyorum ki oldurmek zorlassin

      sf::RectangleShape l2Enemy2({50.f,50.f});
     l2Enemy2.setPosition({1100.f,300.f});
     enemies.push_back(l2Enemy2);
     enemyMovement.push_back(1.5f);
    
      sf::RectangleShape l2Enemy3({50.f,50.f});
     l2Enemy3.setPosition({1400.f,350.f});
     enemies.push_back(l2Enemy3);
     enemyMovement.push_back(2.5f);

      sf::RectangleShape l2Enemy4({50.f,50.f});
     l2Enemy4.setPosition({1600.f,450.f});
     enemies.push_back(l2Enemy4);
     enemyMovement.push_back(3.5f);

     sf::CircleShape l2Coin1(15.f);
     l2Coin1.setFillColor({sf::Color::Yellow});
     l2Coin1.setPosition({850.f,300.f});
     coins.push_back(l2Coin1);

     sf::CircleShape l2Coin2(15.f);
     l2Coin2.setFillColor(sf::Color::Yellow);
     l2Coin2.setPosition({1350.f,350.f});
     coins.push_back(l2Coin2);
  }
  else if(level==3)
  { //level 3 icin platformlar ekliyorum
   
    sf::RectangleShape l3platform1({150.f,30.f});
   l3platform1.setPosition({350.f,400.f});
    platforms.push_back(l3platform1);

sf::RectangleShape l3platform2({200.f,50.f});
   l3platform2.setPosition({650.f,350.f});
    platforms.push_back(l3platform2);

    sf::RectangleShape l3platform3({170.f,80.f});
   l3platform3.setPosition({800.f,380.f});
    platforms.push_back(l3platform3);

sf::RectangleShape l3platform4({230.f,60.f});
   l3platform4.setPosition({1300.f,430.f});
    platforms.push_back(l3platform4);

sf::RectangleShape l3platform5({150.f,30.f});
   l3platform5.setPosition({1750.f,400.f});
    platforms.push_back(l3platform5);

//dusman ekliyorum

sf::RectangleShape l3enemy1({50.f,50.f});
l3enemy1.setPosition({350.f,380.f});
enemies.push_back(l3enemy1);
enemyMovement.push_back(4.5f);

sf::RectangleShape l3enemy2({50.f,50.f});
l3enemy2.setPosition({650.f,330.f});
enemies.push_back(l3enemy2);
enemyMovement.push_back(4.f);

sf::RectangleShape l3enemy3({50.f,50.f});
l3enemy3.setPosition({790.f,360.f});
enemies.push_back(l3enemy3);
enemyMovement.push_back(3.5f);

sf::RectangleShape l3enemy4({50.f,50.f});
l3enemy4.setPosition({1310.f,430.f});
enemies.push_back(l3enemy4);
enemyMovement.push_back(5.f);

sf::RectangleShape l3enemy5({50.f,50.f});
l3enemy5.setPosition({1770.f,280.f});
enemies.push_back(l3enemy5);
enemyMovement.push_back(3.5f);
//coin ekliyorum
sf::CircleShape l3coin1(15.f);
l3coin1.setFillColor(sf::Color::Yellow);
l3coin1.setPosition({340.f,370.f});
coins.push_back(l3coin1);

sf::CircleShape l3coin2(15.f);
l3coin2.setFillColor(sf::Color::Yellow);
l3coin2.setPosition({640.f,330.f});
coins.push_back(l3coin2);

sf::CircleShape l3coin3(15.f);
l3coin3.setFillColor(sf::Color::Yellow);
l3coin3.setPosition({1730.f,280.f});
coins.push_back(l3coin3);
  }
  else if(level>3)
  {
  //kazanma ekrani
  }
}
//oyuncu collision kismi
isOnGround=false;
for(auto& platform:platforms)
{
if(player.getGlobalBounds().findIntersection(platform.getGlobalBounds())&&velocityY>0)
{
  float groundFix=0.f; //oyuncuyu platformlara manuel olarak oturttum ama oyuncu zeminde havada kaliyordu.
  
   if(platform.getSize().x>1000.f)
   {
   groundFix=20.f;
   }
   player.setPosition({

   player.getPosition().x,platform.getPosition().y-player.getSize().y+groundFix});
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
//dusman platformun sonuna gelince geri donsun diye
if(enemies[i].getPosition().x<=0.f||enemies[i].getPosition().x>=2900)
{
enemyMovement[i]*=-1.f;
}
}
//dusman kontrolu
sf::RectangleShape sword({20.f,40.f});
sword.setFillColor(sf::Color::White);
if(facingRight)
{
sword.setPosition({player.getPosition().x+70.f,player.getPosition().y+35.f});
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
score=0;
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

window.clear();
//background cizim
backgroundSprite.setPosition({cameraX/2.0f-400.f,-100.f});//arka planı kamera hareketinin yari hizinda kaydiriyoruz.
window.draw(backgroundSprite);
//platform cizim kismi
for(auto&platform:platforms)
{ 
  
  if(platform.getSize().x>1000.f)
  {groundSprite.setPosition(platform.getPosition());
    groundSprite.setScale({platform.getSize().x / groundTexture.getSize().x, 
   platform.getSize().y / groundTexture.getSize().y});
      window.draw(groundSprite);
}
else
{
platformSprite.setPosition(platform.getPosition());
platformSprite.setScale({platform.getSize().x / platformTexture.getSize().x, 
  platform.getSize().y / platformTexture.getSize().y});
window.draw(platformSprite);
}
   }
//coin cizim
for(auto&coin:coins)
{
window.draw(coin);
}

flagSprite.setPosition({2780.f,330.f});
flagSprite.setScale({0.18f,0.18f});
window.draw(flagSprite);
//enemy cizim
for(auto&enemy:enemies)
{
enemySprite.setPosition(enemy.getPosition());
enemySprite.setScale({0.12f,0.12f});
window.draw(enemySprite);
}
//level string
levelText.setString("Level: "+std::to_string(level));
levelText.setPosition({cameraX-390.f,95.f});
//oyuncu cizim
if(facingRight)
{
playerSprite.setScale({spriteScale,spriteScale});

}
else
{
playerSprite.setScale({-spriteScale,spriteScale});
}
 
playerSprite.setPosition({
    player.getPosition().x+ player.getSize().x / 2.f, 
    player.getPosition().y + player.getSize().y+20.f});
window.draw(playerSprite);

if(isAttacking)
{
swordSprite.setPosition({sword.getPosition().x,sword.getPosition().y});

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
heartSprite.setPosition({cameraX-410.f+(i*45.f),30.f});
window.draw(heartSprite);
}
window.draw(levelText);
window.display();
}
return 0;
}