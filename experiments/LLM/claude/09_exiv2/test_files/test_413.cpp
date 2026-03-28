#include <gtest/gtest.h>
#include <memory>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// A concrete subclass of TiffComponent for testing purposes,
// since TiffComponent has pure virtual methods.
class TestTiffComponent : public TiffComponent {
 public:
  TestTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}
  
  // Override idx() to allow setting a custom index for testing
  void setIdx(int idx) { idx_ = idx; }
  int idx() const override { return idx_; }

 protected:
  void doAccept(TiffVisitor& /*visitor*/) override {}
  size_t doWrite(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                 size_t /*valueIdx*/, size_t /*dataIdx*/, size_t& /*imageIdx*/) override { return 0; }
  size_t doWriteData(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                     size_t /*dataIdx*/, size_t& /*imageIdx*/) const override { return 0; }
  size_t doWriteImage(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/) const override { return 0; }
  size_t doSize() const override { return 0; }
  size_t doCount() const override { return 0; }
  size_t doSizeData() const override { return 0; }
  size_t doSizeImage() const override { return 0; }

 private:
  int idx_ = 0;
};

class CmpTagLtTest_413 : public ::testing::Test {
 protected:
  TiffComponent::SharedPtr makeComponent(uint16_t tag, IfdId group, int idx) {
    auto comp = std::make_shared<TestTiffComponent>(tag, group);
    static_cast<TestTiffComponent*>(comp.get())->setIdx(idx);
    return comp;
  }
};

// Test: When lhs tag is less than rhs tag, cmpTagLt returns true
TEST_F(CmpTagLtTest_413, LhsTagLessThanRhsTag_ReturnsTrue_413) {
  auto lhs = makeComponent(1, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(2, IfdId::ifd0Id, 0);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: When lhs tag is greater than rhs tag, cmpTagLt returns false
TEST_F(CmpTagLtTest_413, LhsTagGreaterThanRhsTag_ReturnsFalse_413) {
  auto lhs = makeComponent(5, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(2, IfdId::ifd0Id, 0);
  EXPECT_FALSE(cmpTagLt(lhs, rhs));
}

// Test: When tags are equal and lhs idx is less than rhs idx, returns true
TEST_F(CmpTagLtTest_413, EqualTags_LhsIdxLessThanRhsIdx_ReturnsTrue_413) {
  auto lhs = makeComponent(10, IfdId::ifd0Id, 1);
  auto rhs = makeComponent(10, IfdId::ifd0Id, 5);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: When tags are equal and lhs idx is greater than rhs idx, returns false
TEST_F(CmpTagLtTest_413, EqualTags_LhsIdxGreaterThanRhsIdx_ReturnsFalse_413) {
  auto lhs = makeComponent(10, IfdId::ifd0Id, 5);
  auto rhs = makeComponent(10, IfdId::ifd0Id, 1);
  EXPECT_FALSE(cmpTagLt(lhs, rhs));
}

// Test: When tags and indices are equal, returns false (not strictly less)
TEST_F(CmpTagLtTest_413, EqualTagsAndIndices_ReturnsFalse_413) {
  auto lhs = makeComponent(10, IfdId::ifd0Id, 3);
  auto rhs = makeComponent(10, IfdId::ifd0Id, 3);
  EXPECT_FALSE(cmpTagLt(lhs, rhs));
}

// Test: Boundary - tag 0 vs tag 0 with same idx
TEST_F(CmpTagLtTest_413, ZeroTagsZeroIdx_ReturnsFalse_413) {
  auto lhs = makeComponent(0, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(0, IfdId::ifd0Id, 0);
  EXPECT_FALSE(cmpTagLt(lhs, rhs));
}

// Test: Boundary - maximum tag value
TEST_F(CmpTagLtTest_413, MaxTagValue_LhsLess_413) {
  auto lhs = makeComponent(0xFFFE, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(0xFFFF, IfdId::ifd0Id, 0);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: Boundary - maximum tag value reversed
TEST_F(CmpTagLtTest_413, MaxTagValue_RhsLess_413) {
  auto lhs = makeComponent(0xFFFF, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(0xFFFE, IfdId::ifd0Id, 0);
  EXPECT_FALSE(cmpTagLt(lhs, rhs));
}

// Test: Tags equal, idx comparison with negative values
TEST_F(CmpTagLtTest_413, EqualTags_NegativeIdx_413) {
  auto lhs = makeComponent(5, IfdId::ifd0Id, -1);
  auto rhs = makeComponent(5, IfdId::ifd0Id, 0);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: Tags equal, both negative idx
TEST_F(CmpTagLtTest_413, EqualTags_BothNegativeIdx_413) {
  auto lhs = makeComponent(5, IfdId::ifd0Id, -5);
  auto rhs = makeComponent(5, IfdId::ifd0Id, -1);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: Verify cmpTagLt provides strict weak ordering (irreflexivity)
TEST_F(CmpTagLtTest_413, StrictWeakOrdering_Irreflexivity_413) {
  auto a = makeComponent(42, IfdId::ifd0Id, 7);
  EXPECT_FALSE(cmpTagLt(a, a));
}

// Test: Verify asymmetry: if a < b then !(b < a)
TEST_F(CmpTagLtTest_413, StrictWeakOrdering_Asymmetry_413) {
  auto a = makeComponent(1, IfdId::ifd0Id, 0);
  auto b = makeComponent(2, IfdId::ifd0Id, 0);
  EXPECT_TRUE(cmpTagLt(a, b));
  EXPECT_FALSE(cmpTagLt(b, a));
}

// Test: Same tag, idx ordering fallback
TEST_F(CmpTagLtTest_413, SameTag_IdxAsymmetry_413) {
  auto a = makeComponent(100, IfdId::ifd0Id, 2);
  auto b = makeComponent(100, IfdId::ifd0Id, 10);
  EXPECT_TRUE(cmpTagLt(a, b));
  EXPECT_FALSE(cmpTagLt(b, a));
}

// Test: Different groups but same tag - tag comparison should still work
TEST_F(CmpTagLtTest_413, DifferentGroups_SameTag_UsesIdx_413) {
  auto lhs = makeComponent(50, IfdId::ifd0Id, 1);
  auto rhs = makeComponent(50, IfdId::exifId, 2);
  // Tags are equal, so idx comparison: 1 < 2
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}

// Test: Tag 0 vs tag 1
TEST_F(CmpTagLtTest_413, TagZeroLessThanTagOne_413) {
  auto lhs = makeComponent(0, IfdId::ifd0Id, 0);
  auto rhs = makeComponent(1, IfdId::ifd0Id, 0);
  EXPECT_TRUE(cmpTagLt(lhs, rhs));
}
