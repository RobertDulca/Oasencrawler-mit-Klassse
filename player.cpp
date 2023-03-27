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
