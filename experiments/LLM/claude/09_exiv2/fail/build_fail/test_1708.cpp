#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffBinaryArray tests
class TiffBinaryArrayTest_1708 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test fixture for TiffFinder tests
class TiffFinderTest_1708 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test fixture for ArrayDef tests
class ArrayDefTest_1708 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test ArrayDef equality operator
TEST_F(ArrayDefTest_1708, EqualityOperatorMatchesIdx_1708) {
  ArrayDef def;
  def.idx_ = 5;
  def.count_ = 1;
  EXPECT_TRUE(def == 5);
  EXPECT_FALSE(def == 3);
  EXPECT_FALSE(def == 0);
}

TEST_F(ArrayDefTest_1708, EqualityOperatorZeroIdx_1708) {
  ArrayDef def;
  def.idx_ = 0;
  def.count_ = 1;
  EXPECT_TRUE(def == 0);
  EXPECT_FALSE(def == 1);
}

// Test TiffBinaryArray construction with ArrayCfg
TEST_F(TiffBinaryArrayTest_1708, ConstructWithArrayCfg_1708) {
  ArrayDef defs[] = {{0, 1}, {1, 1}};
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};

  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, defs, 2);

  EXPECT_EQ(ba.tag(), 0x0001);
  EXPECT_EQ(ba.group(), IfdId::ifd0Id);
  EXPECT_EQ(ba.cfg(), &cfg);
  EXPECT_EQ(ba.def(), defs);
  EXPECT_EQ(ba.defSize(), 2u);
}

// Test TiffBinaryArray construction with ArraySet
TEST_F(TiffBinaryArrayTest_1708, ConstructWithArraySet_1708) {
  TiffBinaryArray ba(0x0002, IfdId::ifd0Id, nullptr, 0, nullptr);

  EXPECT_EQ(ba.tag(), 0x0002);
  EXPECT_EQ(ba.group(), IfdId::ifd0Id);
  EXPECT_EQ(ba.cfg(), nullptr);
  EXPECT_EQ(ba.def(), nullptr);
  EXPECT_EQ(ba.defSize(), 0u);
}

// Test setDecoded and decoded
TEST_F(TiffBinaryArrayTest_1708, SetDecodedAndDecoded_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  ba.setDecoded(true);
  EXPECT_TRUE(ba.decoded());

  ba.setDecoded(false);
  EXPECT_FALSE(ba.decoded());
}

// Test iniOrigDataBuf when no data is set
TEST_F(TiffBinaryArrayTest_1708, IniOrigDataBufNoData_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  // Should not crash when called with no data
  ba.iniOrigDataBuf();
}

// Test updOrigDataBuf
TEST_F(TiffBinaryArrayTest_1708, UpdOrigDataBufNullData_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  // Update with null data and zero size
  bool result = ba.updOrigDataBuf(nullptr, 0);
  // Result depends on internal state; we just verify no crash
  (void)result;
}

// Test TiffFinder initialization and result
TEST_F(TiffFinderTest_1708, InitAndResultNull_1708) {
  TiffFinder finder(0x0001, IfdId::ifd0Id);
  EXPECT_EQ(finder.result(), nullptr);
}

// Test TiffFinder with init
TEST_F(TiffFinderTest_1708, InitResetsState_1708) {
  TiffFinder finder(0x0001, IfdId::ifd0Id);
  finder.init(0x0002, IfdId::exifId);
  EXPECT_EQ(finder.result(), nullptr);
}

// Test ArrayCfg tagStep
TEST(ArrayCfgTest_1708, TagStepDefaultDef_1708) {
  ArrayCfg cfg = {ttUnsignedByte, nullptr, false, false, false, {0, 1}};
  size_t step = cfg.tagStep();
  // tagStep should return a reasonable value based on the default def
  EXPECT_GT(step, 0u);
}

TEST(ArrayCfgTest_1708, TagStepWithUnsignedShort_1708) {
  ArrayCfg cfg = {ttUnsignedShort, nullptr, false, false, false, {0, 1}};
  size_t step = cfg.tagStep();
  EXPECT_GT(step, 0u);
}

// Test TiffEntryBase basic properties through TiffBinaryArray
TEST_F(TiffBinaryArrayTest_1708, TiffEntryBaseProperties_1708) {
  ArrayCfg cfg = {ttUnsignedByte, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0100, IfdId::ifd0Id, cfg, nullptr, 0);

  EXPECT_EQ(ba.tag(), 0x0100);
  EXPECT_EQ(ba.group(), IfdId::ifd0Id);
  EXPECT_EQ(ba.tiffType(), ttUnsignedByte);
  EXPECT_EQ(ba.pData(), nullptr);
  EXPECT_EQ(ba.pValue(), nullptr);
}

// Test TiffBinaryArray with concat config
TEST_F(TiffBinaryArrayTest_1708, ConcatConfigConstruction_1708) {
  ArrayDef defs[] = {{0, 2}, {4, 2}};
  ArrayCfg cfg = {ttUnsignedByte, nullptr, false, false, true, {0, 1}};

  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, defs, 2);

  EXPECT_EQ(ba.cfg(), &cfg);
  EXPECT_TRUE(ba.cfg()->concat_);
  EXPECT_EQ(ba.defSize(), 2u);
}

// Test TiffBinaryArray initialize with null root
TEST_F(TiffBinaryArrayTest_1708, InitializeWithNullRoot_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  bool result = ba.initialize(nullptr);
  // With null root, initialization should fail or handle gracefully
  (void)result;
}

// Test TiffBinaryArray doSize when no data
TEST_F(TiffBinaryArrayTest_1708, DoSizeNoData_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  // Size should be 0 when no data is set
  EXPECT_EQ(ba.size(), 0u);
}

// Test TiffBinaryArray count when no elements
TEST_F(TiffBinaryArrayTest_1708, CountNoElements_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  EXPECT_EQ(ba.count(), 0u);
}

// Test TiffComponent basic tag and group
TEST(TiffComponentTest_1708, TagAndGroup_1708) {
  ArrayCfg cfg = {ttUnsignedByte, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0xABCD, IfdId::exifId, cfg, nullptr, 0);

  EXPECT_EQ(ba.tag(), 0xABCD);
  EXPECT_EQ(ba.group(), IfdId::exifId);
}

// Test TiffEntryBase idx default
TEST_F(TiffBinaryArrayTest_1708, DefaultIdx_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  // Default idx should be 0
  EXPECT_EQ(ba.idx(), 0);
}

// Test TiffEntryBase setData with shared buffer
TEST_F(TiffBinaryArrayTest_1708, SetDataWithSharedBuf_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  byte testData[] = {0x01, 0x02, 0x03, 0x04};
  auto buf = std::make_shared<DataBuf>(testData, 4);
  ba.setData(std::move(buf));

  EXPECT_NE(ba.pData(), nullptr);
}

// Test TiffEntryBase offset
TEST_F(TiffBinaryArrayTest_1708, OffsetDefault_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  EXPECT_EQ(ba.offset(), 0u);
}

// Test TiffEntryBase setOffset
TEST_F(TiffBinaryArrayTest_1708, SetOffset_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  ba.setOffset(42);
  EXPECT_EQ(ba.offset(), 42u);
}

// Test multiple ArrayDef equality checks
TEST_F(ArrayDefTest_1708, EqualityOperatorBoundary_1708) {
  ArrayDef def;
  def.idx_ = SIZE_MAX;
  def.count_ = 1;
  EXPECT_TRUE(def == SIZE_MAX);
  EXPECT_FALSE(def == 0);
}

// Test TiffBinaryArray with different TiffTypes in config
TEST_F(TiffBinaryArrayTest_1708, DifferentTiffTypesInCfg_1708) {
  ArrayCfg cfgByte = {ttUnsignedByte, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba1(0x0001, IfdId::ifd0Id, cfgByte, nullptr, 0);
  EXPECT_EQ(ba1.tiffType(), ttUnsignedByte);

  ArrayCfg cfgShort = {ttUnsignedShort, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba2(0x0002, IfdId::ifd0Id, cfgShort, nullptr, 0);
  EXPECT_EQ(ba2.tiffType(), ttUnsignedShort);

  ArrayCfg cfgUndef = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba3(0x0003, IfdId::ifd0Id, cfgUndef, nullptr, 0);
  EXPECT_EQ(ba3.tiffType(), ttUndefined);
}

// Test TiffBinaryArray initialize with IfdId
TEST_F(TiffBinaryArrayTest_1708, InitializeWithIfdId_1708) {
  ArrayCfg cfg = {ttUndefined, nullptr, false, false, false, {0, 1}};
  TiffBinaryArray ba(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  bool result = ba.initialize(IfdId::ifd0Id);
  // Just verify it doesn't crash; result depends on internal setup
  (void)result;
}
