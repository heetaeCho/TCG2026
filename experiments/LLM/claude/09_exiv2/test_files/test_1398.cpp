#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <exiv2/value.hpp>
#include <exiv2/exif.hpp>

namespace Exiv2 {
namespace Internal {
std::ostream& print0x8827(std::ostream& os, const Value& value, const ExifData*);
}
}

class Print0x8827Test_1398 : public ::testing::Test {
protected:
    std::ostringstream os;
};

TEST_F(Print0x8827Test_1398, NormalValue_PrintsInteger_1398) {
    Exiv2::UShortValue value;
    value.read("100");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "100");
}

TEST_F(Print0x8827Test_1398, ZeroValue_PrintsZero_1398) {
    Exiv2::UShortValue value;
    value.read("0");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "0");
}

TEST_F(Print0x8827Test_1398, LargeValue_PrintsLargeNumber_1398) {
    Exiv2::UShortValue value;
    value.read("65535");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "65535");
}

TEST_F(Print0x8827Test_1398, SmallValue_PrintsOne_1398) {
    Exiv2::UShortValue value;
    value.read("1");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "1");
}

TEST_F(Print0x8827Test_1398, TypicalISO200_1398) {
    Exiv2::UShortValue value;
    value.read("200");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "200");
}

TEST_F(Print0x8827Test_1398, TypicalISO400_1398) {
    Exiv2::UShortValue value;
    value.read("400");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "400");
}

TEST_F(Print0x8827Test_1398, TypicalISO800_1398) {
    Exiv2::UShortValue value;
    value.read("800");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "800");
}

TEST_F(Print0x8827Test_1398, TypicalISO3200_1398) {
    Exiv2::UShortValue value;
    value.read("3200");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "3200");
}

TEST_F(Print0x8827Test_1398, NullExifData_DoesNotCrash_1398) {
    Exiv2::UShortValue value;
    value.read("100");
    EXPECT_NO_THROW(Exiv2::Internal::print0x8827(os, value, nullptr));
}

TEST_F(Print0x8827Test_1398, ReturnsSameStream_1398) {
    Exiv2::UShortValue value;
    value.read("100");
    std::ostream& result = Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(&result, &os);
}

TEST_F(Print0x8827Test_1398, ULongValue_PrintsCorrectly_1398) {
    Exiv2::ULongValue value;
    value.read("12800");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "12800");
}

TEST_F(Print0x8827Test_1398, WithExifData_PrintsNormally_1398) {
    Exiv2::UShortValue value;
    value.read("1600");
    Exiv2::ExifData exifData;
    Exiv2::Internal::print0x8827(os, value, &exifData);
    EXPECT_EQ(os.str(), "1600");
}

TEST_F(Print0x8827Test_1398, HighISO_PrintsCorrectly_1398) {
    Exiv2::ULongValue value;
    value.read("51200");
    Exiv2::Internal::print0x8827(os, value, nullptr);
    EXPECT_EQ(os.str(), "51200");
}
