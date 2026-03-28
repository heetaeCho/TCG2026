// TEST_ID: 541
// File: emitter_write_comment_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterWriteCommentTest_541 : public ::testing::Test {
 protected:
  static std::string Str(const YAML::Emitter& e) {
    const char* p = e.c_str();
    return p ? std::string(p) : std::string();
  }
};

TEST_F(EmitterWriteCommentTest_541, WriteBasicCommentContainsContent_541) {
  YAML::Emitter out;

  ASSERT_TRUE(out.good());
  const std::string before = Str(out);
  const std::size_t beforeSize = out.size();

  YAML::_Comment c("hello");
  YAML::Emitter& ret = out.Write(c);

  EXPECT_EQ(&ret, &out);
  EXPECT_TRUE(out.good());

  const std::string after = Str(out);
  EXPECT_GE(out.size(), beforeSize);
  EXPECT_NE(after, before);
  EXPECT_NE(after.find("hello"), std::string::npos);
}

TEST_F(EmitterWriteCommentTest_541, WriteEmptyCommentDoesNotCrashAndProducesOutput_541) {
  YAML::Emitter out;

  const std::size_t beforeSize = out.size();
  const std::string before = Str(out);

  YAML::_Comment c("");
  out.Write(c);

  EXPECT_TRUE(out.good());
  const std::string after = Str(out);
  EXPECT_GE(out.size(), beforeSize);
  EXPECT_NE(after, before);  // should have written *something* comment-related
}

TEST_F(EmitterWriteCommentTest_541, PreCommentIndentAffectsPositionWhenNotAtColumnZero_541) {
  // Create two independent emitters and write the same prefix so the stream column > 0.
  YAML::Emitter out0;
  YAML::Emitter out4;

  ASSERT_TRUE(out0.good());
  ASSERT_TRUE(out4.good());

  // Ensure we are not at column 0 by writing a single character first.
  out0.Write('a');
  out4.Write('a');

  // Set different pre-comment indents.
  ASSERT_TRUE(out0.SetPreCommentIndent(0));
  ASSERT_TRUE(out4.SetPreCommentIndent(4));

  // Use a unique comment payload to locate it reliably in the output.
  const std::string payload = "PAYLOAD_541";
  out0.Write(YAML::_Comment(payload));
  out4.Write(YAML::_Comment(payload));

  const std::string s0 = Str(out0);
  const std::string s4 = Str(out4);

  const std::size_t pos0 = s0.find(payload);
  const std::size_t pos4 = s4.find(payload);

  ASSERT_NE(pos0, std::string::npos);
  ASSERT_NE(pos4, std::string::npos);

  // With greater pre-comment indent, the payload should appear later (more chars inserted before it).
  EXPECT_GT(pos4, pos0);
  EXPECT_TRUE(out0.good());
  EXPECT_TRUE(out4.good());
}

TEST_F(EmitterWriteCommentTest_541, PostCommentIndentAffectsMultilineCommentFormatting_541) {
  const std::string payload = std::string("line1_541\nline2_541");

  YAML::Emitter out0;
  YAML::Emitter out2;

  ASSERT_TRUE(out0.SetPostCommentIndent(0));
  ASSERT_TRUE(out2.SetPostCommentIndent(2));

  out0.Write(YAML::_Comment(payload));
  out2.Write(YAML::_Comment(payload));

  const std::string s0 = Str(out0);
  const std::string s2 = Str(out2);

  // Both should contain both logical lines.
  EXPECT_NE(s0.find("line1_541"), std::string::npos);
  EXPECT_NE(s0.find("line2_541"), std::string::npos);
  EXPECT_NE(s2.find("line1_541"), std::string::npos);
  EXPECT_NE(s2.find("line2_541"), std::string::npos);

  // Different post-indent settings should yield different serialized output.
  EXPECT_NE(s0, s2);
}

TEST_F(EmitterWriteCommentTest_541, WriteVeryLongCommentIncludesContentAndIncreasesSize_541) {
  YAML::Emitter out;

  const std::size_t beforeSize = out.size();
  std::string big(2048, 'x');
  big.replace(100, 12, "MARK_541_X");  // embed a marker to search for

  out.Write(YAML::_Comment(big));

  EXPECT_TRUE(out.good());
  EXPECT_GT(out.size(), beforeSize);

  const std::string after = Str(out);
  EXPECT_NE(after.find("MARK_541_X"), std::string::npos);
}

TEST_F(EmitterWriteCommentTest_541, WriteReturnsSameEmitterForChaining_541) {
  YAML::Emitter out;

  YAML::Emitter& r1 = out.Write(YAML::_Comment("c1_541"));
  YAML::Emitter& r2 = r1.Write(YAML::_Comment("c2_541"));

  EXPECT_EQ(&r1, &out);
  EXPECT_EQ(&r2, &out);

  const std::string s = Str(out);
  EXPECT_NE(s.find("c1_541"), std::string::npos);
  EXPECT_NE(s.find("c2_541"), std::string::npos);
}

TEST_F(EmitterWriteCommentTest_541, WhenEmitterBecomesBadWriteCommentDoesNotChangeOutputIfBadIsObservable_541) {
  YAML::Emitter out;

  // Try to drive the emitter into a bad state through the public interface (without assuming which values are invalid).
  // If we cannot observe a bad state via the interface, skip.
  bool becameBad = false;

  // A small set of potentially-invalid candidates for indent-related settings.
  const std::size_t candidates[] = {0u, 1u, 2u, 1000u, 10000u};

  for (std::size_t v : candidates) {
    // If any setter returns false or causes good() to become false, we consider the bad state observable.
    const bool okIndent = out.SetIndent(v);
    const bool okPre = out.SetPreCommentIndent(v);
    const bool okPost = out.SetPostCommentIndent(v);

    if (!okIndent || !okPre || !okPost || !out.good()) {
      becameBad = !out.good() || (!okIndent || !okPre || !okPost);
      break;
    }
  }

  if (!becameBad) {
    GTEST_SKIP() << "Could not observe an error state via public setters on this build/config.";
  }

  const std::string before = Str(out);
  const std::size_t beforeSize = out.size();

  out.Write(YAML::_Comment("should_not_write_541"));

  // Based on the implementation snippet, Write(comment) returns early if !good().
  // If the bad state is observable, output should remain unchanged.
  EXPECT_EQ(out.size(), beforeSize);
  EXPECT_EQ(Str(out), before);
}

}  // namespace