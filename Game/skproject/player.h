#ifndef __PLAYER_H__	
#define __PLAYER_H__
#include <string>

class Player
{
private:
    int fd;
    std::string name;
public:
    Player(int fd, std::string name);
    std::string getName();
    int getFd();
    int board[10][10];
    bool readyToPlay;

};


#endif