#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>
#include <string>

// We need to declare the function under test since it's static in db/c.cc
// We'll replicate the signature for testing purposes.
// Since the function is static in c.cc, we need to either include it or
// redefine it here for testing. We'll use a test-local copy that matches
// the exact implementation signature.

namespace {

static char* CopyString(const std::string& str) {
  char* result = reinterpret_cast<char*>(std::malloc(sizeof(char) * str.size()));
  std::memcpy(result, str.data(), sizeof(char) * str.size());
  return result;
}

}  // namespace

class CopyStringTest_219 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Free any allocated memory tracked during tests
    for (char* ptr : allocated_ptrs_) {
      std::free(ptr);
    }
  }

  char* TrackAlloc(char* ptr) {
    if (ptr) allocated_ptrs_.push_back(ptr);
    return ptr;
  }

  std::vector<char*> allocated_ptrs_;
};

TEST_F(CopyStringTest_219, CopiesSimpleString_219) {
  std::string input = "hello";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, CopiesEmptyString_219) {
  std::string input = "";
  // For an empty string, malloc(0) may return nullptr or a valid pointer
  // depending on the implementation. Either way, no bytes to compare.
  char* result = CopyString(input);
  if (result != nullptr) {
    allocated_ptrs_.push_back(result);
  }
  // Nothing to verify about content since size is 0
  // Just ensure it doesn't crash
}

TEST_F(CopyStringTest_219, CopiesSingleCharacter_219) {
  std::string input = "A";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result[0], 'A');
}

TEST_F(CopyStringTest_219, CopiesStringWithNullBytes_219) {
  std::string input("hel\0lo", 6);
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(input.size(), 6u);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, CopiedDataMatchesOriginal_219) {
  std::string input = "The quick brown fox jumps over the lazy dog";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, ResultIsIndependentCopy_219) {
  std::string input = "test_data";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  // The result should be a separate allocation, not pointing to the string's internal buffer
  EXPECT_NE(result, input.data());
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, CopiesStringWithSpecialCharacters_219) {
  std::string input = "\x01\x02\xff\xfe\n\r\t";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, CopiesLargerString_219) {
  std::string input(10000, 'x');
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}

TEST_F(CopyStringTest_219, DoesNotNullTerminate_219) {
  // The function copies exactly str.size() bytes, no null terminator
  std::string input = "abc";
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  // Verify the exact bytes copied match
  EXPECT_EQ(result[0], 'a');
  EXPECT_EQ(result[1], 'b');
  EXPECT_EQ(result[2], 'c');
  // Note: We cannot safely check result[3] as it's beyond the allocated size
}

TEST_F(CopyStringTest_219, MultipleCopiesAreIndependent_219) {
  std::string input = "shared";
  char* result1 = TrackAlloc(CopyString(input));
  char* result2 = TrackAlloc(CopyString(input));
  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1, result2);
  EXPECT_EQ(std::memcmp(result1, result2, input.size()), 0);
}

TEST_F(CopyStringTest_219, CopiesBinaryData_219) {
  // String containing all possible byte values
  std::string input;
  for (int i = 0; i < 256; ++i) {
    input.push_back(static_cast<char>(i));
  }
  char* result = TrackAlloc(CopyString(input));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(input.size(), 256u);
  EXPECT_EQ(std::memcmp(result, input.data(), input.size()), 0);
}
