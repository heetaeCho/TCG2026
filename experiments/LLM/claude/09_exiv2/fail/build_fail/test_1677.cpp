#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a TiffEncoder with minimal valid state
class TiffEncoderTestFixture_1677 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_ = ExifData();
    iptcData_ = IptcData();
    xmpData_ = XmpData();
  }

  ExifData exifData_;
  IptcData iptcData_;
  XmpData xmpData_;
};

// Test: visitBinaryArrayEnd returns early when cfg() is null
// A TiffBinaryArray constructed with ArraySet and cfgSelFct but without
// initialization will have cfg() == nullptr
TEST_F(TiffEncoderTestFixture_1677, VisitBinaryArrayEnd_NoCfg_ReturnsEarly_1677) {
  // Create a TiffBinaryArray without a valid config (using the ArraySet constructor
  // with null arraySet)
  // When cfg() returns nullptr, the function should return immediately
  // We verify no crash occurs and dirty flag is not set
  
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  // Create a TiffBinaryArray with no cfg set (using ArraySet constructor with nullptr)
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
  
  // cfg() should be nullptr, so visitBinaryArrayEnd should return early
  EXPECT_EQ(object.cfg(), nullptr);
  
  // Should not crash - early return because cfg() is null
  encoder.visitBinaryArrayEnd(&object);
  
  // dirty should remain false since we returned early
  EXPECT_FALSE(encoder.dirty());
}

// Test: visitBinaryArrayEnd returns early when decoded() is false
TEST_F(TiffEncoderTestFixture_1677, VisitBinaryArrayEnd_NotDecoded_ReturnsEarly_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  static const ArrayDef arrayDef = {0, ttUnsignedByte, 1};
  static const ArrayCfg arrayCfg = {
    ttUnsignedByte,  // elTiffType
    nullptr,         // cryptFct
    false,           // hasSize
    false,           // hasFillers
    false,           // concat
    {0, ttUnsignedByte, 1}  // elDefaultDef
  };
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
  
  // decoded() should be false by default
  EXPECT_FALSE(object.decoded());
  EXPECT_NE(object.cfg(), nullptr);
  
  // Should return early because decoded() is false
  encoder.visitBinaryArrayEnd(&object);
  
  EXPECT_FALSE(encoder.dirty());
}

// Test: visitBinaryArrayEnd returns early when size is 0
TEST_F(TiffEncoderTestFixture_1677, VisitBinaryArrayEnd_ZeroSize_ReturnsEarly_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  static const ArrayDef arrayDef = {0, ttUnsignedByte, 1};
  static const ArrayCfg arrayCfg = {
    ttUnsignedByte,
    nullptr,
    false,
    false,
    false,
    {0, ttUnsignedByte, 1}
  };
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
  object.setDecoded(true);
  
  // No data set, so size should be 0
  EXPECT_TRUE(object.decoded());
  EXPECT_NE(object.cfg(), nullptr);
  
  // Should return early because size is 0
  encoder.visitBinaryArrayEnd(&object);
  
  EXPECT_FALSE(encoder.dirty());
}

// Test: visitBinaryArrayEnd with decoded=true, valid cfg, data set, but no cryptFct
TEST_F(TiffEncoderTestFixture_1677, VisitBinaryArrayEnd_NoCryptFct_NoCrash_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  static const ArrayCfg arrayCfg = {
    ttUnsignedByte,
    nullptr,         // no cryptFct
    false,
    false,
    false,
    {0, ttUnsignedByte, 1}
  };
  static const ArrayDef arrayDef = {0, ttUnsignedByte, 1};
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
  object.setDecoded(true);
  
  // Set some data so size > 0
  auto buf = std::make_shared<DataBuf>(10);
  object.setData(buf);
  
  // cryptFct is null, so the encryption branch should be skipped
  // The function may still return early if initialize fails
  encoder.visitBinaryArrayEnd(&object);
  
  // Just verify no crash
  SUCCEED();
}

// Test: setDirty and dirty getter work correctly
TEST_F(TiffEncoderTestFixture_1677, SetDirtyAndDirtyGetter_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  EXPECT_FALSE(encoder.dirty());
  
  encoder.setDirty(true);
  EXPECT_TRUE(encoder.dirty());
  
  encoder.setDirty(false);
  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffBinaryArray cfg() returns correct pointer
TEST_F(TiffEncoderTestFixture_1677, TiffBinaryArray_CfgReturnsCorrectPointer_1677) {
  static const ArrayCfg arrayCfg = {
    ttUnsignedByte,
    nullptr,
    false,
    false,
    false,
    {0, ttUnsignedByte, 1}
  };
  static const ArrayDef arrayDef = {0, ttUnsignedByte, 1};
  
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
  
  EXPECT_EQ(object.cfg(), &arrayCfg);
  EXPECT_EQ(object.def(), &arrayDef);
  EXPECT_EQ(object.defSize(), 1u);
}

// Test: TiffBinaryArray decoded() default is false, can be set to true
TEST_F(TiffEncoderTestFixture_1677, TiffBinaryArray_DecodedDefaultFalse_1677) {
  static const ArrayCfg arrayCfg = {
    ttUnsignedByte,
    nullptr,
    false,
    false,
    false,
    {0, ttUnsignedByte, 1}
  };
  static const ArrayDef arrayDef = {0, ttUnsignedByte, 1};
  
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);
  
  EXPECT_FALSE(object.decoded());
  
  object.setDecoded(true);
  EXPECT_TRUE(object.decoded());
  
  object.setDecoded(false);
  EXPECT_FALSE(object.decoded());
}

// Test: TiffBinaryArray with ArraySet constructor has null cfg
TEST_F(TiffEncoderTestFixture_1677, TiffBinaryArray_ArraySetConstructor_NullCfg_1677) {
  TiffBinaryArray object(0x0001, IfdId::ifd0Id, nullptr, 0, nullptr);
  
  EXPECT_EQ(object.cfg(), nullptr);
  EXPECT_EQ(object.def(), nullptr);
  EXPECT_EQ(object.defSize(), 0u);
  EXPECT_FALSE(object.decoded());
}

// Test: byteOrder returns the header's byte order
TEST_F(TiffEncoderTestFixture_1677, ByteOrderReturnsHeaderByteOrder_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  // TiffHeader default byte order should be returned
  ByteOrder bo = encoder.byteOrder();
  EXPECT_TRUE(bo == littleEndian || bo == bigEndian);
}

// Test: writeMethod returns wmNonIntrusive by default
TEST_F(TiffEncoderTestFixture_1677, WriteMethodDefaultNonIntrusive_1677) {
  TiffHeader header;
  PrimaryGroups primaryGroups;
  
  TiffEncoder encoder(exifData_, iptcData_, xmpData_,
                      nullptr, false, std::move(primaryGroups),
                      &header, TiffMapping::findEncoder);
  
  EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

}  // namespace
