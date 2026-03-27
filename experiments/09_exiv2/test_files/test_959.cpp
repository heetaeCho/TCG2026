#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using namespace testing;



class CanonMakerNoteTest_959 : public ::testing::Test {

protected:

    void SetUp() override {

        value = std::make_unique<Exiv2::Value>(Exiv2::unsignedShort);

    }



    std::unique_ptr<Exiv2::Value> value;

    Exiv2::ExifData exifData;

};



TEST_F(CanonMakerNoteTest_959, NormalOperation_959) {

    value->setUint32(0x1f01); // 1 focus point, center used

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "1 focus points; center used");

}



TEST_F(CanonMakerNoteTest_959, NoFocusPointsUsed_959) {

    value->setUint32(0xf000); // 15 focus points, none used

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "15 focus points; none");

}



TEST_F(CanonMakerNoteTest_959, MultipleFocusPointsUsed_959) {

    value->setUint32(0xf007); // 15 focus points, left, center, right used

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "15 focus points; left,center,right used");

}



TEST_F(CanonMakerNoteTest_959, InvalidTypeId_959) {

    value.reset(new Exiv2::Value(Exiv2::asciiString));

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(CanonMakerNoteTest_959, ZeroCount_959) {

    value->setUint32(0xf007); // 15 focus points, left, center, right used

    value->count() = 0; // Mock zero count

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(CanonMakerNoteTest_959, MaxFocusPoints_959) {

    value->setUint32(0xf00f); // 15 focus points, all used

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "15 focus points; left,center,right used");

}



TEST_F(CanonMakerNoteTest_959, NoFocusPoints_959) {

    value->setUint32(0x0000); // 0 focus points, none used

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, *value, &exifData);

    EXPECT_EQ(oss.str(), "0 focus points; none");

}
