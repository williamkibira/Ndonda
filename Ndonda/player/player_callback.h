#ifndef PLAYER_CALLBACK_INTERFACE_H
#define PLAYER_CALLBACK_INTERFACE_H
#include <string>
class PlayerCBInterface{
public:
virtual void onPlayerTouchedOtherPolyGon(std::string,std::string,int);
virtual void onPlayerDetachedFromOtherPolyGon(std::string, int);
};

#endif // PLAYER_CALLBACK_INTERFACE_H