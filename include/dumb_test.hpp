#ifndef H_DUMB_TEST
#define H_DUMB_TEST

#include <iostream>
#include "dumb_test/string_literal.hpp"
#include "dumb_test/operator.hpp"
#include "dumb_test/test_result.hpp"

namespace dumb_test{
		namespace detail{
		template<string_literal Name, auto ValA, typename TOperator, decltype(ValA) ValB>
		[[nodiscard]] static constexpr auto check(){
			if constexpr(TOperator::template operator()<decltype(ValA)>(ValA, ValB)){
				return test_result<Name, TOperator, decltype(ValA)>{ true, ValB, ValA };
			} else{
				return test_result<Name, TOperator, decltype(ValA)>{ false, ValB, ValA };
			}
		}

		template<string_literal CategoryName, auto... Results>
		[[nodiscard]] static constexpr auto evaluate(){
			static constexpr std::size_t totalAmount = sizeof...(Results);
			static constexpr std::size_t failedAmount = ((Results.succeeded ? 0 : 1) + ...);
			static constexpr std::size_t succeededAmount = ((Results.succeeded ? 1 : 0) + ...);
			static_assert(failedAmount == 0, "there's failed tests.");

			return true;
		}
	}

	template<string_literal Name, auto ValA, typename TOperator, decltype(ValA) ValB>
	static constexpr auto static_check = detail::check<Name, ValA, TOperator, ValB>();

	template<string_literal CategoryName, auto... Results>
	static constexpr auto static_evaluate = detail::evaluate<CategoryName, Results...>();

	template<string_literal Name>
	[[nodiscard]] static constexpr auto check(auto a, auto op, decltype(a) b){
		if(op(a, b)){
			return test_result<Name, typename decltype(op)::type, decltype(a)>{ true, a, b };
		} else{
			return test_result<Name, typename decltype(op)::type, decltype(a)>{ false, a, b };
		}
	}

	template<string_literal CategoryName, typename... TResults>
	[[nodiscard]] static constexpr auto evaluate(TResults... results){
		std::size_t totalAmount = sizeof...(TResults);
		std::size_t failedAmount = ((results.succeeded ? 0 : 1) + ...);
		std::size_t succeededAmount = ((results.succeeded ? 1 : 0) + ...);

		std::cout << "total tests: " << totalAmount << "\n";
		std::cout << "failed tests: " << failedAmount << "\n";
		std::cout << "succeeded tests: " << succeededAmount << "\n";

		return failedAmount == 0;
	}
}

#endif
