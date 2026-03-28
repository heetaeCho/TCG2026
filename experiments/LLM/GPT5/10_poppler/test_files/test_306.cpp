// LinkMovie_getAnnotTitle_tests_306.cpp
// Unit tests for LinkMovie::getAnnotTitle()
// The TEST_ID is 306

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

#include "Link.h"
#include "Object.h"

namespace {

// Compile-time interface checks (do not depend on implementation details).
static_assert(std::is_same_v<
                  decltype(std::declval<const LinkMovie&>().getAnnotTitle()),
                  const std::string&>,
              "LinkMovie::getAnnotTitle() must return const std::string&");

}  // namespace

TEST(LinkMovieTest_306, GetAnnotTitle_ReturnsStableConstReference_306) {
  // Arrange: construct with a well-defined "null" Object (boundary / error-like input)
  Object obj;
  obj.initNull();

  LinkMovie movie(&obj);
  const LinkMovie& cmovie = movie;

  // Act
  const std::string& t1 = cmovie.getAnnotTitle();
  const std::string& t2 = cmovie.getAnnotTitle();

  // Assert: should be a stable reference (same underlying string object)
  EXPECT_EQ(&t1, &t2);

  // Basic usability checks (no assumptions about content)
  EXPECT_GE(t1.size(), 0u);
  (void)t1.c_str();  // should be safe to call while movie is alive
}

TEST(LinkMovieTest_306, GetAnnotTitle_IsCallableOnConstObject_306) {
  Object obj;
  obj.initNull();

  const LinkMovie movie(&obj);

  // Just verify it is callable and returns a reference we can bind to.
  const std::string& titleRef = movie.getAnnotTitle();
  EXPECT_GE(titleRef.size(), 0u);
}

TEST(LinkMovieTest_306, GetAnnotTitle_DoesNotChangeAcrossRepeatedCalls_306) {
  Object obj;
  obj.initNull();

  LinkMovie movie(&obj);

  const std::string& before = movie.getAnnotTitle();
  const char* cstrBefore = before.c_str();

  const std::string& after = movie.getAnnotTitle();
  const char* cstrAfter = after.c_str();

  // We do NOT assert content. We only assert the accessor is consistent/stable.
  EXPECT_EQ(&before, &after);
  EXPECT_EQ(cstrBefore, cstrAfter);
}