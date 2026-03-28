#include <gtest/gtest.h>
#include <cstddef>

// We need to declare the template and specialization to test it
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest);

// Declaration of the void* specialization
template <>
bool Parse(const char* str, size_t n, void* dest);

}  // namespace re2_internal
}  // namespace re2

// Test fixture
class ParseVoidTest_266 : public ::testing::Test {
 protected:
};

// Test that Parse returns true when dest is NULL
TEST_F(ParseVoidTest_266, ReturnsTrue_WhenDestIsNull_266) {
  bool result = re2::re2_internal::Parse<void>("hello", 5, static_cast<void*>(nullptr));
  EXPECT_TRUE(result);
}

// Test that Parse returns false when dest is non-NULL
TEST_F(ParseVoidTest_266, ReturnsFalse_WhenDestIsNonNull_266) {
  int dummy = 42;
  bool result = re2::re2_internal::Parse<void>("hello", 5, static_cast<void*>(&dummy));
  EXPECT_FALSE(result);
}

// Test with empty string and NULL dest
TEST_F(ParseVoidTest_266, EmptyString_NullDest_ReturnsTrue_266) {
  bool result = re2::re2_internal::Parse<void>("", 0, static_cast<void*>(nullptr));
  EXPECT_TRUE(result);
}

// Test with empty string and non-NULL dest
TEST_F(ParseVoidTest_266, EmptyString_NonNullDest_ReturnsFalse_266) {
  char buffer[10] = {};
  bool result = re2::re2_internal::Parse<void>("", 0, static_cast<void*>(buffer));
  EXPECT_FALSE(result);
}

// Test with nullptr str and NULL dest
TEST_F(ParseVoidTest_266, NullStr_NullDest_ReturnsTrue_266) {
  bool result = re2::re2_internal::Parse<void>(nullptr, 0, static_cast<void*>(nullptr));
  EXPECT_TRUE(result);
}

// Test with nullptr str and non-NULL dest
TEST_F(ParseVoidTest_266, NullStr_NonNullDest_ReturnsFalse_266) {
  double d = 3.14;
  bool result = re2::re2_internal::Parse<void>(nullptr, 0, static_cast<void*>(&d));
  EXPECT_FALSE(result);
}

// Test with large n value and NULL dest
TEST_F(ParseVoidTest_266, LargeN_NullDest_ReturnsTrue_266) {
  bool result = re2::re2_internal::Parse<void>("test", 999999, static_cast<void*>(nullptr));
  EXPECT_TRUE(result);
}

// Test with large n value and non-NULL dest
TEST_F(ParseVoidTest_266, LargeN_NonNullDest_ReturnsFalse_266) {
  int x = 0;
  bool result = re2::re2_internal::Parse<void>("test", 999999, static_cast<void*>(&x));
  EXPECT_FALSE(result);
}

// Test that the str content doesn't affect the result when dest is NULL
TEST_F(ParseVoidTest_266, DifferentStrings_NullDest_AllReturnTrue_266) {
  EXPECT_TRUE(re2::re2_internal::Parse<void>("abc", 3, static_cast<void*>(nullptr)));
  EXPECT_TRUE(re2::re2_internal::Parse<void>("12345", 5, static_cast<void*>(nullptr)));
  EXPECT_TRUE(re2::re2_internal::Parse<void>("!@#$%", 5, static_cast<void*>(nullptr)));
}

// Test that the str content doesn't affect the result when dest is non-NULL
TEST_F(ParseVoidTest_266, DifferentStrings_NonNullDest_AllReturnFalse_266) {
  int dummy;
  void* dest = static_cast<void*>(&dummy);
  EXPECT_FALSE(re2::re2_internal::Parse<void>("abc", 3, dest));
  EXPECT_FALSE(re2::re2_internal::Parse<void>("12345", 5, dest));
  EXPECT_FALSE(re2::re2_internal::Parse<void>("!@#$%", 5, dest));
}

// Test that n value doesn't affect the result
TEST_F(ParseVoidTest_266, DifferentN_NullDest_AllReturnTrue_266) {
  EXPECT_TRUE(re2::re2_internal::Parse<void>("test", 0, static_cast<void*>(nullptr)));
  EXPECT_TRUE(re2::re2_internal::Parse<void>("test", 1, static_cast<void*>(nullptr)));
  EXPECT_TRUE(re2::re2_internal::Parse<void>("test", 4, static_cast<void*>(nullptr)));
  EXPECT_TRUE(re2::re2_internal::Parse<void>("test", 100, static_cast<void*>(nullptr)));
}
