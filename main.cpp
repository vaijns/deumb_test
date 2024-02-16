#include <dumb_test.hpp>

int main(int argc, char* argv[]){
	{
		// runtime tests (print result)
		using namespace dumb_test::operators;
		dumb_test::evaluate<"aha">(dumb_test::check<"nop">(2, equals, 1));
	}

	{
		// static tests (fail at compile-time)
		using namespace dumb_test::static_operators;
		dumb_test::evaluate<"yep", dumb_test::check<"idk", 3, equals, 3>()>();
	}

	return 0;
}
