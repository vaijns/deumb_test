# dumb_test

A VERY EXPERIMENTAL, small, header-only library for testing in C++, without any macros.
Instead templates are used which probably slows down compile-time by a lot, so it's not recommended to actually use this (it's just for experimenting purposes).

I think the API is kinda cool tho and it allows for "static tests" using static_assert to fail at compile-time (while still going through all the tests and not exiting early).

## Example

```cpp
{
    // runtime tests (print result)
    using namespace dumb_test::operators;
    static auto testResult = dumb_test::evaluate<"aha">(dumb_test::check<"nop">(2, equals, 1));
}

{
    // static tests (fail at compile-time)
    using namespace dumb_test::static_operators;
    static constexpr auto testResult = dumb_test::static_evaluate<"yep", dumb_test::static_check<"idk", 3, equals, 3>>;
}
```
