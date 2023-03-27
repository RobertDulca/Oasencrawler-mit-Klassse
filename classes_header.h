#ifndef CLASSES_HEADER_H_INCLUDED
#define CLASSES_HEADER_H_INCLUDED



#endif // CLASSES_HEADER_H_INCLUDED


enum fieldType {nothing, danger, spring, relict};
enum dangerType {speed, accuracy, dodge, none};

class Player{
    public:
        Player();
        void movingHero();


        int getStats(char stat) const;
        double getHp() const;
        void setStats(char stat, double num);
        int getAttribut(char attribut) const;
        void setAttribut(char attribut, int num);
    private:
        int x;
        int y;
        double hp;
        int rp;
        int speed;
        int accuracy;
        int dodge;
};

class Field{
    public:
        Field();
        void init();

        fieldType getType();
        void setType(fieldType curr);
        int getEnemy() const;
        void setEnemy(int num);
        dangerType getdangerType();
        void setdangerType(dangerType curr);

    private:
        enum fieldType field;
        enum dangerType dangerField;
        int enemy;
};
