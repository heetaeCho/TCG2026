#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class ParserRefImplTest_389 : public ::testing::Test {

protected:

    std::shared_ptr<BoundRef> boundRef = std::make_shared<BoundValueRef<int>>(intVal);

    ParserRefImpl<ParserRefImpl<ParserRefImpl>> parser{boundRef, "testHint"};



    int intVal = 0;

};



TEST_F(ParserRefImplTest_389, IsOptional_DefaultIsTrue_389) {

    EXPECT_TRUE(parser.isOptional());

}



TEST_F(ParserRefImplTest_389, Optional_SetToOptional_ReturnsTrue_389) {

    parser.optional();

    EXPECT_TRUE(parser.isOptional());

}



TEST_F(ParserRefImplTest_389, Required_SetIsRequired_ReturnsFalse_389) {

    parser.required();

    EXPECT_FALSE(parser.isOptional());

}



TEST_F(ParserRefImplTest_389, Hint_DefaultHint_ReturnsCorrectHint_389) {

    EXPECT_EQ(parser.hint(), "testHint");

}
