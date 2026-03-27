#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.cc"

#include "leveldb/slice.h"



using namespace leveldb;



class ComparatorTest_212 : public ::testing::Test {

protected:

    void SetUp() override {

        comparator.compare_ = [](void*, const char* a, size_t alen, const char* b, size_t blen) -> int {

            return std::string(a, alen).compare(std::string(b, blen));

        };

    }



    leveldb_comparator_t comparator;

};



TEST_F(ComparatorTest_212, CompareEqualStrings_212) {

    Slice a("test");

    Slice b("test");

    EXPECT_EQ(comparator.Compare(a, b), 0);

}



TEST_F(ComparatorTest_212, CompareDifferentStringsFirstLess_212) {

    Slice a("abc");

    Slice b("def");

    EXPECT_LT(comparator.Compare(a, b), 0);

}



TEST_F(ComparatorTest_212, CompareDifferentStringsSecondLess_212) {

    Slice a("xyz");

    Slice b("uvw");

    EXPECT_GT(comparator.Compare(a, b), 0);

}



TEST_F(ComparatorTest_212, EmptyStringComparison_212) {

    Slice a("");

    Slice b("");

    EXPECT_EQ(comparator.Compare(a, b), 0);

}



TEST_F(ComparatorTest_212, EmptyStringVsNonEmptyString_212) {

    Slice a("");

    Slice b("nonempty");

    EXPECT_LT(comparator.Compare(a, b), 0);

}



TEST_F(ComparatorTest_212, NonEmptyStringVsEmptyString_212) {

    Slice a("nonempty");

    Slice b("");

    EXPECT_GT(comparator.Compare(a, b), 0);

}
