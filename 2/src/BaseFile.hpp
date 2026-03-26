#pragma once
#include <iostream>
#include <cstdio>
class Ifile
{   
public:
    virtual ~Ifile(){}
    virtual size_t read(void *buf, size_t maxBytes) = 0;
    virtual size_t write(const void *buf, size_t nBytes) = 0;
};

class BaseFile : public Ifile
{
protected:
    FILE *file;
    char mode[4];

public:
    BaseFile();
    BaseFile(const char *filename, const char *mode);
    BaseFile(FILE *file);
    virtual ~BaseFile();

    bool isOpen() const;
    bool canRead() const;
    bool canWrite() const;
    size_t writeRaw(const void *buf, size_t nBytes);
    size_t readRaw(void *buf, size_t maxBytes);
    size_t read(void *buf, size_t maxBytes);
    size_t write(const void *buf, size_t nBytes);
    void close();
};


class RleFile : public BaseFile
{
private:
    unsigned char remainingCount = 0;
    unsigned char remainingValue = 0;
    bool hasRemainingData = false;
    unsigned char pendingCount = 0;
    unsigned char pendingValue = 0;
    bool hasPendingData = false;                
public:
    RleFile();
    RleFile(const char *filename, const char *modeStr);
    RleFile(FILE *newFile);
    ~RleFile();

    
    size_t read(void *buf, size_t maxBytes);
    size_t write(const void *buf, size_t nBytes);
    void flush();
};


class RleFile2 : public Ifile
{
private:
    Ifile* m_file;
    unsigned char remainingCount = 0;
    unsigned char remainingValue = 0;
    bool hasRemainingData = false;
    unsigned char pendingCount = 0;
    unsigned char pendingValue = 0;
    bool hasPendingData = false;
public:
    RleFile2(Ifile* file);
    ~RleFile2();
    size_t read(void* buf, size_t maxBytes);
    size_t write(const void* buf, size_t nBytes);
};


void writeInt(Ifile &file, int n);
