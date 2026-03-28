#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "sonymn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;



class SonyMakerNoteTest_1620 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

    ExifData exifData; // Assuming ExifData is a valid class and we can instantiate it

};



TEST_F(SonyMakerNoteTest_1620, PrintSonyMisc3cSequenceNumber_NormalOperationSingleUnsignedLong_1620) {

    Value value;

    value.setValue(42); // Example unsigned long value

    sonyMakerNote.printSonyMisc3cSequenceNumber(os, value, &exifData);

    EXPECT_EQ(os.str(), "43");

}



TEST_F(SonyMakerNoteTest_1620, PrintSonyMisc3cSequenceNumber_NormalOperationMultipleValues_1620) {

    Value value;

    std::vector<uint32_t> values = {42, 43};

    value.setValue(values); // Example with multiple values

    sonyMakerNote.printSonyMisc3cSequenceNumber(os, value, &exifData);

    EXPECT_EQ(os.str(), "(42 43)");

}



TEST_F(SonyMakerNoteTest_1620, PrintSonyMisc3cSequenceNumber_BoundaryConditionZeroCount_1620) {

    Value value;

    sonyMakerNote.printSonyMisc3cSequenceNumber(os, value, &exifData);

    EXPECT_EQ(os.str(), "()");

}



TEST_F(SonyMakerNoteTest_1620, PrintSonyMisc3cSequenceNumber_ExceptionalOperationWrongType_1620) {

    Value value;

    std::string strValue = "not a number";

    value.setValue(strValue); // Example with wrong type

    sonyMakerNote.printSonyMisc3cSequenceNumber(os, value, &exifData);

    EXPECT_EQ(os.str(), "(not a number)");

}
