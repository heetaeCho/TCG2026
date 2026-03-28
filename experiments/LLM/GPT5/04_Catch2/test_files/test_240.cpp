// exception_message_matches_matcher_test_240.cpp

#include <gtest/gtest.h>
#include <exception>
#include <memory>
#include <string>
#include <vector>

// Include the production header under test.
// Adjust the include path to match your repo layout.
#include "catch2/matchers/catch_matchers_exception.hpp"

namespace {

// A simple recording matcher used as the StringMatcherType collaborator.
// It records every argument it receives and returns a fixed boolean.
// This models an external dependency and lets us assert interactions.
struct RecordingStringMatcher {
  std::shared_ptr<std::vector<std::string>> calls;
  bool result;

  explicit RecordingStringMatcher(bool r,
                                  std::shared_ptr<std::vector<std::string>> rec = nullptr)
      : calls(rec ? std::move(rec) : std::make_shared<std::vector<std::string>>()),
        result(r) {}

  // ex.what() returns const char*, so we provide this overload.
  bool match(const char* s) const {
    if (calls) calls->emplace_back(s ? s : "");
    return result;
  }

  // Optional convenience overload if implementation uses std::string.
  bool match(const std::string& s) const {
    if (calls) calls->push_back(s);
    return result;
  }
};

// Custom exception with fixed what() text to test boundary/explicit messages.
class FixedWhatException : public std::exception {
 public:
  explicit FixedWhatException(const char* msg) : msg_(msg ? msg : "") {}
  const char* what() const noexcept override { return msg_.c_str(); }
 private:
  std::string msg_;
};

}  // namespace

// Test fixture (empty, but provides a consistent naming base with TEST_ID).
class ExceptionMessageMatchesMatcherTest_240 : public ::testing::Test {};

// Alias the matcher under test with our recording collaborator.
using TestMatcher240 =
    Catch::Matchers::ExceptionMessageMatchesMatcher<RecordingStringMatcher>;

// --- Tests ---

TEST_F(ExceptionMessageMatchesMatcherTest_240, ReturnsTrueWhenUnderlyingMatches_240) {
  auto calls = std::make_shared<std::vector<std::string>>();
  RecordingStringMatcher rec_true{/*result=*/true, calls};
  TestMatcher240 sut(rec_true);

  std::runtime_error ex("expected message");

  EXPECT_TRUE(sut.match(ex));
  // Also ensures collaborator received exactly one call.
  ASSERT_EQ(calls->size(), 1u);
  EXPECT_EQ(calls->at(0), std::string("expected message"));
}

TEST_F(ExceptionMessageMatchesMatcherTest_240, ReturnsFalseWhenUnderlyingDoesNotMatch_240) {
  auto calls = std::make_shared<std::vector<std::string>>();
  RecordingStringMatcher rec_false{/*result=*/false, calls};
  TestMatcher240 sut(rec_false);

  std::logic_error ex("different message");

  EXPECT_FALSE(sut.match(ex));
  ASSERT_EQ(calls->size(), 1u);
  EXPECT_EQ(calls->at(0), std::string("different message"));
}

TEST_F(ExceptionMessageMatchesMatcherTest_240, ForwardsExactWhatStringToCollaborator_240) {
  auto calls = std::make_shared<std::vector<std::string>>();
  RecordingStringMatcher rec_true{/*result=*/true, calls};
  TestMatcher240 sut(rec_true);

  FixedWhatException ex("boom!");

  // We only assert interaction (argument forwarding), not internal logic.
  (void)sut.match(ex);
  ASSERT_EQ(calls->size(), 1u);
  EXPECT_EQ(calls->at(0), std::string("boom!"));
}

TEST_F(ExceptionMessageMatchesMatcherTest_240, HandlesEmptyExceptionMessage_240) {
  auto calls = std::make_shared<std::vector<std::string>>();
  RecordingStringMatcher rec_true{/*result=*/true, calls};
  TestMatcher240 sut(rec_true);

  FixedWhatException ex("");

  EXPECT_TRUE(sut.match(ex));  // result comes from collaborator
  ASSERT_EQ(calls->size(), 1u);
  EXPECT_EQ(calls->at(0), std::string(""));
}

TEST_F(ExceptionMessageMatchesMatcherTest_240, WorksWithAnyStdExceptionSubtype_240) {
  auto calls = std::make_shared<std::vector<std::string>>();
  RecordingStringMatcher rec_false{/*result=*/false, calls};
  TestMatcher240 sut(rec_false);

  // Use a different std::exception-derived type.
  std::overflow_error ex("overflow!");

  EXPECT_FALSE(sut.match(ex));
  ASSERT_EQ(calls->size(), 1u);
  EXPECT_EQ(calls->at(0), std::string("overflow!"));
}
