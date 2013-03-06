#ifndef _SLUINT_CONFIG_HPP_
#define _SLUINT_CONFIG_HPP_
#include <stddef.h>
#include <stdint.h>

/*
    Editable configuration to change the way the library works.

    Available defines :

    DEFINE_NAME (initially enabled)
    USLINT_OPERATOR_OVERLOAD (false) : Activate overloaded operators, following operators will be available :

                        CSLuint :
                            CSLuint  operator * (const CSluint &A,const CSLuint& B)
                            CSLuint  operator + (const CSluint &A,const CSLuint& B)
                            CSLuint& operator = (unsigned int I)
                            CSLuint& operator = (const CSLuint & Other)
                            uint8_t operator [] (size_t index) const

                        USLint :
                            {...}

    Operators << and >> will always be avaiable on std::ostream and std::istream.

    USLINT_x32_ATAT (false) : Enable ASM function to check carriages (ATAT, 32 bits)
    USLINT_x64_ATAT (false) : Enable ASM function to check carriages (ATAT, 64 bits)
    {...}

    Modifiable global variables :

    bool (*Carriage_AddFunc) (uint8_t A,uint8_t B)
    bool (*Carriage_SubFunc) (uint8_t A,uint8_t B)

    uint8_t (*Carriage_MulFunc) (uint8_t A,uint8_t B)
    uint8_t (*Carriage_DivFunc) (uint8_t A,uint8_t B)

*/

namespace uslint
{
    //! Functor to specify the function called to check carriage on addition (USLint).
    //! @param[in] A left operand.
    //! @param[in] B right operand.
    //! @return True if a carriage is required, otherwise false.
    extern bool(*Carriage_AddFunc) (uint8_t A,uint8_t B);

    //! Functor to specify the function called to check carriage on subtraction (USLint).
    //! @param[in] A left operand.
    //! @param[in] B right operand.
    //! @return True if a carriage is required, otherwise false.
    extern bool(*Carriage_SubFunc) (uint8_t A,uint8_t B);

    //! Functor to specify the function called to check carriage on multiplication (USLint).
    //! @param[in] A left operand.
    //! @param[in] B right operand.
    //! @return Carriage when applying operator.
    extern uint8_t (*Carriage_MulFunc) (uint8_t A,uint8_t B);

    //! Functor to specify the function called to check carriage on division (USLint).
    //! @param[in] A left operand.
    //! @param[in] B right operand.
    //! @return Carriage when applying operator.
    extern uint8_t (*Carriage_DivFunc) (uint8_t A,uint8_t B);

    //! Initialize the library, must be called once before handling SLuint and CSLuint classes.
    extern void Initialize();
}


#endif
