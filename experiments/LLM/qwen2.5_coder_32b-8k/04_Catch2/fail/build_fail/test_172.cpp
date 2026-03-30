#include <gtest/gtest.h>

#include "catch2/matchers/catch_matchers_templated.hpp"



// Mock classes or handlers if needed (none required for this specific interface)



TEST(MatchAllOfGenericTest_172, OperatorAnd_NormalOperation_172) {

    // Arrange

    Catch::Matchers::MatcherBase<int> matcher1;

    Catch::Matchers::MatcherBase<int> matcher2;



    // Act

    auto result = matcher1 && matcher2;



    // Assert

    EXPECT_TRUE((std::is_same<decltype(result), Catch::Matchers::Detail::MatchAllOfGeneric<Catch::Matchers::MatcherBase<int>, Catch::Matchers::MatcherBase<int>>>::value));

}



// Boundary conditions and exceptional/error cases are not applicable for this specific interface

// as it is a template operator && that combines two matchers. There are no boundary values or error paths to test.

```


