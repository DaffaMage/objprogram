///MUHAMMAD DAFFA ABIYYU RAHMAN
///2916100010
///KELAS A

///LIBRARIES
#include <iostream>
#include <math.h>
#include <graphics.h>

///BLADE COLORS
#define REDBLADE 0
#define YELLOWBLADE 1
#define GREENBLADE 2
#define BLUEBLADE 3
#define CYANBLADE 4
#define MAGENTABLADE 5

///MOVEMENT
#define LEFT 2
#define RIGHT 3

///INTERFACE TYPE
#define INTERFACEBAR 1
#define INTERFACESKILL 2
#define INTERFACEBUFF 3

///SKILLS
#define BLADECLEANSING 0
#define NULLSHIELD 1

using namespace std;

///BASE OBJECTS
class pts
{
protected:
    int x,y;
public:
    pts()
    {
        x = 0; y = 0;
    };
    pts(int a, int b)
    {
        a = x; b = y;
    };
    int getX()
    {
        return x;
    };
    int getY()
    {
        return y;
    };
    void changeX(int a)
    {
        x = a;
    };
    void changeY(int b)
    {
        y = b;
    };
    void changeXY(int a, int b)
    {
        changeX(a);
        changeY(b);
    };
    double dst(pts a)
    {
        return sqrt(pow(x-a.x,2)+pow(y-a.y,2));
    };
    double dst(int a, int b)
    {
        return sqrt(pow(x-a,2)+pow(y-b,2));
    };
    double dstpost(pts a, pts b)
    {
        x = a.getX();
        y = a.getY();
        return dst(b);
    };
};

///OBJECT : SWORD
class blade : public pts
{
private:
    pts node[14];
    int s,l,col,spd,deg;
    void build()
    {
        node[0].changeXY(x,y);
        ///UPPER HILT
        node[1].changeXY((x-(s/4)),y-s);
        node[2].changeXY((x+(s/4)),y-s);
        ///LOWER HILT
        node[3].changeXY((x+(s/4)),y+s);
        node[4].changeXY((x-(s/4)),y+s);
        ///UPPER EDGE
        node[5].changeXY((x+(s/2)),y+s+(s/2));
        node[6].changeXY((x-(s/2)),y+s+(s/2));
        ///EDGE
        node[7].changeXY((x-(s/2)),y+l);
        node[8].changeXY((x+(s/2)),y+l);
        ///TIP
        node[9].changeXY((x)*(int) cos(deg),y+l*2);
        ///GAP
        node[10].changeXY((x-s),y+s);
        node[11].changeXY((x+s),y+s);
        node[12].changeXY((x+s),y+s+(s/2));
        node[13].changeXY((x-s),y+s+(s/2));
    };
public:
    blade()
    {
        x=0;y=0;s=15;l = 50;col=RED;
        build();
    }
    blade(int a, int b, int c, int d, int e, int f)
    {
        x = a;y = b;s = c;l = d;col = e;spd = f;deg=0;
        build();
    }
    void reset()
    {
        y = 100;spd = 10;changeColor(WHITE);
    }
    void draw()
    {
        setcolor(col);
        int i,j;
        for (i=1;i<4;i++)
        {
            for(j=4;j>1;j--)
            {
                line(node[i].getX(),node[i].getY(),node[j].getX(),node[j].getY());
            }
        }
        for (i=5;i<8;i++)
        {
            j = i+1;
            line(node[i].getX(),node[i].getY(),node[j].getX(),node[j].getY());
        }
        line(node[8].getX(),node[8].getY(),node[5].getX(),node[5].getY());
        for(i=7;i<9;i++)
        {
            for(j=9;j>7;j--)
            {
                line(node[i].getX(),node[i].getY(),node[j].getX(),node[j].getY());
            }
        }
        for(i=10;i<13;i++)
        {
            j = i+1;
            line(node[i].getX(),node[i].getY(),node[j].getX(),node[j].getY());
        }
        line(node[13].getX(),node[13].getY(),node[10].getX(),node[10].getY());
    }
    void restat(int x)
    {
        y += spd;
        if (y>=450)
        {
            y = 100;
            spd = 1+rand()%8;
            changeColor(rand()%6);
        }
        build();
    }
    bool collide()
    {
        if (y+spd>=450)
            return true;
        else
            return false;
    }
    void changeColor(int newColor)
    {
        switch (newColor)
        {
            case REDBLADE: newColor=RED;break;
            case YELLOWBLADE: newColor=YELLOW;break;
            case GREENBLADE: newColor=GREEN;break;
            case BLUEBLADE: newColor=BLUE;break;
            case CYANBLADE: newColor=CYAN;break;
            case MAGENTABLADE: newColor=MAGENTA;break;
            case WHITE: newColor=WHITE;break;
        }
        col = newColor;
    }
    int getCurrentColor()
    {
        return col;
    }
    int getEffect(int shieldloc)
    {
        if (shieldloc!=x)
        {
            switch (col)
            {
                case RED:return REDBLADE;break;
                case YELLOW:return YELLOWBLADE;break;
                case GREEN:return GREENBLADE;break;
                case BLUE:return BLUEBLADE;break;
                case CYAN:return CYANBLADE;break;
                case MAGENTA:return MAGENTABLADE;break;
            }
        }
        return -1;
    }
    bool inHitArea(int spotx, int spoty)
    {
        if (x-s<=spotx && spotx<=x+s && y<=spoty && spoty<=y+l)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class shield : public pts
{
private:
    int anglest,anglend,rad,spd,col;
    bool state = false;
public:
    shield()
    {
        anglest=0;anglend=360,rad=20,spd=1;
    }
    shield(int a, int b, int c, int d, int e, int f, int g)
    {
        x = a;y = b; anglest = c; anglend = d; rad = e; col = f; spd = g;
    }
    void update()
    {
        x += spd;
        if (x>1200)
            x = 50;
    }
    void update(int dr)
    {
        if (dr==RIGHT)
            x += spd;
        else
            x -= spd;

        if (x>800)
            x = 100;
        if (x<100)
            x = 800;
    }
    void down()
    {
        y += spd;
        if (y>=450)
            y = 100;
    }
    void draw()
    {
        setcolor(col);
        if (state)
        {
            sector(x,y-rad,anglend,anglest,rad,rad*2-rad/2);
        }
        else
        {
            line(x-rad,y-rad,x+rad,y-rad);
            line(x,y-rad,x,y+rad/2);
            line(x-rad,y-rad/2,x+rad,y-rad/2);
            ellipse(x,y-rad,anglend,anglest,rad,rad*2-rad/2);
        }
    }
};

class gameBox
{
public:
    void create()
    {
        setcolor(WHITE);
        line(50,50,1050,50);
        line(50,50,50,700);
        line(50,700,1050,700);
        line(850,50,850,700);
        line(50,600,850,600);
        line(1050,50,1050,700);
        for (int i=0;i<8;i++)
            line(i*100+150,50,i*100+150,700);
    }
};

class userInterface : public pts
{
protected:
    int inType, cType,l,w;
public:
    void createInterface(int xp, int yp, int xe, int ye, int interfaceType, int colorType)
    {
        cType = colorType;
        inType = interfaceType;
        x = xp;
        y = yp;
        l = xe;
        w = ye;
    }
};

///INTERFACE

class userInterfaceBar : public userInterface
{
public:
    userInterfaceBar(int xp, int yp, int xe, int ye, int colorize)
    {
       createInterface(xp,yp, xe, ye, INTERFACEBAR, colorize);
    }
    void changeLength(int newLen)
    {
        l = newLen;
    }
    void drawBar()
    {
        setfillstyle(1,cType);
        bar(x,y,x+l,y+w);
    }
};

class userInterfaceSkill : public userInterface
{
private:
    bool inCooldown = false;
    int aCode, manaCost;
    double refTime=0.0,remTime;
public:
    userInterfaceSkill(int xp, int yp, int xe, int ye, int colorize, int abilCode, double refreshTime,double frame, int manaNeeded)
    {
       createInterface(xp,yp, xe, ye, INTERFACESKILL, colorize);
       aCode = abilCode;
       refTime = refreshTime*1000;
       manaCost = manaNeeded;
    }
    void useSkill(double frame)
    {
        inCooldown = true;
        remTime = refTime;
    }
    void drawSkill(double frame)
    {
        setcolor(cType);
        if (inCooldown)
        {
            arc(l-((l-x)/2),w-((w-y)/2),90,90-((refTime-remTime)/refTime*360),(l-x)/2);
            remTime -= frame;
            if (remTime<=0)
            {
                inCooldown = false;
            }
        }
        else
        {
            line(x,y,l,y);
            line(x,y,x,w);
            line(l,y,l,w);
            line(x,w,l,w);

            ///DESIGN
            switch (aCode)
            {
                case BLADECLEANSING:setcolor(LIGHTBLUE);line(x,y,l,w);line(l,y,x,w);break;
                case NULLSHIELD:setcolor(WHITE);circle(l-((l-x)/2),w-((w-y)/2),(l-x)/2-8);break;
            }
        }
    }
    int getManaCost()
    {
        return manaCost;
    }
    bool available()
    {
        return !inCooldown;
    }
};

class userInterfaceBuff : public userInterface
{
private:
    bool inEffect = false;
    double timer=0, totalTime=0;
public:
    userInterfaceBuff(int xp, int yp, int xe, int ye, int colorize)
    {
       createInterface(xp,yp, xe, ye, INTERFACEBUFF, colorize);
    }
    void showBuff(double frame)
    {
        if (inEffect)
        {
            setcolor(cType);
            arc(l-((l-x)/2),w-((w-y)/2),90,90+((timer-totalTime)/totalTime*360),(l-x)/2);
            timer -= frame;
            if (timer<=0)
            {
                inEffect = false;
            }
        }
        else
        {
            totalTime = 0;
            setcolor(BLACK);
        }
        line(x,y,l,y);
        line(x,y,x,w);
        line(l,y,l,w);
        line(x,w,l,w);
    }
    bool isInEffect()
    {
        return inEffect;
    }
    void apply(int effectTime)
    {
        timer += effectTime*1000;
        totalTime += effectTime*1000;
        inEffect = true;
    }
};

///VALUES

class PlayerGame
{
private:
    double Health=100, Mana=100, MaxHealth = 100, MaxMana = 100;
public:
    void changeHealth(double modifier)
    {
        Health += modifier;
        if (Health > MaxHealth)
        {
            Health = MaxHealth;
        }
    }
    void changeMana(double modifier)
    {
        Mana += modifier;
        if (Mana > MaxMana)
        {
            Mana = MaxMana;
        }
    }
    int getHealth()
    {
        return Health;
    }
    int getMana()
    {
        return Mana;
    }
};

int main()
{
    int c, effectCode;
    double frame=100;

    blade blade1 = blade(100,100,15,70,MAGENTA,1+rand()%8);
    blade blade2 = blade(200,100,15,70,RED,1+rand()%8);
    blade blade3 = blade(300,100,15,70,RED,1+rand()%8);
    blade blade4 = blade(400,100,15,70,RED,1+rand()%8);
    blade blade5 = blade(500,100,15,70,RED,1+rand()%8);
    blade blade6 = blade(600,100,15,70,RED,1+rand()%8);
    blade blade7 = blade(700,100,15,70,RED,1+rand()%8);
    blade blade8 = blade(800,100,15,70,MAGENTA,1+rand()%8);
    blade bladescore1 = blade(890,80,5,23,CYAN,0);
    blade bladescore2 = blade(1030,80,5,23,CYAN,0);
    shield player = shield(100,660,0,180,40,CYAN,100);
    gameBox box;
    PlayerGame gamer;

    userInterfaceBar OverlayHP = userInterfaceBar(900,150,100,30,RED);
    userInterfaceBar HP = userInterfaceBar(900,150,100,30,GREEN);
    userInterfaceBar OverlayMP = userInterfaceBar(900,200,100,30,WHITE);
    userInterfaceBar MP = userInterfaceBar(900,200,100,30,LIGHTBLUE);
    userInterfaceSkill BladeCleanse = userInterfaceSkill(900,350,950,400,CYAN,BLADECLEANSING,90,frame,100);
    userInterfaceSkill NullifyShield = userInterfaceSkill(960,350,1010,400,MAGENTA,NULLSHIELD,60,frame,70);
    userInterfaceBuff Paralysis = userInterfaceBuff(900,550,950,600,YELLOW);
    userInterfaceBuff Regeneration = userInterfaceBuff(960,550,1010,600,CYAN);
    userInterfaceBuff NullShieldBuff = userInterfaceBuff(900,610,950,660,WHITE);
    userInterfaceBuff Poison = userInterfaceBuff(960,610,1010,660,MAGENTA);

    initwindow(1200,800,"SWORD HAIL");

    while (true)
    {
        delay(frame);
        cleardevice();

        ///Texts
        setcolor(WHITE);
        settextstyle(4,HORIZ_DIR,2);
        outtextxy(900,80,"SCORE");
        settextstyle(7,HORIZ_DIR,2);
        outtextxy(900,100,"XXXXXX");
        settextstyle(1,HORIZ_DIR,1);
        outtextxy(900,330,"SKILLS");
        outtextxy(900,530,"BUFFS");

        ///Game Box
        box.create();

        ///Create Blade
        blade1.restat(player.getX());
        blade2.restat(player.getX());
        blade3.restat(player.getX());
        blade4.restat(player.getX());
        blade5.restat(player.getX());
        blade6.restat(player.getX());
        blade7.restat(player.getX());
        blade8.restat(player.getX());

        blade1.draw();
        blade2.draw();
        blade3.draw();
        blade4.draw();
        blade5.draw();
        blade6.draw();
        blade7.draw();
        blade8.draw();
        bladescore1.draw();
        bladescore2.draw();

        ///User Interface
        HP.changeLength(gamer.getHealth());
        MP.changeLength(gamer.getMana());

        OverlayHP.drawBar();
        HP.drawBar();
        OverlayMP.drawBar();
        MP.drawBar();
        BladeCleanse.drawSkill(frame);
        NullifyShield.drawSkill(frame);
        Paralysis.showBuff(frame);
        Regeneration.showBuff(frame);
        NullShieldBuff.showBuff(frame);
        Poison.showBuff(frame);

        ///Regeneration
        if (Regeneration.isInEffect())
        {
            gamer.changeHealth(0.35);
            gamer.changeMana(0.15);
        }
        if (Poison.isInEffect() && !NullShieldBuff.isInEffect())
        {
            gamer.changeHealth(-0.55);
        }

        ///Collision
        if (blade1.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade1.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade2.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade2.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade3.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade3.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade4.collide()&&!NullShieldBuff.isInEffect())
        {
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade5.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade5.getEffect(player.getX());
           switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade6.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade6.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade7.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade7.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }
        if (blade8.collide()&&!NullShieldBuff.isInEffect())
        {
            effectCode = blade8.getEffect(player.getX());
            switch (effectCode)
            {
                case REDBLADE : gamer.changeHealth(-(5+rand()%21));break;
                case YELLOWBLADE : Paralysis.apply(rand()%5+1);break;
                case GREENBLADE : gamer.changeHealth(5);break;
                case BLUEBLADE : gamer.changeMana(2.5);break;
                case CYANBLADE : Regeneration.apply(5);break;
                case MAGENTABLADE : Poison.apply(5);break;
            }
        }

        player.draw();
        if (gamer.getHealth()<=0)
        {
            cleardevice();
            settextstyle(5,HORIZ_DIR,8);
            outtextxy(300,300,"GAME OVER!");
            settextstyle(1,HORIZ_DIR,5);
            outtextxy(150,370,"Press Any Key to Close Game!");
            getch();
            break;
        }
        if (kbhit() && gamer.getHealth()>0)
        {
            c = getch();
            if (c==224)
            {
                c = getch();
            }
            if (c==113 && !Paralysis.isInEffect() && BladeCleanse.available() && (gamer.getMana() >= BladeCleanse.getManaCost()))
            {
                BladeCleanse.useSkill(frame);
                gamer.changeMana(-BladeCleanse.getManaCost());
                blade1.reset();
                blade2.reset();
                blade3.reset();
                blade4.reset();
                blade5.reset();
                blade6.reset();
                blade7.reset();
                blade8.reset();
            }
            if (c==119 && !Paralysis.isInEffect() && NullifyShield.available() && (gamer.getMana() >= NullifyShield.getManaCost()))
            {
                NullifyShield.useSkill(frame);
                NullShieldBuff.apply(10);
                gamer.changeMana(-NullifyShield.getManaCost());
            }
            if (c==75 && !Paralysis.isInEffect() )
            {
                player.update(LEFT);
            }
            if (c==77 && !Paralysis.isInEffect() )
            {
                player.update(RIGHT);
            }
            if (c==27)
            {
                closegraph();
                break;
            }
            if (c==13)
            {
                settextstyle(5,HORIZ_DIR,8);
                outtextxy(300,300,"GAME PAUSED");
                getch();
            }
        }
    }
    return 0;
}
