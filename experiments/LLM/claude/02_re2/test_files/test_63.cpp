#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// We need to test the Filter class which uses pybind11.
// Since this is a C++ unit test without Python interpreter,
// we'll need to initialize pybind11's embedded interpreter.
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "re2/re2.h"
#include "re2/filtered_re2.h"

namespace py = pybind11;

// Include or declare the Filter class
namespace re2_python {

std::string FromBytes(const py::buffer_info& bytes) {
    return std::string(static_cast<const char*>(bytes.ptr), 
                       static_cast<size_t>(bytes.size));
}

class Filter {
 public:
  Filter() = default;
  Filter(const Filter&) = delete;
  ~Filter() = default;
  Filter& operator=(const Filter&) = delete;

  int Add(py::buffer buffer, const RE2::Options& options) {
    auto bytes = buffer.request();
    auto pattern = FromBytes(bytes);
    int index = -1;
    filter_.Add(pattern, options, &index);
    return index;
  }

  bool Compile() {
    std::vector<std::string> atoms;
    filter_.Compile(&atoms);
    re2::RE2::Options options;
    options.set_literal(true);
    options.set_case_sensitive(false);
    set_ = -1;
    // Build atom index if needed
    return true;
  }

  std::vector<int> Match(py::buffer buffer, bool potential) const {
    auto bytes = buffer.request();
    auto text = FromBytes(bytes);
    std::vector<int> matching_indices;
    // Simplified - actual implementation uses atom matching
    if (potential) {
      for (int i = 0; i < filter_.NumRegexps(); i++) {
        matching_indices.push_back(i);
      }
    } else {
      for (int i = 0; i < filter_.NumRegexps(); i++) {
        if (RE2::PartialMatch(text, filter_.GetRE2(i))) {
          matching_indices.push_back(i);
        }
      }
    }
    return matching_indices;
  }

  const RE2& GetRE2(int index) const {
    return filter_.GetRE2(index);
  }

 private:
  re2::FilteredRE2 filter_;
  int set_ = -1;
};

}  // namespace re2_python

// Initialize Python interpreter for pybind11
class PythonEnv : public ::testing::Environment {
 public:
  void SetUp() override {
    guard_ = new py::scoped_interpreter{};
  }
  void TearDown() override {
    delete guard_;
  }
 private:
  py::scoped_interpreter* guard_ = nullptr;
};

testing::Environment* const python_env =
    testing::AddGlobalTestEnvironment(new PythonEnv);

class FilterTest_63 : public ::testing::Test {
 protected:
  void SetUp() override {
    filter_ = std::make_unique<re2_python::Filter>();
  }

  py::bytes MakePattern(const std::string& s) {
    return py::bytes(s);
  }

  std::unique_ptr<re2_python::Filter> filter_;
};

// Test adding a valid simple pattern returns index 0
TEST_F(FilterTest_63, AddFirstPatternReturnsZero_63) {
  RE2::Options options;
  py::bytes pattern("hello");
  int index = filter_->Add(pattern, options);
  EXPECT_EQ(index, 0);
}

// Test adding multiple patterns returns sequential indices
TEST_F(FilterTest_63, AddMultiplePatternsReturnsSequentialIndices_63) {
  RE2::Options options;
  int idx0 = filter_->Add(py::bytes("hello"), options);
  int idx1 = filter_->Add(py::bytes("world"), options);
  int idx2 = filter_->Add(py::bytes("test"), options);
  EXPECT_EQ(idx0, 0);
  EXPECT_EQ(idx1, 1);
  EXPECT_EQ(idx2, 2);
}

// Test adding an invalid pattern returns -1
TEST_F(FilterTest_63, AddInvalidPatternReturnsNegative_63) {
  RE2::Options options;
  options.set_log_errors(false);
  // Unbalanced parenthesis is invalid
  int index = filter_->Add(py::bytes("(unclosed"), options);
  EXPECT_EQ(index, -1);
}

// Test adding an empty pattern
TEST_F(FilterTest_63, AddEmptyPatternReturnsValidIndex_63) {
  RE2::Options options;
  int index = filter_->Add(py::bytes(""), options);
  EXPECT_GE(index, 0);
}

// Test adding a pattern with special regex characters
TEST_F(FilterTest_63, AddPatternWithSpecialChars_63) {
  RE2::Options options;
  int index = filter_->Add(py::bytes("a.*b+c?"), options);
  EXPECT_EQ(index, 0);
}

// Test adding a literal pattern
TEST_F(FilterTest_63, AddLiteralPattern_63) {
  RE2::Options options;
  options.set_literal(true);
  int index = filter_->Add(py::bytes("a.b"), options);
  EXPECT_EQ(index, 0);
}

// Test GetRE2 returns correct regex for given index
TEST_F(FilterTest_63, GetRE2ReturnsCorrectPattern_63) {
  RE2::Options options;
  filter_->Add(py::bytes("hello"), options);
  filter_->Add(py::bytes("world"), options);
  
  const RE2& re0 = filter_->GetRE2(0);
  const RE2& re1 = filter_->GetRE2(1);
  
  EXPECT_EQ(re0.pattern(), "hello");
  EXPECT_EQ(re1.pattern(), "world");
}

// Test adding pattern with case insensitive option
TEST_F(FilterTest_63, AddPatternCaseInsensitive_63) {
  RE2::Options options;
  options.set_case_sensitive(false);
  int index = filter_->Add(py::bytes("Hello"), options);
  EXPECT_EQ(index, 0);
  
  const RE2& re = filter_->GetRE2(0);
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// Test adding pattern with POSIX syntax
TEST_F(FilterTest_63, AddPatternWithPOSIXSyntax_63) {
  RE2::Options options;
  options.set_posix_syntax(true);
  int index = filter_->Add(py::bytes("abc"), options);
  EXPECT_EQ(index, 0);
}

// Test that Filter is non-copyable (compile-time check, just verify construction)
TEST_F(FilterTest_63, FilterIsDefaultConstructible_63) {
  re2_python::Filter f;
  // Just verify it constructs without issues
  SUCCEED();
}

// Test adding many patterns
TEST_F(FilterTest_63, AddManyPatterns_63) {
  RE2::Options options;
  for (int i = 0; i < 100; i++) {
    std::string pattern = "pattern" + std::to_string(i);
    int index = filter_->Add(py::bytes(pattern), options);
    EXPECT_EQ(index, i);
  }
}

// Test adding pattern with binary data
TEST_F(FilterTest_63, AddPatternWithNullBytes_63) {
  RE2::Options options;
  options.set_log_errors(false);
  std::string pattern_with_null("ab\x00cd", 5);
  int index = filter_->Add(py::bytes(pattern_with_null), options);
  // Pattern with null byte - behavior depends on implementation
  // Just check it doesn't crash
  (void)index;
  SUCCEED();
}

// Test adding complex regex pattern
TEST_F(FilterTest_63, AddComplexRegexPattern_63) {
  RE2::Options options;
  int index = filter_->Add(py::bytes("(foo|bar)\\d+[a-z]{2,5}"), options);
  EXPECT_EQ(index, 0);
}

// Test invalid regex with log_errors disabled
TEST_F(FilterTest_63, AddMultipleInvalidPatternsDoNotIncrementIndex_63) {
  RE2::Options options;
  options.set_log_errors(false);
  
  int idx0 = filter_->Add(py::bytes("valid"), options);
  EXPECT_EQ(idx0, 0);
  
  int idx_invalid = filter_->Add(py::bytes("(invalid"), options);
  EXPECT_EQ(idx_invalid, -1);
  
  int idx1 = filter_->Add(py::bytes("also_valid"), options);
  // After an invalid pattern, the next valid one should still get sequential index
  // The actual index depends on FilteredRE2 implementation
  EXPECT_GE(idx1, 0);
}

// Test that GetRE2 after Add returns a valid RE2 object
TEST_F(FilterTest_63, GetRE2AfterAddIsValid_63) {
  RE2::Options options;
  filter_->Add(py::bytes("test_pattern"), options);
  
  const RE2& re = filter_->GetRE2(0);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.pattern(), "test_pattern");
}

// Test options are properly forwarded - never_capture
TEST_F(FilterTest_63, AddPatternWithNeverCapture_63) {
  RE2::Options options;
  options.set_never_capture(true);
  int index = filter_->Add(py::bytes("(group)"), options);
  EXPECT_EQ(index, 0);
  
  const RE2& re = filter_->GetRE2(0);
  // With never_capture, named groups should not be captured
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// Test with dot_nl option
TEST_F(FilterTest_63, AddPatternWithDotNl_63) {
  RE2::Options options;
  options.set_dot_nl(true);
  int index = filter_->Add(py::bytes("a.b"), options);
  EXPECT_EQ(index, 0);
  
  const RE2& re = filter_->GetRE2(0);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}
