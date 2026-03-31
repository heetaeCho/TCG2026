#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "types.hpp"

// We need to include enough headers to construct the objects
// Since we're testing TiffReader and TiffRwState, we need their full definitions

namespace Exiv2 {
namespace Internal {

// Test fixture for TiffReader tests
class TiffReaderTest_1692 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Minimal data buffer for TiffReader
    data_[0] = 0;
    data_[1] = 0;
  }

  byte data_[64] = {};
};

// Test TiffRwState construction and accessors
TEST(TiffRwStateTest_1692, ConstructWithLittleEndian_1692) {
  TiffRwState state(littleEndian, 0);
  EXPECT_EQ(state.byteOrder(), littleEndian);
  EXPECT_EQ(state.baseOffset(), 0u);
}

TEST(TiffRwStateTest_1692, ConstructWithBigEndian_1692) {
  TiffRwState state(bigEndian, 100);
  EXPECT_EQ(state.byteOrder(), bigEndian);
  EXPECT_EQ(state.baseOffset(), 100u);
}

TEST(TiffRwStateTest_1692, ConstructWithInvalidByteOrder_1692) {
  TiffRwState state(invalidByteOrder, 42);
  EXPECT_EQ(state.byteOrder(), invalidByteOrder);
  EXPECT_EQ(state.baseOffset(), 42u);
}

TEST(TiffRwStateTest_1692, ConstructWithZeroBaseOffset_1692) {
  TiffRwState state(littleEndian, 0);
  EXPECT_EQ(state.baseOffset(), 0u);
}

TEST(TiffRwStateTest_1692, ConstructWithLargeBaseOffset_1692) {
  TiffRwState state(bigEndian, 1000000);
  EXPECT_EQ(state.byteOrder(), bigEndian);
  EXPECT_EQ(state.baseOffset(), 1000000u);
}

// Test TiffReader construction and initial state
TEST_F(TiffReaderTest_1692, ConstructorSetsInitialByteOrder_1692) {
  TiffRwState state(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);
  EXPECT_EQ(reader.byteOrder(), littleEndian);
}

TEST_F(TiffReaderTest_1692, ConstructorSetsInitialBaseOffset_1692) {
  TiffRwState state(bigEndian, 42);
  TiffReader reader(data_, sizeof(data_), nullptr, state);
  EXPECT_EQ(reader.baseOffset(), 42u);
}

TEST_F(TiffReaderTest_1692, ConstructorWithBigEndian_1692) {
  TiffRwState state(bigEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test setMnState with valid state that has a valid byte order
TEST_F(TiffReaderTest_1692, SetMnStateWithValidByteOrder_1692) {
  TiffRwState origState(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState(bigEndian, 100);
  reader.setMnState(&mnState);

  // After setMnState with valid byte order, should use the provided state
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 100u);
}

// Test setMnState with invalidByteOrder - should use origState's byte order
TEST_F(TiffReaderTest_1692, SetMnStateWithInvalidByteOrderUsesOrigByteOrder_1692) {
  TiffRwState origState(littleEndian, 10);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState(invalidByteOrder, 200);
  reader.setMnState(&mnState);

  // When state has invalidByteOrder, should use origState's byteOrder
  EXPECT_EQ(reader.byteOrder(), littleEndian);
  // But should use the provided baseOffset
  EXPECT_EQ(reader.baseOffset(), 200u);
}

// Test setMnState with nullptr - should not change state
TEST_F(TiffReaderTest_1692, SetMnStateWithNullptr_1692) {
  TiffRwState origState(littleEndian, 5);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  // Set a different mn state first
  TiffRwState mnState(bigEndian, 50);
  reader.setMnState(&mnState);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 50u);

  // Now call with nullptr - pState_ should still point to mnState_
  // but mnState_ should not be modified
  reader.setMnState(nullptr);
  // The behavior here depends on implementation; pState_ won't be updated
  // since state is null, so it should still point to mnState_ with previous values
  // But actually looking at the code, when nullptr is passed, nothing happens
  // so previous state should remain
}

// Test setOrigState restores original state
TEST_F(TiffReaderTest_1692, SetOrigStateRestoresOriginalByteOrder_1692) {
  TiffRwState origState(littleEndian, 10);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  // Change to mnState
  TiffRwState mnState(bigEndian, 100);
  reader.setMnState(&mnState);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 100u);

  // Restore original state
  reader.setOrigState();
  EXPECT_EQ(reader.byteOrder(), littleEndian);
  EXPECT_EQ(reader.baseOffset(), 10u);
}

// Test setMnState followed by setOrigState multiple times
TEST_F(TiffReaderTest_1692, AlternatingMnAndOrigState_1692) {
  TiffRwState origState(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState1(bigEndian, 50);
  reader.setMnState(&mnState1);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 50u);

  reader.setOrigState();
  EXPECT_EQ(reader.byteOrder(), littleEndian);
  EXPECT_EQ(reader.baseOffset(), 0u);

  TiffRwState mnState2(bigEndian, 75);
  reader.setMnState(&mnState2);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 75u);

  reader.setOrigState();
  EXPECT_EQ(reader.byteOrder(), littleEndian);
  EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test setMnState with invalidByteOrder preserves orig byte order but updates base offset
TEST_F(TiffReaderTest_1692, SetMnStateInvalidByteOrderPreservesOrigAndUpdatesOffset_1692) {
  TiffRwState origState(bigEndian, 20);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState(invalidByteOrder, 300);
  reader.setMnState(&mnState);

  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 300u);
}

// Test multiple setMnState calls overwrite previous mn state
TEST_F(TiffReaderTest_1692, MultipleSetMnStateCalls_1692) {
  TiffRwState origState(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState1(bigEndian, 10);
  reader.setMnState(&mnState1);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 10u);

  TiffRwState mnState2(littleEndian, 20);
  reader.setMnState(&mnState2);
  EXPECT_EQ(reader.byteOrder(), littleEndian);
  EXPECT_EQ(reader.baseOffset(), 20u);
}

// Test byteOrder after construction matches initial state
TEST_F(TiffReaderTest_1692, ByteOrderMatchesInitialState_1692) {
  TiffRwState state(bigEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
}

// Test baseOffset after construction matches initial state
TEST_F(TiffReaderTest_1692, BaseOffsetMatchesInitialState_1692) {
  TiffRwState state(littleEndian, 999);
  TiffReader reader(data_, sizeof(data_), nullptr, state);
  EXPECT_EQ(reader.baseOffset(), 999u);
}

// Test setMnState with zero base offset
TEST_F(TiffReaderTest_1692, SetMnStateWithZeroBaseOffset_1692) {
  TiffRwState origState(littleEndian, 50);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  TiffRwState mnState(bigEndian, 0);
  reader.setMnState(&mnState);
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 0u);
}

// Test setOrigState called without prior setMnState
TEST_F(TiffReaderTest_1692, SetOrigStateWithoutPriorMnState_1692) {
  TiffRwState origState(bigEndian, 15);
  TiffReader reader(data_, sizeof(data_), nullptr, origState);

  // Call setOrigState right away - should still be in original state
  reader.setOrigState();
  EXPECT_EQ(reader.byteOrder(), bigEndian);
  EXPECT_EQ(reader.baseOffset(), 15u);
}

// Test circularReference with first call - should not be circular
TEST_F(TiffReaderTest_1692, CircularReferenceFirstCallReturnsFalse_1692) {
  TiffRwState state(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);

  // First call with a start pointer and group should not be circular
  bool result = reader.circularReference(data_, IfdId::ifd0Id);
  EXPECT_FALSE(result);
}

// Test circularReference with same start and group twice - should be circular
TEST_F(TiffReaderTest_1692, CircularReferenceSameCallTwiceReturnsTrue_1692) {
  TiffRwState state(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);

  reader.circularReference(data_, IfdId::ifd0Id);
  bool result = reader.circularReference(data_, IfdId::ifd0Id);
  EXPECT_TRUE(result);
}

// Test nextIdx returns incrementing values for same group
TEST_F(TiffReaderTest_1692, NextIdxReturnsIncrementingValues_1692) {
  TiffRwState state(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);

  int idx1 = reader.nextIdx(IfdId::ifd0Id);
  int idx2 = reader.nextIdx(IfdId::ifd0Id);
  EXPECT_EQ(idx2, idx1 + 1);
}

// Test nextIdx for different groups
TEST_F(TiffReaderTest_1692, NextIdxDifferentGroupsIndependent_1692) {
  TiffRwState state(littleEndian, 0);
  TiffReader reader(data_, sizeof(data_), nullptr, state);

  int idx1 = reader.nextIdx(IfdId::ifd0Id);
  int idx2 = reader.nextIdx(IfdId::ifd1Id);
  // Both should start from the same initial value
  EXPECT_EQ(idx1, idx2);
}

}  // namespace Internal
}  // namespace Exiv2
