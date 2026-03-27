// File: ./TestProjects/yaml-cpp/test/stream_column_test_77.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Prefer the project header path used by the codebase.
// If your build exposes it differently, adjust include paths accordingly.
#include "TestProjects/yaml-cpp/src/stream.h"

namespace {

class StreamColumnTest_77 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStreamFrom(const std::string& s, std::stringstream& backing) {
    backing.str(s);
    backing.clear();
    return YAML::Stream(backing);
  }
};

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnOnConstruction_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("", ss);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnIsCallableThroughConstReference_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abc", ss);

  const YAML::Stream& cref = stream;
  const YAML::Mark m = cref.mark();
  EXPECT_EQ(cref.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAfterPeek_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abc", ss);

  (void)stream.peek();

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAfterSingleGet_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abc", ss);

  (void)stream.get();

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAfterGetN_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  (void)stream.get(3);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAfterEat_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  stream.eat(2);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAcrossMixedOperations_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  (void)stream.peek();
  (void)stream.get();
  stream.eat(2);
  (void)stream.get(1);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ColumnMatchesMarkColumnAtEndOfStreamAfterReads_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("x", ss);

  (void)stream.get();   // consume the only character
  (void)stream.peek();  // peek at EOF (behavior is implementation-defined, but should be safe)

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ResetColumnKeepsColumnConsistentWithMark_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  // Advance some amount without assuming exact column semantics.
  (void)stream.get(3);

  // ResetColumn is part of the public interface; verify the observable invariant still holds.
  stream.ResetColumn();

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ZeroLengthEatDoesNotBreakColumnMarkInvariant_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  stream.eat(0);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

TEST_F(StreamColumnTest_77, ZeroLengthGetDoesNotBreakColumnMarkInvariant_77) {
  std::stringstream ss;
  YAML::Stream stream = MakeStreamFrom("abcdef", ss);

  (void)stream.get(0);

  const YAML::Mark m = stream.mark();
  EXPECT_EQ(stream.column(), m.column);
}

}  // namespace
