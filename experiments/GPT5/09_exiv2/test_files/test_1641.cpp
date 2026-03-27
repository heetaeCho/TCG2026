// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tiffcopier_copyobject_1641.cpp
//
// Unit tests for Exiv2::Internal::TiffCopier::copyObject
// The TEST_ID is 1641

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using ::testing::_;
using ::testing::Return;

namespace Exiv2::Internal {
namespace {

// Mock for external collaborator: TiffHeaderBase::isImageTag
class MockTiffHeader : public TiffHeaderBase {
 public:
  MockTiffHeader(uint16_t tag, uint32_t size, ByteOrder bo, uint32_t offset)
      : TiffHeaderBase(tag, size, bo, offset) {}

  MOCK_METHOD(bool, isImageTag, (uint16_t tag, IfdId group, const PrimaryGroups& primaryGroups), (const, override));
};

// Root component that records addPath interactions via doAddPath().
class RecordingRootComponent final : public TiffComponent {
 public:
  RecordingRootComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

  struct AddPathCall {
    uint16_t tag = 0;
    TiffComponent* pRoot = nullptr;
    bool objectWasNull = true;
    uint16_t objectTag = 0;
    IfdId objectGroup{};
  };

  int addPathCallCount() const { return addPathCallCount_; }
  const AddPathCall& lastAddPathCall() const { return lastCall_; }

 protected:
  TiffComponent* doAddPath(uint16_t tag, TiffPath& /*tiffPath*/, TiffComponent* pRoot, UniquePtr object) override {
    ++addPathCallCount_;
    lastCall_.tag = tag;
    lastCall_.pRoot = pRoot;
    lastCall_.objectWasNull = (object.get() == nullptr);
    if (object) {
      lastCall_.objectTag = object->tag();
      lastCall_.objectGroup = object->group();
    }
    // Behave like a simple sink: don't build a full tree here.
    return this;
  }

 private:
  int addPathCallCount_{0};
  AddPathCall lastCall_{};
};

// Component whose clone behavior we can control via doClone().
class CloneableComponent final : public TiffComponent {
 public:
  enum class CloneMode { kReturnValidClone, kReturnNull };

  CloneableComponent(uint16_t tag, IfdId group, CloneMode mode)
      : TiffComponent(tag, group), mode_(mode) {}

 protected:
  const TiffComponent* doClone() override {
    if (mode_ == CloneMode::kReturnNull) {
      return nullptr;
    }
    // Return a new object with the same observable (tag, group).
    return new CloneableComponent(this->tag(), this->group(), CloneMode::kReturnNull);
  }

 private:
  CloneMode mode_;
};

class TiffCopierTest_1641 : public ::testing::Test {
 protected:
  // Choose arbitrary values; behavior is asserted only via observable interactions.
  static constexpr uint16_t kRootTag = 0x0001;

  // NOTE: IfdId is an Exiv2 type; we avoid assuming specific enumerators exist.
  // We use value-initialization where possible.
  static IfdId AnyGroup() { return IfdId{}; }

  RecordingRootComponent root_{kRootTag, AnyGroup()};
  MockTiffHeader header_{/*tag=*/0, /*size=*/0, /*byteOrder=*/littleEndian, /*offset=*/0};

  // PrimaryGroups is an Exiv2 type; default construction is sufficient for these tests.
  PrimaryGroups primaryGroups_{};

  // Root ID passed to TiffCreator::getPath; value not asserted directly.
  uint32_t rootId_{0};
};

TEST_F(TiffCopierTest_1641, CopiesObjectAndAddsPathWhenHeaderSaysImageTag_1641) {
  const uint16_t objTag = 0x0102;
  const IfdId objGroup = AnyGroup();

  CloneableComponent obj{objTag, objGroup, CloneableComponent::CloneMode::kReturnValidClone};

  EXPECT_CALL(header_, isImageTag(objTag, objGroup, _)).WillOnce(Return(true));

  TiffCopier copier(&root_, rootId_, &header_, primaryGroups_);
  copier.copyObject(&obj);

  EXPECT_EQ(root_.addPathCallCount(), 1);
  EXPECT_EQ(root_.lastAddPathCall().tag, objTag);
  EXPECT_EQ(root_.lastAddPathCall().pRoot, &root_);
  EXPECT_FALSE(root_.lastAddPathCall().objectWasNull);
  EXPECT_EQ(root_.lastAddPathCall().objectTag, objTag);
  EXPECT_EQ(root_.lastAddPathCall().objectGroup, objGroup);
}

TEST_F(TiffCopierTest_1641, DoesNotAddPathWhenHeaderSaysNotImageTag_1641) {
  const uint16_t objTag = 0x00FF;
  const IfdId objGroup = AnyGroup();

  CloneableComponent obj{objTag, objGroup, CloneableComponent::CloneMode::kReturnValidClone};

  EXPECT_CALL(header_, isImageTag(objTag, objGroup, _)).WillOnce(Return(false));

  TiffCopier copier(&root_, rootId_, &header_, primaryGroups_);
  copier.copyObject(&obj);

  EXPECT_EQ(root_.addPathCallCount(), 0);
}

TEST_F(TiffCopierTest_1641, AddsPathEvenIfCloneReturnsNullWhenHeaderSaysImageTag_1641) {
  const uint16_t objTag = 0x0A0B;
  const IfdId objGroup = AnyGroup();

  CloneableComponent obj{objTag, objGroup, CloneableComponent::CloneMode::kReturnNull};

  EXPECT_CALL(header_, isImageTag(objTag, objGroup, _)).WillOnce(Return(true));

  TiffCopier copier(&root_, rootId_, &header_, primaryGroups_);
  copier.copyObject(&obj);

  EXPECT_EQ(root_.addPathCallCount(), 1);
  EXPECT_EQ(root_.lastAddPathCall().tag, objTag);
  EXPECT_EQ(root_.lastAddPathCall().pRoot, &root_);
  EXPECT_TRUE(root_.lastAddPathCall().objectWasNull);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(TiffCopierTest_1641, DeathOnNullObjectPointer_1641) {
  // Boundary/exceptional case: current implementation dereferences object.
  // This test documents that passing nullptr is not supported (observable via process death).
  TiffCopier copier(&root_, rootId_, &header_, primaryGroups_);
  EXPECT_DEATH({ copier.copyObject(nullptr); }, ".*");
}
#endif

}  // namespace
}  // namespace Exiv2::Internal