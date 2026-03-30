// TEST_ID 962
// Unit tests for Exiv2::Internal::CanonMakerNote::printSi0x0016
//
// Constraints respected:
// - Treat implementation as a black box (no internal logic re-implementation assertions beyond observable output).
// - Only use public/observable behavior (stream output).
// - No private state access.

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Exiv2 headers (adjust include paths to match your build layout)
#include "canonmn_int.hpp"   // for Exiv2::Internal::CanonMakerNote
#include "value.hpp"         // for Exiv2::Value / type ids
#include "types.hpp"         // for Exiv2 type ids (unsignedShort, etc.)

namespace {

using Exiv2::Internal::CanonMakerNote;

// Helper: render Value via operator<< (used to compare early-return behavior)
static std::string ValueToString(const Exiv2::Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

// Helper: call printSi0x0016 and return resulting stream string
static std::string PrintSi0016ToString(CanonMakerNote& mn, const Exiv2::Value& v) {
  std::ostringstream oss;
  mn.printSi0x0016(oss, v, nullptr);
  return oss.str();
}

}  // namespace

// TEST_ID 962
TEST(CanonMakerNoteTest_962, ReturnsValueStreamedWhenTypeIsNotUnsignedShort_962) {
  CanonMakerNote mn;

  // Use a clearly non-unsignedShort Value type: unsignedByte.
  // (Any non-unsignedShort should take the early-return path.)
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
  ASSERT_TRUE(v.get() != nullptr);

  // Boundary: also ensure it has at least one element; early-return should be by type.
  v->read("1");

  const std::string expected = ValueToString(*v);
  const std::string actual = PrintSi0016ToString(mn, *v);

  EXPECT_EQ(actual, expected);
}

// TEST_ID 962
TEST(CanonMakerNoteTest_962, ReturnsValueStreamedWhenCountIsZeroEvenIfUnsignedShort_962) {
  CanonMakerNote mn;

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);

  // Do not read anything => count() should remain 0.
  const std::string expected = ValueToString(*v);
  const std::string actual = PrintSi0016ToString(mn, *v);

  EXPECT_EQ(actual, expected);
}

// TEST_ID 962
TEST(CanonMakerNoteTest_962, ForUnsignedShortWithOneValue_AppendsSecondsSuffix_962) {
  CanonMakerNote mn;

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);

  // Normal operation: provide one element.
  // We don't assert the numeric formatting (black-box), only the observable suffix contract.
  v->read("0");

  const std::string out = PrintSi0016ToString(mn, *v);

  // Must end with " s" (as implemented).
  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.substr(out.size() - 2), " s");
}

// TEST_ID 962
TEST(CanonMakerNoteTest_962, ForUnsignedShortWithNonZeroValue_AppendsSecondsSuffix_962) {
  CanonMakerNote mn;

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);

  // Another normal value; still should end with " s".
  v->read("10");

  const std::string out = PrintSi0016ToString(mn, *v);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.substr(out.size() - 2), " s");
}

// TEST_ID 962
TEST(CanonMakerNoteTest_962, ForUnsignedShortWithMultipleValues_UsesFirstAndAppendsSecondsSuffix_962) {
  CanonMakerNote mn;

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);

  // Boundary-ish: multiple values in the container.
  // We only require the call succeeds and returns a string ending with " s".
  v->read("1 2 3");

  const std::string out = PrintSi0016ToString(mn, *v);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.substr(out.size() - 2), " s");
}

// TEST_ID 962
TEST(CanonMakerNoteTest_962, StreamObjectIsReturnedAndCanBeChained_962) {
  CanonMakerNote mn;

  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
  ASSERT_TRUE(v.get() != nullptr);
  v->read("0");

  std::ostringstream oss;
  std::ostream& ret = mn.printSi0x0016(oss, *v, nullptr);

  // Chaining should continue writing to same stream.
  ret << "!";
  const std::string out = oss.str();

  // Must contain the suffix and then the chained character.
  ASSERT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '!');
  ASSERT_GE(out.size(), 3u);
  EXPECT_EQ(out.substr(out.size() - 3, 2), " s");  // "... s!"
}