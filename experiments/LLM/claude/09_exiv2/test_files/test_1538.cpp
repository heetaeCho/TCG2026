#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"
#include "exiv2/exiv2.hpp"

#include <cstring>

namespace {

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a TiffComponent tree with a specific camera model string
// embedded in the Exif.Image.Model tag (tag 0x0110 in IFD0).
class SonyCsSelectorTest_1538 : public ::testing::Test {
 protected:
  // Build a minimal TIFF tree that contains the Model tag (0x0110) in IFD0
  // so that getExifModel can find it.
  static TiffComponent* buildRootWithModel(const std::string& model) {
    // We create a minimal Exif structure. The root group is ifd0 (Group::ifd0).
    // Tag 0x0110 is the Model tag.

    // Create root directory
    auto* root = new TiffDirectory(0, Group::ifd0);

    // Create a TiffEntryBase for tag 0x0110 (Model)
    auto* entry = new TiffEntry(0x0110, Group::ifd0);

    // Set the value - Model is an Ascii value
    Value::UniquePtr val = Value::create(asciiString);
    val->read(model);
    entry->setData(std::move(val));

    // Add entry to root
    root->addChild(std::move(std::unique_ptr<TiffComponent>(entry)));

    return root;
  }
};

// Test: When pRoot is nullptr (no model can be extracted), should return -1
TEST_F(SonyCsSelectorTest_1538, ReturnsNegativeOneWhenRootIsNull_1538) {
  int result = sonyCsSelector(0, nullptr, 0, nullptr);
  EXPECT_EQ(-1, result);
}

// Test: When model is a non-matching Sony model, should return 0
TEST_F(SonyCsSelectorTest_1538, ReturnsZeroForNonMatchingModel_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A700");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(0, result);
  delete root;
}

// Test: When model contains "DSLR-A330", should return 1
TEST_F(SonyCsSelectorTest_1538, ReturnsOneForDSLR_A330_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A330");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(1, result);
  delete root;
}

// Test: When model contains "DSLR-A380", should return 1
TEST_F(SonyCsSelectorTest_1538, ReturnsOneForDSLR_A380_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A380");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(1, result);
  delete root;
}

// Test: When model contains "DSLR-A330" as substring, should return 1
TEST_F(SonyCsSelectorTest_1538, ReturnsOneForModelContainingA330Substring_1538) {
  TiffComponent* root = buildRootWithModel("Sony DSLR-A330 Body");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(1, result);
  delete root;
}

// Test: When model contains "DSLR-A380" as substring, should return 1
TEST_F(SonyCsSelectorTest_1538, ReturnsOneForModelContainingA380Substring_1538) {
  TiffComponent* root = buildRootWithModel("Sony DSLR-A380 Body");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(1, result);
  delete root;
}

// Test: Another non-matching Sony model returns 0
TEST_F(SonyCsSelectorTest_1538, ReturnsZeroForDSLR_A100_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A100");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(0, result);
  delete root;
}

// Test: Tag and data parameters are ignored - verify with different tag values
TEST_F(SonyCsSelectorTest_1538, TagAndDataParametersAreIgnored_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A330");
  byte data[] = {0x01, 0x02, 0x03, 0x04};

  int result1 = sonyCsSelector(0, data, sizeof(data), root);
  int result2 = sonyCsSelector(0xFFFF, data, sizeof(data), root);
  int result3 = sonyCsSelector(42, nullptr, 0, root);

  EXPECT_EQ(1, result1);
  EXPECT_EQ(1, result2);
  EXPECT_EQ(1, result3);

  delete root;
}

// Test: Empty model string returns -1
TEST_F(SonyCsSelectorTest_1538, ReturnsNegativeOneForEmptyModel_1538) {
  // When model is empty, function should return -1
  // An empty model scenario occurs when the root tree has no Model tag
  TiffComponent* root = new TiffDirectory(0, Group::ifd0);
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(-1, result);
  delete root;
}

// Test: A completely different brand model returns 0
TEST_F(SonyCsSelectorTest_1538, ReturnsZeroForNonSonyModel_1538) {
  TiffComponent* root = buildRootWithModel("Canon EOS 5D Mark III");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(0, result);
  delete root;
}

// Test: Case sensitivity - "dslr-a330" should not match "DSLR-A330"
TEST_F(SonyCsSelectorTest_1538, CaseSensitiveModelMatching_1538) {
  TiffComponent* root = buildRootWithModel("dslr-a330");
  int result = sonyCsSelector(0, nullptr, 0, root);
  // contains is typically case-sensitive, so lowercase should not match
  EXPECT_EQ(0, result);
  delete root;
}

// Test: Partial match should not trigger - "DSLR-A33" is not "DSLR-A330"
TEST_F(SonyCsSelectorTest_1538, PartialMatchDoesNotReturnOne_1538) {
  TiffComponent* root = buildRootWithModel("DSLR-A33");
  int result = sonyCsSelector(0, nullptr, 0, root);
  EXPECT_EQ(0, result);
  delete root;
}

}  // namespace
