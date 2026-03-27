#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



// Mock class for Value

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(uint32_t, toUint32, (), (const, override));

};



// Test fixture

class PrintTagBitmaskTest_184 : public ::testing::Test {

protected:

    std::ostringstream os;

    MockValue mock_value;



    const TagDetailsBitmask array[3] = {

        {0x0001, "Label1"},

        {0x0002, "Label2"},

        {0x0004, "Label3"}

    };

};



// Test case for normal operation with multiple labels

TEST_F(PrintTagBitmaskTest_184, MultipleLabels_184) {

    EXPECT_CALL(mock_value, toUint32()).WillOnce(::testing::Return(0x0007));

    printTagBitmask(os, mock_value, nullptr);

    EXPECT_EQ(os.str(), "Label1, Label2, Label3");

}



// Test case for normal operation with a single label

TEST_F(PrintTagBitmaskTest_184, SingleLabel_184) {

    EXPECT_CALL(mock_value, toUint32()).WillOnce(::testing::Return(0x0002));

    printTagBitmask(os, mock_value, nullptr);

    EXPECT_EQ(os.str(), "Label2");

}



// Test case for no labels

TEST_F(PrintTagBitmaskTest_184, NoLabels_184) {

    EXPECT_CALL(mock_value, toUint32()).WillOnce(::testing::Return(0x0000));

    printTagBitmask(os, mock_value, nullptr);

    EXPECT_EQ(os.str(), "Label1");

}



// Test case for boundary condition with highest bit

TEST_F(PrintTagBitmaskTest_184, HighestBit_184) {

    EXPECT_CALL(mock_value, toUint32()).WillOnce(::testing::Return(0x0004));

    printTagBitmask(os, mock_value, nullptr);

    EXPECT_EQ(os.str(), "Label3");

}



// Test case for boundary condition with no matching bits

TEST_F(PrintTagBitmaskTest_184, NoMatchingBits_184) {

    EXPECT_CALL(mock_value, toUint32()).WillOnce(::testing::Return(0x0008));

    printTagBitmask(os, mock_value, nullptr);

    EXPECT_EQ(os.str(), "");

}
