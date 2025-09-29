#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "./log.h"



enum JsonType {
    Null,
    Boolean,
    Number,
    String,
    Array,
    Object
};

// JSON值类，是一个数据类型
class JsonValue {
public:
    // 构造函数
    JsonValue();
    JsonValue(std::nullptr_t);
    JsonValue(bool b);
    JsonValue(int n);
    JsonValue(double d);
    JsonValue(const char* str);
    JsonValue(const std::string& str);
    JsonValue(const std::vector<JsonValue>& arr);
    JsonValue(const std::unordered_map<std::string, JsonValue>& obj);
    
    // 拷贝构造函数
    JsonValue(const JsonValue& other);
    // 赋值运算符
    JsonValue& operator=(const JsonValue& other);
    // 移动构造函数（C++11）
    JsonValue(JsonValue&& other);
    // 移动赋值运算符（C++11）
    JsonValue& operator=(JsonValue&& other);
    // 析构函数
    ~JsonValue();
    // 类型检查
    JsonType type() const { return type_; }
    bool isNull() const { return type_ == JsonType::Null; }
    bool isBoolean() const { return type_ == JsonType::Boolean; }
    bool isNumber() const { return type_ == JsonType::Number; }
    bool isString() const { return type_ == JsonType::String; }
    bool isArray() const { return type_ == JsonType::Array; }
    bool isObject() const { return type_ == JsonType::Object; }
    // 值获取（带类型检查）
    bool asBoolean() const;
    double asNumber() const;
    int asInt() const;
    const std::string& asString() const;
    const std::vector<JsonValue>& asArray() const;
    const std::unordered_map<std::string, JsonValue>& asObject() const;
    // 数组操作
    size_t size() const;
    // 对象操作
    bool has(const std::string& key) const;
    const JsonValue& operator[](const std::string& key) const;
    const JsonValue& operator[](size_t index) const;

    // 转换为字符串
    std::string toString(bool pretty = false, int indent = 0) const;
private:
    void cleanup();
    void copyFrom(const JsonValue& other);
private:
    // json值类型枚举
    JsonType type_;
    // json的value值
    union ValueUnion {
        bool boolean_value;
        double number_value;
        std::string* string_value;
        std::vector<JsonValue>* array_value;
        std::unordered_map<std::string, JsonValue>* object_value;
        
        ValueUnion() : number_value(0) {}
        ValueUnion(bool b) : boolean_value(b) {}
        ValueUnion(double d) : number_value(d) {}
    } value_;
};

class JsonParser {
public:
    JsonValue parse(const std::string& jsonString);
private:
    std::string input_;
    size_t pos_;
    size_t length_;

    // 工具函数
    void skipWhitespace();  // 跳过空格
    char currentChar() const;  // 获取当前一个字符
    char nextChar();           // 获取到下一个字符，当前处理位置移动一位
    bool expect(char expected);//判断是否存在expected字符
    
    // 解析函数，对应各个类型
    JsonValue parseValue();
    JsonValue parseNull();
    JsonValue parseBoolean();
    JsonValue parseNumber();
    JsonValue parseString();
    JsonValue parseArray();
    JsonValue parseObject();
};

//前两个是工具类，这个是数据类，对解析的数据进行缓存
class JsonData {
public:
    JsonData(std::string path);
public:
    
    int serverPort;          // 服务器绑定的端口
    int threadPoolNum;       // 线程池线程数量
    std::string clientFileStrogePath; // 客户端的所有文件存储地址
    int skipListHigh;        // 调表高度
    std::string usersPath;   // 用户信息存储地址

};