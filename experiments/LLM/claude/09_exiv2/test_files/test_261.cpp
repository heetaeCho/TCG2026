#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need a valid ArrayCfg to instantiate the template.
// ArrayCfg is typically defined in tiffimage_int.hpp or similar headers.
// We'll define test configurations if needed.

namespace {

// Define a test ArrayCfg for use with the template
constexpr ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,      // group
    invalidByteOrder,   // byte order
    ttUndefined,        // type
    notEncrypted,       // encryption
    false,              // has size element
    false,              // has fillers
    false,              // concatenate
    {0, ttUnsignedByte, 1}  // element definition (tag, type, count)
};

constexpr ArrayCfg testArrayCfg2 = {
    IfdId::exifId,
    invalidByteOrder,
    ttUndefined,
    notEncrypted,
    false,
    false,
    false,
    {0, ttUnsignedByte, 1}
};

} // namespace

class NewTiffBinaryArray1Test_261 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the function returns a non-null pointer
TEST_F(NewTiffBinaryArray1Test_261, ReturnsNonNullPointer_261) {
    auto result = newTiffBinaryArray1<testArrayCfg>(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(NewTiffBinaryArray1Test_261, HasCorrectTag_261) {
    uint16_t expectedTag = 0x0042;
    auto result = newTiffBinaryArray1<testArrayCfg>(expectedTag, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test that the returned component has the correct group
TEST_F(NewTiffBinaryArray1Test_261, HasCorrectGroup_261) {
    IfdId expectedGroup = IfdId::ifd0Id;
    auto result = newTiffBinaryArray1<testArrayCfg>(0x0001, expectedGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), expectedGroup);
}

// Test with tag value of 0 (boundary)
TEST_F(NewTiffBinaryArray1Test_261, TagZero_261) {
    auto result = newTiffBinaryArray1<testArrayCfg>(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value (boundary)
TEST_F(NewTiffBinaryArray1Test_261, TagMaxValue_261) {
    auto result = newTiffBinaryArray1<testArrayCfg>(0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with different group
TEST_F(NewTiffBinaryArray1Test_261, DifferentGroup_261) {
    IfdId group = IfdId::exifId;
    auto result = newTiffBinaryArray1<testArrayCfg>(0x0010, group);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), group);
}

// Test with a different ArrayCfg template parameter
TEST_F(NewTiffBinaryArray1Test_261, DifferentArrayCfg_261) {
    auto result = newTiffBinaryArray1<testArrayCfg2>(0x0001, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0001);
    EXPECT_EQ(result->group(), IfdId::exifId);
}

// Test that two calls with same parameters produce independent objects
TEST_F(NewTiffBinaryArray1Test_261, ProducesIndependentObjects_261) {
    auto result1 = newTiffBinaryArray1<testArrayCfg>(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffBinaryArray1<testArrayCfg>(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test that two calls with different tags produce objects with different tags
TEST_F(NewTiffBinaryArray1Test_261, DifferentTagsProduceDifferentObjects_261) {
    auto result1 = newTiffBinaryArray1<testArrayCfg>(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffBinaryArray1<testArrayCfg>(0x0002, IfdId::ifd0Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1->tag(), result2->tag());
}
