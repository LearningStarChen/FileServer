#include "../include/json.h"
#include <sstream>

/**************************************************JsonValue数据类型有关*****************************************************/
void JsonValue::cleanup() {
    switch (type_) {
        case JsonType::String:
            delete value_.string_value;
            break;
        case JsonType::Array:
            delete value_.array_value;
            break;
        case JsonType::Object:
            delete value_.object_value;
            break;
        default:
            break;
    }
    type_ = JsonType::Null;
    value_.number_value = 0;
}

void JsonValue::copyFrom(const JsonValue& other) {
    type_ = other.type_;
    
    switch (type_) {
        case JsonType::Null:
            break;
        case JsonType::Boolean:
            value_.boolean_value = other.value_.boolean_value;
            break;
        case JsonType::Number:
            value_.number_value = other.value_.number_value;
            break;
        case JsonType::String:
            value_.string_value = new std::string(*other.value_.string_value);
            break;
        case JsonType::Array:
            value_.array_value = new std::vector<JsonValue>(*other.value_.array_value);
            break;
        case JsonType::Object:
            value_.object_value = new std::unordered_map<std::string, JsonValue>(*other.value_.object_value);
            break;
    }
}

JsonValue::JsonValue() : type_(JsonType::Null) {
    value_.number_value = 0;
}

JsonValue::JsonValue(std::nullptr_t) : type_(JsonType::Null) {
    value_.number_value = 0;
}

JsonValue::JsonValue(bool b) : type_(JsonType::Boolean) {
    value_.boolean_value = b;
}

JsonValue::JsonValue(int n) : type_(JsonType::Number) {
    value_.number_value = int(n);
}

JsonValue::JsonValue(double d) : type_(JsonType::Number) {
    value_.number_value = d;
}

JsonValue::JsonValue(const char* str) : type_(JsonType::String) {
    value_.string_value = new std::string(str);
}

JsonValue::JsonValue(const std::string& str) : type_(JsonType::String) {
    value_.string_value = new std::string(str);
}

JsonValue::JsonValue(const std::vector<JsonValue>& arr) : type_(JsonType::Array) {
    value_.array_value = new std::vector<JsonValue>(arr);
}

JsonValue::JsonValue(const std::unordered_map<std::string, JsonValue>& obj) : type_(JsonType::Object) {
    value_.object_value = new std::unordered_map<std::string, JsonValue>(obj);
}

JsonValue::JsonValue(const JsonValue& other) {
    copyFrom(other);
}

JsonValue& JsonValue::operator=(const JsonValue& other) {
    if (this != &other) {
        cleanup();
        copyFrom(other);
    }
    return *this;
}

JsonValue::JsonValue(JsonValue&& other) : type_(other.type_), value_(other.value_) {
    other.type_ = JsonType::Null;
    other.value_.number_value = 0;
}

JsonValue& JsonValue::operator=(JsonValue&& other) {
    if (this != &other) {
        cleanup();
        type_ = other.type_;
        value_ = other.value_;
        other.type_ = JsonType::Null;
        other.value_.number_value = 0;
    }
    return *this;
}

JsonValue::~JsonValue() {
    cleanup();
}

bool JsonValue::asBoolean() const {
    if (!isBoolean()) {
        LOG_ERROR << "JsonValue: Not a boolean";
        exit(-1);
    }
    return value_.boolean_value;
}

double JsonValue::asNumber() const {
    if (!isNumber()) {
        LOG_ERROR << "JsonValue: Not a number";
        exit(-1);
    }
    return value_.number_value;
}

int JsonValue::asInt() const {
    return int(asNumber());
}

const std::string& JsonValue::asString() const {
    if (!isString()) {
        LOG_ERROR << "JsonValue: Not a string";
        exit(-1);
    }
    return *value_.string_value;
}

const std::vector<JsonValue>& JsonValue::asArray() const {
    if (!isArray()) {
        LOG_ERROR << "JsonValue: Not a array";
        exit(-1);
    }
    return *value_.array_value;
}

const std::unordered_map<std::string, JsonValue>& JsonValue::asObject() const {
    if (!isObject()) {
        LOG_ERROR << "JsonValue: Not a object";
        exit(-1);
    }
    return *value_.object_value;
}

size_t JsonValue::size() const {
    if (isArray()) return asArray().size();
    if (isObject()) return asObject().size();
    LOG_ERROR << "JsonValue: Not a container type";
    exit(-1);
}

bool JsonValue::has(const std::string& key) const {
    if (!isObject()) return false;
    return asObject().find(key) != asObject().end();
}

const JsonValue& JsonValue::operator[](const std::string& key) const {
    if (!isObject()) {
        LOG_ERROR << "JsonValue: Not a object";
        exit(-1);
    }
    auto it = asObject().find(key);
    if (it == asObject().end()) {
        LOG_ERROR << "JsonValue: Key not found:" + key;
        exit(-1);
    }
    return it->second;
}

const JsonValue& JsonValue::operator[](size_t index) const {
    if (!isArray()) {
        LOG_ERROR << "JsonValue: Not a array";
        exit(-1);
    }
    if (index >= asArray().size())  {
        LOG_ERROR << "JsonValue: Index out of bounds";
        exit(-1);
    }
    return asArray()[index];
}

std::string JsonValue::toString(bool pretty, int indent) const {
    std::ostringstream oss;
    
    switch (type_) {
        case JsonType::Null:
            oss << "null";
            break;
            
        case JsonType::Boolean:
            oss << (asBoolean() ? "true" : "false");
            break;
            
        case JsonType::Number: {
            double num = asNumber();
            if (num == int(num)) {
                oss << int(num);
            } else {
                oss << num;
            }
            break;
        }
            
        case JsonType::String:
            oss << "\"" << asString() << "\"";
            break;
            
        case JsonType::Array: {
            oss << "[";
            const auto& arr = asArray();
            for (size_t i = 0; i < arr.size(); ++i) {
                if (i > 0) oss << ",";
                if (pretty) oss << "\n" << std::string(indent + 2, ' ');
                oss << arr[i].toString(pretty, indent + 2);
            }
            if (pretty && !arr.empty()) oss << "\n" << std::string(indent, ' ');
            oss << "]";
            break;
        }
            
        case JsonType::Object: {
            oss << "{";
            const auto& obj = asObject();
            size_t count = 0;
            for (const auto& pair : obj) {
                if (count++ > 0) oss << ",";
                if (pretty) oss << "\n" << std::string(indent + 2, ' ');
                oss << "\"" << pair.first << "\":" << (pretty ? " " : "");
                oss << pair.second.toString(pretty, indent + 2);
            }
            if (pretty && !obj.empty()) oss << "\n" << std::string(indent, ' ');
            oss << "}";
            break;
        }
    }
    
    return oss.str();
}


/**************************************************JsonParser解析器有关*****************************************************/
void JsonParser::skipWhitespace() {
    while (pos_ < length_ && std::isspace(input_[pos_])) {
        pos_++;
    }
}

char JsonParser::currentChar() const {
    return (pos_ < length_) ? input_[pos_] : '\0';
}

char JsonParser::nextChar() {
    if (pos_ < length_) {
        return input_[pos_++];
    }
    return '\0';
}

bool JsonParser::expect(char expected) {
    skipWhitespace();
    if (currentChar() == expected) {
        pos_++;
        return true;
    }
    return false;
}

JsonValue JsonParser::parse(const std::string& jsonString) {
    input_ = jsonString;
    pos_ = 0;
    length_ = jsonString.length();
    
    skipWhitespace();
    JsonValue result = parseValue();
    
    skipWhitespace();
    if (pos_ < length_) {
        LOG_ERROR << "JsonParser: Unexpected characters at end of input";
        exit(-1);
    }
    
    return result;
}

JsonValue JsonParser::parseValue() {
    skipWhitespace();
    char c = currentChar();
    
    switch (c) {
        case 'n': return parseNull();
        case 't':
        case 'f': return parseBoolean();
        case '"': return parseString();
        case '[': return parseArray();
        case '{': return parseObject();
        case '-':
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return parseNumber();
        default: {
            LOG_ERROR << "JsonParser: Unexpected character: " + std::string(1, c);
            exit(-1);
        }
    }
}

JsonValue JsonParser::parseNull() {
    if (input_.compare(pos_, 4, "null") == 0) {
        pos_ += 4;
        return JsonValue(nullptr);
    }
    {
        LOG_ERROR << "JsonParser: Expected 'null'";
        exit(-1);
    }
}

JsonValue JsonParser::parseBoolean() {
    if (input_.compare(pos_, 4, "true") == 0) {
        pos_ += 4;
        return JsonValue(true);
    }
    if (input_.compare(pos_, 5, "false") == 0) {
        pos_ += 5;
        return JsonValue(false);
    }
    {
        LOG_ERROR << "JsonParser: Expected 'true' or 'false'";
        exit(-1);
    }
}

JsonValue JsonParser::parseNumber() {
    size_t start = pos_;
    
    // 处理负数
    if (currentChar() == '-') {
        pos_++;
    }
    
    // 处理整数部分
    while (pos_ < length_ && std::isdigit(currentChar())) {
        pos_++;
    }
    
    // 处理小数部分
    if (currentChar() == '.') {
        pos_++;
        while (pos_ < length_ && std::isdigit(currentChar())) {
            pos_++;
        }
    }
    
    // 处理指数部分
    if (currentChar() == 'e' || currentChar() == 'E') {
        pos_++;
        if (currentChar() == '+' || currentChar() == '-') {
            pos_++;
        }
        while (pos_ < length_ && std::isdigit(currentChar())) {
            pos_++;
        }
    }
    
    std::string numStr = input_.substr(start, pos_ - start);
    try {
        return JsonValue(std::stod(numStr));
    } catch (const std::exception& e) {
        LOG_ERROR << "JsonParser: Invalid number format: " + numStr;
        exit(-1);
    }
}

JsonValue JsonParser::parseString() {
    if (!expect('"')) {
        LOG_ERROR << "JsonParser: Expected '\"'";
        exit(-1);
    }
    
    std::string result;
    while (pos_ < length_ && currentChar() != '"') {
        char c = nextChar();
        
        // 处理转义字符
        if (c == '\\') {
            if (pos_ >= length_) {
                LOG_ERROR << "JsonParser: Unterminated string";
                exit(-1);
            }
            char escapeChar = nextChar();
            switch (escapeChar) {
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                case '/': result += '/'; break;
                case 'b': result += '\b'; break;
                case 'f': result += '\f'; break;
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                case 'u': 
                    // 简化版：跳过Unicode转义
                    result += '?';
                    pos_ += 3; // 跳过4位十六进制
                    break;
                default:
                    result += escapeChar;
                    break;
            }
        } else {
            result += c;
        }
    }
    
    if (!expect('"')) {
        LOG_ERROR << "JsonParser: Unterminated string";
        exit(-1);
    }
    
    return JsonValue(result);
}

JsonValue JsonParser::parseArray() {
    if (!expect('[')) {
        LOG_ERROR << "JsonParser: Expected '['";
        exit(-1);
    }
    
    std::vector<JsonValue> array;
    skipWhitespace();
    
    if (currentChar() != ']') {
        while (true) {
            array.push_back(parseValue());
            skipWhitespace();
            
            if (currentChar() == ']') {
                break;
            }
            if (!expect(',')) {
                LOG_ERROR << "JsonParser: Expected ',' or ']' in array";
                exit(-1);
            }
            skipWhitespace();
        }
    }
    
    if (!expect(']')) {
        LOG_ERROR << "JsonParser: Expected ']'";
        exit(-1);
    }
    
    return JsonValue(array);
}

JsonValue JsonParser::parseObject() {
    if (!expect('{')) {
        LOG_ERROR << "JsonParser: Expected '{'";
        exit(-1);
    }
    
    std::unordered_map<std::string, JsonValue> object;
    skipWhitespace();
    
    if (currentChar() != '}') {
        while (true) {
            // 解析键
            JsonValue keyValue = parseString();
            std::string key = keyValue.asString();
            
            skipWhitespace();
            if (!expect(':')) {
                LOG_ERROR << "JsonParser: Expected ':' after key";
                exit(-1);
            }
            
            // 解析值
            object[key] = parseValue();
            skipWhitespace();
            
            if (currentChar() == '}') {
                break;
            }
            if (!expect(',')) {
                LOG_ERROR << "JsonParser: Expected ',' or '}' in object";
                exit(-1);
            }
            skipWhitespace();
        }
    }
    
    if (!expect('}')) {
        LOG_ERROR << "JsonParser: Expected '}'";
        exit(-1);
    }
    
    return JsonValue(object);
}

/***************************************************启动解析函数对文件进行解析****************************************************** */
JsonData::JsonData(std::string path) {
    // 打开文件
    std::ifstream file(path);
    if (!file.is_open()) {
        LOG_ERROR << "JsonData: openfile error";
        exit(-1);
    }
    // 读取文件的内容之后关闭
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string jsonContent = buffer.str();
    file.close();
    // Json解析器解析读取到的内容
    JsonParser parser; 
    JsonValue json_ = parser.parse(jsonContent); //获取解析后的值
    // 将读取到的值记录下来
    serverPort = json_["serverPort"].asInt();
    threadPoolNum = json_["threadPoolNum"].asInt();
    clientFileStrogePath = json_["clientFileStrogePath"].asString();
    skipListHigh = json_["skipListHigh"].asInt();
    usersPath = json_["usersPath"].asString();
}