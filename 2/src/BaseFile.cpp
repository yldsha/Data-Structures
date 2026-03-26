#include <iostream>
#include <cstdio>
#include "BaseFile.hpp"

BaseFile::BaseFile()
{
    file = nullptr;
    mode[0] = '\0';
    std::cout << "Вызван Base конструктор по умолчанию" << std::endl;
}
void BaseFile::close() {
    if (file != nullptr) {
        fclose(file);
        file = nullptr;
    }
}
BaseFile::BaseFile(const char *filename, const char *modeStr)
{
    if (modeStr)
    {
        strncpy(mode, modeStr, 3);
        mode[3] = '\0';
    }
    else
    {
        mode[0] = '\0';
    }
    file = fopen(filename, mode);
    if (file == nullptr)
    {
        throw ::std::runtime_error("Не удалось открыть файл");
    }
    std::cout << "Вызван Base конструктор, принимающий путь к файлу и флаг" << std::endl;
}

BaseFile::BaseFile(FILE *newFile)
{
    file = newFile;
    mode[0] = '\0';
    std::cout << "Вызван Base конструктор, принимающий указатель типа File" << std::endl;
}

BaseFile::~BaseFile()
{
    if (file != nullptr)
    {
        fclose(file);
    }
    std::cout << "Вызван Base деструктор" << std::endl;
}

bool BaseFile::isOpen() const
{
    if (file != nullptr)
    {
        return true;
    }
    return false;
}

bool BaseFile::canRead() const
{
    if (!isOpen())
    {
        return false;
    }
    if (strchr(mode, 'r') != nullptr)
    {
        return true;
    }
    if (strchr(mode, '+') != nullptr)
    {
        return true;
    }
    return false;
}

bool BaseFile::canWrite() const
{
    if (!isOpen())
    {
        return false;
    }
    if (strchr(mode, 'w') != nullptr)
    {
        return true;
    }
    if (strchr(mode, 'a') != nullptr)
    {
        return true;
    }
    if (strchr(mode, '+') != nullptr)
    {
        return true;
    }
    return false;
}

size_t BaseFile::writeRaw(const void *buf, size_t nBytes)
{
    if (!isOpen() || !canWrite())
    {
        return 0;
    }
    size_t bytesWritten = fwrite(buf, 1, nBytes, file);
    return bytesWritten;
}
size_t BaseFile::readRaw(void *buf, size_t maxBytes)
{
    if (!isOpen() || !canRead())
    {
        return 0;
    }
    size_t bytesRead = fread(buf, 1, maxBytes, file);
    return bytesRead;
}
size_t BaseFile::read(void *buf, size_t maxBytes)
{
    return readRaw(buf, maxBytes);
}
size_t BaseFile::write(const void *buf, size_t nBytes)
{
    return writeRaw(buf, nBytes);
}
void writeInt(Ifile &file, int n)
{
    if (n == 0) {
        char zero = '0';
        file.write(&zero, 1);
        return;
    }
    if (n < 0)
    {
        char minus = '-';
        file.write(&minus, 1);
        n = -n;
    }
    int d = 1;
    int temp = n;
    while (temp > 0)
    {
        d *= 10;
        temp /= 10;
    }
    d /= 10;
    
    while (n > 0) 
    {
        char s = '0' + (n / d);
        file.write(&s, 1);
            n = n % d;
            d /= 10;
    }
}
RleFile::RleFile() : BaseFile()
{
    remainingCount = 0;
    remainingValue = 0;
    hasRemainingData = false;
    pendingCount = 0;
    pendingValue = 0;
    hasPendingData = false;
    std::cout << "Вызван RLE конструктор по умолчанию" << std::endl;
}
RleFile::RleFile(const char *filename, const char *modeStr)
    : BaseFile(filename, modeStr)
{
    remainingCount = 0;
    remainingValue = 0;
    hasRemainingData = false;
    pendingCount = 0;
    pendingValue = 0;
    hasPendingData = false;
    std::cout << "Вызван RLE конструктор, принимающий путь к файлу и флаг" << std::endl;
}

RleFile::RleFile(FILE *newFile) : BaseFile(newFile)
{
    remainingCount = 0;
    remainingValue = 0;
    hasRemainingData = false;
    pendingCount = 0;
    pendingValue = 0;
    hasPendingData = false;
    std::cout << "Вызван RLE конструктор, принимающий указатель типа File" << std::endl;
}



size_t RleFile::read(void *buf, size_t maxBytes)
{
    if (!isOpen() || !canRead())
    {
        return 0;
    }
    unsigned char *output = static_cast<unsigned char *>(buf);
    size_t totalRead = 0;

    if (hasRemainingData) {
        size_t toRead = remainingCount;
        if (toRead > maxBytes)
        {
            toRead = maxBytes;
        }

        for (size_t i = 0; i < toRead; i++)
        {
            output[totalRead + i] = remainingValue;
        }

        remainingCount -= toRead;
        totalRead += toRead;

        if (remainingCount == 0)
        {
            hasRemainingData = false;
        }
        else
        {
            return totalRead;
        }
    }

    while (totalRead < maxBytes)
    {
        unsigned char count;
        size_t bytesRead = BaseFile::read(&count, 1);

        if (bytesRead < 1)
        {
            break;
        }

        unsigned char value;
        bytesRead = BaseFile::read(&value, 1);
        if (bytesRead < 1)
        {
            break;
        }

        size_t toWrite = count;
        if (totalRead + toWrite > maxBytes)
        {
            toWrite = maxBytes - totalRead;

            remainingCount = count - toWrite;
            remainingValue = value;
            hasRemainingData = true;
        }

        for (size_t i = 0; i < toWrite; i++)
        {
            output[totalRead + i] = value;
        }
        totalRead += toWrite;
    }
    return totalRead;
}

size_t RleFile::write(const void *buf, size_t nBytes)
{
    if (!isOpen() || !canWrite())
    {
        return 0;
    }

    const unsigned char *data = static_cast<const unsigned char *>(buf);
    size_t totalWritten = 0;
    
    if (hasPendingData) {
        if (nBytes > 0 && data[0] == pendingValue) {
            size_t sameCount = 0;
            while (sameCount < nBytes && data[sameCount] == pendingValue && pendingCount + sameCount < 255) {
                sameCount++;
            }
            
            pendingCount += sameCount;
            totalWritten = sameCount;
            
            if (pendingCount == 255) {
                BaseFile::write(&pendingCount, 1);
                BaseFile::write(&pendingValue, 1);
                hasPendingData = false;
                pendingCount = 0;
                pendingValue = 0;
            }
        } else {
            BaseFile::write(&pendingCount, 1);
            BaseFile::write(&pendingValue, 1);
            hasPendingData = false;
            pendingCount = 0;
            pendingValue = 0;
        }
    }

    while (totalWritten < nBytes)
    {
        unsigned char currentByte = data[totalWritten];
        unsigned char count = 1;

        while (totalWritten + count < nBytes &&
               data[totalWritten + count] == currentByte &&
               count < 255)
        {
            count++;
        }
        BaseFile::write(&count, 1);
        BaseFile::write(&currentByte, 1);
        totalWritten += count;
    }
    
    hasPendingData = false;
    pendingCount = 0;
    pendingValue = 0;
    
    return totalWritten;
}
RleFile::~RleFile() {
    std::cout << "Вызван RLE деструктор" << std::endl;
    std::cout << "  hasPendingData = " << hasPendingData << std::endl;
    if (hasPendingData) {
        std::cout << "  pendingCount = " << (int)pendingCount << ", pendingValue = " << (int)pendingValue << std::endl;
    }
    
    if (hasPendingData && file != nullptr) {
        size_t written1 = fwrite(&pendingCount, 1, 1, file);
        size_t written2 = fwrite(&pendingValue, 1, 1, file);
        hasPendingData = false;
    }
}
void RleFile::flush() {
    if (hasPendingData && isOpen() && canWrite()) {
        BaseFile::write(&pendingCount, 1);
        BaseFile::write(&pendingValue, 1);
        hasPendingData = false;
        pendingCount = 0;
        pendingValue = 0;
    }
}
RleFile2::RleFile2(Ifile* file): m_file(file) {
    remainingCount = 0;
    remainingValue = 0;
    hasRemainingData = false;
    pendingCount = 0;
    pendingValue = 0;
    hasPendingData = false;
    std::cout << "Вызван RLE2 конструктор" << std::endl;
}

size_t RleFile2::read(void *buf, size_t maxBytes) {
    if (!m_file) return 0;  

    unsigned char *output = static_cast<unsigned char *>(buf);
    size_t totalRead = 0;

    if (hasRemainingData) {
        size_t toRead = remainingCount;
        if (toRead > maxBytes) toRead = maxBytes;

        for (size_t i = 0; i < toRead; i++) {
            output[totalRead + i] = remainingValue;
        }

        remainingCount -= toRead;
        totalRead += toRead;

        if (remainingCount == 0) {
            hasRemainingData = false;
        } else {
            return totalRead;
        }
    }

    while (totalRead < maxBytes) {
        unsigned char count;
        size_t bytesRead = m_file->read(&count, 1);  

        if (bytesRead < 1) break;

        unsigned char value;
        bytesRead = m_file->read(&value, 1); 

        if (bytesRead < 1) break;

        size_t toWrite = count;
        if (totalRead + toWrite > maxBytes) {
            toWrite = maxBytes - totalRead;
            remainingCount = count - toWrite;
            remainingValue = value;
            hasRemainingData = true;
        }

        for (size_t i = 0; i < toWrite; i++) {
            output[totalRead + i] = value;
        }
        totalRead += toWrite;
    }

    return totalRead;
}

size_t RleFile2::write(const void *buf, size_t nBytes) {
    if (!m_file) return 0;  

    const unsigned char *data = static_cast<const unsigned char *>(buf);
    size_t totalWritten = 0;

    if (hasPendingData) {
        if (nBytes > 0 && data[0] == pendingValue) {
            size_t canAdd = nBytes;
            if (pendingCount + canAdd > 255) {
                canAdd = 255 - pendingCount;
            }

            pendingCount += canAdd;
            totalWritten = canAdd;

            if (pendingCount == 255) {
                m_file->write(&pendingCount, 1);   
                m_file->write(&pendingValue, 1);   
                hasPendingData = false;
                pendingCount = 0;
                pendingValue = 0;
            }
        } else {
            m_file->write(&pendingCount, 1);   
            m_file->write(&pendingValue, 1);   
            hasPendingData = false;
            pendingCount = 0;
            pendingValue = 0;
        }
    }
    while (totalWritten < nBytes) {
        unsigned char currentByte = data[totalWritten];
        unsigned char count = 1;

        while (totalWritten + count < nBytes &&
               data[totalWritten + count] == currentByte &&
               count < 255) {
            count++;
        }

        m_file->write(&count, 1);       
        m_file->write(&currentByte, 1);   
        totalWritten += count;
    }
    
    hasPendingData = false;
    pendingCount = 0;
    pendingValue = 0;
    
    return totalWritten;
}

RleFile2::~RleFile2() {
    if (hasPendingData && m_file) {  
        m_file->write(&pendingCount, 1);
        m_file->write(&pendingValue, 1);
        hasPendingData = false;
    }
    std::cout<<"Вызван RLE2 деструктор"<<std::endl;
    delete m_file;
}


