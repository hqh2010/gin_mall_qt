#ifndef MODEL_DATA_DATA_DEF_H_
#define MODEL_DATA_DATA_DEF_H_

#include <QString>

// "{\"status\":200,\"data\":{\"user\":{\"id\":1,\"user_name\":\"uos\",\"nickname\":\"雨夜之光\",\"type\":0,\"email\":\"hqh2010_9@163.com\",\"status\":\"active\",\"avatar\":\"http://127.0.0.1:3000/static/imgs/avatar/user1/uos.jpg\",\"create_at\":1678694531},\"token\":\"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6MSwidXNlcm5hbWUiOiJ1b3MiLCJhdXRob3JpdHkiOjAsImV4cCI6MTY3OTcwNzI0NiwiaXNzIjoibWFsbCJ9.ES99qOWQgbg0d51iV_NNVRtvX9qtKptq8Yt6B6PUTFY\"},\"msg\":\"ok\",\"error\":\"\"}
// User 用户模型
typedef struct _user_info
{
    int id;
    QString user_name;
    QString pwd;
    QString email;
    QString nickname;
    QString Status;
    QString avatar;
    QString money;
    QString token;
} UserInfo;

enum user_action_type
{
    REGISTER,
    LOGIN,
    AVATAR,
    MAX_ACTION_TYPE
};

const QString user_action[MAX_ACTION_TYPE] = {
    [REGISTER] = "api/v1/user/register",
    [LOGIN] = "api/v1/user/login",
    [AVATAR] = "api/v1/avatar",
};

#endif
