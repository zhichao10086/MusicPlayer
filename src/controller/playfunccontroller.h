#ifndef PLAYFUNCCONTROLLER_H
#define PLAYFUNCCONTROLLER_H


#include <playfuncmodel.h>
#include <playfuncview.h>

class PlayFuncModel;
class PlayFuncView;

class PlayFuncController
{
public:


    PlayFuncController();


    PlayFuncModel* _playFuncModel;
    PlayFuncView*  _playFuncView;


    void init();


};

#endif // PLAYFUNCCONTROLLER_H
