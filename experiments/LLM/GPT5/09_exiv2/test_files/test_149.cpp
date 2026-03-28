#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/value.hpp"

using namespace Exiv2;

class ValueTypeTest_149 : public testing::Test {
protected:
    ValueType<int> valueTypeInt;
    ValueType<float> valueTypeFloat;
    ValueType<std::string> valueTypeString;

    void SetUp() override {
        // Set up initial values for tests if needed
    }

    void TearDown() override {
        // Clean up after each test if needed
    }
};

TEST_F(ValueTypeTest_149, ReadValidStringInput_149) {
    std::string input = "1 2 3 4 5";
    EXPECT_EQ(valueTypeInt.read(input), 0);
    EXPECT_EQ(valueTypeInt.count(), 5);
    EXPECT_EQ(valueTypeInt.size(), sizeof(int) * 5);
}

TEST_F(ValueTypeTest_149, ReadInvalidStringInput_149) {
    std::string input = "1 2 abc 4 5"; // Invalid input 'abc'
    EXPECT_EQ(valueTypeInt.read(input), 1); // Should return error due to invalid input
}

TEST_F(ValueTypeTest_149, ReadValidByteInput_149) {
    // Simulate byte buffer input
    const byte buf[] = {1, 2, 3, 4, 5};
    EXPECT_EQ(valueTypeInt.read(buf, sizeof(buf), ByteOrder::BigEndian), 0);
    EXPECT_EQ(valueTypeInt.count(), 5);
}

TEST_F(ValueTypeTest_149, ReadInvalidByteInput_149) {
    const byte buf[] = {1, 2, 3}; // Incomplete or invalid data
    EXPECT_EQ(valueTypeInt.read(buf, sizeof(buf), ByteOrder::BigEndian), 1); // Should fail due to invalid input size
}

TEST_F(ValueTypeTest_149, ToInt64Conversion_149) {
    std::string input = "1 2 3 4 5";
    valueTypeInt.read(input);
    EXPECT_EQ(valueTypeInt.toInt64(0), 1);
    EXPECT_EQ(valueTypeInt.toInt64(4), 5);
}

TEST_F(ValueTypeTest_149, ToInt64InvalidIndex_149) {
    std::string input = "1 2 3";
    valueTypeInt.read(input);
    EXPECT_THROW(valueTypeInt.toInt64(5), std::out_of_range); // Should throw an exception for out-of-range access
}

TEST_F(ValueTypeTest_149, ToFloatConversion_149) {
    std::string input = "1.1 2.2 3.3 4.4 5.5";
    valueTypeFloat.read(input);
    EXPECT_FLOAT_EQ(valueTypeFloat.toFloat(0), 1.1f);
    EXPECT_FLOAT_EQ(valueTypeFloat.toFloat(4), 5.5f);
}

TEST_F(ValueTypeTest_149, ToStringConversion_149) {
    std::string input = "hello world";
    valueTypeString.read(input);
    EXPECT_EQ(valueTypeString.toString(0), "hello");
    EXPECT_EQ(valueTypeString.toString(1), "world");
}

TEST_F(ValueTypeTest_149, CloneTest_149) {
    std::string input = "clone test";
    valueTypeString.read(input);
    UniquePtr clonePtr = valueTypeString.clone();
    EXPECT_EQ(clonePtr->toString(0), "clone");
    EXPECT_EQ(clonePtr->toString(1), "test");
}

TEST_F(ValueTypeTest_149, SizeTest_149) {
    std::string input = "1 2 3 4 5";
    valueTypeInt.read(input);
    EXPECT_EQ(valueTypeInt.size(), sizeof(int) * 5);
}

TEST_F(ValueTypeTest_149, CountTest_149) {
    std::string input = "10 20 30";
    valueTypeInt.read(input);
    EXPECT_EQ(valueTypeInt.count(), 3);
}

TEST_F(ValueTypeTest_149, SetDataAreaTest_149) {
    const byte buf[] = {10, 20, 30};
    EXPECT_EQ(valueTypeInt.setDataArea(buf, sizeof(buf)), 0);
    EXPECT_EQ(valueTypeInt.sizeDataArea(), sizeof(buf));
}

TEST_F(ValueTypeTest_149, DataAreaTest_149) {
    const byte buf[] = {1, 2, 3};
    valueTypeInt.setDataArea(buf, sizeof(buf));
    EXPECT_EQ(valueTypeInt.dataArea().size(), sizeof(buf));
}

TEST_F(ValueTypeTest_149, ExceptionalCaseTest_149) {
    const byte buf[] = {1, 2, 3}; // Malformed data
    EXPECT_EQ(valueTypeFloat.read(buf, sizeof(buf), ByteOrder::BigEndian), 1); // Read error expected
}