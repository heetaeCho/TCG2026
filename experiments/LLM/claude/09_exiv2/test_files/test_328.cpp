#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "exiv2/error.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffSubIfd tests
class TiffSubIfdTest_328 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create a TiffSubIfd instance for testing
    // Using reasonable default values for tag, group, and newGroup
    subIfd_ = std::make_unique<TiffSubIfd>(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  }

  std::unique_ptr<TiffSubIfd> subIfd_;
};

// Test that adding a valid TiffDirectory child succeeds and returns non-null
TEST_F(TiffSubIfdTest_328, AddChildWithValidTiffDirectory_ReturnsNonNull_328) {
  auto dir = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
  TiffComponent* result = subIfd_->addChild(std::move(dir));
  ASSERT_NE(result, nullptr);
}

// Test that adding a null shared_ptr (cast to TiffComponent::SharedPtr) that cannot be
// dynamic_cast to TiffDirectory throws an error
TEST_F(TiffSubIfdTest_328, AddChildWithNonTiffDirectory_ThrowsError_328) {
  // Create a TiffComponent that is NOT a TiffDirectory
  // TiffEntry is a TiffComponent but not a TiffDirectory
  auto entry = std::make_shared<TiffEntry>(0x0100, IfdId::ifd0Id);
  TiffComponent::SharedPtr component = std::static_pointer_cast<TiffComponent>(entry);
  
  EXPECT_THROW(subIfd_->addChild(std::move(component)), Exiv2::Error);
}

// Test that adding multiple TiffDirectory children all succeed
TEST_F(TiffSubIfdTest_328, AddMultipleChildren_AllReturnNonNull_328) {
  auto dir1 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
  auto dir2 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage2Id);
  auto dir3 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage3Id);

  TiffComponent* result1 = subIfd_->addChild(std::move(dir1));
  TiffComponent* result2 = subIfd_->addChild(std::move(dir2));
  TiffComponent* result3 = subIfd_->addChild(std::move(dir3));

  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  ASSERT_NE(result3, nullptr);
}

// Test that each added child returns a different pointer (they are distinct entries)
TEST_F(TiffSubIfdTest_328, AddMultipleChildren_ReturnDistinctPointers_328) {
  auto dir1 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
  auto dir2 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage2Id);

  TiffComponent* result1 = subIfd_->addChild(std::move(dir1));
  TiffComponent* result2 = subIfd_->addChild(std::move(dir2));

  EXPECT_NE(result1, result2);
}

// Test that the error thrown when adding a non-TiffDirectory has the correct error code
TEST_F(TiffSubIfdTest_328, AddChildWithNonTiffDirectory_ThrowsCorrectErrorCode_328) {
  auto entry = std::make_shared<TiffEntry>(0x0100, IfdId::ifd0Id);
  TiffComponent::SharedPtr component = std::static_pointer_cast<TiffComponent>(entry);

  try {
    subIfd_->addChild(std::move(component));
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), ErrorCode::kerErrorMessage);
  }
}

// Test construction with different parameters
TEST_F(TiffSubIfdTest_328, ConstructWithDifferentParams_328) {
  TiffSubIfd subIfd(0x8769, IfdId::ifd0Id, IfdId::exifId);
  auto dir = std::make_shared<TiffDirectory>(0x8769, IfdId::exifId);
  TiffComponent* result = subIfd.addChild(std::move(dir));
  ASSERT_NE(result, nullptr);
}

// Test that the returned pointer from addChild points to a valid TiffDirectory
TEST_F(TiffSubIfdTest_328, AddChild_ReturnedPointerIsValid_328) {
  auto dir = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
  TiffComponent* result = subIfd_->addChild(std::move(dir));
  
  // The returned pointer should be usable - we can at least verify it's not null
  // and that its tag matches
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->tag(), 0x014a);
}

// Test that adding a nullptr shared_ptr throws (dynamic_pointer_cast of null returns null)
TEST_F(TiffSubIfdTest_328, AddChildWithNullptr_ThrowsError_328) {
  TiffComponent::SharedPtr nullComponent;
  EXPECT_THROW(subIfd_->addChild(std::move(nullComponent)), Exiv2::Error);
}
