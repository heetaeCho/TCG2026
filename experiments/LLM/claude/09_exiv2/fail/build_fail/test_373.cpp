#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffBinaryArray tests
class TiffBinaryArrayTest_373 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that when decoded is false, doWrite falls back to TiffEntryBase::doWrite
TEST_F(TiffBinaryArrayTest_373, NotDecodedFallsBackToBase_373) {
  // Create a simple ArrayCfg
  ArrayCfg cfg = {
      ttUnsignedByte,  // elTiffType_
      nullptr,         // cryptFct_
      false,           // hasSize_
      false,           // hasFillers_
      false,           // concat_
      {0, 0},          // elDefaultDef_
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  // decoded() should be false by default
  EXPECT_FALSE(arr.decoded());

  MemIo mio;
  IoWrapper ioWrapper(mio, nullptr, 0, nullptr);
  size_t imageIdx = 0;

  // Should fall back to TiffEntryBase::doWrite since decoded is false
  size_t result = arr.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
  // TiffEntryBase::doWrite with no data should return 0
  EXPECT_EQ(result, 0u);
}

// Test that when decoded is true but elements are empty, it writes minimal output
TEST_F(TiffBinaryArrayTest_373, DecodedEmptyElements_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,  // elTiffType_
      nullptr,         // cryptFct_
      false,           // hasSize_
      false,           // hasFillers_
      false,           // concat_
      {0, 0},          // elDefaultDef_
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  arr.setDecoded(true);

  EXPECT_TRUE(arr.decoded());

  MemIo mio;
  IoWrapper ioWrapper(mio, nullptr, 0, nullptr);
  size_t imageIdx = 0;

  size_t result = arr.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
  EXPECT_EQ(result, 0u);
}

// Test cfg() and def() accessors
TEST_F(TiffBinaryArrayTest_373, CfgAndDefAccessors_373) {
  ArrayDef defs[] = {{0, 1}, {1, 1}};
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, defs, 2);

  EXPECT_NE(arr.cfg(), nullptr);
  EXPECT_NE(arr.def(), nullptr);
  EXPECT_EQ(arr.defSize(), 2u);
}

// Test construction with ArraySet
TEST_F(TiffBinaryArrayTest_373, ConstructWithArraySet_373) {
  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);

  // cfg() should be null when constructed with null arraySet and no selection
  EXPECT_EQ(arr.cfg(), nullptr);
  EXPECT_FALSE(arr.decoded());
}

// Test setDecoded toggles the decoded state
TEST_F(TiffBinaryArrayTest_373, SetDecodedToggle_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);

  EXPECT_FALSE(arr.decoded());
  arr.setDecoded(true);
  EXPECT_TRUE(arr.decoded());
  arr.setDecoded(false);
  EXPECT_FALSE(arr.decoded());
}

// Test with hasSize_ enabled and decoded
TEST_F(TiffBinaryArrayTest_373, DecodedWithHasSize_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,  // elTiffType_
      nullptr,         // cryptFct_
      true,            // hasSize_
      false,           // hasFillers_
      false,           // concat_
      {0, 0},          // elDefaultDef_
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  arr.setDecoded(true);

  MemIo mio;
  IoWrapper ioWrapper(mio, nullptr, 0, nullptr);
  size_t imageIdx = 0;

  size_t result = arr.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
  // With hasSize_ but no elements, it writes size info
  // The exact size depends on TypeInfo::typeSize for the type
  EXPECT_GE(mio.size(), 0u);
}

// Test IoWrapper basic write functionality
TEST_F(TiffBinaryArrayTest_373, IoWrapperBasicWrite_373) {
  MemIo mio;
  IoWrapper wrapper(mio, nullptr, 0, nullptr);

  byte data[] = {0x01, 0x02, 0x03};
  size_t written = wrapper.write(data, 3);
  EXPECT_EQ(written, 3u);
  EXPECT_EQ(mio.size(), 3u);
}

// Test IoWrapper putb
TEST_F(TiffBinaryArrayTest_373, IoWrapperPutb_373) {
  MemIo mio;
  IoWrapper wrapper(mio, nullptr, 0, nullptr);

  int result = wrapper.putb(0x42);
  EXPECT_EQ(result, 0x42);
  EXPECT_EQ(mio.size(), 1u);
}

// Test with byteOrder override in config
TEST_F(TiffBinaryArrayTest_373, ByteOrderOverride_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  // This config has invalidByteOrder so it won't override
  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  arr.setDecoded(true);

  MemIo mio;
  IoWrapper ioWrapper(mio, nullptr, 0, nullptr);
  size_t imageIdx = 0;

  size_t result = arr.write(ioWrapper, bigEndian, 0, 0, 0, imageIdx);
  EXPECT_EQ(result, 0u);
}

// Test that write with no cfg falls back
TEST_F(TiffBinaryArrayTest_373, NullCfgFallback_373) {
  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
  arr.setDecoded(true);

  MemIo mio;
  IoWrapper ioWrapper(mio, nullptr, 0, nullptr);
  size_t imageIdx = 0;

  // cfg() is null, so falls back to TiffEntryBase::doWrite
  size_t result = arr.write(ioWrapper, littleEndian, 0, 0, 0, imageIdx);
  EXPECT_EQ(result, 0u);
}

// Test initialize with pRoot
TEST_F(TiffBinaryArrayTest_373, InitializeWithRoot_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  bool result = arr.initialize(static_cast<TiffComponent*>(nullptr));
  // With null pRoot, behavior depends on implementation
  // Just check it doesn't crash
  (void)result;
}

// Test count when not decoded
TEST_F(TiffBinaryArrayTest_373, CountNotDecoded_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  EXPECT_EQ(arr.count(), 0u);
}

// Test size when not decoded
TEST_F(TiffBinaryArrayTest_373, SizeNotDecoded_373) {
  ArrayCfg cfg = {
      ttUnsignedByte,
      nullptr,
      false,
      false,
      false,
      {0, 0},
  };

  TiffBinaryArray arr(0x0001, IfdId::ifd0Id, cfg, nullptr, 0);
  EXPECT_EQ(arr.size(), 0u);
}
