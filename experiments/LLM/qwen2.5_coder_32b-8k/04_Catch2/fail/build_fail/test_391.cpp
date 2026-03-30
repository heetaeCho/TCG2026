#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara::Detail;



class ParserRefImplMock : public ParserRefImpl<ParserRefImplMock> {

public:

    using ParserRefImpl<ParserRefImplMock>::ParserRefImpl;

};



class ParserRefImplTest_391 : public ::testing::Test {

protected:

    std::shared_ptr<BoundRef> boundRef;

    StringRef hint = "test_hint";

    StringRef description = "test_description";



    void SetUp() override {

        boundRef = std::make_shared<BoundValueRef<int>>(intVar);

    }



    int intVar = 0;

    ParserRefImplMock parser{boundRef, hint};

};



TEST_F(ParserRefImplTest_391, HintReturnsCorrectValue_391) {

    EXPECT_EQ(parser.hint(), hint);

}



TEST_F(ParserRefImplTest_391, DescriptionSetsCorrectly_391) {

    auto& updatedParser = parser(description);

    EXPECT_EQ(updatedParser.m_description, description);

}



TEST_F(ParserRefImplTest_391, OptionalSetsCorrectly_391) {

    auto& optionalParser = parser.optional();

    EXPECT_TRUE(optionalParser.isOptional());

}



TEST_F(ParserRefImplTest_391, RequiredSetsCorrectly_391) {

    auto& requiredParser = parser.required();

    EXPECT_FALSE(requiredParser.isOptional());

}



TEST_F(ParserRefImplTest_391, CardinalityReturnsZeroByDefault_391) {

    EXPECT_EQ(parser.cardinality(), 0);

}
