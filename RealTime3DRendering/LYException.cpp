#include "LYException.h"
#include <sstream>
#include <tchar.h>

LYException::LYException(int line, const char* file) noexcept
    : line(line), file(file)
{
}

const char* LYException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << GetOriginString();

    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* LYException::GetType() const noexcept
{
    return "LYException";
}

int LYException::GetLine() const noexcept
{
    return line;
}

const std::string& LYException::GetFile() const noexcept
{
    return file;
}

std::string LYException::GetOriginString() const noexcept
{
    std::ostringstream oss;
    oss << "[File] " << file << std::endl
        << "[Line] " << line;

    return oss.str();
}