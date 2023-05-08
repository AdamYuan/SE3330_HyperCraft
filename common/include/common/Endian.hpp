#ifndef HYPERCRAFT_COMMON_ENDIAN_HPP
#define HYPERCRAFT_COMMON_ENDIAN_HPP

#ifndef IS_BIG_ENDIAN
#define IS_SMALL_ENDIAN
#endif

namespace common {

constexpr bool IsBigEndian() {
#ifdef IS_BIG_ENDIAN
	return true;
#else
	return false;
#endif
}
constexpr bool IsSmallEndian() {
#ifdef IS_SMALL_ENDIAN
	return true;
#else
	return false;
#endif
}

} // namespace common

#endif
