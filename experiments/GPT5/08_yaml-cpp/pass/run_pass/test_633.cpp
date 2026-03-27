// TEST_ID: 633
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

// Forward declaration (avoid relying on additional headers not provided in prompt).
namespace YAML {
namespace Utils {
bool WriteComment(ostream_wrapper& out, const char* str, std::size_t size,
                  std::size_t postCommentIndent);
}  // namespace Utils
}  // namespace YAML

namespace {

static std::string GetOutput(std::stringstream& ss, YAML::ostream_wrapper& out) {
  // Prefer the underlying stream content (most direct observable output).
  const std::string fromStream = ss.str();
  if (!fromStream.empty()) return fromStream;

  // Fallback to wrapper's internal buffer view if stream output isn't used.
  const char* s = out.str();
  return s ? std::string(s) : std::string();
}

}  // namespace

TEST(WriteCommentTest_633, SingleLineWritesHashIndentAndText_633) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  const char* text = "hello";
  const std::size_t size = 5;

  const bool ok = YAML::Utils::WriteComment(out, text, size, /*postCommentIndent=*/1);

  EXPECT_TRUE(ok);
  EXPECT_EQ(GetOutput(ss, out), std::string("# ") + "hello");
  EXPECT_TRUE(out.comment());
}

TEST(WriteCommentTest_633, EmptySizeWritesOnlyHashAndIndent_633) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  const char* text = "ignored";
  const bool ok = YAML::Utils::WriteComment(out, text, /*size=*/0, /*postCommentIndent=*/3);

  EXPECT_TRUE(ok);
  EXPECT_EQ(GetOutput(ss, out), std::string("#") + "   ");
  EXPECT_TRUE(out.comment());
}

TEST(WriteCommentTest_633, MultiLinePrefixesEachLineWithCommentMarker_633) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  const std::string text = "a\nb";
  const bool ok =
      YAML::Utils::WriteComment(out, text.c_str(), text.size(), /*postCommentIndent=*/2);

  EXPECT_TRUE(ok);
  EXPECT_EQ(GetOutput(ss, out), std::string("#  ") + "a\n" + "#  " + "b");
  EXPECT_TRUE(out.comment());
}

TEST(WriteCommentTest_633, NewlineReappliesCurrentIndentBeforeNextComment_633) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  // Establish a non-zero current column (indent) before writing the comment.
  out.write("ABC", 3);
  ASSERT_EQ(GetOutput(ss, out), "ABC");
  ASSERT_EQ(out.col(), 3u);

  const std::string text = "x\ny";
  const bool ok =
      YAML::Utils::WriteComment(out, text.c_str(), text.size(), /*postCommentIndent=*/0);

  EXPECT_TRUE(ok);
  // After newline, it should indent back to the column that existed at entry (3 spaces here).
  EXPECT_EQ(GetOutput(ss, out), std::string("ABC") + "#x\n" + "   " + "#y");
  EXPECT_TRUE(out.comment());
}

TEST(WriteCommentTest_633, HandlesUtf8TextAcrossLines_633) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  const std::string text = u8"π\n🙂";
  const bool ok =
      YAML::Utils::WriteComment(out, text.c_str(), text.size(), /*postCommentIndent=*/1);

  EXPECT_TRUE(ok);
  EXPECT_EQ(GetOutput(ss, out), std::string("# ") + u8"π\n" + "# " + u8"🙂");
  EXPECT_TRUE(out.comment());
}