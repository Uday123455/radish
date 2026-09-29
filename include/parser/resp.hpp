#pragma once

#include<string>
#include<vector>

enum class RespType{
    BulkString,
    Array
};

struct RespValue{
    RespType type;

    std::string str;
    std::vector<RespValue> elements;
};