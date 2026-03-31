#include <gtest/gtest.h>
#include <memory>
#include <cstdint>

#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewCasio2Mn2Test_1534 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that the function returns a non-null pointer
TEST_F(NewCasio2Mn2Test_1534, ReturnsNonNullPointer_1534) {
    auto result = newCasio2Mn2(0x927c, IfdId::ifd0Id, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
}

// Test with typical Makernote tag value
TEST_F(NewCasio2Mn2Test_1534, CreatesWithTypicalMakernoteTag_1534) {
    const uint16_t exifMakernoteTag = 0x927c;
    auto result = newCasio2Mn2(exifMakernoteTag, IfdId::exifId, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), exifMakernoteTag);
}

// Test that the created object has the correct tag
TEST_F(NewCasio2Mn2Test_1534, HasCorrectTag_1534) {
    uint16_t tag = 0x0001;
    auto result = newCasio2Mn2(tag, IfdId::ifd0Id, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with zero tag value
TEST_F(NewCasio2Mn2Test_1534, ZeroTagValue_1534) {
    auto result = newCasio2Mn2(0, IfdId::ifd0Id, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0);
}

// Test with maximum uint16_t tag value (boundary)
TEST_F(NewCasio2Mn2Test_1534, MaxTagValue_1534) {
    auto result = newCasio2Mn2(0xFFFF, IfdId::ifd0Id, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with different group IDs
TEST_F(NewCasio2Mn2Test_1534, DifferentGroupIds_1534) {
    auto result = newCasio2Mn2(0x927c, IfdId::exifId, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls return independent objects
TEST_F(NewCasio2Mn2Test_1534, MultipleCallsReturnIndependentObjects_1534) {
    auto result1 = newCasio2Mn2(0x0001, IfdId::ifd0Id, IfdId::casio2Id);
    auto result2 = newCasio2Mn2(0x0002, IfdId::ifd0Id, IfdId::casio2Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
}

// Test that the returned object is a valid TiffIfdMakernote
TEST_F(NewCasio2Mn2Test_1534, ReturnedObjectIsValidTiffIfdMakernote_1534) {
    auto result = newCasio2Mn2(0x927c, IfdId::exifId, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
    // The object should be usable as a TiffIfdMakernote
    TiffIfdMakernote* raw = result.get();
    ASSERT_NE(raw, nullptr);
}

// Test with ifd1Id group
TEST_F(NewCasio2Mn2Test_1534, WithIfd1Group_1534) {
    auto result = newCasio2Mn2(0x927c, IfdId::ifd1Id, IfdId::casio2Id);
    ASSERT_NE(result, nullptr);
}
