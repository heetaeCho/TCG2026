#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "tags_int.cpp"  // Assuming the implementation is in this file



namespace Exiv2 {

namespace Internal {



class ValueMock : public Value {

public:

    MOCK_METHOD(size_t, size, (), (const));

    MOCK_METHOD(TypeId, typeId, (), (const));

    MOCK_METHOD(int64_t, toInt64, (size_t), (const));

};



TEST_F(ExifVersionTest_1422, NormalOperation_1422) {

    ValueMock value;

    EXPECT_CALL(value, size()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(undefined));

    EXPECT_CALL(value, toInt64(0)).WillOnce(::testing::Return('0'));

    EXPECT_CALL(value, toInt64(1)).WillOnce(::testing::Return('2'));

    EXPECT_CALL(value, toInt64(2)).WillOnce(::testing::Return('3'));

    EXPECT_CALL(value, toInt64(3)).WillOnce(::testing::Return('0'));



    std::ostringstream os;

    printExifVersion(os, value, nullptr);



    EXPECT_EQ("0230", os.str());

}



TEST_F(ExifVersionTest_1422, IncorrectSize_1422) {

    ValueMock value;

    EXPECT_CALL(value, size()).WillOnce(::testing::Return(5));



    std::ostringstream os;

    printExifVersion(os, value, nullptr);



    EXPECT_EQ("(Value())", os.str());

}



TEST_F(ExifVersionTest_1422, IncorrectTypeId_1422) {

    ValueMock value;

    EXPECT_CALL(value, size()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(int8));



    std::ostringstream os;

    printExifVersion(os, value, nullptr);



    EXPECT_EQ("(Value())", os.str());

}



TEST_F(ExifVersionTest_1422, ZeroSize_1422) {

    ValueMock value;

    EXPECT_CALL(value, size()).WillOnce(::testing::Return(0));



    std::ostringstream os;

    printExifVersion(os, value, nullptr);



    EXPECT_EQ("(Value())", os.str());

}



TEST_F(ExifVersionTest_1422, LargeTypeId_1422) {

    ValueMock value;

    EXPECT_CALL(value, size()).WillOnce(::testing::Return(4));

    EXPECT_CALL(value, typeId()).WillOnce(::testing::Return(lastType));



    std::ostringstream os;

    printExifVersion(os, value, nullptr);



    EXPECT_EQ("(Value())", os.str());

}



}  // namespace Internal

}  // namespace Exiv2
