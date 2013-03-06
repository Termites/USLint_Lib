#ifndef _CSLUINT_H_
#define _CSLUINT_H_

#include "Config.hpp"
#include<iostream>


namespace uslint
{
    // Forward declaration of USLint (copy c-tor)
    class USLint;

    //! CSLuint.
    /*!
        CSLuint stands for 'Character super long unsigned integer', and is used to deal with huge number on base 10.
        It is only used to convert an USLint to a 10-base number in order to print and read values.
    */
	class CSLuint
	{
		protected:
             //! Array of digits. (base 10)
			char* Buffer;
			 //! Number of digits.
			size_t Length;

            //! Remove extra-zeros that can appears when adding or multiplying CSLuint.
			virtual void RemoveExtraZeros();

			//! Copy values from another CSLuint without reallocating Buffer.
			//! @param[in] Other CSLuint to copy.
			virtual void RawCopy(const CSLuint& Other);

            //! Allocate buffer and set 0 to every values.
            //! @param[in] n Length of new buffer.
			virtual void Allocate(size_t n);

			//! Deallocate buffer.
			virtual void Deallocate();

		public:
            //! Default constructor.
			CSLuint();

            //! Constructor from an unsigned integer.
            //! @param[in] I Unsigned integer number to copy.
			explicit CSLuint(unsigned int I);

            //! Constructor from a string.
			//! @param[in] Str String number to copy.
			explicit CSLuint (const char* Str);

            //! Constructor from another CSLuint.
			//! @param[in] Other CSLuint number to copy.
			CSLuint (const CSLuint& Other);

			/*! Constructor from a USLint, which will perform a 256-to-10 base conversion. */
			//! @param[in] Other USLint to copy.
			CSLuint (const USLint& Other);

            //! Assign current CSLuint to an unsigned integer.
            //! @param[in] i Unsigned integer to assign to.
			CSLuint & assign(unsigned int i);

            //! Assign current CSLuint to another CSLuint.
			//! @param[in] Other CSLuint to assign to.
			CSLuint & assign(const CSLuint& Other);

			//! Add current CSLuint and the one provided.
			//! Does not modify current CSLuint.
			//! @param[in] Other Right operand
			//! @return Result of Current + Other.
			CSLuint Add(const CSLuint& Other) const;

            //! Multiply current CSLuint and the one provided.
            //! Does not modify current CSLuint.
			//! @param[in] Other Right operand
			//! @return Result of Current * Other.
			CSLuint Mul(const CSLuint& Other) const;

			CSLuint& Pow256(size_t n);

            //! Get the character at an index.
            //! If the index is not valid, 0 ASCII character is returned.
            //! @param[in] Index Index of the character.
            //! @return Character at index Index.
			virtual char At(int Index) const;

			#ifdef USLINT_OVERLOADED_OPERATORS
            //! Operator + between two CSLuint
            /*!
                Only exists if USLINT_OVERLOADED_OPERATORS is defined.
            */
            CSLuint operator+(const CSLuint&Other);
			#endif

            virtual ~CSLuint();

            friend class USLint;
            friend std::ostream& operator << (std::ostream&, const CSLuint&);

	};

    //! Allow user to print CSLuint on a standard output stream
    //! @param[in] Stream Stream in which the number will be printed.
    //! @param[in] N Number to print.
	std::ostream& operator<<(std::ostream& Stream, const CSLuint & N);



};




#endif
