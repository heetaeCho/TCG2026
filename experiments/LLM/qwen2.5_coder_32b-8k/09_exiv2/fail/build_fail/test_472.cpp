#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_472 : public ::testing::Test {

protected:

    Value value;

    const ExifData* metadata = nullptr;  // Assuming no internal state reliance



    Nikon3MakerNoteTest_472() : value(TypeId::unsignedLong) {}



    virtual void SetUp() {

        // Setup can be used to initialize common variables if needed

    }



    virtual void TearDown() {

        // Teardown can be used to cleanup after tests

    }

};



TEST_F(Nikon3MakerNoteTest_472, NormalOperation_PrintsLensId1_472) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>("dummy"), 5);

    EXPECT_CALL(*this, testConfigFile(os, value)).WillOnce(::testing::Return(false));

    Nikon3MakerNote nikon3MakerNote;

    auto result = nikon3MakerNote.printLensId1(os, value, metadata);

    EXPECT_EQ(&result, &os);

}



TEST_F(Nikon3MakerNoteTest_472, ConfigFileTrue_PrintsNothing_472) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>("dummy"), 5);

    EXPECT_CALL(*this, testConfigFile(os, value)).WillOnce(::testing::Return(true));

    Nikon3MakerNote nikon3MakerNote;

    auto result = nikon3MakerNote.printLensId1(os, value, metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Nikon3MakerNoteTest_472, EmptyDataArea_PrintsNothing_472) {

    std::ostringstream os;

    value.setDataArea(nullptr, 0);

    EXPECT_CALL(*this, testConfigFile(os, value)).WillOnce(::testing::Return(false));

    Nikon3MakerNote nikon3MakerNote;

    auto result = nikon3MakerNote.printLensId1(os, value, metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Nikon3MakerNoteTest_472, ValueNotOk_PrintsNothing_472) {

    std::ostringstream os;

    value.ok_ = false;

    value.setDataArea(reinterpret_cast<const byte*>("dummy"), 5);

    EXPECT_CALL(*this, testConfigFile(os, value)).WillOnce(::testing::Return(false));

    Nikon3MakerNote nikon3MakerNote;

    auto result = nikon3MakerNote.printLensId1(os, value, metadata);

    EXPECT_EQ(&result, &os);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Nikon3MakerNoteTest_472, MetadataNull_PrintsNothing_472) {

    std::ostringstream os;

    value.setDataArea(reinterpret_cast<const byte*>("dummy"), 5);

    EXPECT_CALL(*this, testConfigFile(os, value)).WillOnce(::testing::Return(false));

    Nikon3MakerNote nikon3MakerNote;

    auto result = nikon3MakerNote.printLensId1(os, value, nullptr);

    EXPECT_EQ(&result, &os);

}



// Mock function for testConfigFile

bool Nikon3MakerNoteTest_472::testConfigFile(std::ostream& os, const Value& value) {

    return false;  // Default behavior, can be mocked in tests

}
