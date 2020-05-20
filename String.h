#pragma once
#ifndef _STRING_C_
#define _STRING_C_
//#include <string.h>
#include <malloc.h>
#include <stdio.h>
class String
{
public:
	String();
	String(const String&);
	String(char);
	String(const char*);
	int replaceAll(char, char);
	String subString(int, int);
	const char* getCstr();
	bool isEmpty();
	bool equals(const String&);
	bool equals(const char*);
	String& operator+(char);
	String& operator+(char*);
	String& operator+(String&);
	bool operator==(const String&);
	String operator=(char*);
	~String();
protected:
	void memmCpy(char*, int, const char*, int);
	int strLen(const char*);
	void alloc(size_t size);
	void destroy();
private:
	char* buff;
	int length;
};

#endif // !_STRING_C_



