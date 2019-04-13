
#include "globalvariable.h"



bool GlobalVariable::IsLogin()
{
    return GlobalVariable::global_Islogin;
}

User& GlobalVariable::get_global_User()
{
    return global_User;
}

void GlobalVariable::saveUserTolocal()
{
    GlobalVariable::global_User;

}



GlobalVariable::GlobalVariable()
{
}



GlobalVariable::~GlobalVariable()
{

}

PlayMusicDetialController* GlobalVariable::global_PlayMusicDetialCtrl = nullptr;
QJsonObject GlobalVariable::settingObj = QJsonObject();
User GlobalVariable::global_User = User();
bool GlobalVariable::global_Islogin = false;
QString GlobalVariable::global_user_absolute_file = "";
