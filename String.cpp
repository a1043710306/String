#include "String.h"

String::String()
{
	this->length = 0;
	this->buff = (char*)malloc(sizeof(char));
}
String::String(const String& object)
{
	this->length = object.length;
	this->buff = (char*)malloc(sizeof(char) * this->length + 1);
	memmCpy(this->buff, this->length, object.buff, object.length);
	this->buff[this->length] = '\0';
}
String::String(char ch)
{
	this->length = 1;
	this->buff = (char*)malloc(sizeof(char) * this->length + 1);
	(this->buff)[0] = ch;
	(this->buff)[1] = 0;
}
String::String(const char* str)
{
	this->length = this->strLen(str);
	this->buff = (char*)malloc(sizeof(char) * this->length + 1);
	this->memmCpy(this->buff, this->length, str, this->length);
	this->buff[this->length] = '\0';
}
int String::replaceAll(char ch, char c)
{
	int count = 0;
	for (int i = 0; i < this->length; i++)
	{
		if (this->buff[i] == ch)
		{
			this->buff[i] = c;
			count++;
		}
	}
	return count;
}
String String::subString(int startIndex, int endIndex)
{
	//不合法 抛空指针 
	if (startIndex<0 || startIndex>length ||
		endIndex<0 || endIndex>length ||
		endIndex < startIndex)
	{
		return *(String*)0;
	}
	String desc;
	desc.length = endIndex - startIndex;
	desc.alloc(endIndex - startIndex);
	desc.memmCpy(desc.buff, endIndex - startIndex, (const char*)(this->buff + startIndex), endIndex - startIndex);
	desc.buff[desc.length] = '\0';
	return desc;
}
const char* String::getCstr()
{
	return this->buff;
}
bool String::isEmpty()
{
	if (length == 0)
		return true;
	return false;
}
bool String::equals(const String& desc)
{
	if (this->length != desc.length)
		return false;
	for (int i = 0; i < desc.length; i++)
	{
		if (this->buff[i] != desc.buff[i])
			return false;
	}
	return true;
}
bool String::equals(const char* str)
{
	int lenth = String::strLen(str);
	if (this->length != lenth)
		return false;
	for (int i = 0; i < this->length; i++)
	{
		if (this->buff[i] != str[i])
			return false;
	}
	return true;
}
String& String::operator+(char ch)
{
	this->alloc(this->length + 1);
	this->memmCpy(buff + length, 1, &ch, 1);
	return *this;
}
String& String::operator+(char* cstr)
{
	int cStrLength = strLen(cstr);
	this->alloc(this->length + cStrLength);
	this->memmCpy(buff + length, cStrLength, cstr, cStrLength);
	return *this;
}
String& String::operator+(String& obj)
{
	int tempLength = obj.length + this->length + 1;
	char* tempBuffer = (char*)malloc(sizeof(char) * tempLength);
	memmCpy(tempBuffer, tempLength, this->buff, this->length);
	memmCpy(tempBuffer + this->length, tempLength - (this->length), obj.buff, obj.length);
	//释放buffer
	this->destroy();
	tempBuffer[tempLength] = 0;
	this->buff = tempBuffer;
	this->length = tempLength;
	return *this;
}
bool String::operator==(const String& cmO)
{
	return this->equals(cmO);
}
String::~String()
{
	if ((this->buff))
	{
		free(this->buff);
		this->buff = NULL;
		this->length = 0;
	}
}
String String::operator=(char* str)
{
	String t(str);
	return t;
}
void String::memmCpy(char* desc, int dLength, const char* from, int fLength)
{
	for (int in = 0; in < fLength; in++)
	{
		//截断  防止OOM
		if (dLength == in)
		{
			desc[dLength + 1] = 0;
			break;
		}
		desc[in] = from[in];
	}
}
int String::strLen(const char* str)
{
	int length = 0;
	while (str[length] != '\0')
		length++;
	return length;
}
void String::destroy()
{
	if ((this->buff))
	{
		free(this->buff);
		this->buff = NULL;
		this->length = 0;
	}
}
void String::alloc(size_t size)
{
	int fromlength = this->length;
	char* descBuffer = (char*)malloc(sizeof(char) * (this->length + (int)size) + 1);
	this->memmCpy(descBuffer, (this->length + (int)size), this->buff, this->length);

	this->destroy();
	this->buff = descBuffer;
	this->length = fromlength;
}
