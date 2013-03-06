#include "USLint.hpp"
#include <cstring>
#include <cmath>
#include "CSLuint.hpp"

using namespace uslint;

USLint::USLint()
{
    Length=0;
    Buffer=NULL;
}

USLint::USLint(const CSLuint&Other)
{
    Length = 0;
    Buffer = NULL;

   // const CSLuint Base(int(256));
    for (size_t i=0;i<Other.Length;++i)
    {
        USLint N(Other.Buffer[i]-'0');
        USLint R;
        R.Pow10(Other.Length-i-1);
        this->assign(this->Add(N.Mul(R)));
    }

}

USLint::USLint(const char* Other)
{
    Length = 0;
    Buffer = NULL;

    CSLuint Converted(Other);
    for (size_t i=0;i<Converted.Length;++i)
    {
        USLint N(Converted.Buffer[i]-'0');
        USLint R;
        R.Pow10(Converted.Length-i-1);
        this->assign(this->Add(N.Mul(R)));
    }
}

USLint::USLint(uint8_t Other)
{
    Length = 1;
    Buffer = new uint8_t(Other);

}

void USLint::Allocate(size_t N)
{
    if (Length>0)
        Deallocate();

    Buffer = new uint8_t[N];
    Length=N;
    memset(Buffer,0,sizeof(uint8_t)*N);
}

void USLint::Deallocate()
{
    delete [] Buffer;
}

USLint& USLint::assign(const USLint& Other)
{
    Allocate(Other.Length);

    memcpy(this->Buffer,Other.Buffer,Other.Length);

    return *this;
}

USLint USLint::Add(const USLint& Other) const
{
    size_t MaxLength = this->Length<Other.Length ? Other.Length : this->Length;

    uint8_t tmpBuffer[MaxLength+1];

    uint8_t Carriage=0;

    for (int i = MaxLength;i>=0;--i)
    {
        uint8_t dA = this->AtC(i + this->Length - MaxLength);
        uint8_t dB = Other.AtC(i + Other.Length - MaxLength);
        uint8_t R = dA+dB+Carriage;

        if (R < dA || R < dB)
            Carriage = 1;
        else
            Carriage = 0;

        tmpBuffer[i+1] = R;
    }
    tmpBuffer[0] = Carriage;

    USLint Result;

    Result.Allocate(MaxLength + Carriage);

    memcpy(Result.Buffer,static_cast<const void*>(tmpBuffer + (1-Carriage)),MaxLength + Carriage);

    return Result;
}

USLint USLint::Sub(const USLint& Other) const
{
    size_t MaxLength = this->Length<Other.Length ? Other.Length : this->Length;

    uint8_t tmpBuffer[MaxLength];

    uint8_t Carriage=0;
    for (int i=MaxLength+1;i>=0;--i)
    {
        uint8_t dA = this->AtC(i + this->Length - MaxLength);
        uint8_t dB = Other.AtC(i + Other.Length - MaxLength);
        uint16_t dR = dA - dB - Carriage;
        if (dA < dB)
            Carriage = 1;
        else
            Carriage = 0;

        tmpBuffer[i] = dR;
    }

     USLint Result;

    size_t Offset=0;
    while (tmpBuffer[Offset]==0 && Offset < MaxLength)
        ++Offset;

    Result.Allocate(MaxLength - Offset);

    memcpy(Result.Buffer,static_cast<const void*>(tmpBuffer + Offset),MaxLength-Offset);

    return Result;
}

USLint USLint::Mul(const USLint& Other) const
{
    const size_t MaxLength = this->Length + Other.Length;

    uint8_t Carriage=0;
    uint8_t tmpBuffer[MaxLength+1];
    memset(tmpBuffer,0,sizeof(uint8_t)*(MaxLength+1));

    for (size_t i=Length;i>0;--i)
    {
        uint8_t dA,dB;
        dA = this->AtC(i-1);

        size_t n = MaxLength-1-(this->Length-i);

        for (size_t j=Other.Length;j>0;--j)
        {
            dB = Other.AtC(j-1);
            uint16_t R = tmpBuffer[n] + dA*dB+Carriage;
            if (R > 256)
                Carriage = R/256;
            else
                Carriage = 0;

            tmpBuffer[n] = R; // will actually be R%256.
            --n;
        }
        tmpBuffer[n] = Carriage;
        Carriage=0;
    }

    // Copy tmpBuffer to result :
    USLint Result;

    size_t Offset=0; // Offset to the first digit :
    while (tmpBuffer[Offset]==0 && Offset<MaxLength)
        ++Offset;

    Result.Allocate(MaxLength - Offset);
    memcpy(Result.Buffer,tmpBuffer+Offset,MaxLength-Offset);

    return Result;
}

USLint USLint::Div(const USLint& Other) const
{
}

USLint USLint::Mod(const USLint& Other) const
{

}

uint8_t USLint::AtC(int Index) const
{
    if (Index<0 || Index>=Length)
        return 0;

    return Buffer[Index];
}

uint8_t USLint::At(size_t Index) const
{
    if (Index>=Length)
    {
        //throw ...
    }

    return Buffer[Index];
}

int USLint::Compare(const USLint &Other) const
{
    if (this->Length > Other.Length)
        return 1;
    else if (this->Length < Other.Length)
        return 0;
    else
        return memcmp(this->Buffer,Other.Buffer,this->Length);
}

void USLint::RawPrint(std::ostream &Output) const
{
    if (Length>0)
        for (size_t i=0;i<Length;++i)
            Output<<'['<<int(Buffer[i])<<"] ";
    else
        Output<<"<NULL>";
}

USLint& USLint::Pow10(size_t n)
{
    Allocate(1);
    Buffer[0]=1;

    for (size_t i=0;i<n;++i)
        this->assign(this->Mul(USLint(10)));

    return *this;
}

std::ostream& uslint::operator<<(std::ostream& Stream, const USLint & N)
{
    Stream<<CSLuint(N);
    return Stream;
}
