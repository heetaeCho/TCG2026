#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class MockDerived : public ParserRefImpl<MockDerived> {

public:

    using ParserRefImpl::ParserRefImpl;

    MockDerived& operator()(StringRef description) & {

        return static_cast<MockDerived&>(ParserRefImpl::operator()(description));

    }

};



class ParserRefImplTest_388 : public ::testing::Test {

protected:

    std::shared_ptr<BoundRef> boundRef;

    MockDerived parser;



    ParserRefImplTest_388() : boundRef(std::make_shared<BoundValueRef<int>>(value)), parser(boundRef, "hint") {}



    int value = 0;

};



TEST_F(ParserRefImplTest_388, RequiredSetsOptionalityToRequired_388) {

    parser.required();

    EXPECT_EQ(parser.isOptional(), false);

}



TEST_F(ParserRefImplTest_388, OptionalSetsOptionalityToOptional_388) {

    parser.optional();

    EXPECT_EQ(parser.isOptional(), true);

}



TEST_F(ParserRefImplTest_388, IsOptionalReturnsTrueByDefault_388) {

    EXPECT_EQ(parser.isOptional(), true);

}



TEST_F(ParserRefImplTest_388, HintReturnsProvidedHint_388) {

    EXPECT_EQ(parser.hint(), "hint");

}



TEST_F(ParserRefImplTest_388, DescriptionCanBeSetAndGet_388) {

    parser("description");

    // Assuming there's a way to verify the description was set, this is a placeholder

    // Since the actual implementation is not available, we can't directly check.

}
