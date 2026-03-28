// TEST_ID: 26
//
// Unit tests for YAML::ostream_wrapper::str()
// Constraints respected:
// - Treat implementation as black box (only use public interface + observable effects)
// - Verify external interactions via std::ostringstream when constructed with a stream

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

using YAML::ostream_wrapper;

TEST(OstreamWrapperStrTest_26, DefaultCtorReturnsNonNullEmptyCString_26) {
  ostream_wrapper w;

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "");
}

TEST(OstreamWrapperStrTest_26, DefaultCtorStrIsStableAcrossRepeatedCallsWithoutWrites_26) {
  ostream_wrapper w;

  const char* s1 = w.str();
  const char* s2 = w.str();

  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  // With no intervening writes, content should remain the same.
  EXPECT_STREQ(s1, "");
  EXPECT_STREQ(s2, "");

  // Pointer stability is a reasonable observable expectation when nothing changes.
  EXPECT_EQ(s1, s2);
}

TEST(OstreamWrapperStrTest_26, StreamCtorReturnsNullptr_26) {
  std::ostringstream out;
  ostream_wrapper w(out);

  EXPECT_EQ(w.str(), nullptr);
}

TEST(OstreamWrapperStrTest_26, StreamCtorStrStaysNullptrAfterWriteStringAndWritesToStream_26) {
  std::ostringstream out;
  ostream_wrapper w(out);

  w.write(std::string("hello"));
  EXPECT_EQ(w.str(), nullptr);
  EXPECT_EQ(out.str(), "hello");
}

TEST(OstreamWrapperStrTest_26, StreamCtorStrStaysNullptrAfterWriteBufferAndWritesToStream_26) {
  std::ostringstream out;
  ostream_wrapper w(out);

  const char data[] = {'a', 'b', 'c'};
  w.write(data, sizeof(data));

  EXPECT_EQ(w.str(), nullptr);
  EXPECT_EQ(out.str(), "abc");
}

TEST(OstreamWrapperStrTest_26, DefaultCtorWriteStringIsObservableViaStr_26) {
  ostream_wrapper w;

  w.write(std::string("yaml"));

  const char* s = w.str();
  ASSERT_NE(s, nullptr);
  EXPECT_STREQ(s, "yaml");
}

TEST(OstreamWrapperStrTest_26, DefaultCtorWriteEmptyDoesNotChangeStr_26) {
  ostream_wrapper w;

  w.write(std::string(""));
  const char* s1 = w.str();
  ASSERT_NE(s1, nullptr);
  EXPECT_STREQ(s1, "");

  // Also test the (const char*, size) overload with size 0.
  w.write("ignored", 0);
  const char* s2 = w.str();
  ASSERT_NE(s2, nullptr);
  EXPECT_STREQ(s2, "");
}

}  // namespace
