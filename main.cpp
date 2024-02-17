#include "include/dumb_test.hpp"

int main(int argc, char* argv[]){
	{
		// runtime tests (print result)
		using namespace dumb_test::operators;
		static bool testResultA = dumb_test::evaluate<"aha">(
			dumb_test::check<"test a">(2, equals, 1),
			dumb_test::check<"test b">(2, not_equals, 1),
			dumb_test::check<"test c">(2, greater_than, 1),
			dumb_test::check<"test d">(2, less_than, 1),
			dumb_test::check<"test e">(2, greater_or_equals, 1),
			dumb_test::check<"test f">(2, less_or_equals, 1)
		);
	}

	{
		// static tests (fail at compile-time)
		using namespace dumb_test::static_operators;
		static constexpr bool testResult = dumb_test::static_evaluate<"yep", dumb_test::static_check<"idk", 3, equals, 3>>;
	}

	return 0;
}
