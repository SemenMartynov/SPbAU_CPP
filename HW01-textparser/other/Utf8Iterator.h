/*
 * Utf8Iterator.h
 *
 *  Created on: 9 Mar 2013
 *      Author: Semen Martynov
 */

#ifndef UTF8ITERATOR_H_
#define UTF8ITERATOR_H_

#ifndef __GXX_EXPERIMENTAL_CXX0X__
typedef unsigned long char32_t;
#endif

// http://en.wikipedia.org/wiki/UTF-8
class Utf8Iterator: public std::iterator<std::bidirectional_iterator_tag,
		char32_t, std::string::difference_type, const char32_t*, const char32_t&>
{
public:

	Utf8Iterator(std::string::iterator it) :
			mStringIterator(it), mCurrentValue(0), mDirty(true)
	{
	}

	Utf8Iterator(const Utf8Iterator& source) :
			mStringIterator(source.mStringIterator), mCurrentValue(
					source.mCurrentValue), mDirty(source.mDirty)
	{
	}

	Utf8Iterator& operator=(const Utf8Iterator& rhs)
	{
		mStringIterator = rhs.mStringIterator;
		mCurrentValue = rhs.mCurrentValue;
		mDirty = rhs.mDirty;

		return *this;
	}

	Utf8Iterator& operator=(std::string::iterator it)
	{
		mStringIterator = it;
		mCurrentValue = 0;
		mDirty = true;

		return *this;
	}

	~Utf8Iterator()
	{
	}

	Utf8Iterator& operator++()
	{
		char firstByte = *mStringIterator;

		std::string::difference_type offset = 1;

		if (firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
		{
			if (firstByte & kThirdBitMask) // This means that the first byte has a value greater than 224, and so it must be at least a three-octet code point.
			{
				if (firstByte & kFourthBitMask) // This means that the first byte has a value greater than 240, and so it must be a four-octet code point.
					offset = 4;
				else
					offset = 3;
			}
			else
			{
				offset = 2;
			}
		}

		mStringIterator += offset;
		mDirty = true;
		return *this;
	}

	Utf8Iterator operator++(int)
	{
		Utf8Iterator temp = *this;
		++(*this);
		return temp;
	}

	Utf8Iterator& operator--()
	{
		--mStringIterator;

		if (*mStringIterator & kFirstBitMask) // This means that the previous byte is not an ASCII character.
		{
			--mStringIterator;
			if ((*mStringIterator & kSecondBitMask) == 0)
			{
				--mStringIterator;
				if ((*mStringIterator & kSecondBitMask) == 0)
				{
					--mStringIterator;
				}
			}
		}
		mDirty = true;
		return *this;
	}

	Utf8Iterator operator--(int)
	{
		Utf8Iterator temp = *this;
		--(*this);
		return temp;
	}

	Utf8Iterator operator+(size_t steps) const
	{
		Utf8Iterator temp = *this;
		while (--steps > 0)
		{
			temp++;
		}
		return temp;
	}

	Utf8Iterator operator-(size_t steps) const
	{
		Utf8Iterator temp = *this;
		while (--steps > 0)
		{
			temp--;
		}
		return temp;
	}

	char32_t operator*()
	{
		CalculateCurrentCodePoint();
		return mCurrentValue;
	}

	bool operator==(const Utf8Iterator& rhs) const
	{
		return mStringIterator == rhs.mStringIterator;
	}

	bool operator!=(const Utf8Iterator& rhs) const
	{
		return mStringIterator != rhs.mStringIterator;
	}

	bool operator==(std::string::iterator rhs) const
	{
		return mStringIterator == rhs;
	}

	bool operator==(std::string::const_iterator rhs) const
	{
		return mStringIterator == rhs;
	}

	bool operator!=(std::string::iterator rhs) const
	{
		return mStringIterator != rhs;
	}

	bool operator!=(std::string::const_iterator rhs) const
	{
		return mStringIterator != rhs;
	}

	bool isalpha()
	{
		CalculateCurrentCodePoint();
		return std::isalpha(wchar_t(mCurrentValue), std::locale("ru_RU.UTF-8"));
	}

	std::string::iterator toStrIt() const
	{
		return mStringIterator;
	}

private:
	std::string::iterator mStringIterator;

	mutable char32_t mCurrentValue;
	mutable bool mDirty;

	void CalculateCurrentCodePoint()
	{
		if (mDirty)
		{
			mCurrentValue = 0;

			char firstByte = *mStringIterator;

			if (firstByte & kFirstBitMask) // This means the first byte has a value greater than 127, and so is beyond the ASCII range.
			{
				if (firstByte & kThirdBitMask) // This means that the first byte has a value greater than 191, and so it must be at least a three-octet code point.
				{
					if (firstByte & kFourthBitMask) // This means that the first byte has a value greater than 224, and so it must be a four-octet code point.
					{
						mCurrentValue = (firstByte & 0x07) << 18;
						char secondByte = *(mStringIterator + 1);
						mCurrentValue += (secondByte & 0x3f) << 12;
						char thirdByte = *(mStringIterator + 2);
						mCurrentValue += (thirdByte & 0x3f) << 6;
						char fourthByte = *(mStringIterator + 3);
						mCurrentValue += (fourthByte & 0x3f);
					}
					else
					{
						mCurrentValue = (firstByte & 0x0f) << 12;
						char secondByte = *(mStringIterator + 1);
						mCurrentValue += (secondByte & 0x3f) << 6;
						char thirdByte = *(mStringIterator + 2);
						mCurrentValue += (thirdByte & 0x3f);
					}
				}
				else
				{
					mCurrentValue = (firstByte & 0x1f) << 6;
					char secondByte = *(mStringIterator + 1);
					mCurrentValue += (secondByte & 0x3f);
				}
			}
			else
			{
				mCurrentValue = firstByte;
			}

			mDirty = false;
		}
	}

	const static unsigned char kFirstBitMask = 128; // 1000000
	const static unsigned char kSecondBitMask = 64; // 0100000
	const static unsigned char kThirdBitMask = 32; // 0010000
	const static unsigned char kFourthBitMask = 16; // 0001000
	const static unsigned char kFifthBitMask = 8; // 0000100
};
#endif /* UTF8ITERATOR_H_ */
