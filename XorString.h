#pragma once

#include <cstddef>
#include <type_traits>

#define xor_(stringToEncrypt) \
[](){ \
	constexpr const std::size_t stringLength = sizeof(stringToEncrypt) / sizeof(stringToEncrypt[0x0]); \
	static xStr::xorString<std::remove_all_extents_t<std::remove_const_t<std::remove_reference_t<decltype(stringToEncrypt)>>>, stringLength> \
	xorStringClass(stringToEncrypt, std::make_index_sequence<stringLength>{ }); \
	return xorStringClass.xorGetString(); \
}()

namespace xStr {
	template <typename type, std::size_t length>
	class xorString {
	private:
		type newString[length];

		constexpr const type xorEncryptChar(const type charToEncrypt, const std::size_t index) {
			return (charToEncrypt ^ ((index + __TIME__[0x0] + __TIME__[0x1]) * (index + __TIME__[0x4] + __TIME__[0x7])));
		}

		const void xorDecryptString(const type stringToDecrypt[]) {
			for (std::size_t index = 0x0; index < length; index++) {
				newString[index] = xorEncryptChar(stringToDecrypt[index], index);
			}
		}
	public:
		template<std::size_t... indexSequence>
		constexpr const xorString(const type stringToEncrypt[], std::index_sequence<indexSequence...>) 
			:newString{ xorEncryptChar(stringToEncrypt[indexSequence], indexSequence)... }
		{
			return;
		}

		type* xorGetString() {
			xorDecryptString(newString);
			return newString;
		}
	};
}