#include <iostream>
#include <graphics.h>

#define MOBIL 1
#define TRUK 2

using namespace std;

class VehicleCounter
{
private:
    unsigned int totalMotor, totalMobil, totalTruk;
    double estimateWeight;
public:
    VehicleCounter()
    {
        totalMotor = 0;
        totalMobil = 0;
        totalTruk = 0;
        estimateWeight = 0;
    }
    void vehicleWeight(int type, double weight)
    {
        estimateWeight += weight;
        if (type==MOBIL)
            totalMobil++;
        if (type==TRUK)
            totalTruk++;
    }
    void motorWeight(double weight)
    {
        totalMotor++;
    }
    void display()
    {
        cout << "Number of Motorcycles : " << totalMotor << endl;
        cout << "Number of Cars : " << totalMobil << endl;
        cout << "Number of Trucks : " << totalTruk << endl;
        cout << "Total Weight Estimation : " << estimateWeight << " tons" << endl;
    }
};

int main()
{
    VehicleCounter DataKemenhub;
    int c;

    initwindow(100,100);

    cout << "Welcome to Vehicle Counter!" << endl;
    cout << "Press 0 to count motorcycle" << endl;
    cout << "Press 1 to count cars" << endl;
    cout << "Press 2-6 to count trucks" << endl << endl;

    while(true)
    {
        if (kbhit())
        {
            c = getch();
            if (c==48)
            {
                DataKemenhub.motorWeight(0.);
            }
            if (c==49)
            {
                DataKemenhub.vehicleWeight(MOBIL,1.);
            }
            if (c>=50 && c<=54)
            {
                DataKemenhub.vehicleWeight(TRUK,(double) c-48);
            }
            if (c==27)
            {
                DataKemenhub.display();
                break;
            }
        }
    }
    return 0;
}
