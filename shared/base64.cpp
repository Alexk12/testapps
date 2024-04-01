//
// base64.cpp
//
// https:// stackoverflow.com/questions/180947/base64-decode-snippet-in-c
#include "stdafx.h"
#include "base64.h"

// Usage:
//  std::vector<unsigned char> myData;
//  ...
//  std::string encodedData;
//  base64_encode(&myData[0], myData.size(), encodedData);
//  std::vector<unsigned char> decodedData;
//  base64_decode(encodedData, decodedData);

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline bool is_base64(char c) // KAV: char instead of unsigned char
{
    return (isalnum((int)c) || (c == '+') || (c == '/'));
}

// KAV: const unsigned char* instead of BYTE const*
void base64_encode(const unsigned char* _buf, size_t _bufLen, std::string& _ret)
{
    _ret = "";
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    while (_bufLen--) {
        char_array_3[i++] = *(_buf++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            for (i = 0; (i < 4); i++) {
                _ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;
        for (j = 0; (j < i + 1); j++) {
            _ret += base64_chars[char_array_4[j]];
        }
        while ((i++ < 3)) {
            _ret += '=';
        }
    }
}

void base64_encode(const std::vector<unsigned char>& _data, std::string& _ret)
{
    base64_encode(&_data[0], _data.size(), _ret);
}

void base64_decode(const std::string& _encodedString, std::vector<unsigned char>& _ret)
{
    _ret.clear();
    int in_len = (int)_encodedString.size(); // KAV: (int)
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    while (in_len-- && (_encodedString[in_] != '=') && is_base64(_encodedString[in_])) {
        char_array_4[i++] = _encodedString[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++) {
                char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]); // KAV: (unsigned char)
            }
            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
            for (i = 0; (i < 3); i++) {
                _ret.push_back(char_array_3[i]);
            }
            i = 0;
        }
    }
    if (i) {
        for (j = i; j < 4; j++) {
            char_array_4[j] = 0;
        }
        for (j = 0; j < 4; j++) {
            char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]); // KAV: (unsigned char)
        }
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
        for (j = 0; (j < i - 1); j++) {
            _ret.push_back(char_array_3[j]);
        }
    }
}
