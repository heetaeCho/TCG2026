#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/olympusmn_int.hpp"



using namespace testing;

using namespace Exiv2;

using namespace Exiv2::Internal;



class OlympusMakerNoteTest_907 : public Test {

protected:

    Value value;

    ExifData metadata;



    void SetUp() override {

        // Initialize a default value with TypeId unsignedShort

        value = *Value::create(unsignedShort);

    }

};



TEST_F(OlympusMakerNoteTest_907, NormalOperation_DefaultModel_907) {

    std::ostringstream os;

    uint16_t testValue = 3; // Corresponds to "Center (vertical)" in default model

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Center (vertical)");

}



TEST_F(OlympusMakerNoteTest_907, NormalOperation_E3Model_907) {

    std::ostringstream os;

    uint16_t testValue = 0x15; // Corresponds to "Bottom-center (horizontal)" in E-3 model

    value.setValue(&testValue);



    metadata.add(ExifKey("Exif.Image.Model"), Value::create(string));

    metadata["Exif.Image.Model"].setValue(std::string("E-3 Body"));



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Bottom-center (horizontal), Single Target");

}



TEST_F(OlympusMakerNoteTest_907, BoundaryCondition_MinValue_DefaultModel_907) {

    std::ostringstream os;

    uint16_t testValue = 0; // Corresponds to "Left (or n/a)" in default model

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Left (or n/a)");

}



TEST_F(OlympusMakerNoteTest_907, BoundaryCondition_MaxValue_DefaultModel_907) {

    std::ostringstream os;

    uint16_t testValue = 255; // Corresponds to "None" in default model

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "None");

}



TEST_F(OlympusMakerNoteTest_907, BoundaryCondition_OutOfRange_DefaultModel_907) {

    std::ostringstream os;

    uint16_t testValue = 4; // Out of range for default model

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "4");

}



TEST_F(OlympusMakerNoteTest_907, BoundaryCondition_MaxValue_E3Model_907) {

    std::ostringstream os;

    uint16_t testValue = 0x1f; // Corresponds to last entry in E-3 model

    value.setValue(&testValue);



    metadata.add(ExifKey("Exif.Image.Model"), Value::create(string));

    metadata["Exif.Image.Model"].setValue(std::string("E-3 Body"));



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Bottom-right (vertical), Single Target");

}



TEST_F(OlympusMakerNoteTest_907, ErrorCase_ValueTypeMismatch_907) {

    std::ostringstream os;

    uint32_t testValue = 3; // Incorrect type

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "3"); // Should print raw value due to type mismatch

}



TEST_F(OlympusMakerNoteTest_907, ErrorCase_ValueCountMismatch_907) {

    std::ostringstream os;

    uint16_t testValue = 3;

    value.setValue(&testValue);

    value.setCount(2); // Incorrect count



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "3"); // Should print raw value due to count mismatch

}



TEST_F(OlympusMakerNoteTest_907, NormalOperation_NoMetadata_907) {

    std::ostringstream os;

    uint16_t testValue = 2; // Corresponds to "Right" in default model

    value.setValue(&testValue);



    OlympusMakerNote::print0x0308(os, value, nullptr);

    EXPECT_EQ(os.str(), "Right");

}



TEST_F(OlympusMakerNoteTest_907, NormalOperation_AllTargetFlag_E3Model_907) {

    std::ostringstream os;

    uint16_t testValue = 0x65; // Corresponds to "Mid-left (horizontal)" with All Target flag

    value.setValue(&testValue);



    metadata.add(ExifKey("Exif.Image.Model"), Value::create(string));

    metadata["Exif.Image.Model"].setValue(std::string("E-3 Body"));



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Mid-left (horizontal), All Target");

}



TEST_F(OlympusMakerNoteTest_907, NormalOperation_DynamicSingleTargetFlag_E3Model_907) {

    std::ostringstream os;

    uint16_t testValue = 0x85; // Corresponds to "Mid-left (horizontal)" with Dynamic Single Target flag

    value.setValue(&testValue);



    metadata.add(ExifKey("Exif.Image.Model"), Value::create(string));

    metadata["Exif.Image.Model"].setValue(std::string("E-3 Body"));



    OlympusMakerNote::print0x0308(os, value, &metadata);

    EXPECT_EQ(os.str(), "Mid-left (horizontal), Dynamic Single Target");

}
