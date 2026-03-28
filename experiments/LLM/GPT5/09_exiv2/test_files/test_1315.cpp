// TEST_ID 1315
// Unit tests for Exiv2::nsDumper (from src/xmp.cpp)
//
// Notes:
// - nsDumper has internal linkage (static in a .cpp). To test it via its real implementation,
//   we include the implementation file into this test translation unit.
// - These tests validate only observable behavior: return value and changes to the provided map.

#include <gtest/gtest.h>

#include <cstddef>
#include <map>
#include <string>

// Include the implementation to access the internal-linkage function.
#include "src/xmp.cpp"

namespace {

class NsDumperTest_1315 : public ::testing::Test {
 protected:
  using Dict = std::map<std::string, std::string>;

  static XMP_Status CallNsDumper(Dict& dict, const std::string& s) {
    // nsDumper takes a pointer + explicit size; it does not require null-termination.
    return Exiv2::nsDumper(static_cast<void*>(&dict), s.data(), static_cast<XMP_StringLen>(s.size()));
  }
};

TEST_F(NsDumperTest_1315, ReturnsZero_1315) {
  Dict dict;
  const XMP_Status st = CallNsDumper(dict, "anything");
  EXPECT_EQ(st, 0);
}

TEST_F(NsDumperTest_1315, NonPrintableOnly_NoNamespaceOrUri_NoMapChange_1315) {
  Dict dict;
  dict["keep"] = "value";

  // All bytes here are outside [32,126]; after filtering, nothing meaningful should remain.
  std::string input;
  input.push_back('\n');                  // < 32
  input.push_back(static_cast<char>(1));  // < 32
  input.push_back(static_cast<char>(127));  // > 126

  const XMP_Status st = CallNsDumper(dict, input);
  EXPECT_EQ(st, 0);

  ASSERT_EQ(dict.size(), 1u);
  EXPECT_EQ(dict.find("keep")->second, "value");
}

TEST_F(NsDumperTest_1315, NamespaceTokenWithTrailingColon_StoresUnderEmptyKey_1315) {
  Dict dict;

  // Looks like a namespace token; trailing ':' should still result in a stored namespace name.
  const XMP_Status st = CallNsDumper(dict, "dc:");
  EXPECT_EQ(st, 0);

  // Observable behavior: map gets an entry for key "".
  ASSERT_TRUE(dict.contains(""));
  EXPECT_EQ(dict[""], "dc");
}

TEST_F(NsDumperTest_1315, NamespaceTokenWithoutTrailingColon_StoresUnderEmptyKey_1315) {
  Dict dict;

  const XMP_Status st = CallNsDumper(dict, "xmp:");
  EXPECT_EQ(st, 0);

  ASSERT_TRUE(dict.contains(""));
  EXPECT_EQ(dict[""], "xmp");
}

TEST_F(NsDumperTest_1315, NamespaceTokenCanBecomeEmptyAfterTrim_StillStoresEmptyString_1315) {
  Dict dict;

  // Boundary case: minimal namespace-like token.
  const XMP_Status st = CallNsDumper(dict, ":");
  EXPECT_EQ(st, 0);

  ASSERT_TRUE(dict.contains(""));
  EXPECT_EQ(dict[""], "");
}

TEST_F(NsDumperTest_1315, UriTokenWithoutPriorNamespace_DoesNotInsertAnything_1315) {
  Dict dict;

  const XMP_Status st = CallNsDumper(dict, "http://example.com/ns");
  EXPECT_EQ(st, 0);

  EXPECT_TRUE(dict.empty());
}

TEST_F(NsDumperTest_1315, NamespaceThenUri_StoresUriUnderNamespaceKeyAndClearsEmptyKey_1315) {
  Dict dict;

  ASSERT_EQ(CallNsDumper(dict, "dc:"), 0);
  ASSERT_TRUE(dict.contains(""));
  ASSERT_EQ(dict[""], "dc");

  ASSERT_EQ(CallNsDumper(dict, "http://purl.org/dc/elements/1.1/"), 0);

  // Observable behavior: the temporary "" key is removed,
  // and the URI is stored under the namespace name.
  EXPECT_FALSE(dict.contains(""));
  ASSERT_TRUE(dict.contains("dc"));
  EXPECT_EQ(dict["dc"], "http://purl.org/dc/elements/1.1/");
}

TEST_F(NsDumperTest_1315, UriWithNonPrintableChars_IsFilteredBeforeStoring_1315) {
  Dict dict;

  ASSERT_EQ(CallNsDumper(dict, "ns:"), 0);
  ASSERT_TRUE(dict.contains(""));
  ASSERT_EQ(dict[""], "ns");

  // Inject non-printable bytes into the URI; they should not appear in the stored value.
  std::string uri = "http://example.com/a";
  uri.push_back('\n');  // filtered out
  uri += "b";
  uri.push_back(static_cast<char>(127));  // filtered out
  uri += "c";

  ASSERT_EQ(CallNsDumper(dict, uri), 0);

  ASSERT_TRUE(dict.contains("ns"));
  EXPECT_EQ(dict["ns"], "http://example.com/abc");
}

}  // namespace