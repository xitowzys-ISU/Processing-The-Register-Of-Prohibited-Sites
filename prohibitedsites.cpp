#include "prohibitedsites.h"

using namespace std;

ProhibitedSites::ProhibitedSites(){}

ProhibitedSites::~ProhibitedSites()
{
    registryFile.close();

    delete[] siteData;
    siteData = nullptr;
}

bool ProhibitedSites::setRegistry(const string filePath)
{
    registryFile.open(filePath);

    if(!registryFile.is_open())
    {
        cout << "--------------------------------------------" << endl;
        cout << "Ошибка открытие реестра" << endl;
        cout << "--------------------------------------------" << endl;
        return false;
    }
    else
    {
        cout << "--------------------------------------------" << endl;
        cout << "Реестр загружен" << endl;
        cout << "--------------------------------------------" << endl;
        return true;
    }
}

void ProhibitedSites::setSite(const string url)
{
    regex regular("(http|https)://([^/ :]+):?([^/ ]*)(/?[^ #?]*)\\x3f?([^ #]*)#?([^ ]*)");

    cmatch what;

    if (regex_match(url.c_str(), what, regular))
    {
        this->siteData[0] = url;

        this->siteData[1] = string(what[2].first, what[2].second);

        QHostInfo info = QHostInfo::fromName(QString::fromStdString(siteData[1]));
        QHostAddress address = info.addresses().first();

        this->siteData[2] = address.toString().toStdString();

        cout << "--------------------------------------------" << endl;
        cout << "URL: " << this->siteData[0] << endl;
        cout << "Домен: " << this->siteData[1] << endl;
        cout << "IP адрес: " << this->siteData[2] << endl;
        cout << "--------------------------------------------" << endl;
    }
    else
    {
        cout << "Некорректная ссылка" << endl;
    }

}

bool ProhibitedSites::isBlocked()
{
    // Положение указателя в файле
    unsigned int pPosition = 0;
    // Размер буфера
    unsigned int size = registryFile.seekg(0, ios::end).tellg();
    // Перемещение указателя в начало файла
    registryFile.seekg(0);
    // Буфер с данными файла
    char* buf = new char[size + 1];
    // Запись файла в буфер
    registryFile.read(buf, size);
    // Терминирующий ноль в конец буфера
    buf[size] = '\0';

    // Совпадение строки
    bool isBlock = false;

    // Размер вектора
    unsigned int vectorSize;

    vector<vector<char>> registryData;
    registryData.push_back(vector<char>());
    registryData.push_back(vector<char>());
    registryData.push_back(vector<char>());
    registryData.push_back(vector<char>());

    while(true)
    {

        // Считывает строку
        for (unsigned short i = 0; i < 4; ++i)
        {
            for (unsigned int j = 0; (buf[pPosition] != ';' && buf[pPosition] != '\n'); j++)
            {
                 registryData[i].push_back(buf[pPosition]);
                 pPosition++;
            }
            pPosition++;
        }

        #ifdef DEBUG

        cout << "--------------------------------------------" << endl;
        for (int i = 0; i < 4; ++i)
        {
            vectorSize = registryData[i].size();

            for (int j = 0; j < vectorSize; j++) {
                std::cout << registryData[i][j];
            }
            cout << endl;
        }
        cout << "--------------------------------------------" << endl;

        #endif

        // Проверка URL, домена и IP
        for (unsigned short i = 1; i < 4; i++)
        {
            vectorSize = registryData[i].size();

            for (unsigned int j = 0; j < vectorSize; j++) {
                if (registryData[i][j] != this->siteData[i - 1][j])
                {
                    isBlock = false;
                    break;
                }
                else
                {
                    isBlock = true;
                }
            }

            if (isBlock == true)
            {
                return true;
            }
        }

        // Очистка векторов
        for (unsigned short i = 0; i < 4; ++i)
        {
            registryData[i].clear();
        }

        // Выход из цикла если не нашел сайт
        if (pPosition == size)
        {
            return false;
        }
    }
}
