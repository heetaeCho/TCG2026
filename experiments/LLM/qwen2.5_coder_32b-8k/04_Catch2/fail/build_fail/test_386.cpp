#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class ParserRefImplTest : public ::testing::Test {

protected:

    struct DerivedT : public ParserRefImpl<DerivedT> {

        using ParserRefImpl::ParserRefImpl;

        DerivedT& operator() (StringRef description) & { return ParserRefImpl::operator()(description); }

    };



    std::shared_ptr<BoundRef> boundRef = std::make_shared<BoundRef>();

    DerivedT parserRefImpl{boundRef};

};



TEST_F(ParserRefImplTest_386, SetDescription_ReturnsSelfReference_386) {

    DerivedT& result = parserRefImpl("test description");

    EXPECT_EQ(&result, &parserRefImpl);

}



TEST_F(ParserRefImplTest_386, SetDescription_StoresCorrectDescription_386) {

    parserRefImpl("test description");

    EXPECT_EQ(parserRefImpl.m_description, "test description");

}



TEST_F(ParserRefImplTest_386, Optional_ReturnsSelfReference_386) {

    DerivedT& result = parserRefImpl.optional();

    EXPECT_EQ(&result, &parserRefImpl);

}



TEST_F(ParserRefImplTest_386, Required_ReturnsSelfReference_386) {

    DerivedT& result = parserRefImpl.required();

    EXPECT_EQ(&result, &parserRefImpl);

}



TEST_F(ParserRefImplTest_386, IsOptional_DefaultValueIsTrue_386) {

    EXPECT_TRUE(parserRefImpl.isOptional());

}



TEST_F(ParserRefImplTest_386, IsOptional_SetToFalseAfterRequired_386) {

    parserRefImpl.required();

    EXPECT_FALSE(parserRefImpl.isOptional());

}



TEST_F(ParserRefImplTest_386, Hint_DefaultValueIsEmptyStringRef_386) {

    EXPECT_TRUE(parserRefImpl.hint().empty());

}



TEST_F(ParserRefImplTest_386, Hint_SetInConstructor_IsStoredCorrectly_386) {

    DerivedT parserWithHint{boundRef, "test hint"};

    EXPECT_EQ(parserWithHint.hint(), "test hint");

}
