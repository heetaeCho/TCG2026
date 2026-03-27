// TEST_ID: 78
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamResetColumnTest_78 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& s, std::istringstream& backing) {
    backing.str(s);
    backing.clear();
    return YAML::Stream(backing);
  }

  // Tries to move the stream forward until column() becomes non-zero (if possible).
  // This avoids assuming how column is tracked internally while still enabling an
  // observable "changed -> reset to 0" assertion when available.
  static void TryMakeColumnNonZero(YAML::Stream& stream) {
    // Avoid infinite loops; a small cap is enough for tests.
    for (int i = 0; i < 64 && stream; ++i) {
      if (stream.column() != 0) return;
      (void)stream.get();
    }
  }
};

TEST_F(StreamResetColumnTest_78, ResetColumnOnFreshStreamKeepsColumnZero_78) {
  std::istringstream input;
  YAML::Stream stream = MakeStream("abc", input);

  EXPECT_EQ(stream.column(), 0);
  stream.ResetColumn();
  EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamResetColumnTest_78, ResetColumnAfterAdvancingSetsColumnToZero_78) {
  std::istringstream input;
  YAML::Stream stream = MakeStream("abcdef", input);

  TryMakeColumnNonZero(stream);

  // If the implementation tracks column advancement, this should be non-zero here.
  // If not, the test still verifies that ResetColumn results in column()==0.
  stream.ResetColumn();
  EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamResetColumnTest_78, ResetColumnDoesNotChangePosOrLine_78) {
  std::istringstream input;
  YAML::Stream stream = MakeStream("abc\ndef", input);

  // Advance a bit to put the stream in a non-trivial state (if possible).
  (void)stream.get();
  (void)stream.get();

  const int before_pos = stream.pos();
  const int before_line = stream.line();

  stream.ResetColumn();

  EXPECT_EQ(stream.column(), 0);
  EXPECT_EQ(stream.pos(), before_pos);
  EXPECT_EQ(stream.line(), before_line);
}

TEST_F(StreamResetColumnTest_78, ResetColumnIsIdempotent_78) {
  std::istringstream input;
  YAML::Stream stream = MakeStream("xyz", input);

  TryMakeColumnNonZero(stream);

  stream.ResetColumn();
  EXPECT_EQ(stream.column(), 0);

  stream.ResetColumn();
  EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamResetColumnTest_78, ResetColumnAtEndOfStreamSetsColumnToZero_78) {
  std::istringstream input;
  YAML::Stream stream = MakeStream("a", input);

  // Consume the stream fully.
  while (stream) {
    (void)stream.get();
  }

  // Even at EOF (observable via operator bool / operator!), ResetColumn should be safe.
  stream.ResetColumn();
  EXPECT_EQ(stream.column(), 0);
}

}  // namespace
