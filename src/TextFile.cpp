/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "TextFile.h"
#include "ErrorCategory.h"
#include "Utilities.h"

namespace Ishiko
{
namespace FileSystem
{

void TextFile::create(const std::string& path, Error& error)
{
    // TODO: use lower level file functions to make this more robust
    if (!Exists(path))
    {
        m_file.open(path, std::ios::out);
        FailIfCreateFileError(error, m_file, path, __FILE__, __LINE__);
        m_file.close();
        m_file.open(path);
        FailIfCreateFileError(error, m_file, path, __FILE__, __LINE__);
    }
    else
    {
        Fail(error, ErrorCategory::eAlreadyExists, std::string("path \'") + path + "\' already exists", __FILE__,
            __LINE__);
    }
}

void TextFile::open(const std::string& path, Error& error)
{
    m_file.open(path);
    FailIfOpenFileError(error, m_file, path, __FILE__, __LINE__);
}

std::string TextFile::readLine(Error& error)
{
    std::string result;
    
    std::getline(m_file, result);
    if (m_file.fail() && m_file.eof())
    {
        Fail(error, ErrorCategory::eEndOfFile);
    }

    // TODO: handle other errors

    return result;
}

std::vector<std::string> TextFile::readAllLines()
{
    std::vector<std::string> result;

    while (true)
    {
        Error error;
        std::string line = readLine(error);
        if (error)
        {
            // TODO: handle errors other than EOF
            break;
        }
        result.push_back(line);
    }

    return result;
}

void TextFile::write(const char* str)
{
    // TODO: error handling
    m_file << str;
}

void TextFile::writeLine(const char* str)
{
    // TODO: error handling
    m_file << str << std::endl;
}

}
}
