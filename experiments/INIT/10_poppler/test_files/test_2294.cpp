// build_uri_test_2294.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>
#include <optional>
#include <string>

#include "poppler-action.h"
#include "Link.h"
#include "Object.h"
#include "GooString.h"

// Include the .cc directly to access the internal static function under test.
#include "poppler-action.cc"

namespace {

class BuildUriTest_2294 : public ::testing::Test {
protected:
  void TearDown() override {
    // Nothing here; individual tests free any allocated uri strings they create.
  }
};

TEST_F(BuildUriTest_2294, CopiesNonEmptyUriString_2294) {
  Object uriObj;
  uriObj.initString(new GooString("https://example.com/path?x=1"));

  LinkURI link(&uriObj, std::optional<std::string>{});
  ASSERT_TRUE(link.isOk());

  PopplerAction action;
  std::memset(&action, 0, sizeof(action));

  build_uri(&action, &link);

  ASSERT_NE(action.uri.uri, nullptr);
  EXPECT_STREQ(action.uri.uri, "https://example.com/path?x=1");

  // Verify the stored string is a duplicate (i.e., not the same pointer as link's c_str()).
  EXPECT_NE(static_cast<const void*>(action.uri.uri),
            static_cast<const void*>(link.getURI().c_str()));

  g_free(action.uri.uri);
  action.uri.uri = nullptr;
}

TEST_F(BuildUriTest_2294, CopiesEmptyUriString_2294) {
  Object uriObj;
  uriObj.initString(new GooString(""));

  LinkURI link(&uriObj, std::optional<std::string>{});
  ASSERT_TRUE(link.isOk());

  PopplerAction action;
  std::memset(&action, 0, sizeof(action));

  build_uri(&action, &link);

  ASSERT_NE(action.uri.uri, nullptr);
  EXPECT_STREQ(action.uri.uri, "");

  g_free(action.uri.uri);
  action.uri.uri = nullptr;
}

TEST_F(BuildUriTest_2294, OverwritesExistingActionUriPointer_2294) {
  Object firstObj;
  firstObj.initString(new GooString("https://first.example/"));

  Object secondObj;
  secondObj.initString(new GooString("https://second.example/"));

  LinkURI firstLink(&firstObj, std::optional<std::string>{});
  LinkURI secondLink(&secondObj, std::optional<std::string>{});
  ASSERT_TRUE(firstLink.isOk());
  ASSERT_TRUE(secondLink.isOk());

  PopplerAction action;
  std::memset(&action, 0, sizeof(action));

  build_uri(&action, &firstLink);
  ASSERT_NE(action.uri.uri, nullptr);
  EXPECT_STREQ(action.uri.uri, "https://first.example/");
  gchar* first_ptr = action.uri.uri;

  build_uri(&action, &secondLink);
  ASSERT_NE(action.uri.uri, nullptr);
  EXPECT_STREQ(action.uri.uri, "https://second.example/");

  // Observable effect: pointer value changes (new duplicate assigned).
  EXPECT_NE(action.uri.uri, first_ptr);

  // Clean up: both allocations need freeing to avoid leaks in the test binary.
  g_free(first_ptr);
  g_free(action.uri.uri);
  action.uri.uri = nullptr;
}

TEST_F(BuildUriTest_2294, HandlesUriWithEmbeddedNulByCopyingCStringPrefix_2294) {
  // Boundary-ish case: std::string may contain embedded '\0'. build_uri uses c_str(),
  // so the duplicated C string will end at the first NUL.
  const char raw[] = {'a', 'b', 'c', '\0', 'd', 'e', 'f', '\0'};

  Object uriObj;
  uriObj.initString(new GooString(raw)); // GooString constructed from C string will stop at first NUL.

  LinkURI link(&uriObj, std::optional<std::string>{});
  ASSERT_TRUE(link.isOk());

  PopplerAction action;
  std::memset(&action, 0, sizeof(action));

  build_uri(&action, &link);

  ASSERT_NE(action.uri.uri, nullptr);
  // At minimum, the prefix up to the first NUL should match.
  EXPECT_STREQ(action.uri.uri, "abc");

  g_free(action.uri.uri);
  action.uri.uri = nullptr;
}

} // namespace