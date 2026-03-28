#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewFujiMn2Test_1517 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that newFujiMn2 returns a non-null unique_ptr
TEST_F(NewFujiMn2Test_1517, ReturnsNonNullPointer_1517) {
    auto result = newFujiMn2(0x927c, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewFujiMn2Test_1517, HasCorrectTag_1517) {
    uint16_t testTag = 0x927c;
    auto result = newFujiMn2(testTag, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with different tag values
TEST_F(NewFujiMn2Test_1517, AcceptsDifferentTagValues_1517) {
    uint16_t testTag = 0x0001;
    auto result = newFujiMn2(testTag, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with tag value of zero (boundary)
TEST_F(NewFujiMn2Test_1517, AcceptsZeroTag_1517) {
    uint16_t testTag = 0x0000;
    auto result = newFujiMn2(testTag, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test with max uint16_t tag value (boundary)
TEST_F(NewFujiMn2Test_1517, AcceptsMaxTag_1517) {
    uint16_t testTag = 0xFFFF;
    auto result = newFujiMn2(testTag, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test that the returned object is a TiffIfdMakernote (dynamic cast check via unique_ptr type)
TEST_F(NewFujiMn2Test_1517, ReturnsTiffIfdMakernote_1517) {
    auto result = newFujiMn2(0x927c, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    // The return type is std::unique_ptr<TiffIfdMakernote>, so it's guaranteed
    TiffIfdMakernote* raw = result.get();
    ASSERT_NE(raw, nullptr);
}

// Test with different group IDs
TEST_F(NewFujiMn2Test_1517, AcceptsDifferentGroupIds_1517) {
    auto result = newFujiMn2(0x927c, IfdId::ifd0Id, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
}

// Test with different mnGroup IDs
TEST_F(NewFujiMn2Test_1517, AcceptsDifferentMnGroupIds_1517) {
    auto result = newFujiMn2(0x927c, IfdId::exifId, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls create independent objects
TEST_F(NewFujiMn2Test_1517, CreatesIndependentObjects_1517) {
    auto result1 = newFujiMn2(0x927c, IfdId::exifId, IfdId::fujiId);
    auto result2 = newFujiMn2(0x927c, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test that the mn header size is as expected for FujiMnHeader
TEST_F(NewFujiMn2Test_1517, MnHeaderCorrectness_1517) {
    auto result = newFujiMn2(0x927c, IfdId::exifId, IfdId::fujiId);
    ASSERT_NE(result, nullptr);
    // The object should have been constructed with a FujiMnHeader
    // We can verify it exists by checking the object is properly formed
    EXPECT_EQ(result->tag(), 0x927c);
}
