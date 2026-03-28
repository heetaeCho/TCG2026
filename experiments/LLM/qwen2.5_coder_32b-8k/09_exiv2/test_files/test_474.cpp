#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_474 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote_;

    std::ostringstream os_;

    Value value_{TypeId::asciiString};

    const ExifData* metadata_{nullptr}; // Assuming no specific metadata is required for these tests

};



TEST_F(Nikon3MakerNoteTest_474, NormalOperationWithValue_474) {

    value_.setDataArea(reinterpret_cast<const byte*>("SampleLensID"), 12);

    nikonMakerNote_.printLensId3(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "NikonLd3: SampleLensID");

}



TEST_F(Nikon3MakerNoteTest_474, EmptyValue_474) {

    value_.setDataArea(nullptr, 0);

    nikonMakerNote_.printLensId3(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "NikonLd3: ");

}



TEST_F(Nikon3MakerNoteTest_474, LargeValue_474) {

    std::string largeValue(1000000, 'A');

    value_.setDataArea(reinterpret_cast<const byte*>(largeValue.c_str()), largeValue.size());

    nikonMakerNote_.printLensId3(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "NikonLd3: " + largeValue);

}



TEST_F(Nikon3MakerNoteTest_474, TestConfigFileReturnsTrue_474) {

    // Assuming testConfigFile is a static method that can be mocked if needed

    // Since we cannot mock internal behavior, we assume the implementation detail here.

    EXPECT_CALL(testing::A<const Value&>(), testing::_).WillOnce(testing::Return(true));

    nikonMakerNote_.printLensId3(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "");

}



TEST_F(Nikon3MakerNoteTest_474, TestConfigFileReturnsFalse_474) {

    // Assuming testConfigFile is a static method that can be mocked if needed

    // Since we cannot mock internal behavior, we assume the implementation detail here.

    EXPECT_CALL(testing::A<const Value&>(), testing::_).WillOnce(testing::Return(false));

    nikonMakerNote_.printLensId3(os_, value_, metadata_);

    EXPECT_EQ(os_.str(), "NikonLd3: ");

}
