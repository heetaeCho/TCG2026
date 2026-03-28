#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"

#include "catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::NiceMock;



class MockConfig : public IConfig {

public:

    MOCK_CONST_METHOD0(allowThrows, bool());

};



class AssertionHandlerTest_553 : public ::testing::Test {

protected:

    NiceMock<MockConfig> mockConfig;

    Context context;

    AssertionHandler handler{"MACRO_NAME", SourceLineInfo{"filename.cpp", 10}, "expression", ResultDisposition::None()};



    void SetUp() override {

        context.setConfig(&mockConfig);

    }

};



TEST_F(AssertionHandlerTest_553, AllowThrows_ReturnsTrue_553) {

    EXPECT_CALL(mockConfig, allowThrows()).WillOnce(Return(true));

    EXPECT_TRUE(handler.allowThrows());

}



TEST_F(AssertionHandlerTest_553, AllowThrows_ReturnsFalse_553) {

    EXPECT_CALL(mockConfig, allowThrows()).WillOnce(Return(false));

    EXPECT_FALSE(handler.allowThrows());

}
