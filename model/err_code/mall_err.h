#ifndef MODEL_ERR_CODE_ERR_CODE_H_
#define MODEL_ERR_CODE_ERR_CODE_H_

#include <QString>

enum err_code_type
{
    BASE = 4000,
    FAIL,
    SUCCESS,
    MAX_ERR_CODE_TYPE
} ErrType;

const QString err_msg[MAX_ERR_CODE_TYPE] =
    {
        "失败",
        "成功"，
        "用户名不存在"};

QString getMsg(ErrType e)
{
    if (e < MAX_ERR_CODE_TYPE && e > BASE)
    {
        return err_msg[e - BASE - 1];
    }
    return "";
};

#endif