#pragma once
#include <string>
#include <windows.h>

inline std::wstring Utf8ToWide(const char* utf8)
{
    if (!utf8 || !*utf8)
        return {};

    int length = MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        nullptr,
        0
    );

    if (length <= 0)
        return {};

    std::wstring result(length, 0);
    MultiByteToWideChar(
        CP_UTF8,
        0,
        utf8,
        -1,
        &result[0],
        length
    );

    result.pop_back(); // 去掉结尾的 \0
    return result;
}