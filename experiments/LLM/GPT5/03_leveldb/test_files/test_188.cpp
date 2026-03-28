// db/dbformat_name_test_188.cc
#include <gtest/gtest.h>
#include <cstring>
#include <string>

// The SUT is defined in db/dbformat.cc as shown in the prompt:
// namespace leveldb {
// class InternalKeyComparator {
//  public:
//   const char* Name() const { return "leveldb.InternalKeyComparator"; }
// };
// }

namespace leveldb {

class InternalKeyComparatorTest_188 : public ::testing::Test {};

// Verifies that Name() returns the expected comparator name string.
TEST_F(InternalKeyComparatorTest_188, Name_ReturnsExpectedLiteral_188) {
  InternalKeyComparator cmp;
  EXPECT_STREQ("leveldb.InternalKeyComparator", cmp.Name());
}

// Verifies the returned pointer is non-null and points to a C-string.
TEST_F(InternalKeyComparatorTest_188, Name_ReturnsNonNullCString_188) {
  InternalKeyComparator cmp;
  const char* name = cmp.Name();
  ASSERT_NE(nullptr, name);
  // Use strlen to confirm it is a valid null-terminated C-string.
  EXPECT_EQ(std::strlen("leveldb.InternalKeyComparator"), std::strlen(name));
}

// Verifies repeated calls return the same address (string literal stability).
TEST_F(InternalKeyComparatorTest_188, Name_ReturnsStablePointer_188) {
  InternalKeyComparator cmp;
  const char* first = cmp.Name();
  const char* second = cmp.Name();
  EXPECT_EQ(first, second);
}

// Verifies multiple instances expose the same observable name.
TEST_F(InternalKeyComparatorTest_188, Name_ConsistentAcrossInstances_188) {
  InternalKeyComparator a;
  InternalKeyComparator b;
  EXPECT_STREQ(a.Name(), b.Name());
  // Optional: pointer equality—both call the same function that returns
  // the same string literal in this build.
  EXPECT_EQ(a.Name(), b.Name());
}

}  // namespace leveldb
