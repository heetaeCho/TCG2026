#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    AnsiSkippingString ansiSkippingString;

};



TEST_F(AnsiSkippingStringTest_40, ConstIteratorDecrementReturnsPrevious_40) {

    // Arrange

    AnsiSkippingString::const_iterator it;



    // Act

    AnsiSkippingString::const_iterator prevIt = it--;



    // Assert

    // Since we cannot access internal state, we assume the decrement operator is working as expected.

    // This test checks if the returned iterator is different from the current one after decrement.

    EXPECT_NE(prevIt, it);

}



TEST_F(AnsiSkippingStringTest_40, ConstIteratorDecrementPrePostConsistency_40) {

    // Arrange

    AnsiSkippingString::const_iterator it;



    // Act

    auto preDecrement = --it;

    auto postDecrement = it--;



    // Assert

    // Check if pre-decrement and post-decrement behave consistently.

    EXPECT_EQ(preDecrement, postDecrement);

}

```


