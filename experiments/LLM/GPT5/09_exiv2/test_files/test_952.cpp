// =================================================================================================
// TEST_ID: 952
// File: test_canonmn_int_printLe0x0000_952.cpp
//
// Unit tests for Exiv2::Internal::CanonMakerNote::printLe0x0000
// Constraints:
//  - Treat implementation as black box: test only observable behavior via public interface.
//  - No private state access.
//  - No re-implementation of logic beyond what is observable through the interface contract.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// Exiv2 headers (adjust include paths to match your test environment)
#include "canonmn_int.hpp"
#include "exif.hpp"
#include "value.hpp"

namespace {

// Helper to build an Exiv2::Value that is an unsignedByte array of given bytes.
// We use the public Value API only.
static Exiv2::Value::UniquePtr MakeUByteValue(const std::vector<uint8_t>& bytes) {
  auto v = Exiv2::Value::create(Exiv2::unsignedByte);
  // Value::read expects raw bytes for unsignedByte values.
  if (!bytes.empty()) {
    v->read(reinterpret_cast<const Exiv2::byte*>(bytes.data()),
            static_cast<long>(bytes.size()),
            Exiv2::invalidByteOrder);
  } else {
    // Read zero bytes to create an empty value of the right type.
    v->read(nullptr, 0, Exiv2::invalidByteOrder);
  }
  return v;
}

// Helper to build a Value of a different type (e.g., asciiString).
static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  v->read(s);
  return v;
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Fixture
// -------------------------------------------------------------------------------------------------
class CanonMakerNotePrintLe0x0000Test_952 : public ::testing::Test {
 protected:
  Exiv2::Internal::CanonMakerNote uut_;
};

// -------------------------------------------------------------------------------------------------
// Normal operation: correct type + correct size(5) => prints 10 lowercase hex digits (2 per byte).
// -------------------------------------------------------------------------------------------------
TEST_F(CanonMakerNotePrintLe0x0000Test_952, PrintsHexForFiveUnsignedBytes_952) {
  const std::vector<uint8_t> bytes = {0x00, 0x01, 0x0a, 0x10, 0xff};
  auto v = MakeUByteValue(bytes);

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  EXPECT_EQ(os.str(), "00010a10ff");
}

// Boundary-ish values: ensure leading zeros are present and values > 0x7f still render as hex bytes.
TEST_F(CanonMakerNotePrintLe0x0000Test_952, PrintsLeadingZerosAndHighBytes_952) {
  const std::vector<uint8_t> bytes = {0x05, 0x80, 0x09, 0x00, 0x7f};
  auto v = MakeUByteValue(bytes);

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  EXPECT_EQ(os.str(), "058009007f");
}

// -------------------------------------------------------------------------------------------------
// Error/exceptional observable cases: wrong type OR wrong size => prints "(" << value << ")"
// We do not assume the exact internal formatting of Value streaming beyond that it is enclosed.
// -------------------------------------------------------------------------------------------------
TEST_F(CanonMakerNotePrintLe0x0000Test_952, WrongTypePrintsParenthesizedValue_952) {
  auto v = MakeAsciiValue("abcde");  // wrong type (asciiString), size doesn't matter.

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

// Size boundary: correct type but size != 5 (e.g., 0) => parenthesized value.
TEST_F(CanonMakerNotePrintLe0x0000Test_952, UnsignedByteSizeZeroPrintsParenthesizedValue_952) {
  auto v = MakeUByteValue({});  // size 0

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

// Size boundary: correct type but size != 5 (e.g., 4) => parenthesized value.
TEST_F(CanonMakerNotePrintLe0x0000Test_952, UnsignedByteSizeFourPrintsParenthesizedValue_952) {
  auto v = MakeUByteValue({0x01, 0x02, 0x03, 0x04});  // size 4

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

// Size boundary: correct type but size != 5 (e.g., 6) => parenthesized value.
TEST_F(CanonMakerNotePrintLe0x0000Test_952, UnsignedByteSizeSixPrintsParenthesizedValue_952) {
  auto v = MakeUByteValue({0x01, 0x02, 0x03, 0x04, 0x05, 0x06});  // size 6

  std::ostringstream os;
  uut_.printLe0x0000(os, *v, nullptr);

  const std::string out = os.str();
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

// -------------------------------------------------------------------------------------------------
// API behavior: returns the same ostream reference (chainable).
// -------------------------------------------------------------------------------------------------
TEST_F(CanonMakerNotePrintLe0x0000Test_952, ReturnsSameOstreamReference_952) {
  auto v = MakeUByteValue({0x00, 0x00, 0x00, 0x00, 0x00});

  std::ostringstream os;
  std::ostream& ret = uut_.printLe0x0000(os, *v, nullptr);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
}