// TEST_ID: 156
#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>
#include <utility>

#include "scanner.h"
#include "stream.h"

namespace {

// --- Mark comparison helpers (robust to different Mark implementations) ---

template <typename T, typename = void>
struct has_mark_equal_op : std::false_type {};
template <typename T>
struct has_mark_equal_op<T, std::void_t<decltype(std::declval<const T&>() ==
                                                std::declval<const T&>())>> : std::true_type {};

template <typename T, typename = void>
struct has_mark_pos_line_col : std::false_type {};
template <typename T>
struct has_mark_pos_line_col<
    T, std::void_t<decltype(std::declval<const T&>().pos),
                   decltype(std::declval<const T&>().line),
                   decltype(std::declval<const T&>().column)>> : std::true_type {};

template <typename MarkT>
typename std::enable_if<has_mark_equal_op<MarkT>::value, void>::type
ExpectMarksEqual(const MarkT& a, const MarkT& b) {
  EXPECT_TRUE(a == b);
}

template <typename MarkT>
typename std::enable_if<!has_mark_equal_op<MarkT>::value &&
                            has_mark_pos_line_col<MarkT>::value,
                        void>::type
ExpectMarksEqual(const MarkT& a, const MarkT& b) {
  EXPECT_EQ(a.pos, b.pos);
  EXPECT_EQ(a.line, b.line);
  EXPECT_EQ(a.column, b.column);
}

// Fallback: if neither operator== nor (pos,line,column) are available, we can
// only verify the call is well-formed (compiles) and returns a Mark value.
template <typename MarkT>
typename std::enable_if<!has_mark_equal_op<MarkT>::value &&
                            !has_mark_pos_line_col<MarkT>::value,
                        void>::type
ExpectMarksEqual(const MarkT&, const MarkT&) {
  SUCCEED() << "Mark has no observable equality/fields; verified mark() is callable.";
}

}  // namespace

namespace YAML {

class ScannerMarkTest_156 : public ::testing::Test {};

TEST_F(ScannerMarkTest_156, MarkMatchesStreamAtConstruction_NonEmpty_156) {
  std::stringstream ss_scanner("abc\n123");
  std::stringstream ss_stream("abc\n123");

  Scanner scanner(ss_scanner);
  Stream stream(ss_stream);

  const Mark m_scanner = scanner.mark();
  const Mark m_stream = stream.mark();

  ExpectMarksEqual(m_scanner, m_stream);
}

TEST_F(ScannerMarkTest_156, MarkMatchesStreamAtConstruction_Empty_156) {
  std::stringstream ss_scanner("");
  std::stringstream ss_stream("");

  Scanner scanner(ss_scanner);
  Stream stream(ss_stream);

  const Mark m_scanner = scanner.mark();
  const Mark m_stream = stream.mark();

  ExpectMarksEqual(m_scanner, m_stream);
}

TEST_F(ScannerMarkTest_156, MarkIsStableAcrossRepeatedCalls_156) {
  std::stringstream ss("key: value\n");
  Scanner scanner(ss);

  const Mark m1 = scanner.mark();
  const Mark m2 = scanner.mark();
  ExpectMarksEqual(m1, m2);
}

TEST_F(ScannerMarkTest_156, MarkAfterSameObservableOperations_IsDeterministic_156) {
  std::stringstream ss1("a: 1\nb: 2\n");
  std::stringstream ss2("a: 1\nb: 2\n");

  Scanner s1(ss1);
  Scanner s2(ss2);

  // Observable operations through public API (black-box):
  // calling peek() should be safe even if it triggers tokenization internally.
  (void)s1.peek();
  (void)s2.peek();

  const Mark m1 = s1.mark();
  const Mark m2 = s2.mark();
  ExpectMarksEqual(m1, m2);

  // Pop once (if possible) and compare again. Guard against empty scanners.
  if (!s1.empty() && !s2.empty()) {
    s1.pop();
    s2.pop();
    const Mark m1_after = s1.mark();
    const Mark m2_after = s2.mark();
    ExpectMarksEqual(m1_after, m2_after);
  }
}

}  // namespace YAML
