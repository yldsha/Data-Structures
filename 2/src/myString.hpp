#pragma once

class myString
{
private:
    char* data;
    int length;
public:
    myString();
    myString(const char* str);
    myString(const myString& other);

    ~myString();

    char get(int i) const;
    void set(int i, char c);
    void setNewString(const char *str);
    void print();
    void readLine();

    int getLength(const char* str);

    void copyString(char* dest, const char* src);

};