#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace testing;

using namespace Exiv2;

using namespace Exiv2::Internal;



class NikonMnIntTest_471 : public Test {

protected:

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

};



class MockValue : public Value {

public:

    MOCK_CONST_METHOD0(toString, std::string());

};



TEST_F(NikonMnIntTest_471, ConfigFileFound_NormalOperation_471) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("test_value"));

    EXPECT_TRUE(testConfigFile(os, mockValue));

    EXPECT_EQ(os.str(), "test_value");

}



TEST_F(NikonMnIntTest_471, ConfigFileNotFound_NormalOperation_471) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return("undefined"));

    EXPECT_FALSE(testConfigFile(os, mockValue));

    EXPECT_EQ(os.str(), "");

}



TEST_F(NikonMnIntTest_471, EmptyString_BoundaryCondition_471) {

    EXPECT_CALL(mockValue, toString()).WillOnce(Return(""));

    EXPECT_FALSE(testConfigFile(os, mockValue));

    EXPECT_EQ(os.str(), "");

}



TEST_F(NikonMnIntTest_471, LargeString_BoundaryCondition_471) {

    std::string largeString(LARGE_INT, 'a');

    EXPECT_CALL(mockValue, toString()).WillOnce(Return(largeString));

    EXPECT_TRUE(testConfigFile(os, mockValue));

    EXPECT_EQ(os.str(), largeString);

}
