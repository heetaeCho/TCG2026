// File: ./TestProjects/yaml-cpp/test/regeximpl_match_test_114.cpp

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#if __has_include("regex_yaml.h")
  #include "regex_yaml.h"
#elif __has_include("../src/regex_yaml.h")
  #include "../src/regex_yaml.h"
#else
  #include "TestProjects/yaml-cpp/src/regex_yaml.h"
#endif

#if __has_include("regeximpl.h")
  #include "regeximpl.h"
#elif __has_include("../src/regeximpl.h")
  #include "../src/regeximpl.h"
#else
  #include "TestProjects/yaml-cpp/src/regeximpl.h"
#endif

namespace {

template <class...>
inline constexpr bool kDependentFalse = false;

// Helper: build a StringCharSource from a std::string without assuming a specific ctor signature.
template <typename TSource>
TSource MakeValidSourceFromString(const std::string& s) {
  if constexpr (std::is_constructible_v<TSource, const std::string&>) {
    return TSource(s);
  } else if constexpr (std::is_constructible_v<TSource, const char*, const char*>) {
    return TSource(s.data(), s.data() + s.size());
  } else if constexpr (std::is_constructible_v<TSource, const char*>) {
    return TSource(s.c_str());
  } else {
    static_assert(kDependentFalse<TSource>,
                  "No supported constructor found for Source from std::string");
  }
}

template <typename TSource>
TSource MakeInvalidSource() {
  if constexpr (std::is_default_constructible_v<TSource>) {
    return TSource{};
  } else if constexpr (std::is_constructible_v<TSource, const char*, const char*>) {
    return TSource(nullptr, nullptr);
  } else if constexpr (std::is_constructible_v<TSource, const char*>) {
    return TSource(nullptr);
  } else {
    static_assert(kDependentFalse<TSource>,
                  "No supported constructor found to create an invalid Source");
  }
}

}  // namespace

namespace YAML {

class RegExMatchImplTest_114 : public ::testing::Test {};

TEST_F(RegExMatchImplTest_114, TemplateMatch_StringCharSource_ConsistentWithStringOverload_114) {
  const RegEx ex('a');

  const std::string s1 = "abc";
  const std::string s2 = "xbc";

  const auto src1 = MakeValidSourceFromString<StringCharSource>(s1);
  const auto src2 = MakeValidSourceFromString<StringCharSource>(s2);

  // Observable behavior: template Match(Source) should behave consistently with Match(std::string).
  EXPECT_EQ(ex.Match(s1), ex.Match(src1));
  EXPECT_EQ(ex.Match(s2), ex.Match(src2));
}

TEST_F(RegExMatchImplTest_114, TemplateMatch_RangeRegex_ConsistentWithStringOverload_114) {
  const RegEx ex('a', 'z');

  const std::string s1 = "mno";
  const std::string s2 = "7up";

  const auto src1 = MakeValidSourceFromString<StringCharSource>(s1);
  const auto src2 = MakeValidSourceFromString<StringCharSource>(s2);

  EXPECT_EQ(ex.Match(s1), ex.Match(src1));
  EXPECT_EQ(ex.Match(s2), ex.Match(src2));
}

TEST_F(RegExMatchImplTest_114, TemplateMatch_EmptyRegex_ConsistentWithStringOverload_114) {
  const RegEx ex;  // REGEX_EMPTY

  const std::string empty = "";
  const std::string nonempty = "xyz";

  const auto src_empty = MakeValidSourceFromString<StringCharSource>(empty);
  const auto src_nonempty = MakeValidSourceFromString<StringCharSource>(nonempty);

  EXPECT_EQ(ex.Match(empty), ex.Match(src_empty));
  EXPECT_EQ(ex.Match(nonempty), ex.Match(src_nonempty));
}

TEST_F(RegExMatchImplTest_114, TemplateMatch_InvalidSource_ReturnsMinusOne_114) {
  const RegEx ex('a');

  // The template Match(Source) is documented (in the partial impl) to return -1
  // when IsValidSource(source) is false.
  const auto invalid = MakeInvalidSource<StringCharSource>();

  EXPECT_EQ(-1, ex.Match(invalid));
}

TEST_F(RegExMatchImplTest_114, TemplateMatch_ComposedRegex_ConsistentWithStringOverload_114) {
  // Build a composed regex using the public operators (sequence via +).
  // We don't assume the numeric meaning of the return value; we only require consistency
  // between overloads for the same observable inputs.
  const RegEx ex = RegEx('a') + RegEx('b');

  const std::string s1 = "abcd";
  const std::string s2 = "axcd";

  const auto src1 = MakeValidSourceFromString<StringCharSource>(s1);
  const auto src2 = MakeValidSourceFromString<StringCharSource>(s2);

  EXPECT_EQ(ex.Match(s1), ex.Match(src1));
  EXPECT_EQ(ex.Match(s2), ex.Match(src2));
}

}  // namespace YAML
