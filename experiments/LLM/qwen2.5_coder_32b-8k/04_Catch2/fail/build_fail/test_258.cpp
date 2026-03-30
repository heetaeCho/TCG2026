#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_context.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_tostring.cpp"



using namespace Catch;

using namespace Catch::Detail;



class MockConfig : public IConfig {

public:

    MOCK_METHOD(bool, showInvisibles, (), (const, override));

};



class ConvertIntoStringTest_258 : public ::testing::Test {

protected:

    void SetUp() override {

        context.setConfig(&mockConfig);

        Context::createContext();

        Context::getCurrentMutableContext().setConfig(&mockConfig);

    }



    MockConfig mockConfig;

    StringRef testStringRef;

    Context context;

};



TEST_F(ConvertIntoStringTest_258, ConvertEmptyString_258) {

    EXPECT_CALL(mockConfig, showInvisibles()).WillOnce(::testing::Return(false));

    StringRef emptyStringRef("");

    std::string result = convertIntoString(emptyStringRef);

    ASSERT_EQ(result, "");

}



TEST_F(ConvertIntoStringTest_258, ConvertNormalStringWithoutInvisibles_258) {

    EXPECT_CALL(mockConfig, showInvisibles()).WillOnce(::testing::Return(false));

    StringRef normalStringRef("test");

    std::string result = convertIntoString(normalStringRef);

    ASSERT_EQ(result, "test");

}



TEST_F(ConvertIntoStringTest_258, ConvertNormalStringWithInvisibles_258) {

    EXPECT_CALL(mockConfig, showInvisibles()).WillOnce(::testing::Return(true));

    StringRef normalStringRef("test\n");

    std::string result = convertIntoString(normalStringRef);

    ASSERT_EQ(result, "test\\n");

}



TEST_F(ConvertIntoStringTest_258, ConvertStringWithSpecialCharactersWithoutInvisibles_258) {

    EXPECT_CALL(mockConfig, showInvisibles()).WillOnce(::testing::Return(false));

    StringRef specialCharStringRef("te\tst\n");

    std::string result = convertIntoString(specialCharStringRef);

    ASSERT_EQ(result, "te\tst\n");

}



TEST_F(ConvertIntoStringTest_258, ConvertStringWithSpecialCharactersWithInvisibles_258) {

    EXPECT_CALL(mockConfig, showInvisibles()).WillOnce(::testing::Return(true));

    StringRef specialCharStringRef("te\tst\n");

    std::string result = convertIntoString(specialCharStringRef);

    ASSERT_EQ(result, "te\\tst\\n");

}
