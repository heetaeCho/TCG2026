#include <gtest/gtest.h>

#include "canonmn_int.hpp"

#include "exif.hpp"

#include "value.hpp"

#include "types.hpp"

#include <sstream>



using namespace Exiv2;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_941 : public ::testing::Test {

protected:

    Value valueUnsignedLong;

    std::ostringstream os;

    ExifData metadata;



    void SetUp() override {

        valueUnsignedLong = *Value::create(unsignedLong);

        valueUnsignedLong.setValue(0x12345678); // Example value

    }

};



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_20D_941) {

    metadata["Exif.Image.Model"] = "Canon EOS 20D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "768-0304");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_350D_941) {

    metadata["Exif.Image.Model"] = "Canon EOS 350D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "768-0304");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_RebelXT_941) {

    metadata["Exif.Image.Model"] = "Canon EOS REBEL XT";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "768-0304");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_KissDigitalN_941) {

    metadata["Exif.Image.Model"] = "Canon EOS Kiss Digital N";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "768-0304");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_30D_941) {

    metadata["Exif.Image.Model"] = "Canon EOS 30D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "256-8272");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_400D_941) {

    metadata["Exif.Image.Model"] = "Canon EOS 400D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "256-8272");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_RebelXTi_941) {

    metadata["Exif.Image.Model"] = "Canon EOS REBEL XTi";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "256-8272");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_KissDigitalX_941) {

    metadata["Exif.Image.Model"] = "Canon EOS Kiss Digital X";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "256-8272");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_NormalOperation_K236_941) {

    metadata["Exif.Image.Model"] = "Canon EOS K236";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "256-8272");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_MetadataNull_941) {

    metadata.clear();

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, nullptr);

    EXPECT_EQ(os.str(), "(0x12345678)");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_ValueTypeMismatch_941) {

    Value valueAsciiString(asciiString);

    metadata["Exif.Image.Model"] = "Canon EOS 20D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueAsciiString, &metadata);

    EXPECT_EQ(os.str(), "(null)");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_ValueCountZero_941) {

    Value emptyValueUnsignedLong(unsignedLong);

    metadata["Exif.Image.Model"] = "Canon EOS 20D";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, emptyValueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "(null)");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_ModelNotFound_941) {

    metadata["Exif.Image.Model"] = "Unknown Model";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "(0x12345678)");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_ModelEmptyString_941) {

    metadata["Exif.Image.Model"] = "";

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "(0x12345678)");

}



TEST_F(CanonMakerNoteTest_941, PrintFiFileNumber_MetadataEmpty_941) {

    metadata.clear();

    os.str("");

    CanonMakerNote::printFiFileNumber(os, valueUnsignedLong, &metadata);

    EXPECT_EQ(os.str(), "(0x12345678)");

}
