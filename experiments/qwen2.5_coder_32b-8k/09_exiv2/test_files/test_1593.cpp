#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/sonymn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1593 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    void SetUp() override {

        value = Value(unsignedByte);

    }



    std::string captureOutput(std::ostream& os) {

        testing::internal::CaptureStdout();

        os.flush();

        auto output = testing::internal::GetCapturedStdout();

        return output;

    }

};



TEST_F(SonyMakerNoteTest_1593, ValueCountNotOne_1593) {

    value.setDataArea(nullptr, 2); // Set count to 2

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1593, ValueTypeNotUnsignedByte_1593) {

    Value invalidValue(unsignedShort); // Use unsigned short instead of unsigned byte

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, invalidValue, &metadata);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1593, MetadataIsNull_1593) {

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1593, ModelNotFoundInList_1593) {

    metadata["Make"] = "OtherBrand";

    value.toUint32(0); // Assuming some default value

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1593, ModelNotStartingWithDSC_1593) {

    metadata["Make"] = "DSCX-RX10M4";

    value.toUint32(0); // Assuming some default value

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1593, ValidModelAndValue_1593) {

    metadata["Make"] = "DSC-RX10M4";

    value.setDataArea(reinterpret_cast<const byte*>(&sonyFocusMode2[0].value_), 1); // Set to Manual

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_EQ(captureOutput(os), "Manual\n");

}



TEST_F(SonyMakerNoteTest_1593, ValidModelAndInvalidValue_1593) {

    metadata["Make"] = "DSC-RX10M4";

    uint32_t invalidValue = 99; // Invalid value

    value.setDataArea(reinterpret_cast<const byte*>(&invalidValue), 1);

    std::ostringstream os;

    SonyMakerNote::printFocusMode2(os, value, &metadata);

    EXPECT_EQ(captureOutput(os), "n/a\n");

}
