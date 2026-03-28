#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch;

using namespace Catch::Detail;



// Mock for StringRef if necessary (not needed in this case as it's a simple wrapper)

class MockStringRef {

public:

    MOCK_CONST_METHOD0(data, const char*());

    MOCK_CONST_METHOD0(size, std::size_t());

};



TEST(TagComparisonTest_993, CaseInsensitiveEquality_SameString_993) {

    StringRef lhs("example");

    StringRef rhs("example");

    Tag tag1(lhs);

    Tag tag2(rhs);



    EXPECT_TRUE(tag1 == tag2);

}



TEST(TagComparisonTest_993, CaseInsensitiveEquality_DifferentCase_993) {

    StringRef lhs("Example");

    StringRef rhs("example");

    Tag tag1(lhs);

    Tag tag2(rhs);



    EXPECT_TRUE(tag1 == tag2);

}



TEST(TagComparisonTest_993, CaseInsensitiveEquality_DifferentStrings_993) {

    StringRef lhs("example");

    StringRef rhs("different");

    Tag tag1(lhs);

    Tag tag2(rhs);



    EXPECT_FALSE(tag1 == tag2);

}



TEST(TagComparisonTest_993, CaseInsensitiveEquality_EmptyStrings_993) {

    StringRef lhs("");

    StringRef rhs("");

    Tag tag1(lhs);

    Tag tag2(rhs);



    EXPECT_TRUE(tag1 == tag2);

}



TEST(TagComparisonTest_993, CaseInsensitiveEquality_OneEmptyString_993) {

    StringRef lhs("example");

    StringRef rhs("");

    Tag tag1(lhs);

    Tag tag2(rhs);



    EXPECT_FALSE(tag1 == tag2);

}
