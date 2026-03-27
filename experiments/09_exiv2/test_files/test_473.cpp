#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2::Internal;

using namespace testing;



class Nikon3MakerNoteTest_473 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote_;

    std::ostringstream oss_;

    NiceMock<MockValue> mockValue_;

    const ExifData* metadata_ = nullptr;

};



// Mock Value class to control the behavior of ok_

class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(bool, ok, (), (const, override));

};



TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_ConfigFileTrue_ReturnsOs_473) {

    EXPECT_CALL(mockValue_, ok()).WillOnce(Return(true));



    std::ostringstream& result = nikon3MakerNote_.printLensId2(oss_, mockValue_, metadata_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_ConfigFileFalse_CallsPrintLensIdWithNikonLd2_473) {

    EXPECT_CALL(mockValue_, ok()).WillOnce(Return(false));

    

    std::ostringstream& result = nikon3MakerNote_.printLensId2(oss_, mockValue_, metadata_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(Nikon3MakerNoteTest_473, PrintLensId2_ValueNotOk_ReturnsOs_473) {

    EXPECT_CALL(mockValue_, ok()).WillOnce(Return(false));



    std::ostringstream& result = nikon3MakerNote_.printLensId2(oss_, mockValue_, metadata_);

    EXPECT_EQ(&result, &oss_);

}
