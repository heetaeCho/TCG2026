#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// We need access to the internal class
namespace Exiv2 {
namespace Internal {
class OlympusMakerNote {
public:
  std::ostream& print0x0201(std::ostream& os, const Value& value, const ExifData*);
};
}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class OlympusMakerNoteTest_900 : public ::testing::Test {
protected:
  OlympusMakerNote maker_;
  std::ostringstream os_;
};

// Helper to create a 6-byte unsigned byte value with specific bytes
static Value::UniquePtr makeUnsignedByteValue(std::initializer_list<uint8_t> bytes) {
  auto val = Value::create(unsignedByte);
  for (auto b : bytes) {
    val->read(reinterpret_cast<const byte*>(&b), 1, invalidByteOrder);
  }
  return val;
}

// Test: None lens type {0, 0, 0}
TEST_F(OlympusMakerNoteTest_900, LensTypeNone_900) {
  auto val = makeUnsignedByteValue({0, 0, 0, 0, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "None");
}

// Test: Known Olympus lens {0, 1, 0} -> "Olympus Zuiko Digital ED 50mm F2.0 Macro"
TEST_F(OlympusMakerNoteTest_900, LensTypeOlympus50mmMacro_900) {
  // v0=0, v2=1, v3=0 (indices 0, 2, 3 of the 6-byte value)
  auto val = makeUnsignedByteValue({0, 99, 1, 0, 99, 99});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Olympus Zuiko Digital ED 50mm F2.0 Macro");
}

// Test: Known Olympus lens {0, 1, 1} -> "Olympus Zuiko Digital 40-150mm F3.5-4.5"
TEST_F(OlympusMakerNoteTest_900, LensTypeOlympus40_150_900) {
  auto val = makeUnsignedByteValue({0, 0, 1, 1, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Olympus Zuiko Digital 40-150mm F3.5-4.5");
}

// Test: Known Olympus M.Zuiko {0, 1, 16} -> "Olympus M.Zuiko Digital ED 14-42mm F3.5-5.6"
TEST_F(OlympusMakerNoteTest_900, LensTypeMZuiko14_42_900) {
  auto val = makeUnsignedByteValue({0, 0, 1, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Olympus M.Zuiko Digital ED 14-42mm F3.5-5.6");
}

// Test: Sigma lens {1, 1, 0} -> "Sigma 18-50mm F3.5-5.6 DC"
TEST_F(OlympusMakerNoteTest_900, LensTypeSigma18_50_900) {
  auto val = makeUnsignedByteValue({1, 0, 1, 0, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Sigma 18-50mm F3.5-5.6 DC");
}

// Test: Leica lens {2, 1, 0} -> "Leica D Vario Elmarit 14-50mm F2.8-3.5 Asph."
TEST_F(OlympusMakerNoteTest_900, LensTypeLeica14_50_900) {
  auto val = makeUnsignedByteValue({2, 0, 1, 0, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Leica D Vario Elmarit 14-50mm F2.8-3.5 Asph.");
}

// Test: Lumix lens {2, 1, 16} -> "Lumix G Vario 14-45mm F3.5-5.6 Asph. Mega OIS"
TEST_F(OlympusMakerNoteTest_900, LensTypeLumix14_45_900) {
  auto val = makeUnsignedByteValue({2, 0, 1, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Lumix G Vario 14-45mm F3.5-5.6 Asph. Mega OIS");
}

// Test: Tamron lens {5, 1, 16} -> "Tamron 14-150mm F3.5-5.8 Di III"
TEST_F(OlympusMakerNoteTest_900, LensTypeTamron_900) {
  auto val = makeUnsignedByteValue({5, 0, 1, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Tamron 14-150mm F3.5-5.8 Di III");
}

// Test: Unknown lens type should return raw value
TEST_F(OlympusMakerNoteTest_900, UnknownLensType_900) {
  auto val = makeUnsignedByteValue({255, 0, 255, 255, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  // Should output the raw value since no match is found
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
  // It should not match any known lens label
  EXPECT_TRUE(result.find("Olympus") == std::string::npos);
  EXPECT_TRUE(result.find("Sigma") == std::string::npos);
  EXPECT_TRUE(result.find("Leica") == std::string::npos);
  EXPECT_TRUE(result.find("Lumix") == std::string::npos);
  EXPECT_TRUE(result.find("Tamron") == std::string::npos);
}

// Test: Wrong count (not 6) should return raw value
TEST_F(OlympusMakerNoteTest_900, WrongCount_900) {
  // Create value with only 3 bytes
  auto val = makeUnsignedByteValue({0, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  std::string result = os_.str();
  // Should output raw value, not "None"
  EXPECT_FALSE(result.empty());
}

// Test: Wrong type (not unsignedByte) should return raw value
TEST_F(OlympusMakerNoteTest_900, WrongType_900) {
  auto val = Value::create(unsignedShort);
  // Add some unsigned short values
  uint16_t data[] = {0, 0, 0};
  val->read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
  maker_.print0x0201(os_, *val, nullptr);
  std::string result = os_.str();
  EXPECT_FALSE(result.empty());
}

// Test: Empty value
TEST_F(OlympusMakerNoteTest_900, EmptyValue_900) {
  auto val = Value::create(unsignedByte);
  maker_.print0x0201(os_, *val, nullptr);
  std::string result = os_.str();
  // count is 0, not 6, so raw value is output
  // Empty value should still produce some output (possibly empty or "0")
}

// Test: Kenko lens {0, 16, 1} -> "Kenko Tokina Reflex 300mm F6.3 MF Macro"
TEST_F(OlympusMakerNoteTest_900, LensTypeKenko_900) {
  auto val = makeUnsignedByteValue({0, 0, 16, 1, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Kenko Tokina Reflex 300mm F6.3 MF Macro");
}

// Test: Value bytes at indices 1, 4, 5 (not used for lookup) don't affect result
TEST_F(OlympusMakerNoteTest_900, UnusedBytesIgnored_900) {
  // {0, X, 1, 0, X, X} should still match {0, 1, 0}
  auto val1 = makeUnsignedByteValue({0, 0, 1, 0, 0, 0});
  maker_.print0x0201(os_, *val1, nullptr);
  std::string result1 = os_.str();

  std::ostringstream os2;
  auto val2 = makeUnsignedByteValue({0, 42, 1, 0, 123, 255});
  maker_.print0x0201(os2, *val2, nullptr);
  std::string result2 = os2.str();

  EXPECT_EQ(result1, result2);
  EXPECT_EQ(result1, "Olympus Zuiko Digital ED 50mm F2.0 Macro");
}

// Test: Last entry in table {5, 1, 16}
TEST_F(OlympusMakerNoteTest_900, LastTableEntry_900) {
  auto val = makeUnsignedByteValue({5, 0, 1, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Tamron 14-150mm F3.5-5.8 Di III");
}

// Test: Olympus M.Zuiko Digital ED 25mm F1.2 Pro {0, 40, 16}
TEST_F(OlympusMakerNoteTest_900, LensTypeMZuiko25mmF12Pro_900) {
  auto val = makeUnsignedByteValue({0, 0, 40, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Olympus M.Zuiko Digital ED 25mm F1.2 Pro");
}

// Test: Sigma 50mm F1.4 EX DG HSM {1, 23, 0}
TEST_F(OlympusMakerNoteTest_900, LensTypeSigma50mmF14_900) {
  auto val = makeUnsignedByteValue({1, 0, 23, 0, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Sigma 50mm F1.4 EX DG HSM");
}

// Test: Leica DG Nocticron 42.5mm {2, 33, 16}
TEST_F(OlympusMakerNoteTest_900, LensTypeLeicaNocticron_900) {
  auto val = makeUnsignedByteValue({2, 0, 33, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Leica DG Nocticron 42.5mm F1.2 Asph. Power OIS");
}

// Test: Null ExifData pointer doesn't cause issues
TEST_F(OlympusMakerNoteTest_900, NullExifData_900) {
  auto val = makeUnsignedByteValue({0, 0, 0, 0, 0, 0});
  EXPECT_NO_THROW(maker_.print0x0201(os_, *val, nullptr));
  EXPECT_EQ(os_.str(), "None");
}

// Test: Value with exactly 6 bytes but all 255 (no match)
TEST_F(OlympusMakerNoteTest_900, AllMaxBytes_900) {
  auto val = makeUnsignedByteValue({255, 255, 255, 255, 255, 255});
  maker_.print0x0201(os_, *val, nullptr);
  std::string result = os_.str();
  // Should not match any known lens
  EXPECT_TRUE(result.find("None") == std::string::npos || result.find("255") != std::string::npos);
}

// Test: Sigma 30mm F1.4 DC DN | C {1, 6, 16}
TEST_F(OlympusMakerNoteTest_900, LensTypeSigma30mmDN_900) {
  auto val = makeUnsignedByteValue({1, 0, 6, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Sigma 30mm F1.4 DC DN | C");
}

// Test: Olympus M.Zuiko Digital ED 12-45mm F4.0 Pro {0, 52, 16}
TEST_F(OlympusMakerNoteTest_900, LensTypeMZuiko12_45Pro_900) {
  auto val = makeUnsignedByteValue({0, 0, 52, 16, 0, 0});
  maker_.print0x0201(os_, *val, nullptr);
  EXPECT_EQ(os_.str(), "Olympus M.Zuiko Digital ED 12-45mm F4.0 Pro");
}

// Test: Multiple calls to print0x0201 append to the stream
TEST_F(OlympusMakerNoteTest_900, MultipleCallsAppend_900) {
  auto val1 = makeUnsignedByteValue({0, 0, 0, 0, 0, 0});
  maker_.print0x0201(os_, *val1, nullptr);
  auto val2 = makeUnsignedByteValue({0, 0, 0, 0, 0, 0});
  maker_.print0x0201(os_, *val2, nullptr);
  EXPECT_EQ(os_.str(), "NoneNone");
}
