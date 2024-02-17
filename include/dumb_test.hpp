#ifndef H_DUMB_TEST
#define H_DUMB_TEST

#include <iostream>
#include "dumb_test/string_literal.hpp"
#include "dumb_test/test_result.hpp"

namespace dumb_test{
		namespace detail{
		template<string_literal Name, auto ValA, typename TOperator, decltype(ValA) ValB>
		[[nodiscard]] static constexpr auto check(){
			test_result<Name, TOperator, decltype(ValA)> result{};
			result.succeeded = TOperator::template operator()<decltype(ValA)>(ValA, ValB);
			result.expected_value = ValB;
			result.actual_value = ValA;

			return result;
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

	template<string_literal Name = "">
	[[nodiscard]] static constexpr auto check(auto a, auto op, decltype(a) b){
		test_result<Name, typename decltype(op)::type, decltype(a)> result{};
		result.succeeded = op(a, b);
		result.expected_value = b;
		result.actual_value = a;

		return result;
	}

	template<string_literal CategoryName, typename... TResults>
	[[nodiscard]] static constexpr auto evaluate(TResults... results){
		std::size_t totalAmount = sizeof...(TResults);
		std::size_t failedAmount = ((results.succeeded ? 0 : 1) + ...);
		std::size_t succeededAmount = ((results.succeeded ? 1 : 0) + ...);

		std::cout
			<< "["
			<< (failedAmount == 0 ? "PASSED: " : "FAILED: ")
			<< CategoryName.value
			<< "]\n";
		std::cout << "total: " << totalAmount << "\n";
		std::cout << "failed: " << failedAmount << "\n";
		std::cout << "succeeded: " << succeededAmount << "\n";
		std::cout << "----------\n";
		([&](){
			std::cout
				<< (results.succeeded ? "PASSED: " : "FAILED: ")
				<< results.name
				<< " "
				<< results.actual_value
				<< " "
				<< results.operator_name
				<< " "
				<< results.expected_value
				<< "\n";
		 }(), ...);
		std::cout << "----------\n";

		return failedAmount == 0;
	}
}

#endif
