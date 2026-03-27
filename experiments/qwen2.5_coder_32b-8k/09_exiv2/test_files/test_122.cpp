#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/exiv2/src/pentaxmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class PentaxMakerNoteTest_122 : public ::testing::Test {

protected:

    std::ostringstream os;

    MockValue mockValue;  // Assuming Value is a class that can be mocked

    MockExifData mockMetadata;  // Assuming ExifData is a class that can be mocked



    PentaxMakerNoteTest_122() {}

};



TEST_F(PentaxMakerNoteTest_122, TagListReturnsConstantValue_122) {

    auto tagList = PentaxMakerNote::tagList();

    EXPECT_EQ(tagList, PentaxMakerNote::tagInfo_);

}



TEST_F(PentaxMakerNoteTest_122, PrintVersionCallsOstream_122) {

    PentaxMakerNote::printVersion(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintResolutionCallsOstream_122) {

    PentaxMakerNote::printResolution(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintDateCallsOstream_122) {

    PentaxMakerNote::printDate(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintTimeCallsOstream_122) {

    PentaxMakerNote::printTime(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintExposureCallsOstream_122) {

    PentaxMakerNote::printExposure(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintFValueCallsOstream_122) {

    PentaxMakerNote::printFValue(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintFocalLengthCallsOstream_122) {

    PentaxMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintCompensationCallsOstream_122) {

    PentaxMakerNote::printCompensation(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintTemperatureCallsOstream_122) {

    PentaxMakerNote::printTemperature(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintFlashCompensationCallsOstream_122) {

    PentaxMakerNote::printFlashCompensation(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintBracketingCallsOstream_122) {

    PentaxMakerNote::printBracketing(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(PentaxMakerNoteTest_122, PrintShutterCountCallsOstream_122) {

    PentaxMakerNote::printShutterCount(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}

```


