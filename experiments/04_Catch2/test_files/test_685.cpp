#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stringref.hpp"



using namespace Catch;



class StringRefTest_685 : public ::testing::Test {

protected:

    std::string testString = "Hello, World!";

    StringRef stringRef = StringRef(testString);

};



TEST_F(StringRefTest_685, ConstructionFromCString_685) {

    const char* cstr = "Hello";

    StringRef ref(cstr);

    EXPECT_EQ(ref.size(), 5);

    EXPECT_STREQ(ref.data(), "Hello");

}



TEST_F(StringRefTest_685, ConstructionFromString_685) {

    std::string str = "World";

    StringRef ref(str);

    EXPECT_EQ(ref.size(), 5);

    EXPECT_STREQ(ref.data(), "World");

}



TEST_F(StringRefTest_685, DefaultConstructor_685) {

    StringRef ref;

    EXPECT_EQ(ref.size(), 0);

    EXPECT_STREQ(ref.data(), "");

}



TEST_F(StringRefTest_685, OperatorPlusEquals_685) {

    std::string lhs = "Hello";

    StringRef rhs(" World");

    lhs += rhs;

    EXPECT_EQ(lhs, "Hello World");

}



TEST_F(StringRefTest_685, OperatorEqualEqual_685) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    StringRef ref3("Hello");

    EXPECT_TRUE(ref1 == ref3);

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(StringRefTest_685, OperatorNotEqual_685) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    StringRef ref3("Hello");

    EXPECT_FALSE(ref1 != ref3);

    EXPECT_TRUE(ref1 != ref2);

}



TEST_F(StringRefTest_685, SubstrBasic_685) {

    StringRef sub = stringRef.substr(7, 5);

    EXPECT_EQ(sub.size(), 5);

    EXPECT_STREQ(sub.data(), "World");

}



TEST_F(StringRefTest_685, SubstrBoundaryStart_685) {

    StringRef sub = stringRef.substr(0, 5);

    EXPECT_EQ(sub.size(), 5);

    EXPECT_STREQ(sub.data(), "Hello");

}



TEST_F(StringRefTest_685, SubstrBoundaryEnd_685) {

    StringRef sub = stringRef.substr(7, 50); // Length greater than remaining

    EXPECT_EQ(sub.size(), 5);

    EXPECT_STREQ(sub.data(), "World");

}



TEST_F(StringRefTest_685, EmptyCheck_685) {

    StringRef ref;

    EXPECT_TRUE(ref.empty());

    EXPECT_FALSE(stringRef.empty());

}



TEST_F(StringRefTest_685, SizeCheck_685) {

    EXPECT_EQ(stringRef.size(), testString.size());

}



TEST_F(StringRefTest_685, DataPointer_685) {

    EXPECT_STREQ(stringRef.data(), testString.c_str());

}



TEST_F(StringRefTest_685, OperatorLessThan_685) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    EXPECT_TRUE(ref1 < ref2);

    EXPECT_FALSE(ref2 < ref1);

}



TEST_F(StringRefTest_685, CompareFunction_685) {

    StringRef ref1("Hello");

    StringRef ref2("World");

    StringRef ref3("Hello");

    EXPECT_EQ(ref1.compare(ref3), 0); // Equal

    EXPECT_LT(ref1.compare(ref2), 0); // Less than

    EXPECT_GT(ref2.compare(ref1), 0); // Greater than

}



TEST_F(StringRefTest_685, ConversionToStdString_685) {

    std::string str = static_cast<std::string>(stringRef);

    EXPECT_EQ(str, testString);

}
