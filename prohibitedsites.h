#ifndef PROHIBITEDSITES_H
#define PROHIBITEDSITES_H

//#define DEBUG
#include <regex>
#include <string>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <QHostInfo>

class ProhibitedSites
{
private:
    // siteData[0] → URL; siteData[1] → domain; siteData[2] → ip
    std::string *siteData = new std::string[3];
    std::ifstream registryFile;

public:
    ProhibitedSites();
    ~ProhibitedSites();

    bool setRegistry(const std::string filePath);
    void setSite(const std::string url);

    bool isBlocked();
};

// PROHIBITEDSITES_H
#endif
