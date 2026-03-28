#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/src/canonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



// Mock class for Value

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(uint16_t, typeId, (), (const));

    MOCK_METHOD(size_t, count, (), (const));

    MOCK_METHOD(int64_t, toInt64, (), (const));

};



TEST_F(CanonMakerNoteTest_963, PrintSi0x0017_NormalOperation_963) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(80));



    CanonMakerNote makerNote;

    makerNote.printSi0x0017(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "2.00");

}



TEST_F(CanonMakerNoteTest_963, PrintSi0x0017_TypeIdNotUnsignedShort_963) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::shortType));



    CanonMakerNote makerNote;

    makerNote.printSi0x0017(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_963, PrintSi0x0017_CountZero_963) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(0));



    CanonMakerNote makerNote;

    makerNote.printSi0x0017(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "");

}



TEST_F(CanonMakerNoteTest_963, PrintSi0x0017_LargeValue_963) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(1000));



    CanonMakerNote makerNote;

    makerNote.printSi0x0017(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "123.00");

}



TEST_F(CanonMakerNoteTest_963, PrintSi0x0017_SmallValue_963) {

    MockValue mockValue;

    std::ostringstream os;



    EXPECT_CALL(mockValue, typeId()).WillOnce(Return(Exiv2::unsignedShort));

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(0));



    CanonMakerNote makerNote;

    makerNote.printSi0x0017(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "-6.00");

}
