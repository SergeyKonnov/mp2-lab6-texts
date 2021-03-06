#ifndef __T_TEXT_LINK_H__
#define __T_TEXT_LINK_H__

#include <string.h>
#include "datvalue.h"
//#include "text.h"
#define TextLineLength 20
#define MemSize        20

#define TextError 101
#define TextNoPrev 102

class TText;
class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];

class TTextMem {
      PTTextLink pFirst;     // ��������� �� ������ �����
      PTTextLink pLast;      // ��������� �� ��������� �����
      PTTextLink pFree;      // ��������� �� ������ ��������� �����
      friend class TTextLink;
};
typedef TTextMem *PTTextMem;

class TTextLink : public TDatValue {
protected:
     TStr Str;  // ���� ��� �������� ������ ������
     PTTextLink pNext, pDown;  // ��������� �� ���. ������� � �� ����������
     static TTextMem MemHeader; // ������� ���������� �������
public:
     static void InitMemSystem (int size=MemSize); // ������������� ������
     static void PrintFreeLink ();  // ������ ��������� �������
     void * operator new (size_t size); // ��������� �����
     void operator delete (void *pM);   // ������������ �����
     static void MemCleaner (TText &txt); // ������ ������
     TTextLink(TStr s = nullptr, PTTextLink pn = nullptr, PTTextLink pd = nullptr)
     {
        pNext = pn; pDown = pd;
        if (s != nullptr)
            strcpy(Str,s);
        else Str[0]='\0';
     }
     ~TTextLink() {}
     int IsAtom () {return pDown == nullptr;} // �������� ����������� �����
     PTTextLink GetNext() {return pNext;}
     PTTextLink GetDown() {return pDown;}
     PTDatValue GetCopy() {return new TTextLink(Str,pNext,pDown);}
protected:
     virtual void Print (std::ostream &os) {os << Str;}
     friend class TText;
};

#endif // __T_TEXT_LINK_H__
