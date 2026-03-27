// tests/catch_test_spec_pattern_stream_32_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Include the production header (path as given in the prompt)
#include "Catch2/src/catch2/catch_test_spec.hpp"

// Create a test-double that derives from the interface and overrides the
// virtuals via the public interface only (no access to private state).
namespace Catch {

struct PatternMock_32 : public TestSpec::Pattern {
  using TestSpec::Pattern::Pattern; // inherit explicit ctor

  // We override the private virtual in the base — this is allowed in C++.
  MOCK_METHOD(void, serializeTo, (std::ostream& out), (const, override));

  // In Catch2 this is typically pure virtual; we provide a trivial override.
  MOCK_METHOD(bool, matches, (const TestCaseInfo&), (const, override));
};

} // namespace Catch

using ::testing::_;
using ::testing::Invoke;
using ::testing::StrEq;

class PatternStreamTest_32 : public ::testing::Test {};

//
// Normal operation: operator<< calls serializeTo and writes into the stream.
//
TEST_F(PatternStreamTest_32, StreamsViaSerializeTo_32) {
  Catch::PatternMock_32 pat("Alpha");

  EXPECT_CALL(pat, serializeTo(_))
      .Times(1)
      .WillOnce(Invoke([&](std::ostream& out) {
        // Produce some recognizable rendering that depends on public API.
        out << "Pattern(" << pat.name() << ")";
      }));
  EXPECT_CALL(pat, matches(_)).Times(0); // not used in these tests

  std::ostringstream oss;
  oss << pat;

  EXPECT_THAT(oss.str(), StrEq("Pattern(Alpha)"));
}

//
// External interaction verification: the very same stream object is passed in.
//
TEST_F(PatternStreamTest_32, PassesSameStreamObjectToSerialize_32) {
  Catch::PatternMock_32 pat("Beta");

  std::ostringstream oss;
  std::ostream* expected = &oss;

  EXPECT_CALL(pat, serializeTo(_))
      .Times(1)
      .WillOnce(Invoke([&](std::ostream& out) {
        // Ensure identity of the stream instance is preserved.
        EXPECT_EQ(&out, expected);
        out << "OK";
      }));

  std::ostream& returned = (oss << pat);
  EXPECT_EQ(&returned, expected);              // operator<< returns same stream
  EXPECT_THAT(oss.str(), StrEq("OK"));
}

//
// Boundary: empty name should be handled and serialization still works.
//
TEST_F(PatternStreamTest_32, HandlesEmptyName_32) {
  Catch::PatternMock_32 pat("");

  // The name() accessor is public; verify it reflects the ctor input.
  EXPECT_THAT(pat.name(), StrEq(""));

  EXPECT_CALL(pat, serializeTo(_))
      .WillOnce(Invoke([&](std::ostream& out) {
        out << "Pattern(" << pat.name() << ")"; // should print empty between parens
      }));

  std::ostringstream oss;
  oss << pat;
  EXPECT_THAT(oss.str(), StrEq("Pattern()"));
}

//
// Boundary: very long name does not break streaming (appends to existing content).
//
TEST_F(PatternStreamTest_32, StreamsLongNameAndAppends_32) {
  std::string longName(4096, 'X');
  Catch::PatternMock_32 pat(longName);

  EXPECT_CALL(pat, serializeTo(_))
      .WillOnce(Invoke([&](std::ostream& out) {
        out << "Name:" << pat.name();
      }));

  std::ostringstream oss;
  oss << "BEGIN|" << pat << "|END";
  const std::string s = oss.str();

  ASSERT_GE(s.size(), 6u + 5u + longName.size()); // basic sanity on length
  EXPECT_THAT(s.substr(0, 6), StrEq("BEGIN|"));
  EXPECT_THAT(s.substr(s.size() - 4), StrEq("|END"));
  // Spot check that long name content made it in.
  EXPECT_NE(s.find("Name:"), std::string::npos);
  EXPECT_NE(s.find(std::string(16, 'X')), std::string::npos);
}

//
// International text: non-ASCII names are surfaced intact through operator<<.
//
TEST_F(PatternStreamTest_32, StreamsUnicodeName_32) {
  const std::string unicodeName = u8"테스트🌟";
  Catch::PatternMock_32 pat(unicodeName);

  EXPECT_CALL(pat, serializeTo(_))
      .WillOnce(Invoke([&](std::ostream& out) {
        out << "[" << pat.name() << "]";
      }));

  std::ostringstream oss;
  oss << pat;
  EXPECT_THAT(oss.str(), StrEq("[" + unicodeName + "]"));
}

//
// Const-correctness: streaming via const reference uses the virtual serializeTo.
//
TEST_F(PatternStreamTest_32, ConstObjectStreamsCorrectly_32) {
  Catch::PatternMock_32 mutablePat("Consty");
  const Catch::PatternMock_32& pat = mutablePat; // const view

  EXPECT_CALL(mutablePat, serializeTo(_))  // expectation must be set on the object
      .Times(1)
      .WillOnce(Invoke([&](std::ostream& out) {
        out << pat.name(); // const method
      }));

  std::ostringstream oss;
  oss << pat;
  EXPECT_THAT(oss.str(), StrEq("Consty"));
}
