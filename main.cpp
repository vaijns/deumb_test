#include <dumb_test.hpp>

int main(int argc, char* argv[]){
	{
		// runtime tests (print result)
		using namespace dumb_test::operators;
		static bool testResult = dumb_test::evaluate<"aha">(dumb_test::check<"nop">(2, equals, 1));
	}

	{
		// static tests (fail at compile-time)
		using namespace dumb_test::static_operators;
		static constexpr bool testResult = dumb_test::static_evaluate<"yep", dumb_test::static_check<"idk", 3, equals, 3>>;
	}

	return 0;
}
