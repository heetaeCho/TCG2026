// File: ./TestProjects/yaml-cpp/util/read_test.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

// Unit under test
std::string read_stream(std::istream& in);

namespace {

class ReadStreamTest_674 : public ::testing::Test {};

TEST_F(ReadStreamTest_674, ReadsEmptyStream_674) {
  std::istringstream in("");
  const std::string out = read_stream(in);
  EXPECT_TRUE(out.empty());
}

TEST_F(ReadStreamTest_674, ReadsSingleCharacter_674) {
  std::istringstream in("x");
  const std::string out = read_stream(in);
  EXPECT_EQ(out, "x");
}

TEST_F(ReadStreamTest_674, ReadsMultipleLinesPreservingNewlines_674) {
  std::istringstream in("line1\nline2\nline3");
  const std::string out = read_stream(in);
  EXPECT_EQ(out, "line1\nline2\nline3");
}

TEST_F(ReadStreamTest_674, ReadsBinaryLikeDataIncludingNullByte_674) {
  const char data[] = {'a', '\0', 'b', '\n', 'c', '\0'};
  std::string input(data, sizeof(data));

  std::istringstream in(input);
  const std::string out = read_stream(in);

  ASSERT_EQ(out.size(), input.size());
  EXPECT_EQ(out, input);
  EXPECT_EQ(out[0], 'a');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'b');
  EXPECT_EQ(out[3], '\n');
  EXPECT_EQ(out[4], 'c');
  EXPECT_EQ(out[5], '\0');
}

TEST_F(ReadStreamTest_674, ReadsLargeContent_674) {
  // Boundary-ish test: ensure it can handle a reasonably large stream.
  std::string big;
  big.reserve(256 * 1024);
  for (int i = 0; i < 256 * 1024; ++i) {
    big.push_back(static_cast<char>('a' + (i % 26)));
  }

  std::istringstream in(big);
  const std::string out = read_stream(in);

  EXPECT_EQ(out.size(), big.size());
  EXPECT_EQ(out, big);
}

TEST_F(ReadStreamTest_674, ReadsFromCurrentPositionNotFromBeginning_674) {
  std::istringstream in("prefix-skip-this|keep-this");
  // Move the read cursor to after the separator.
  in.seekg(static_cast<std::streamoff>(std::string("prefix-skip-this|").size()),
           std::ios_base::beg);

  const std::string out = read_stream(in);
  EXPECT_EQ(out, "keep-this");
}

TEST_F(ReadStreamTest_674, LeavesStreamAtEofAfterRead_674) {
  std::istringstream in("abc");
  const std::string out = read_stream(in);
  EXPECT_EQ(out, "abc");

  // Observable post-condition via stream state/position.
  EXPECT_TRUE(in.eof());
  EXPECT_FALSE(in.fail());  // reading to EOF should not imply hard failure
}

TEST_F(ReadStreamTest_674, SecondReadAfterEofReturnsEmpty_674) {
  std::istringstream in("abc");
  const std::string first = read_stream(in);
  EXPECT_EQ(first, "abc");

  const std::string second = read_stream(in);
  EXPECT_TRUE(second.empty());
}

TEST_F(ReadStreamTest_674, ErrorCaseBadStreamReturnsEmptyString_674) {
  std::istringstream in("should-not-be-read");
  // Put stream into a bad state (observable error case).
  in.setstate(std::ios::badbit);

  const std::string out = read_stream(in);
  EXPECT_TRUE(out.empty());
}

}  // namespace