#pragma once 

// 前后端消息交互格式采用json格式，所以可以采用这个模式来解析
/*客户端来的消息格式为"
{
    "name" : "chn",
    "passwd" : "123456",
    "type" : 0(1,2),//0表示文件类型，1表示消息类型，2表示查看所有文件，3表示登录验证，4表示用户注册
    "fileName" : "1.zip",
    "message" : "Hello world"
}"*/

/*服务器发送给客户端的消息格式为"
{
    "type" : 0(1,2), //0表示文件类型，1表示消息类型
}"*/

#include "json.h"
#include "../tool/tool.h"

class ProtocolFromClient {
public:
    ProtocolFromClient(std::string mess) {
        JsonParser parser; 
        JsonValue json_ = parser.parse(mess); //获取解析后的值
        name = json_["name"].asString();
        type = json_["type"].asInt();
        if (type == 0) {
            fileName = json_["fileName"].asString();
        } else if (type == 1) {
            message = json_["message"].asString();
        } else if (type == 2) {

        } else if (type == 3 || type == 4) { //登录或者注册
            passwd = json_["passwd"].asString();
        } 
    }
public:
    std::string name;
    std::string passwd;
    int type;
    std::string fileName;
    std::string message;   //客户端的类型是消息，这个是消息的内容
};

class ProtocolFromServer {
public:
    ProtocolFromServer(int type, std::string toclientmess = "", off_t filesize = 0, std::string fileContent = "") {
        std::unordered_map<std::string, JsonValue> mess;
        if (type == 0) { //表示收到文件类型，回复文件
            mess["fileSize"] = JsonValue(std::to_string(filesize));
            mess["fileContent"] = JsonValue(fileContent);
        } else if (type == 1) { // 表示收到消息类型，回复消息
            mess["message"] = JsonValue(toclientmess);
        }
        JsonValue json_(mess);
        message = json_.toString();
    }
public:
    std::string message;
};