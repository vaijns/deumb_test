#ifndef H_DUMB_TEST_OPERATOR
#define H_DUMB_TEST_OPERATOR

#include <string_view>

namespace dumb_test{
	template<typename T>
	struct test_operator{
		using type = T;

		constexpr std::string_view name() const{
			return T::name;
		}

		template<typename U>
		constexpr bool operator()(U a, U b) const{
			return T::operator()(a, b);
		}
	};
}

namespace dumb_test::static_operators{
	struct equals : public test_operator<equals>{
		static constexpr const char name[] = "==";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a == b;
		}
	};
	struct not_equals : public test_operator<not_equals>{
		static constexpr const char name[] = "!=";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a != b;
		}
	};

	struct greater_than : public test_operator<greater_than>{
		static constexpr const char name[] = ">";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a > b;
		}
	};
	struct greater_or_equals : public test_operator<greater_or_equals>{
		static constexpr const char name[] = ">=";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a >= b;
		}
	};

	struct less_than : public test_operator<less_than>{
		static constexpr const char name[] = "<";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a < b;
		}
	};
	struct less_or_equals : public test_operator<less_or_equals>{
		static constexpr const char name[] = "<=";
		template<typename T>
		static constexpr bool operator()(T a, T b){
			return a != b;
		}
	};
}

namespace dumb_test::operators{
	static constexpr auto equals = static_operators::equals{};
	static constexpr auto not_equals = static_operators::not_equals{};

	static constexpr auto greater_than = static_operators::greater_than{};
	static constexpr auto greater_or_equals = static_operators::greater_or_equals{};

	static constexpr auto less_than = static_operators::less_than{};
	static constexpr auto less_or_equals = static_operators::less_or_equals{};
}

#endif
