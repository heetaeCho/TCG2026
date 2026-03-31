#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <string>

using namespace Exiv2;

// Test default construction
TEST(StringValueTest_130, DefaultConstruction_130) {
    StringValue sv;
    EXPECT_EQ(sv.toString(), "");
    EXPECT_EQ(sv.size(), 0u);
}

// Test construction with a string
TEST(StringValueTest_130, ConstructionWithString_130) {
    StringValue sv("hello");
    EXPECT_EQ(sv.toString(), "hello");
}

// Test construction with empty string
TEST(StringValueTest_130, ConstructionWithEmptyString_130) {
    StringValue sv("");
    EXPECT_EQ(sv.toString(), "");
    EXPECT_EQ(sv.size(), 0u);
}

// Test clone returns a valid copy
TEST(StringValueTest_130, CloneReturnsCopy_130) {
    StringValue sv("test_clone");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "test_clone");
}

// Test clone returns independent copy (modifying original doesn't affect clone)
TEST(StringValueTest_130, CloneIsIndependent_130) {
    StringValue sv("original");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "original");
    // The cloned value should be independent
    sv.read("modified");
    EXPECT_EQ(sv.toString(), "modified");
    EXPECT_EQ(cloned->toString(), "original");
}

// Test clone of default-constructed StringValue
TEST(StringValueTest_130, CloneOfDefaultConstructed_130) {
    StringValue sv;
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), "");
}

// Test read method to set value
TEST(StringValueTest_130, ReadSetsValue_130) {
    StringValue sv;
    sv.read("new value");
    EXPECT_EQ(sv.toString(), "new value");
}

// Test read with empty string
TEST(StringValueTest_130, ReadEmptyString_130) {
    StringValue sv("initial");
    sv.read("");
    EXPECT_EQ(sv.toString(), "");
}

// Test construction with string containing special characters
TEST(StringValueTest_130, SpecialCharacters_130) {
    StringValue sv("hello\nworld\ttab");
    EXPECT_EQ(sv.toString(), "hello\nworld\ttab");
}

// Test construction with string containing null-like content
TEST(StringValueTest_130, StringWithSpaces_130) {
    StringValue sv("   spaces   ");
    EXPECT_EQ(sv.toString(), "   spaces   ");
}

// Test size after construction with string
TEST(StringValueTest_130, SizeAfterConstruction_130) {
    StringValue sv("12345");
    EXPECT_EQ(sv.size(), 5u);
}

// Test that typeId is string
TEST(StringValueTest_130, TypeIdIsString_130) {
    StringValue sv;
    EXPECT_EQ(sv.typeId(), Exiv2::string);
}

// Test clone preserves type
TEST(StringValueTest_130, ClonePreservesType_130) {
    StringValue sv("typed");
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), Exiv2::string);
}

// Test with a very long string
TEST(StringValueTest_130, LongString_130) {
    std::string longStr(10000, 'x');
    StringValue sv(longStr);
    EXPECT_EQ(sv.toString(), longStr);
    EXPECT_EQ(sv.size(), 10000u);
}

// Test multiple reads overwrite previous value
TEST(StringValueTest_130, MultipleReadsOverwrite_130) {
    StringValue sv("first");
    EXPECT_EQ(sv.toString(), "first");
    sv.read("second");
    EXPECT_EQ(sv.toString(), "second");
    sv.read("third");
    EXPECT_EQ(sv.toString(), "third");
}

// Test clone of long string
TEST(StringValueTest_130, CloneLongString_130) {
    std::string longStr(5000, 'a');
    StringValue sv(longStr);
    auto cloned = sv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toString(), longStr);
}

// Test copy behavior through clone
TEST(StringValueTest_130, CloneMultipleTimes_130) {
    StringValue sv("multi");
    auto clone1 = sv.clone();
    auto clone2 = sv.clone();
    ASSERT_NE(clone1, nullptr);
    ASSERT_NE(clone2, nullptr);
    EXPECT_EQ(clone1->toString(), "multi");
    EXPECT_EQ(clone2->toString(), "multi");
}
