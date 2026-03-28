#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/sonymn_int.cpp"



using namespace Exiv2::Internal;

using testing::_;



// Mock class for Value to control behavior in tests

class MockValue : public Value {

public:

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(TypeId, typeId, (), (const));

    MOCK_METHOD(std::string, toString, (), (const));

    MOCK_METHOD(uint32_t, toUint32, (size_t), (const));

};



class SonyMakerNoteTest_1607 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    MockValue mockValue;

    std::ostringstream os;

};



TEST_F(SonyMakerNoteTest_1607, InvalidCount_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(4));

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "(MockValue)");

}



TEST_F(SonyMakerNoteTest_1607, InvalidTypeId_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(int32));

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "(MockValue)");

}



TEST_F(SonyMakerNoteTest_1607, AllZeros_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("0 0 0 0 0 0 0 0"));

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(SonyMakerNoteTest_1607, ZeroFocalLengthMin_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 3 4 5 6 7 8"));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(0));

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(SonyMakerNoteTest_1607, ZeroApertureMin_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 3 4 5 6 7 8"));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(10));

    EXPECT_CALL(mockValue, toUint32(5)).WillOnce(::testing::Return(0));

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(SonyMakerNoteTest_1607, NormalOperation_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 3 4 5 6 7 8"));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(20)); // 1.4

    EXPECT_CALL(mockValue, toUint32(3)).WillOnce(::testing::Return(30)); // 2.5

    EXPECT_CALL(mockValue, toUint32(4)).WillOnce(::testing::Return(40)); // 4.6

    EXPECT_CALL(mockValue, toUint32(5)).WillOnce(::testing::Return(50)); // f1.8

    EXPECT_CALL(mockValue, toUint32(6)).WillOnce(::testing::Return(60)); // f2.9

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "14-2546mm F1.8-2.9");

}



TEST_F(SonyMakerNoteTest_1607, NoMaxFocalLength_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 0 0 5 6 7 8"));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(10)); // 1.4

    EXPECT_CALL(mockValue, toUint32(5)).WillOnce(::testing::Return(50)); // f1.8

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "14mm F1.8-2.9");

}



TEST_F(SonyMakerNoteTest_1607, NoMaxAperture_1607) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(8));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(unsignedByte));

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("1 2 3 4 5 6 0 0"));

    EXPECT_CALL(mockValue, toUint32(2)).WillOnce(::testing::Return(10)); // 1.4

    EXPECT_CALL(mockValue, toUint32(3)).WillOnce(::testing::Return(20)); // 2.5

    EXPECT_CALL(mockValue, toUint32(4)).WillOnce(::testing::Return(30)); // 3.6

    EXPECT_CALL(mockValue, toUint32(5)).WillOnce(::testing::Return(40)); // f1.8

    sonyMakerNote.printLensSpec(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "14-2536mm F1.8");

}
