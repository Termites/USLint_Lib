#ifndef _USLINT_H_
#define _USLINT_H_

#include "Config.hpp"
#include <iostream>

namespace uslint
{
	// Forward declaration of CSLUint (copy c-tor)
	class CSLuint;

	class USLint
	{
		protected:
			//! Array of digits. (base 256)
			uint8_t* Buffer;
			//! Number of digits.
			size_t Length;

			//! Remove extra-zeros that can appears when adding or multiplying USLint.
			void RemoveExtraZeros();

			//! Allocate buffer and set 0 to every values.
			//! @param[in] n Length of the new buffer.
			virtual void Allocate(size_t n);

			//! Deallocate buffer.
			virtual void Deallocate();

            //! Returns 10^n
            //! @param[in] n the exponent.
            USLint& Pow10(size_t n);

		public:
			//! Default constructor.
			USLint();

			//! Constructor from a CSLuint
			//! @param[in] Other unsigned integer number to copy.
			explicit USLint(const CSLuint& Other);

			//! Constructor from a string
			//! @param[in] Other number to copy
			explicit USLint(const char* Other);

			//! Constructor from a single digit.
			//! @param[in] N digit to copy.
			explicit USLint(uint8_t N);

			//! Assign current USLint to another USLint.
			//! @param[in] Other unsigned integer to copy.
			virtual USLint& assign(const USLint&Other);

			//! Perform addition between current & Other.
			//! Does not modify current USLint.
			//! @param[in] Other Right operand.
			//! @return Result of Current + Other.
			virtual USLint Add(const USLint & Other) const;

			//! Perform subtraction between current & A.
			//! Does not modify current USLint.
			//! @param[in] Other Right operand.
			//! @return Result of Current - Other.
			virtual USLint Sub(const USLint & Other) const;

			//! Perform multiplication between current & Other.
			//! Does not modify current USLint.
			//! @param[in] Other Right operand.
			//! @return Result of Current * Other.
			virtual USLint Mul(const USLint & Other) const;

			//! Perform division between current & Other.
			//! Does not modify current USLint.
			//! @param[in] Other Right operand.
			//! @return Result of Current / Other.
			virtual USLint Div(const USLint & Other) const;

			//! Does not modify current USLint.
			//! @param[in] Other Right operand.
			//! @return Result of Current % Other.
			//! Perform modulo between current & other.
			virtual USLint Mod(const USLint & Other) const;

			//! Get the digit at a given index.
			//! If the index is not valid 0 is returned.
			//! @param[in] Index Index of the digit.
			virtual uint8_t AtC(int Index) const;

			//! Get the digit at a given index.
			//! If the index is not valid, and error is thrown.
			//! @param[in] Index Index of the digit.
			virtual uint8_t At(size_t Index) const;

			//! Compare current and Other.
			//! @param[in] Other Right operand.
			//! @return -1 if Current < Other, 1 if Current > Other, 0 if Current == Other.
			virtual int Compare(const USLint & Other) const;

			virtual void RawPrint(std::ostream & Output) const;


			friend class CSLuint;
            friend std::ostream& operator << (std::ostream&, const CSLuint&);
	};

    //! Allow user to print CSLuint on a standard output stream
    //! @param[in] Stream Stream in which the number will be printed.
    //! @param[in] N Number to print.
	std::ostream& operator<<(std::ostream& Stream, const USLint & N);
};

#endif
