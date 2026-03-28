#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class MockDerivedT : public ParserRefImpl<MockDerivedT> {

public:

    using ParserRefImpl<MockDerivedT>::ParserRefImpl;

};



class ParserRefImplTest_387 : public ::testing::Test {

protected:

    std::shared_ptr<BoundRef> ref = std::make_shared<BoundValueRef<int>>(value);

    MockDerivedT parser{ref, "hint"};

    int value = 0;



    void SetUp() override {

        value = 0;

    }

};



TEST_F(ParserRefImplTest_387, OptionalSetsOptionalityToOptional_387) {

    parser.optional();

    EXPECT_TRUE(parser.isOptional());

}



TEST_F(ParserRefImplTest_387, RequiredSetsOptionalityToRequired_387) {

    parser.required();

    EXPECT_FALSE(parser.isOptional());

}



TEST_F(ParserRefImplTest_387, HintReturnsCorrectHint_387) {

    EXPECT_EQ(parser.hint(), "hint");

}



TEST_F(ParserRefImplTest_387, CardinalityReturnsOneByDefault_387) {

    EXPECT_EQ(parser.cardinality(), 1);

}
