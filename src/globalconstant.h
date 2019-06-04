#ifndef GLOBALCONSTANT_H
#define GLOBALCONSTANT_H

#include <QString>


const QString CONST_GLOBAL_STRING_LOCAL_DIR = "local";
const QString CONST_GLOBAL_STRING_DOWNLOAD_DIR = "download";
const QString CONST_GLOBAL_STRING_USER_DIR = "user";
const QString CONST_GLOBAL_STRING_SETTING_DIR = "setting";
const QString CONST_GLOBAL_STRING_LOCAL_USER_FILE_NAME = "localUser.json";
const QString CONST_GLOBAL_STRING_SETTING_FILE_NAME = "setting.json";
const QString CONST_GLOBAL_STRING_SHEETIMAGES_DIR = "sheetImages";


const int CONST_GLOBAL_INT_MUSIClISTITEMVIEW_HIEGHT = 40;

const QString CONST_ERROR_STRING_SHUJUCUOWU = "数据错误";


const QString CONST_STRING_RET_CODE = "ret_code";
const QString CONST_STRING_DATA = "data";

//返回错误
const int CONST_INT_RET_CODE_ERROR =  -1;

//返回成功
const int CONST_INT_RET_CODE_SUCCESS = 0;


/*
 *网络返回数据结构
 * { "ret_code":0,
 *  "data":[]
 *
 *
 * }
 */









class GlobalConstant
{
public:
    GlobalConstant();
};

#endif // GLOBALCONSTANT_H
