#include <gtest/gtest.h>

#include "leveldb/slice.h"

#include <string>



using namespace leveldb;



class SliceTest_4 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialization if needed

    }

};



TEST_F(SliceTest_4, DefaultConstructorCreatesEmptySlice_4) {

    Slice slice;

    EXPECT_TRUE(slice.empty());

    EXPECT_EQ(slice.size(), 0);

}



TEST_F(SliceTest_4, ConstructorWithCharPtrAndSizeSetsDataAndSizeCorrectly_4) {

    const char* data = "hello";

    size_t size = 5;

    Slice slice(data, size);

    EXPECT_EQ(slice.data(), data);

    EXPECT_EQ(slice.size(), size);

}



TEST_F(SliceTest_4, ConstructorWithStringLiteralSetsDataAndSizeCorrectly_4) {

    const char* expected_data = "world";

    Slice slice(expected_data);

    EXPECT_STREQ(slice.data(), expected_data);

    EXPECT_EQ(slice.size(), strlen(expected_data));

}



TEST_F(SliceTest_4, ConstructorWithStdStringSetsDataAndSizeCorrectly_4) {

    std::string str = "example";

    Slice slice(str);

    EXPECT_STREQ(slice.data(), str.c_str());

    EXPECT_EQ(slice.size(), str.size());

}



TEST_F(SliceTest_4, CopyConstructorCreatesIdenticalSlice_4) {

    const char* data = "test";

    size_t size = 4;

    Slice original(data, size);

    Slice copy(original);

    EXPECT_EQ(copy.data(), original.data());

    EXPECT_EQ(copy.size(), original.size());

}



TEST_F(SliceTest_4, AssignmentOperatorCreatesIdenticalSlice_4) {

    const char* data = "assignment";

    size_t size = 10;

    Slice original(data, size);

    Slice copy;

    copy = original;

    EXPECT_EQ(copy.data(), original.data());

    EXPECT_EQ(copy.size(), original.size());

}



TEST_F(SliceTest_4, BeginAndEndReturnCorrectPointers_4) {

    const char* data = "boundary";

    size_t size = 8;

    Slice slice(data, size);

    EXPECT_EQ(slice.begin(), data);

    EXPECT_EQ(slice.end(), data + size);

}



TEST_F(SliceTest_4, OperatorBracketReturnsCorrectCharacter_4) {

    const char* data = "indexing";

    Slice slice(data);

    for (size_t i = 0; i < slice.size(); ++i) {

        EXPECT_EQ(slice[i], data[i]);

    }

}



TEST_F(SliceTest_4, ClearMethodResetsSliceToEmpty_4) {

    const char* data = "clearing";

    Slice slice(data);

    slice.clear();

    EXPECT_TRUE(slice.empty());

    EXPECT_EQ(slice.size(), 0);

}



TEST_F(SliceTest_4, RemovePrefixReducesSizeAndMovesDataPointer_4) {

    const char* data = "prefix";

    size_t prefix_size = 2;

    Slice slice(data);

    slice.remove_prefix(prefix_size);

    EXPECT_STREQ(slice.data(), data + prefix_size);

    EXPECT_EQ(slice.size(), strlen(data) - prefix_size);

}



TEST_F(SliceTest_4, ToStringReturnsCorrectStringRepresentation_4) {

    const char* data = "string";

    Slice slice(data);

    std::string result = slice.ToString();

    EXPECT_STREQ(result.c_str(), data);

}



TEST_F(SliceTest_4, StartsWithReturnsTrueForMatchingPrefix_4) {

    const char* data = "startswith";

    Slice slice(data);

    Slice prefix("start");

    EXPECT_TRUE(slice.starts_with(prefix));

}



TEST_F(SliceTest_4, StartsWithReturnsFalseForNonMatchingPrefix_4) {

    const char* data = "startswith";

    Slice slice(data);

    Slice prefix("nonmatch");

    EXPECT_FALSE(slice.starts_with(prefix));

}



TEST_F(SliceTest_4, CompareReturnsZeroForEqualSlices_4) {

    const char* data = "equal";

    Slice a(data);

    Slice b(data);

    EXPECT_EQ(a.compare(b), 0);

}



TEST_F(SliceTest_4, CompareReturnsNegativeForFirstSliceSmaller_4) {

    Slice a("small");

    Slice b("large");

    EXPECT_LT(a.compare(b), 0);

}



TEST_F(SliceTest_4, CompareReturnsPositiveForFirstSliceLarger_4) {

    Slice a("large");

    Slice b("small");

    EXPECT_GT(a.compare(b), 0);

}
