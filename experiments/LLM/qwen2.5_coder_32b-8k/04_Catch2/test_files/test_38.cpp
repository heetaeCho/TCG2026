#include <gtest/gtest.h>

#include "catch2/internal/catch_textflow.hpp"



using namespace Catch::TextFlow;



class AnsiSkippingStringTest : public ::testing::Test {

protected:

    AnsiSkippingString ansiSkippingString;

};



TEST_F(AnsiSkippingStringTest_38, ConstIteratorIncrementPostfix_ReturnsPreviousState_38) {

    // Arrange

    AnsiSkippingString::const_iterator it(ansiSkippingString);



    // Act

    auto prevIt = it++;



    // Assert

    EXPECT_NE(&(*it), &(*prevIt));

}



TEST_F(AnsiSkippingStringTest_38, ConstIteratorIncrementPostfix_AdvancesIterator_38) {

    // Arrange

    AnsiSkippingString::const_iterator it(ansiSkippingString);

    auto prevIt = it;



    // Act

    it++;



    // Assert

    EXPECT_NE(&(*it), &(*prevIt));

}

```


