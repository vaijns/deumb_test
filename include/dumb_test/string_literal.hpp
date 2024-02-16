#ifndef H_DUMB_TEST_STRING_LITERAL
#define H_DUMB_TEST_STRING_LITERAL

#include <algorithm>
#include <cstddef>

namespace dumb_test{
	template<std::size_t N>
	struct string_literal{
		static constexpr std::size_t size = N;

		constexpr string_literal(const char (&str)[N]){
			std::copy_n(str, N, value);
		}

		char value[N];
	};
}

#endif
