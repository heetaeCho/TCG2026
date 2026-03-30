// TEST_ID 1330
// Unit tests for Exiv2::ExifTags::taglist(std::ostream&, const std::string&)
//
// Constraints honored:
// - Treat implementation as a black box
// - Verify only observable behavior via public interface (stream output / exceptions)

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <sstream>
#include <string>

namespace {

class ExifTagsTaglistGroupTest_1330 : public ::testing::Test {
 protected:
  // Call through an instance to be compatible whether taglist is declared static or non-static
  // in the build configuration.
  static std::string TaglistForGroup(const std::string& groupName) {
    std::ostringstream os;
    Exiv2::ExifTags tags;
    tags.taglist(os, groupName);
    return os.str();
  }

  static std::string TaglistAll() {
    std::ostringstream os;
    Exiv2::ExifTags tags;
    tags.taglist(os);
    return os.str();
  }
};

TEST_F(ExifTagsTaglistGroupTest_1330, KnownGroupProducesNonEmptyOutput_1330) {
  // Pick a commonly available Exif group name in Exiv2.
  EXPECT_NO_THROW({
    const std::string out = TaglistForGroup("Exif.Image");
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(ExifTagsTaglistGroupTest_1330, AnotherKnownGroupProducesNonEmptyOutput_1330) {
  EXPECT_NO_THROW({
    const std::string out = TaglistForGroup("Exif.Photo");
    EXPECT_FALSE(out.empty());
  });
}

TEST_F(ExifTagsTaglistGroupTest_1330, EmptyGroupNameDoesNotThrowAndLeavesStreamUsable_1330) {
  std::ostringstream os;
  Exiv2::ExifTags tags;

  EXPECT_NO_THROW({ tags.taglist(os, ""); });

  // Observable behavior: stream should remain in a usable state.
  EXPECT_TRUE(os.good());
  // Avoid asserting specific content; implementations may treat empty group name specially.
}

TEST_F(ExifTagsTaglistGroupTest_1330, UnknownGroupNameDoesNotThrowAndLeavesStreamUsable_1330) {
  std::ostringstream os;
  Exiv2::ExifTags tags;

  EXPECT_NO_THROW({ tags.taglist(os, "This.Group.Does.Not.Exist"); });

  EXPECT_TRUE(os.good());
  // Content for unknown groups is implementation-defined; do not assert emptiness/non-emptiness.
}

TEST_F(ExifTagsTaglistGroupTest_1330, GroupOutputIsContainedWithinFullTaglistWhenBothNonEmpty_1330) {
  // Observable relationship test:
  // If the implementation prints the full taglist as a concatenation of per-group lists,
  // then the group's output should appear inside the full output.
  //
  // This avoids relying on private/internal functions (Internal::groupId / Internal::taglist).
  EXPECT_NO_THROW({
    const std::string groupOut = TaglistForGroup("Exif.Image");
    const std::string allOut = TaglistAll();

    // Only assert containment if both outputs are non-empty (format may vary across builds).
    ASSERT_FALSE(groupOut.empty());
    ASSERT_FALSE(allOut.empty());

    EXPECT_NE(allOut.find(groupOut), std::string::npos);
  });
}

TEST_F(ExifTagsTaglistGroupTest_1330, RepeatedCallsWithSameGroupAreDeterministic_1330) {
  EXPECT_NO_THROW({
    const std::string out1 = TaglistForGroup("Exif.Image");
    const std::string out2 = TaglistForGroup("Exif.Image");
    EXPECT_EQ(out1, out2);
  });
}

}  // namespace