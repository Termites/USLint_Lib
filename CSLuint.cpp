#include "CSLuint.hpp"
#include <cmath>
#include <cstdio>
#include <cstring>
#include "USLint.hpp"

using namespace uslint;
CSLuint::CSLuint()
{
	Length=0;
	Buffer=NULL;
}

CSLuint::CSLuint(unsigned int I)
{
	size_t n = 1 + log10(I);
	Length = n;
	Buffer = new char [Length];
	sprintf(Buffer,"%i",I);
}

CSLuint::CSLuint(const char* S)
{
	size_t n = strlen(S);
	Length = n;
	Buffer = new char [Length];
	memcpy(Buffer,S,n*sizeof(uint8_t));
}

CSLuint::CSLuint(const CSLuint & Other)
{
	Length = Other.Length;
	Buffer = new char [Length];
	memcpy(Buffer,Other.Buffer,sizeof(uint8_t) * Other.Length);
}

CSLuint & CSLuint::assign(const CSLuint& Other)
{
    Allocate(Other.Length);
    memcpy(Buffer,Other.Buffer,sizeof(uint8_t) * Other.Length);

    return *this;
}

CSLuint::CSLuint(const USLint & Other)
{
    Allocate(1);
    Buffer[0]='0';

   // const CSLuint Base(int(256));
    for (size_t i=0;i<Other.Length;++i)
    {
        CSLuint N(Other.Buffer[i]);
        CSLuint R;
        R.Pow256(Other.Length-i-1);
        this->assign(this->Add(N.Mul(R)));
    }
}


void CSLuint::Allocate(size_t Length)
{
	if (Length >0)
		Deallocate();

	this->Length = Length;
	Buffer = new char[Length];
	memset(Buffer,'0',sizeof(uint8_t) * Length);
}

void CSLuint::Deallocate()
{
	if (Length>0)
		delete [] Buffer;

	Buffer=NULL;
	Length=0;
}

void CSLuint::RemoveExtraZeros()
{
    int NBZ = 0;
    for (int i=0;i<Length;++i)
    {
        if (Buffer[i]!='0')
        {
            NBZ = i;
            break;
        }
    }

    if (NBZ==0)
        return;

    size_t L = Length - NBZ;

    char * NewBuffer = new char[L];
    memcpy(NewBuffer,Buffer+NBZ,L*sizeof(char));
    Deallocate();
    Buffer=NewBuffer;
    Length=L;
}

void CSLuint::RawCopy(const CSLuint &Other)
{

}

char CSLuint::At(int Index) const
{
    if (Index<0 || Index>=Length)
        return '0';
    else
        return Buffer[Index];
}

CSLuint::~CSLuint()
{
    Deallocate();
}

std::ostream& uslint::operator << (std::ostream&Input,const CSLuint & N)
{
    for (int i=0;i<N.Length;++i)
        Input<<N.Buffer[i];

    return Input;
}

CSLuint CSLuint::Mul(const CSLuint& Other) const
{
   // Start from the end, go to the beg
    size_t MaxLen = this->Length+Other.Length;

    char Carriage=0;

    CSLuint C;
    C.Allocate(MaxLen+1);

    char Res[MaxLen];
    memset(Res,0,sizeof(char) * MaxLen);

    for (int i=Length;i>0;--i)
    {
        char cA,cB;
        cA =  this->At(i-1) - '0';

        int n=MaxLen-1-(this->Length-i);

        for(int j=Other.Length; j>0; --j){
            cB =  Other.At(j-1) - '0';
            Res[n] += cA*cB+Carriage;
            if (Res[n]>9)
            {
                Carriage=Res[n]/10;
                Res[n]%=10;
            }
            else
                Carriage = 0;
            --n;
        }
        if(Carriage)
            Res[n]=Carriage;
        Carriage=0;
    }

    for(int k=MaxLen-1; k>=0; --k)
        C.Buffer[k+1] = Res[k]+'0';

    C.RemoveExtraZeros();

    return C;
}

CSLuint CSLuint::Add(const CSLuint& Other) const
{
    // Maximal length of result (without last carriage):
    int MaxLen = this->Length>Other.Length ? this->Length : Other.Length;

    //
    char Carriage=0;

    CSLuint C;
    C.Allocate(MaxLen+1);


    for (int i=MaxLen-1;i>=0;--i)
    {
        char cA,cB;
        cA =  this->At(i + this->Length - MaxLen) - '0';
        cB =  Other.At(i + Other.Length - MaxLen) - '0';

        char R = cA+cB+Carriage;
        if (R >9)
        {
            Carriage = 1;
            R%=10;
        }
        else
            Carriage = 0;

        C.Buffer[i+1] = R+'0';
    }


    // Last carriage :
    if (Carriage)
        C.Buffer[0]='1';
    else
        C.Buffer[0]='0';

    // Remove extra zeros :
    C.RemoveExtraZeros();

    return C;
}

CSLuint& CSLuint::Pow256(size_t n)
{

    Allocate(1);
    Buffer[0]='1';

    for (size_t i=0;i<n;++i)
        this->assign(this->Mul(CSLuint(256)));

    return *this;
}
