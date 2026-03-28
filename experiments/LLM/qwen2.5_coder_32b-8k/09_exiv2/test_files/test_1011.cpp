#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/minoltamn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



// Mock Value class to simulate the behavior of the actual Value class

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(long long, toInt64, (), (const));

};



TEST_F(MinoltaMakerNoteTest_1011, PrintMinoltaExposureCompensation5D_NormalOperation_1011) {

    MinoltaMakerNote minoltaMakerNote;

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(350));



    std::ostringstream os;

    minoltaMakerNote.printMinoltaExposureCompensation5D(os, mockValue, &exifData);



    EXPECT_EQ("0.50", os.str());

}



TEST_F(MinoltaMakerNoteTest_1011, PrintMinoltaExposureCompensation5D_BoundaryConditionZero_1011) {

    MinoltaMakerNote minoltaMakerNote;

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(300));



    std::ostringstream os;

    minoltaMakerNote.printMinoltaExposureCompensation5D(os, mockValue, &exifData);



    EXPECT_EQ("0.00", os.str());

}



TEST_F(MinoltaMakerNoteTest_1011, PrintMinoltaExposureCompensation5D_NegativeValue_1011) {

    MinoltaMakerNote minoltaMakerNote;

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(250));



    std::ostringstream os;

    minoltaMakerNote.printMinoltaExposureCompensation5D(os, mockValue, &exifData);



    EXPECT_EQ("-0.50", os.str());

}



TEST_F(MinoltaMakerNoteTest_1011, PrintMinoltaExposureCompensation5D_LargePositiveValue_1011) {

    MinoltaMakerNote minoltaMakerNote;

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(1300));



    std::ostringstream os;

    minoltaMakerNote.printMinoltaExposureCompensation5D(os, mockValue, &exifData);



    EXPECT_EQ("10.00", os.str());

}



TEST_F(MinoltaMakerNoteTest_1011, PrintMinoltaExposureCompensation5D_LargeNegativeValue_1011) {

    MinoltaMakerNote minoltaMakerNote;

    MockValue mockValue;

    ExifData exifData;



    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(200));



    std::ostringstream os;

    minoltaMakerNote.printMinoltaExposureCompensation5D(os, mockValue, &exifData);



    EXPECT_EQ("-1.00", os.str());

}
