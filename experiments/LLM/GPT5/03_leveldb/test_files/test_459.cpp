// File: escape_string_test.cc

#include <gtest/gtest.h>
#include <string>

// Bring in Slice interface (public API only).
#include "leveldb/slice.h"

// ---- Forward declare the collaborator so util/logging.cc compiles. ----
namespace leveldb {
class Slice;  // already included via header, but forward-decl is harmless
void AppendEscapedStringTo(std::string* dst, const Slice& value);  // test double will define this
}  // namespace leveldb

// ---- Compile the function under test into this TU. ----
#include "util/logging.cc"  // defines: leveldb::EscapeString(const Slice&)

// ---- Test double for the external collaborator. ----
namespace leveldb {

// Simple global state to observe calls (kept local to test TU).
static int g_append_called = 0;
static std::string g_last_value_bytes;

void AppendEscapedStringTo(std::string* dst, const Slice& value) {
  ++g_append_called;
  g_last_value_bytes.assign(value.data(), value.size());

  // Deterministic, observable append so tests can assert exact return.
  dst->append("[ESC]");
  dst->append(g_last_value_bytes);
  dst->append("[/ESC]");
}

}  // namespace leveldb

// ---- Test fixture to reset observation state. ----
class EscapeStringTest_459 : public ::testing::Test {
 protected:
  void SetUp() override {
    leveldb::g_append_called = 0;
    leveldb::g_last_value_bytes.clear();
  }
};

// Normal operation: ensures single delegation and exact returned string.
TEST_F(EscapeStringTest_459, DelegatesOnceAndReturnsCollaboratorOutput_459) {
  using namespace leveldb;

  const std::string input = "hello";
  const std::string expected = std::string("[ESC]") + input + "[/ESC]";

  const std::string out = EscapeString(Slice(input));

  EXPECT_EQ(1, g_append_called) << "AppendEscapedStringTo should be called exactly once";
  EXPECT_EQ(input, g_last_value_bytes) << "Collaborator must receive the exact bytes of the Slice";
  EXPECT_EQ(expected, out) << "EscapeString must return exactly what collaborator appended";
}

// Boundary: empty input should still delegate once and return the collaborator's append result.
TEST_F(EscapeStringTest_459, EmptyInput_StillDelegates_AndReturnsAppended_459) {
  using namespace leveldb;

  const std::string input = "";
  const std::string expected = "[ESC][/ESC]";  // collaborator appends markers around empty payload

  const std::string out = EscapeString(Slice(input));

  EXPECT_EQ(1, g_append_called);
  EXPECT_TRUE(g_last_value_bytes.empty());
  EXPECT_EQ(expected, out);
}

// Boundary: binary input (including embedded NULs) must be passed through unmodified to collaborator.
TEST_F(EscapeStringTest_459, BinaryInput_PreservesExactBytes_ForCollaborator_459) {
  using namespace leveldb;

  // Construct a string containing embedded NUL and non-printable bytes.
  std::string input;
  input.push_back('\0');
  input.push_back('\x01');
  input.push_back('A');
  input.push_back('\xFF');

  const std::string expected = std::string("[ESC]") + input + "[/ESC]";

  const std::string out = EscapeString(Slice(input));

  EXPECT_EQ(1, g_append_called);
  ASSERT_EQ(input.size(), g_last_value_bytes.size());
  EXPECT_EQ(0, std::memcmp(input.data(), g_last_value_bytes.data(), input.size()))
      << "Collaborator must receive identical raw bytes";
  ASSERT_EQ(expected.size(), out.size());
  EXPECT_EQ(0, std::memcmp(expected.data(), out.data(), expected.size()))
      << "Return value must exactly match collaborator's appended bytes";
}
