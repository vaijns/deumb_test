#ifndef H_DUMB_TEST_TEST_RESULT
#define H_DUMB_TEST_TEST_RESULT

#include "string_literal.hpp"

namespace dumb_test{
	template<string_literal Name, typename TOperator, typename T>
	struct test_result{
		static constexpr auto name = Name.value;
		static constexpr auto operator_name = TOperator::name;

		bool succeeded;
		T expected_value;
		T actual_value;
	};
}

#endif
