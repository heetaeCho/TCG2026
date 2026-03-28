#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1612 : public ::testing::Test {

protected:

    Value value;

    std::ostringstream os;

    ExifData metadata;

};



TEST_F(SonyMakerNoteTest_1612, NormalOperation_DSC_Model_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{0}), sizeof(uint16_t));

    metadata["Model"] = "DSC-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "Normal");

}



TEST_F(SonyMakerNoteTest_1612, NormalOperation_Stellar_Model_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{1}), sizeof(uint16_t));

    metadata["Model"] = "Stellar-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "High");

}



TEST_F(SonyMakerNoteTest_1612, NormalOperation_Other_Model_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{2}), sizeof(uint16_t));

    metadata["Model"] = "Other-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(SonyMakerNoteTest_1612, InvalidType_1612) {

    // Setup

    value = Value(unsignedLong);  // Invalid type for this function

    value.setDataArea(reinterpret_cast<const byte*>(&uint32_t{0}), sizeof(uint32_t));

    metadata["Model"] = "DSC-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "(U(0))");

}



TEST_F(SonyMakerNoteTest_1612, CountNotOne_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{0}), sizeof(uint16_t));

    value.setSize_(2);  // Invalid count for this function

    metadata["Model"] = "DSC-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "(U(0))");

}



TEST_F(SonyMakerNoteTest_1612, NullMetadata_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{3}), sizeof(uint16_t));



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, nullptr);



    // Verify

    EXPECT_EQ(os.str(), "(U(3))");

}



TEST_F(SonyMakerNoteTest_1612, UnknownModel_1612) {

    // Setup

    value = Value(unsignedShort);

    value.setDataArea(reinterpret_cast<const byte*>(&uint16_t{4}), sizeof(uint16_t));

    metadata["Model"] = "Unknown-Model";



    // Test

    SonyMakerNote::printHighISONoiseReduction2(os, value, &metadata);



    // Verify

    EXPECT_EQ(os.str(), "n/a");

}
