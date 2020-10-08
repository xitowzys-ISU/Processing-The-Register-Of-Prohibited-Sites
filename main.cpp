#include <iostream>
#include <QHostInfo>
#include <QCoreApplication>
#include <prohibitedsites.h>


int main(int argc, char *argv[])
{
    using namespace std;

    QCoreApplication a(argc, argv);

    ProhibitedSites prohibitedsites;

    prohibitedsites.setRegistry("register.txt");
    prohibitedsites.setSite("http://rutracker.ru");

    if(prohibitedsites.isBlocked())
    {
        cout << "--------------------------------------------" << endl;
        cout << "Сайт заблокирован" << endl;
        cout << "--------------------------------------------" << endl;
    }
    else
    {
       cout << "--------------------------------------------" << endl;
       cout << "Сайт в открытом доступе" << endl;
       cout << "--------------------------------------------" << endl;
    }

    return 0;
}
