// File: pcre_exec_test_186.cc
#include <gtest/gtest.h>

// Forward declarations to match the interface under test.
// We do not include or rely on any private/internal implementation details.
struct pcre;
struct pcre_extra;

// Function under test (provided by ./TestProjects/re2/util/pcre.cc)
int pcre_exec(const pcre*,
              const pcre_extra*,
              const char* subject,
              int length,
              int startoffset,
              int options,
              int* ovector,
              int ovecsize);

// Test fixture (kept minimal since there are no external collaborators to mock)
class PcreExecTest_186 : public ::testing::Test {};

// Normal operation: simple, typical inputs
TEST_F(PcreExecTest_186, ReturnsIntOnSimpleCall_186) {
  const char* subject = "hello";
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/5,
                     /*startoffset=*/0,
                     /*options=*/0,
                     /*ovector=*/nullptr,
                     /*ovecsize=*/0);
  // Observable behavior: function returns an int. We assert it succeeds returning a value.
  // Given the provided implementation, we expect 0 (black-box observable behavior).
  EXPECT_EQ(rc, 0);
}

// Boundary: empty subject with zero length
TEST_F(PcreExecTest_186, HandlesEmptySubject_186) {
  const char* subject = "";
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/0,
                     /*startoffset=*/0,
                     /*options=*/0,
                     /*ovector=*/nullptr,
                     /*ovecsize=*/0);
  EXPECT_EQ(rc, 0);
}

// Boundary: nullptr subject pointer (interface allows const char*; passing nullptr should be handled gracefully)
TEST_F(PcreExecTest_186, HandlesNullSubjectPointer_186) {
  const char* subject = nullptr;
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/0,
                     /*startoffset=*/0,
                     /*options=*/0,
                     /*ovector=*/nullptr,
                     /*ovecsize=*/0);
  EXPECT_EQ(rc, 0);
}

// Boundary: negative start offset (atypical but possible to pass via interface)
TEST_F(PcreExecTest_186, AcceptsNegativeStartOffset_186) {
  const char* subject = "abc";
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/3,
                     /*startoffset=*/-1,
                     /*options=*/0,
                     /*ovector=*/nullptr,
                     /*ovecsize=*/0);
  EXPECT_EQ(rc, 0);
}

// Boundary: large length and flags; verifies it accepts values at extremes without observable error
TEST_F(PcreExecTest_186, AcceptsLargeLengthAndOptions_186) {
  const char* subject = "abc";
  int ovec[6] = {0};
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/INT_MAX,  // extreme length
                     /*startoffset=*/0,
                     /*options=*/0x7fffffff,  // extreme options bitmask
                     /*ovector=*/ovec,
                     /*ovecsize=*/static_cast<int>(std::size(ovec)));
  EXPECT_EQ(rc, 0);
}

// Robustness: null pcre and pcre_extra with non-null output vector
TEST_F(PcreExecTest_186, NullPatternAndExtraWithOutputVector_186) {
  const char* subject = "xyz";
  int ovec[2] = {123, 456};  // we do not assert on side effects per constraints
  int rc = pcre_exec(nullptr, nullptr, subject,
                     /*length=*/3,
                     /*startoffset=*/0,
                     /*options=*/0,
                     /*ovector=*/ovec,
                     /*ovecsize=*/2);
  EXPECT_EQ(rc, 0);
}

// Consistency: repeated calls with same inputs yield the same observable return value
TEST_F(PcreExecTest_186, IdempotentReturnForSameInputs_186) {
  const char* subject = "repeat";
  int rc1 = pcre_exec(nullptr, nullptr, subject, 6, 0, 0, nullptr, 0);
  int rc2 = pcre_exec(nullptr, nullptr, subject, 6, 0, 0, nullptr, 0);
  EXPECT_EQ(rc1, rc2);
  EXPECT_EQ(rc1, 0);
}
