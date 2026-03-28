#include <gtest/gtest.h>
#include <cstdint>

#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// We need valid ArrayCfg and ArrayDef instances to instantiate the template.
// These must be constexpr/const with external linkage to be used as template parameters.

namespace {

// Define a minimal ArrayCfg for testing purposes
constexpr ArrayCfg testArrayCfg = {
    IfdId::ifd0Id,       // group
    invalidByteOrder,    // byte order
    ttUndefined,         // element type
    notEncrypted,        // not encrypted
    false,               // hasSize
    false,               // hasFillers
    false,               // concat
    0,                   // cryptFct tag
    0,                   // size tag
    0,                   // tag step
};

constexpr ArrayDef testArrayDef[] = {
    {0, ttUndefined, 1},
};

constexpr ArrayDef testArrayDefMultiple[] = {
    {0, ttUndefined, 1},
    {1, ttUndefined, 2},
    {2, ttUndefined, 4},
};

}  // namespace

class NewTiffBinaryArray0Test_260 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that the function returns a non-null unique_ptr
TEST_F(NewTiffBinaryArray0Test_260, ReturnsNonNullPtr_260) {
  auto result = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(NewTiffBinaryArray0Test_260, HasCorrectTag_260) {
  const uint16_t expectedTag = 0x0042;
  auto result = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      expectedTag, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), expectedTag);
}

// Test with tag value of 0 (boundary)
TEST_F(NewTiffBinaryArray0Test_260, TagZeroBoundary_260) {
  auto result = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0), IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0);
}

// Test with maximum tag value (boundary)
TEST_F(NewTiffBinaryArray0Test_260, TagMaxBoundary_260) {
  const uint16_t maxTag = 0xFFFF;
  auto result = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      maxTag, IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), maxTag);
}

// Test with multiple array definitions
TEST_F(NewTiffBinaryArray0Test_260, MultipleArrayDefs_260) {
  auto result = newTiffBinaryArray0<testArrayCfg, 3, testArrayDefMultiple>(
      static_cast<uint16_t>(0x0010), IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0x0010);
}

// Test with different IfdId group values
TEST_F(NewTiffBinaryArray0Test_260, DifferentGroupValues_260) {
  auto result1 = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::ifd0Id);
  ASSERT_NE(result1, nullptr);

  auto result2 = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::exifId);
  ASSERT_NE(result2, nullptr);
}

// Test that two calls return distinct objects
TEST_F(NewTiffBinaryArray0Test_260, ReturnsDistinctObjects_260) {
  auto result1 = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::ifd0Id);
  auto result2 = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::ifd0Id);
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1.get(), result2.get());
}

// Test that the returned pointer is of the expected dynamic type (TiffBinaryArray)
TEST_F(NewTiffBinaryArray0Test_260, ReturnsTiffBinaryArrayType_260) {
  auto result = newTiffBinaryArray0<testArrayCfg, 1, testArrayDef>(
      static_cast<uint16_t>(0x0001), IfdId::ifd0Id);
  ASSERT_NE(result, nullptr);
  // Verify it can be dynamically cast to TiffBinaryArray
  TiffBinaryArray* binaryArray = dynamic_cast<TiffBinaryArray*>(result.get());
  EXPECT_NE(binaryArray, nullptr);
}
