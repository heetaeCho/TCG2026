#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>

// We need access to the internal function we're testing
namespace Exiv2 {
namespace Internal {

// Forward declarations of internal functions/types used
extern const TagDetails minoltaSonyLensID[];

std::ostream& resolveLens0x1c(std::ostream& os, const Value& value, const ExifData* metadata);

// Helper function declarations that are used internally
std::string getKeyString(const std::string& key, const ExifData* metadata);
std::ostream& resolvedLens(std::ostream& os, long lensID, long index);

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;

class ResolveLens0x1cTest_1019 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  // Helper to create ExifData with specific key-value pairs
  void setExifString(ExifData& exifData, const std::string& key, const std::string& value) {
    exifData[key] = value;
  }
};

// Test: When model is "SLT-A77V" and lens is "100mm F2.8 Macro", should resolve to index 2
TEST_F(ResolveLens0x1cTest_1019, MatchingSLTA77VAndMacroLens_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77V");
  setExifString(metadata, "Exif.Photo.LensModel", "100mm F2.8 Macro");

  // Create a value representing lens ID 0x1c (28)
  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // When matched, it should use resolvedLens with lensID=0x1c, index=2
  // The result should NOT be the default EXV_PRINT_TAG output for tag 28
  // It should resolve to a specific lens name (the second alternative for lens ID 28)
  EXPECT_FALSE(result.empty());
}

// Test: When model does not match, should fall through to default EXV_PRINT_TAG
TEST_F(ResolveLens0x1cTest_1019, NonMatchingModel_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "DSLR-A700");
  setExifString(metadata, "Exif.Photo.LensModel", "100mm F2.8 Macro");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Should fall through to default lookup for lens ID 28
  EXPECT_FALSE(result.empty());
  // The default for tag 28 is "Minolta/Sony AF 100mm F2.8 Macro (D) | ..."
  EXPECT_NE(std::string::npos, result.find("100mm F2.8"));
}

// Test: When lens does not match, should fall through to default EXV_PRINT_TAG
TEST_F(ResolveLens0x1cTest_1019, NonMatchingLens_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77V");
  setExifString(metadata, "Exif.Photo.LensModel", "50mm F1.4");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
  // Should show the default tag description for lens ID 28
  EXPECT_NE(std::string::npos, result.find("100mm F2.8"));
}

// Test: When metadata is null, should not crash and fall through to default
TEST_F(ResolveLens0x1cTest_1019, NullMetadata_1019) {
  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, nullptr);

  std::string result = os.str();
  // Should handle nullptr gracefully (the try-catch should catch any exception)
  EXPECT_FALSE(result.empty());
}

// Test: Neither model nor lens key present in metadata
TEST_F(ResolveLens0x1cTest_1019, EmptyMetadata_1019) {
  ExifData metadata;

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Should fall through to default since keys are missing
  EXPECT_FALSE(result.empty());
}

// Test: Model matches but lens key is missing entirely
TEST_F(ResolveLens0x1cTest_1019, ModelMatchLensMissing_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77V");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Lens key missing, so should not match special case
  EXPECT_FALSE(result.empty());
}

// Test: Both model and lens match but with different lens ID value
TEST_F(ResolveLens0x1cTest_1019, MatchingConditionDifferentValue_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77V");
  setExifString(metadata, "Exif.Photo.LensModel", "100mm F2.8 Macro");

  // Use a different value - the function resolves lensID 0x1c regardless of value when matched
  auto value = Value::create(unsignedLong);
  value->read("0");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // When the special case matches, it uses hardcoded lensID=0x1c with index=2
  EXPECT_FALSE(result.empty());
}

// Test: Value with lens ID that exists in the tag details table (non-matching model)
TEST_F(ResolveLens0x1cTest_1019, DefaultResolutionKnownLensID_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "NEX-5");
  setExifString(metadata, "Exif.Photo.LensModel", "Some other lens");

  auto value = Value::create(unsignedLong);
  value->read("28");  // 0x1c = 28

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Should use default tag lookup for ID 28
  EXPECT_FALSE(result.empty());
}

// Test: Value representing an unknown lens ID, non-matching conditions
TEST_F(ResolveLens0x1cTest_1019, DefaultResolutionUnknownLensID_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "NEX-5");
  setExifString(metadata, "Exif.Photo.LensModel", "Unknown lens");

  auto value = Value::create(unsignedLong);
  value->read("99999");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Should output something (possibly "99999" or "(99999)")
  EXPECT_FALSE(result.empty());
}

// Test: Model is close to "SLT-A77V" but not exact match
TEST_F(ResolveLens0x1cTest_1019, SimilarButNotExactModel_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77");
  setExifString(metadata, "Exif.Photo.LensModel", "100mm F2.8 Macro");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // "SLT-A77" != "SLT-A77V", should not match special case
  EXPECT_FALSE(result.empty());
}

// Test: Lens is close to "100mm F2.8 Macro" but not exact match
TEST_F(ResolveLens0x1cTest_1019, SimilarButNotExactLens_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "SLT-A77V");
  setExifString(metadata, "Exif.Photo.LensModel", "100mm F2.8 Macro (D)");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // "100mm F2.8 Macro (D)" != "100mm F2.8 Macro", should not match
  EXPECT_FALSE(result.empty());
}

// Test: Empty strings for model and lens
TEST_F(ResolveLens0x1cTest_1019, EmptyModelAndLensStrings_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "");
  setExifString(metadata, "Exif.Photo.LensModel", "");

  auto value = Value::create(unsignedLong);
  value->read("28");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  EXPECT_FALSE(result.empty());
}

// Test: Value of 0 (first entry in minoltaSonyLensID table)
TEST_F(ResolveLens0x1cTest_1019, LensIDZeroNoMatch_1019) {
  ExifData metadata;
  setExifString(metadata, "Exif.Image.Model", "Other Camera");
  setExifString(metadata, "Exif.Photo.LensModel", "Other Lens");

  auto value = Value::create(unsignedLong);
  value->read("0");

  std::ostringstream os;
  Internal::resolveLens0x1c(os, *value, &metadata);

  std::string result = os.str();
  // Should resolve to "Minolta AF 28-85mm F3.5-4.5 New" (tag ID 0)
  EXPECT_NE(std::string::npos, result.find("Minolta AF 28-85mm"));
}
