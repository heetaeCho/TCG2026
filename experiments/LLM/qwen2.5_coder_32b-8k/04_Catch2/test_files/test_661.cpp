#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Catch2/internal/catch_clara.hpp>

#include <string>



using namespace Catch::Clara;

using namespace Catch::Detail;



class MockBoundValueRefBase : public BoundValueRefBase {

public:

    MOCK_METHOD(ParseResult, setValue, (std::string), (override));

};



class ArgTest_661 : public ::testing::Test {

protected:

    std::shared_ptr<MockBoundValueRefBase> mock_bound_value_ref;

    Arg arg;



    ArgTest_661() {

        mock_bound_value_ref = std::make_shared<MockBoundValueRefBase>();

        arg.m_ref = mock_bound_value_ref;

    }

};



TEST_F(ArgTest_661, ParseValidArgument_661) {

    TokenStream tokens{Token(TokenType::Argument, "value")};

    EXPECT_CALL(*mock_bound_value_ref, setValue("value")).WillOnce(::testing::Return(ParseResult{}));

    

    auto result = arg.parse("", tokens);



    ASSERT_TRUE(result);

    ASSERT_EQ(result->type(), ParseResultType::Matched);

}



TEST_F(ArgTest_661, ParseInvalidArgumentType_661) {

    TokenStream tokens{Token(TokenType::Flag, "value")};

    EXPECT_CALL(*mock_bound_value_ref, setValue).Times(0);



    auto result = arg.parse("", tokens);



    ASSERT_TRUE(result);

    ASSERT_EQ(result->type(), ParseResultType::NoMatch);

}



TEST_F(ArgTest_661, ParseEmptyTokenStream_661) {

    TokenStream tokens;

    EXPECT_CALL(*mock_bound_value_ref, setValue).Times(0);



    auto result = arg.parse("", tokens);



    ASSERT_TRUE(result);

    ASSERT_EQ(result->type(), ParseResultType::NoMatch);

}



TEST_F(ArgTest_661, SetValueFails_661) {

    TokenStream tokens{Token(TokenType::Argument, "value")};

    EXPECT_CALL(*mock_bound_value_ref, setValue("value")).WillOnce(::testing::Return(ParseResult{"Error"}));



    auto result = arg.parse("", tokens);



    ASSERT_FALSE(result);

}



TEST_F(ArgTest_661, ValidateFails_661) {

    ON_CALL(*mock_bound_value_ref, setValue).WillByDefault(::testing::Return(ParseResult{}));

    EXPECT_CALL(*mock_bound_value_ref, validate()).WillOnce(::testing::Return(ParseResult{"Validation Error"}));



    TokenStream tokens{Token(TokenType::Argument, "value")};

    auto result = arg.parse("", tokens);



    ASSERT_FALSE(result);

}
