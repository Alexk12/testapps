//
// base65.h
//
#pragma once
#include <string>
#include <vector>

void base64_encode(const unsigned char* _buf, size_t _bufLen, std::string& _ret);
void base64_encode(const std::vector<unsigned char>& _data, std::string& _ret);
void base64_decode(const std::string& _encodedString, std::vector<unsigned char>& _ret);
