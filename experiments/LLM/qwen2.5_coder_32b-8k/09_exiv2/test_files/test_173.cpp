#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



TEST_F(ValueTypeTest_173, DefaultConstructorInitializesEmptyDataArea_173) {

    ValueType<int> value;

    EXPECT_EQ(value.sizeDataArea(), 0);

}



TEST_F(ValueTypeTest_173, SetDataAreaUpdatesSizeCorrectly_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    EXPECT_EQ(value.setDataArea(data, len), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, SetDataAreaWithZeroLengthDoesNotChangeSize_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    EXPECT_EQ(value.setDataArea(data, 0), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, SetDataAreaWithNullBufferDoesNotChangeSize_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    EXPECT_EQ(value.setDataArea(nullptr, len), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, CopyMethodReturnsCorrectSize_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    byte buffer[10];

    EXPECT_EQ(value.copy(buffer, littleEndian), len);

}



TEST_F(ValueTypeTest_173, CountMethodReturnsZeroForDefaultConstructedObject_173) {

    ValueType<int> value;

    EXPECT_EQ(value.count(), 0);

}



TEST_F(ValueTypeTest_173, SizeMethodReturnsNonZeroForDataAreaSet_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    EXPECT_GT(value.size(), 0);

}



TEST_F(ValueTypeTest_173, ReadMethodWithNullBufferReturnsError_173) {

    ValueType<int> value;

    EXPECT_EQ(value.read(nullptr, 4, littleEndian), -1);

}



TEST_F(ValueTypeTest_173, ReadMethodWithZeroLengthDoesNotModifyObject_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    EXPECT_EQ(value.read(data, 0, littleEndian), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, ReadMethodWithValidBufferUpdatesObject_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    EXPECT_EQ(value.read(data, len, littleEndian), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, ReadStringMethodWithEmptyStringDoesNotModifyObject_173) {

    ValueType<int> value;

    byte data[] = {1, 2, 3, 4};

    size_t len = sizeof(data);

    value.setDataArea(data, len);

    EXPECT_EQ(value.read(""), 0);

    EXPECT_EQ(value.sizeDataArea(), len);

}



TEST_F(ValueTypeTest_173, ReadStringMethodWithValidStringUpdatesObject_173) {

    ValueType<int> value;

    std::string data = "test";

    EXPECT_EQ(value.read(data), 0);

    EXPECT_GT(value.sizeDataArea(), 0);

}
