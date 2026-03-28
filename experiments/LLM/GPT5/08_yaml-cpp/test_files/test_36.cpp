// TEST_ID: 36
//
// Unit tests for YAML::operator<<(Emitter&, const std::string_view&)
// File under test: yaml-cpp/emitter.h

#include <gtest/gtest.h>

#include <yaml-cpp/emitter.h>

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

namespace {

std::string ExtractEmitterBuffer(const YAML::Emitter& e) {
  const std::size_t n = e.size();
  if (n == 0) return std::string();
  const char* p = e.c_str();
  // Even if p is nullptr (shouldn't be in normal implementations), avoid UB.
  if (!p) return std::string();
  return std::string(p, n);
}

}  // namespace

TEST(EmitterStringViewOperatorTest_36, OperatorMatchesWriteCharPtrSize_36) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  const std::string payload = "plain-text";
  const std::string_view sv(payload);

  via_op << sv;
  via_write.Write(sv.data(), sv.size());

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(ExtractEmitterBuffer(via_op), ExtractEmitterBuffer(via_write));
}

TEST(EmitterStringViewOperatorTest_36, ChainingMatchesMultipleWriteCalls_36) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  const std::string a = "a";
  const std::string b = "bbb";
  const std::string c = "ccc";

  via_op << std::string_view(a) << std::string_view(b) << std::string_view(c);

  via_write.Write(a.data(), a.size());
  via_write.Write(b.data(), b.size());
  via_write.Write(c.data(), c.size());

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(ExtractEmitterBuffer(via_op), ExtractEmitterBuffer(via_write));
}

TEST(EmitterStringViewOperatorTest_36, EmptyStringViewMatchesWriteWithZeroSize_36) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  const std::string_view empty_sv("");

  via_op << empty_sv;
  via_write.Write(empty_sv.data(), empty_sv.size());

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(ExtractEmitterBuffer(via_op), ExtractEmitterBuffer(via_write));
}

TEST(EmitterStringViewOperatorTest_36, EmbeddedNullsAreHandledConsistently_36) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  // string_view can include embedded nulls; operator<< forwards (data,size).
  const std::string with_nulls(std::string("A\0B\0C", 5));
  const std::string_view sv(with_nulls.data(), with_nulls.size());

  via_op << sv;
  via_write.Write(sv.data(), sv.size());

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(ExtractEmitterBuffer(via_op), ExtractEmitterBuffer(via_write));
}

TEST(EmitterStringViewOperatorTest_36, LargeInputMatchesWriteCharPtrSize_36) {
  YAML::Emitter via_op;
  YAML::Emitter via_write;

  // Boundary-ish test: larger than small-string optimization sizes.
  std::string large(10000, 'x');
  std::string_view sv(large);

  via_op << sv;
  via_write.Write(sv.data(), sv.size());

  EXPECT_EQ(via_op.good(), via_write.good());
  EXPECT_EQ(via_op.GetLastError(), via_write.GetLastError());
  EXPECT_EQ(via_op.size(), via_write.size());
  EXPECT_EQ(ExtractEmitterBuffer(via_op), ExtractEmitterBuffer(via_write));
}
