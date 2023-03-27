#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "classes_header.h"

#define GRID_SIZE 5

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// Struct for the player and field, enum for the types of fields and counter for the relicts, damage, and healing
/////////////////////////////////////////////////////////////////////////////////////////

int level = 1;
int relictsCounter = 0;
double damageCounter = 0;
int hpCounter = 0;
int enemySpawnCounter = 0;
int enemyFought = 0;
int enemyHit = 0;


/////////////////////////////////////////////////////////////////////////////////////////
//Function to move the Hero
/////////////////////////////////////////////////////////////////////////////////////////

Player::Player(){
    this->x = 0;
    this->y = 0;
    this->hp = 5;
    this->rp = 0;
    this->accuracy = 2;
    this->dodge = 4;
    this->speed = 3;
}

void Player::movingHero(){
    char movement;
    int moved = 0;

    while (true) {
        cout  << "Press w,a,s,d to move the Hero: ";
        cin >> movement;
        cout << endl;

        switch (movement) {
            case 'w':
                if (y == 0) {
                    cout<< "You are at the border of this world. Please try another direction."<<endl;
                    break;
                } else{
                    y--;
                    moved = 1;
                }
                break;
            case 'a':
                if (x == 0) {
                    cout<< "You are at the border of this world. Please try another direction."<<endl;
                    break;
                } else{
                    x--;
                    moved = 1;
                }
                break;
            case 's':
                if (y == 4) {
                    cout<< "You are at the border of this world. Please try another direction."<<endl;
                    break;
                } else{
                    y++;
                    moved = 1;
                }
                break;
            case 'd':
                if (x == 4) {
                    cout<< "You are at the border of this world. Please try another direction."<<endl;
                    break;
                } else{
                    x++;
                    moved = 1;
                }
                break;
            default:
                cout<< "Invalid input. Please try again.";
                break;
        }
        if(moved == 1)
            break;
    }
}

int Player::getStats(char stat) const{
    switch (stat) {
        case 'x':
            return x;
        case 'y':
            return y;
        case 'r':
            return rp;
    }
}

void Player::setStats(char stat, double num) {
    switch (stat) {
        case 'h':
            this->hp = num;
            break;
        case 'r':
            this->rp = num;
            break;
    }
}

double Player::getHp() const {
    return hp;
}

int Player::getAttribut(char attribut) const {
    switch (attribut) {
        case 's':
            return speed;
        case 'a':
            return accuracy;
        case 'd':
            return dodge;
    }
}

void Player::setAttribut(char attribut, int num) {
    switch (attribut) {
        case 's':
            speed += num;
            break;
        case 'a':
            accuracy += num;
            break;
        case 'd':
            dodge += num;
            break;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function to create and print World
/////////////////////////////////////////////////////////////////////////////////////////

Field::Field(){
    this->field = nothing;
    this->dangerField = none;
    this->enemy = 0;
    level = 1;
}

void Field::init() {
    int fieldType  = rand() % 10;
    int nothingNum = 3;
    int dangerNum = 7;
    int springNum = 8;
    int relictNum = 9;

    if(level==2){
        nothingNum--;
        dangerNum--;
        springNum--;
    }
    if(level==3){
        nothingNum-=2;
    }
    if(level==4){
        nothingNum-=3;
        dangerNum-=2;
    }
    if(level>=5){
        nothingNum-=4;
    }

    if(fieldType>-1 && fieldType<=nothingNum){
        this->field = nothing;
        this->dangerField = none;
    } else if(fieldType>nothingNum && fieldType<=dangerNum){
        this->field = danger;
        int danger = rand() % 3;
        switch (danger) {
            case 0:
                this->dangerField = speed;
                break;
            case 1:
                this->dangerField = accuracy;
                break;
            case 2:
                this->dangerField = dodge;
                break;
        }
    } else if(fieldType > dangerNum && fieldType <= springNum){
        this->field = spring;
        this->dangerField = none;
    } else if(fieldType > springNum && fieldType <= relictNum){
        this->field = relict;
        this->dangerField = none;
        relictsCounter++;
    }
}

fieldType Field::getType() {
    return field;
}

void Field::setType(fieldType curr) {
    this->field = curr;
}

int Field::getEnemy() const {
    return enemy;
}

void Field::setEnemy(int num) {
    this->enemy = num;
}

dangerType Field::getdangerType() {
    return dangerField;
}

void Field::setdangerType(dangerType curr) {
    this->dangerField = curr;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Function for the interaction with the different fields and hero's stats
/////////////////////////////////////////////////////////////////////////////////////////

void initializeWorld(Field World[GRID_SIZE][GRID_SIZE]){
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            World[i][j].init();
        }
    }
    //Randbedingungen werden überprüft
    if(relictsCounter == 0){
        int x = rand() % 5;
        int y = rand() % 5;
        World[y][x].setType(relict);
        relictsCounter++;
    }
    //Feinde werden mit jedem Level erhöht
    int enemies = 2;
    if(level == 3){
        enemies++;
    }
    if(level >= 5){
        enemies = level-1;
    }

    for(int i= 0; i<2; i++){
        int x = rand() % 5;
        int y = rand() % 5;
        World[y][x].setEnemy(1);
        enemySpawnCounter++;
    }
}

int fieldAction(Field World[GRID_SIZE][GRID_SIZE], Player* Hero){
    enum fieldType currentField = World[Hero->getStats('y')][Hero->getStats('x')].getType();
    int damageReceived = rand() % 6;
    double heal;
    int possAttribut;
    int attri = rand() % 10;
    int dangerField = 0;
    int getItem = 0;

    if(World[Hero->getStats('y')][Hero->getStats('x')].getEnemy() == 1){
        int enemyDamage = rand() % 6;
        if(enemyDamage == 5){
            double damage = Hero->getHp() - 1.5;
            Hero->setStats('h', damage);
            damageCounter += 1.5;
            enemyHit = 1;
        }
        World[Hero->getStats('y')][Hero->getStats('x')].setEnemy(0);
        enemyFought++;
    }

    switch (currentField) {
        case nothing:
            World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
            return 0;
        case danger:
            dangerField = 1;
            World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
            break;
        case spring:
            heal = Hero->getHp() + 1;
            Hero->setStats('h', heal);
            hpCounter++;
            World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
            getItem = 1;
            break;
        case relict:
            int relict = Hero->getStats('r') + 1;
            Hero->setStats('r', relict);
            World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
            getItem = 2;
            break;
    }

    dangerType gefahr = World[Hero->getStats('y')][Hero->getStats('x')].getdangerType();
    if(dangerField == 1) {
        switch (gefahr) {
            case speed:
                possAttribut = Hero->getAttribut('s');
                World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
                if (attri < possAttribut) {
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 5;
                } else {
                    double damage = Hero->getHp() - 0.25;
                    Hero->setStats('h', damage);
                    damageCounter += 0.25;
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 6;
                }
            case accuracy:
                possAttribut = Hero->getAttribut('a');
                World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
                if (attri < possAttribut) {
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 7;
                } else {
                    double damage = Hero->getHp() - 0.25;
                    Hero->setStats('h', damage);
                    damageCounter += 0.25;
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 8;
                }
            case dodge:
                possAttribut = Hero->getAttribut('d');
                World[Hero->getStats('y')][Hero->getStats('x')].setType(nothing);
                if (attri < possAttribut) {
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 9;
                } else {
                    double damage = Hero->getHp() - 0.25;
                    Hero->setStats('h', damage);
                    damageCounter += 0.25;
                    World[Hero->getStats('y')][Hero->getStats('x')].setdangerType(none);
                    return 10;
                }
            case none:
                return 0;
        }
    }

    if(getItem == 1 || getItem == 2){
        int item = rand() % 3;

        switch (item) {
            case 0:
                if(getItem == 1){
                    if(Hero->getAttribut('s') <=10)
                        Hero->setAttribut('s',1);
                    else
                        return 17;
                    return 11;
                } else{
                    if(Hero->getAttribut('s') <=10)
                        Hero->setAttribut('s',1);
                    else
                        return 17;
                    return 12;
                }
            case 1:
                if(getItem == 1){
                    if(Hero->getAttribut('a') <=10)
                        Hero->setAttribut('a',1);
                    else
                        return 17;
                    return 13;
                } else{
                    if(Hero->getAttribut('a') <=10)
                        Hero->setAttribut('a',1);
                    else
                        return 17;
                    return 14;
                }
            case 2:
                if(getItem == 1){
                    if(Hero->getAttribut('d') <=10)
                        Hero->setAttribut('d',1);
                    else
                        return 17;
                    return 15;
                } else{
                    if(Hero->getAttribut('d') <=10)
                        Hero->setAttribut('d',1);
                    else
                        return 17;
                    return 16;
                }
        }
    }
}

void printWorld(Field World[GRID_SIZE][GRID_SIZE], Player Hero){
    for (int i = 0; i < GRID_SIZE; i++) {
        cout<<"| ";
        for (int j = 0; j < GRID_SIZE; j++) {
            Field current = World[i][j];
            if(i == Hero.getStats('y') && j == Hero.getStats('x')){
                cout<< "H";
                cout<<" | ";
                continue;
            } else if(current.getEnemy() == 1){
                cout<<"E";
                cout<<" | ";
                continue;
            }
            switch (current.getType()) {
                case nothing: cout<< " ";
                    break;
                case danger: cout<< "D";
                    break;
                case spring: cout<< "S";
                    break;
                case relict: cout<< "R";
                    break;
            }
            cout<<" | ";
        }
        cout<< endl;
    }
}

void showStats(Player Hero){
    cout<<"Location: " << Hero.getStats('x') <<"|" << Hero.getStats('y') <<endl;
    cout<<"HP: "<<Hero.getHp() <<endl;
    cout<<"Speed:"<<Hero.getAttribut('s')<<endl;
    cout<<"Accuracy:"<<Hero.getAttribut('a')<<endl;
    cout<<"Dodge:"<<Hero.getAttribut('d')<<endl;
    cout<<"Relicts: "<<Hero.getStats('r') <<endl<<endl;
}

void gameLog(Player Hero){
    cout<<"Received Damage: "<< damageCounter <<endl;
    cout<<"Healed damage: "<< hpCounter <<endl;
    cout<<"Found relicts: "<<Hero.getStats('r') <<"/"<< relictsCounter <<endl;
    cout << "Enemies encountered: " << enemyFought << "/" << enemySpawnCounter << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////
//Main function
/////////////////////////////////////////////////////////////////////////////////////////

int main(){
    srand (time(0));
    //initialising the variables
    Field World[GRID_SIZE][GRID_SIZE];
    Player Hero;

    int actionOutput;
    int enemySeen = 0;

    while(true) {
        //welcome text
        cout<<endl<<endl;
        cout << "Welcome to The Oasencrawler Game. You are at Level " << level << endl << endl;
        cout << "Index:" << endl;
        cout << "| |....... empty field (nothing will happen on this field)" << endl;
        cout
                << "|D|....... damage field (there is a chance of 1:6 that you will receive damage on this field, so watch out)"
                << endl;
        cout << "|S|....... spring field (you will receive +1HP)" << endl;
        cout
                << "|R|....... relict field (here are the relicts which you need to collect. Collect them all and you will win the game)"
                << endl;
        cout
                << "|E|....... enemy field (each enemy deals each round 0.25 damage; if you attack them head on, they will instantly die,"
                << endl << "but there is a 1:6 chance that you will receive 1.5 damage)" << endl << endl << endl;

        //Initialize World
        initializeWorld(World);

        while (true) {

            actionOutput = fieldAction(World,
                                       &Hero);//before printing the world, the action for which the field stands for is being executed
            showStats(Hero);//stats and World are being printed
            cout << "Current damage:" << damageCounter << endl;
            printWorld(World, Hero);
            //in case there was an encounter with an enemy, the message with the dealt damage is being printed here
            if (enemySeen < enemyFought) {
                double dealt = 0;
                if (enemyHit == 1)
                    dealt = 1.5;
                cout << "An enemy attacked you and dealt " << dealt << " damage.";
                enemySeen++;
                enemyHit = 0;
            }

            //this switch case takes care of printing the messages for each field
            switch (actionOutput) {
                case 0:
                    cout << "This Field is empty, so don't worry and keep collecting all Relicts." << endl;
                    break;
                    /*case 1:
                        cout  << "You entered a Danger Field. Damage received: 1"<<endl;
                        break;
                    case 2:
                        cout  << "You entered a Danger Field. Damage received: 0"<<endl;
                        break;
                    case 3:
                        cout  << "This is a Spring Field. You can rest for a while and you will receive 1 HP"<<endl;
                        break;
                    case 4:
                        cout  << "You have found a relict."<<endl;
                        break;*/
                case 5:
                    cout
                            << "You have entered a parkour field and successfully mastered the course. You don't lose any HP."
                            << endl;
                    break;
                case 6:
                    cout << "You have entered a parkour field and failed the course. You lose 0.25HP." << endl;
                    break;
                case 7:
                    cout
                            << "You have entered an archery field and successfully hit all  targets. You don't lose any HP."
                            << endl;
                    break;
                case 8:
                    cout << "You have entered an archery field and missed a target. You lose 0.25HP." << endl;
                    break;
                case 9:
                    cout
                            << "You have entered a dodging field and successfully dodged every boulder. You don't lose any HP."
                            << endl;
                    break;
                case 10:
                    cout << "You have entered a dodging field and were hit by one of the boulders. You lose  0.25 HP. "
                         << endl;
                    break;
                case 11:
                    cout
                            << "This is a Spring Field. You can rest for a while and you will receive 1 HP. You also found a boost elixir which will upgrade your speed by 1."
                            << endl;
                    break;
                case 12:
                    cout << "You have found a relict. You also found a boost elixir which will upgrade your speed by 1."
                         << endl;
                    break;
                case 13:
                    cout
                            << "This is a Spring Field. You can rest for a while and you will receive 1 HP. You also found a boost elixir which increases your accuracy by 1."
                            << endl;
                    break;
                case 14:
                    cout << "You have found a relict. You also found a boost elixir which increases you accuracy by 1."
                         << endl;
                    break;
                case 15:
                    cout
                            << "This is a Spring Field. You can rest for a while and you will receive 1 HP. You also found a boost elixir which increases your dodging ability by 1."
                            << endl;
                    break;
                case 16:
                    cout
                            << "You have found a relict. You also found a boost elixir which increases your dodging ability by 1."
                            << endl;
                    break;
                case 17:
                    cout << "Your attribute is maxed out, you are not able to upgrade it anymore." << endl;
                    break;
            }


            if (relictsCounter == Hero.getStats('r')) {
                cout << endl << endl << "Congratulations. You have won the level. You will soon be teleported to the next level." << endl;
                gameLog(Hero);
                level++;
                if(level<5)
                    Hero.setStats('h', (5 + level -1));
                Sleep(2000);
                break;
            }

            if (Hero.getHp() <= 0) {
                cout << endl << endl << "You died. The game is over." << endl;
                gameLog(Hero);
                break;
            }

            for (int i = 0; i < enemySpawnCounter - enemyFought; i++) {
                int enemyRangeHit = rand() % 5;
                if (enemyRangeHit >= 3) {
                    double damage = Hero.getHp() - (0.25);
                    Hero.setStats('h', damage);
                    damageCounter += (0.25);
                }
            }
            Hero.movingHero();
        }
        if (Hero.getHp() <= 0) {
            cout << endl << endl << "You died. The game is over." << endl;
            gameLog(Hero);
            break;
        }
    }

    return 0;
}
