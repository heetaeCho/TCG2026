#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "sonymn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mock Value class to simulate behavior of Value passed to printColorTemperature

class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(count, uint32_t());

    MOCK_CONST_METHOD1(toUint32, uint32_t(size_t) const);

    MOCK_CONST_METHOD0(typeId, Exiv2::TypeId());

};



// Test fixture for SonyMakerNote tests

class SonyMakerNoteTest_1604 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    MockValue mockValue;

    std::ostringstream oss;



    void SetUp() override {}

    void TearDown() override {}

};



// Normal operation: value.count() == 1, value.typeId() == unsignedLong, and v0 is a normal color temperature

TEST_F(SonyMakerNoteTest_1604, PrintNormalColorTemperature_1604) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(Exiv2::unsignedLong));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(5000));



    sonyMakerNote.printColorTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("5000 K", oss.str());

}



// Boundary condition: value.count() == 1, value.typeId() == unsignedLong, and v0 == 0 (Auto)

TEST_F(SonyMakerNoteTest_1604, PrintAutoColorTemperature_1604) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(Exiv2::unsignedLong));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(0));



    sonyMakerNote.printColorTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("Auto", oss.str());

}



// Boundary condition: value.count() == 1, value.typeId() == unsignedLong, and v0 == 0xffffffff (n/a)

TEST_F(SonyMakerNoteTest_1604, PrintNotApplicableColorTemperature_1604) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(Exiv2::unsignedLong));

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(0xffffffff));



    sonyMakerNote.printColorTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("n/a", oss.str());

}



// Error case: value.count() != 1

TEST_F(SonyMakerNoteTest_1604, PrintInvalidCountColorTemperature_1604) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(2));

    EXPECT_CALL(mockValue, typeId()).Times(0);

    EXPECT_CALL(mockValue, toUint32(_)).Times(0);



    sonyMakerNote.printColorTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("(256) ", oss.str()); // Assuming the value is default constructed and has count 256

}



// Error case: value.typeId() != unsignedLong

TEST_F(SonyMakerNoteTest_1604, PrintInvalidTypeIdColorTemperature_1604) {

    EXPECT_CALL(mockValue, count()).WillOnce(::testing::Return(1));

    EXPECT_CALL(mockValue, typeId()).WillOnce(::testing::Return(Exiv2::undefined));

    EXPECT_CALL(mockValue, toUint32(_)).Times(0);



    sonyMakerNote.printColorTemperature(oss, mockValue, nullptr);



    EXPECT_EQ("(0) ", oss.str()); // Assuming the value is default constructed and has type undefined

}
