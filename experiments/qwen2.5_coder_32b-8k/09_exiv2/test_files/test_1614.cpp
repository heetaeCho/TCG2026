#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class SonyMakerNoteTest_1614 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is a necessary parameter, even if not used.

};



TEST_F(SonyMakerNoteTest_1614, PutManualMode_1614) {

    Value value;

    value.setValue(0);

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "Manual");

}



TEST_F(SonyMakerNoteTest_1614, PutAFSMode_1614) {

    Value value;

    value.setValue(2);

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "AF-S");

}



TEST_F(SonyMakerNoteTest_1614, PutAFCMode_1614) {

    Value value;

    value.setValue(3);

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "AF-C");

}



TEST_F(SonyMakerNoteTest_1614, PutAFAutoMode_1614) {

    Value value;

    value.setValue(4);

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "AF-A");

}



TEST_F(SonyMakerNoteTest_1614, PutDMFMode_1614) {

    Value value;

    value.setValue(6);

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "DMF");

}



TEST_F(SonyMakerNoteTest_1614, PutUnknownValue_1614) {

    Value value;

    value.setValue(1); // An unknown value

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_THAT(os.str(), HasSubstr("(1)"));

}



TEST_F(SonyMakerNoteTest_1614, PutMultiValue_1614) {

    Value value;

    value.setValue(0); // Setting first value

    value.addValue(2); // Adding second value to make count > 1

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "0"); // Should return the raw value as count is not 1

}



TEST_F(SonyMakerNoteTest_1614, PutNegativeValue_1614) {

    Value value;

    value.setValue(-1); // A negative value

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_THAT(os.str(), HasSubstr("(-1)"));

}



TEST_F(SonyMakerNoteTest_1614, PutLargeValue_1614) {

    Value value;

    value.setValue(0x80); // A large value that gets masked to 0

    sonyMakerNote.printSony2FpFocusMode(os, value, &exifData);

    EXPECT_EQ(os.str(), "Manual");

}
