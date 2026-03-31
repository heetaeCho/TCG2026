#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog with prefix acceleration configured.
// We use RE2 to get the compiled Prog, which internally calls ConfigurePrefixAccel.
class PrefixAccelShiftDFATest_419 : public ::testing::Test {
 protected:
  // Helper: compile a Regexp into a Prog
  Prog* CompilePattern(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prog* prog = re->CompileToProg(0);
    re->Decref();
    return prog;
  }
};

// Test that PrefixAccel returns NULL when data size is smaller than prefix size
TEST_F(PrefixAccelShiftDFATest_419, SizeSmallerThanPrefixReturnsNull_419) {
  // Pattern "hello.*world" should have prefix "hello" (size 5)
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  // The internal prog should have prefix accel configured for "hello"
  // We test via the RE2 interface indirectly - search in data smaller than prefix
  // Direct Prog test:
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "hel";
    const void* result = prog->PrefixAccel(data, 3);
    // If prefix_size_ > 3, should return NULL
    // "hello" prefix is 5 bytes, so size 3 < 5 => NULL
    EXPECT_EQ(result, nullptr);
  }
  delete prog;
}

// Test that PrefixAccel finds the prefix in data that exactly matches the prefix
TEST_F(PrefixAccelShiftDFATest_419, ExactPrefixMatch_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "helloworld";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    // Should find "hello" at the beginning
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      EXPECT_EQ(result, data);
    }
  }
  delete prog;
}

// Test that PrefixAccel finds the prefix when it appears after some bytes
TEST_F(PrefixAccelShiftDFATest_419, PrefixAfterOffset_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "XXXhelloworld";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      // Should point to where "hello" starts
      EXPECT_EQ(result, data + 3);
    }
  }
  delete prog;
}

// Test that PrefixAccel returns NULL when prefix is not in data
TEST_F(PrefixAccelShiftDFATest_419, PrefixNotFound_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "xxxxxxxxxxxxxxxxxx";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    EXPECT_EQ(result, nullptr);
  }
  delete prog;
}

// Test with empty data
TEST_F(PrefixAccelShiftDFATest_419, EmptyData_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const void* result = prog->PrefixAccel("", 0);
    EXPECT_EQ(result, nullptr);
  }
  delete prog;
}

// Test with data that exercises the 8-byte unrolled loop
TEST_F(PrefixAccelShiftDFATest_419, LargeDataWith8ByteLoop_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    // Create data larger than 8 bytes with prefix somewhere in it
    std::string data(64, 'x');
    data += "helloworld";
    const void* result = prog->PrefixAccel(data.data(), data.size());
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      EXPECT_EQ(result, data.data() + 64);
    }
  }
  delete prog;
}

// Test with data exactly 8 bytes and no match
TEST_F(PrefixAccelShiftDFATest_419, Exactly8BytesNoMatch_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "abcdefgh";
    const void* result = prog->PrefixAccel(data, 8);
    EXPECT_EQ(result, nullptr);
  }
  delete prog;
}

// Test with a single-character prefix
TEST_F(PrefixAccelShiftDFATest_419, SingleCharPrefix_419) {
  Prog* prog = CompilePattern("a.*bc");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "xxxabc";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    EXPECT_NE(result, nullptr);
  }
  delete prog;
}

// Test with prefix at the very end of data
TEST_F(PrefixAccelShiftDFATest_419, PrefixAtEnd_419) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    std::string data(100, 'z');
    data += "hello";
    const void* result = prog->PrefixAccel(data.data(), data.size());
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      EXPECT_EQ(result, data.data() + 100);
    }
  }
  delete prog;
}

// Test with data that has a partial prefix match but not complete
TEST_F(PrefixAccelShiftDFATest_419, PartialPrefixNoMatch_419) {
  Prog* prog = CompilePattern("hello.*world");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "hellxxxxxxxxxx";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    // "hell" is not "hello", so no match for the prefix
    EXPECT_EQ(result, nullptr);
  }
  delete prog;
}

// Test with multiple occurrences of the prefix - should find the first
TEST_F(PrefixAccelShiftDFATest_419, MultiplePrefixOccurrences_419) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    const char* data = "XXhelloXXhello";
    size_t size = strlen(data);
    const void* result = prog->PrefixAccel(data, size);
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      // Should find the first occurrence
      EXPECT_LE(reinterpret_cast<const char*>(result), data + 2);
    }
  }
  delete prog;
}

// Test that can_prefix_accel returns false when no prefix is configured
TEST_F(PrefixAccelShiftDFATest_419, NoPrefixAccel_419) {
  // A pattern with alternation at the start has no fixed prefix
  Prog* prog = CompilePattern("(a|b)cd");
  ASSERT_NE(prog, nullptr);
  // This pattern may or may not have prefix accel, depending on implementation
  // We just verify the interface doesn't crash
  if (prog->can_prefix_accel()) {
    const char* data = "acd";
    const void* result = prog->PrefixAccel(data, 3);
    // Just ensure no crash; result may or may not be null
    (void)result;
  }
  delete prog;
}

// Test with very large data to exercise the 8-byte unrolled loop extensively
TEST_F(PrefixAccelShiftDFATest_419, VeryLargeData_419) {
  Prog* prog = CompilePattern("hello");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    // Large buffer with no match
    std::string data(10000, 'x');
    const void* result = prog->PrefixAccel(data.data(), data.size());
    EXPECT_EQ(result, nullptr);
    
    // Now put "hello" near the end
    data[9990] = 'h';
    data[9991] = 'e';
    data[9992] = 'l';
    data[9993] = 'l';
    data[9994] = 'o';
    result = prog->PrefixAccel(data.data(), data.size());
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      EXPECT_EQ(result, data.data() + 9990);
    }
  }
  delete prog;
}

// Test with data size that is not a multiple of 8 (exercises tail loop)
TEST_F(PrefixAccelShiftDFATest_419, NonMultipleOf8Size_419) {
  Prog* prog = CompilePattern("ab");
  ASSERT_NE(prog, nullptr);
  
  if (prog->can_prefix_accel()) {
    // 11 bytes: 8 bytes processed in unrolled loop, 3 in tail
    const char* data = "xxxxxXXXxab";
    size_t size = 11;
    const void* result = prog->PrefixAccel(data, size);
    EXPECT_NE(result, nullptr);
    if (result != nullptr) {
      EXPECT_EQ(result, data + 9);
    }
  }
  delete prog;
}

// Test through RE2 interface to validate prefix acceleration works end-to-end
TEST_F(PrefixAccelShiftDFATest_419, RE2EndToEnd_419) {
  RE2 re("hello.*world");
  ASSERT_TRUE(re.ok());
  
  std::string text = "some stuff before helloworld and after";
  EXPECT_TRUE(RE2::PartialMatch(text, re));
  
  std::string noMatchText = "some stuff without the prefix";
  EXPECT_FALSE(RE2::PartialMatch(noMatchText, re));
}

// Test with case-folding prefix
TEST_F(PrefixAccelShiftDFATest_419, CaseFoldingPrefix_419) {
  RE2 re("(?i)hello.*world");
  ASSERT_TRUE(re.ok());
  
  EXPECT_TRUE(RE2::PartialMatch("HeLLo and world", re));
  EXPECT_TRUE(RE2::PartialMatch("HELLO and WORLD", re));
  EXPECT_FALSE(RE2::PartialMatch("no match here", re));
}

}  // namespace re2
