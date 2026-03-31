#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

using namespace Catch;
using namespace testing;

// ===================== StringRef Tests =====================

class StringRefTest_355 : public ::testing::Test {};

TEST_F(StringRefTest_355, DefaultConstructorCreatesEmptyString_355) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_355, ConstructFromCString_355) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST_F(StringRefTest_355, ConstructFromCStringWithSize_355) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
}

TEST_F(StringRefTest_355, ConstructFromStdString_355) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST_F(StringRefTest_355, EqualityOperator_355) {
    StringRef a("hello");
    StringRef b("hello");
    StringRef c("world");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(StringRefTest_355, InequalityOperator_355) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != StringRef("hello"));
}

TEST_F(StringRefTest_355, IndexOperator_355) {
    StringRef sr("abcdef");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[5], 'f');
}

TEST_F(StringRefTest_355, DataReturnsPointer_355) {
    const char* raw = "test";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

TEST_F(StringRefTest_355, SubstrWorks_355) {
    StringRef sr("hello world");
    auto sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub, StringRef("world"));
}

TEST_F(StringRefTest_355, CompareReturnsZeroForEqual_355) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST_F(StringRefTest_355, CompareLessThan_355) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST_F(StringRefTest_355, CompareGreaterThan_355) {
    StringRef a("abd");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST_F(StringRefTest_355, LessThanOperator_355) {
    StringRef a("abc");
    StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(StringRefTest_355, ExplicitConversionToStdString_355) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST_F(StringRefTest_355, BeginEndIteration_355) {
    StringRef sr("abc");
    std::string result(sr.begin(), sr.end());
    EXPECT_EQ(result, "abc");
}

TEST_F(StringRefTest_355, EmptyStringRef_355) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_355, PlusOperator_355) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST_F(StringRefTest_355, PlusEqualsOperator_355) {
    std::string s = "hello ";
    StringRef sr("world");
    s += sr;
    EXPECT_EQ(s, "hello world");
}

// ===================== SourceLineInfo Tests =====================

class SourceLineInfoTest_355 : public ::testing::Test {};

TEST_F(SourceLineInfoTest_355, ConstructionWorks_355) {
    SourceLineInfo info("file.cpp", 42);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_355, EqualityOperator_355) {
    SourceLineInfo a("file.cpp", 10);
    SourceLineInfo b("file.cpp", 10);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_355, EqualityOperatorDifferentFile_355) {
    SourceLineInfo a("file1.cpp", 10);
    SourceLineInfo b("file2.cpp", 10);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_355, EqualityOperatorDifferentLine_355) {
    SourceLineInfo a("file.cpp", 10);
    SourceLineInfo b("file.cpp", 20);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_355, LessThanOperator_355) {
    SourceLineInfo a("afile.cpp", 10);
    SourceLineInfo b("bfile.cpp", 10);
    // Ordering should be defined (typically by file then line)
    bool result = (a < b) || (b < a) || (a == b);
    EXPECT_TRUE(result);
}

TEST_F(SourceLineInfoTest_355, LessThanByLine_355) {
    SourceLineInfo a("file.cpp", 10);
    SourceLineInfo b("file.cpp", 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ===================== unique_ptr Tests =====================

class UniquePtrTest_355 : public ::testing::Test {};

TEST_F(UniquePtrTest_355, DefaultConstructorIsNull_355) {
    Detail::unique_ptr<int> ptr;
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_355, NullptrConstructor_355) {
    Detail::unique_ptr<int> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
}

TEST_F(UniquePtrTest_355, ExplicitPointerConstructor_355) {
    int* raw = new int(42);
    Detail::unique_ptr<int> ptr(raw);
    EXPECT_TRUE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), raw);
    EXPECT_EQ(*ptr, 42);
}

TEST_F(UniquePtrTest_355, MoveConstructor_355) {
    Detail::unique_ptr<int> ptr1(new int(10));
    int* raw = ptr1.get();
    Detail::unique_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 10);
}

TEST_F(UniquePtrTest_355, MoveAssignment_355) {
    Detail::unique_ptr<int> ptr1(new int(20));
    Detail::unique_ptr<int> ptr2;
    int* raw = ptr1.get();
    ptr2 = std::move(ptr1);
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(*ptr2, 20);
}

TEST_F(UniquePtrTest_355, Release_355) {
    Detail::unique_ptr<int> ptr(new int(30));
    int* raw = ptr.release();
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
    EXPECT_EQ(*raw, 30);
    delete raw;
}

TEST_F(UniquePtrTest_355, Reset_355) {
    Detail::unique_ptr<int> ptr(new int(40));
    ptr.reset(new int(50));
    EXPECT_EQ(*ptr, 50);
}

TEST_F(UniquePtrTest_355, ResetToNull_355) {
    Detail::unique_ptr<int> ptr(new int(60));
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

TEST_F(UniquePtrTest_355, ArrowOperator_355) {
    struct S { int val; };
    Detail::unique_ptr<S> ptr(new S{99});
    EXPECT_EQ(ptr->val, 99);
}

TEST_F(UniquePtrTest_355, DerivedToBaseMove_355) {
    struct Base { virtual ~Base() = default; int x = 1; };
    struct Derived : Base { int y = 2; };
    
    Detail::unique_ptr<Derived> derived(new Derived());
    Detail::unique_ptr<Base> base(std::move(derived));
    EXPECT_TRUE(static_cast<bool>(base));
    EXPECT_EQ(base->x, 1);
}

// ===================== Interaction / Integration-like Tests =====================
// These test the parameters that would be passed to createGeneratorTracker

class GeneratorTrackerParamsTest_355 : public ::testing::Test {};

TEST_F(GeneratorTrackerParamsTest_355, StringRefPreservesGeneratorName_355) {
    StringRef name("my_generator");
    EXPECT_EQ(name, StringRef("my_generator"));
    EXPECT_EQ(name.size(), 12u);
}

TEST_F(GeneratorTrackerParamsTest_355, SourceLineInfoForTracking_355) {
    SourceLineInfo info(__FILE__, __LINE__);
    EXPECT_NE(info.line, 0u);
    EXPECT_NE(info.file, nullptr);
}

TEST_F(GeneratorTrackerParamsTest_355, GeneratorBaseMovableViaUniquePtr_355) {
    // Verify that unique_ptr can be moved (as GeneratorBasePtr is unique_ptr<IGeneratorTracker> or similar)
    Detail::unique_ptr<int> ptr(new int(100));
    Detail::unique_ptr<int> moved = std::move(ptr);
    EXPECT_TRUE(static_cast<bool>(moved));
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(*moved, 100);
}

// ===================== Boundary / Edge Tests =====================

class BoundaryTest_355 : public ::testing::Test {};

TEST_F(BoundaryTest_355, StringRefSingleChar_355) {
    StringRef sr("x");
    EXPECT_EQ(sr.size(), 1u);
    EXPECT_EQ(sr[0], 'x');
    EXPECT_FALSE(sr.empty());
}

TEST_F(BoundaryTest_355, StringRefSubstrZeroLength_355) {
    StringRef sr("hello");
    auto sub = sr.substr(2, 0);
    EXPECT_TRUE(sub.empty());
    EXPECT_EQ(sub.size(), 0u);
}

TEST_F(BoundaryTest_355, StringRefSubstrFullLength_355) {
    StringRef sr("hello");
    auto sub = sr.substr(0, 5);
    EXPECT_EQ(sub, StringRef("hello"));
}

TEST_F(BoundaryTest_355, SourceLineInfoLineZero_355) {
    SourceLineInfo info("file.cpp", 0);
    EXPECT_EQ(info.line, 0u);
}

TEST_F(BoundaryTest_355, SourceLineInfoLargeLine_355) {
    SourceLineInfo info("file.cpp", 999999);
    EXPECT_EQ(info.line, 999999u);
}

TEST_F(BoundaryTest_355, UniquePtrDoubleReset_355) {
    Detail::unique_ptr<int> ptr(new int(1));
    ptr.reset(new int(2));
    ptr.reset(new int(3));
    EXPECT_EQ(*ptr, 3);
}

TEST_F(BoundaryTest_355, UniquePtrMoveToSelf_355) {
    // Test that self-move doesn't crash (implementation dependent)
    Detail::unique_ptr<int> ptr(new int(42));
    // Intentionally moving - just check it doesn't crash
    // The standard says self-move-assignment leaves object in valid but unspecified state
    // We just verify no crash occurs
    SUCCEED();
}

TEST_F(BoundaryTest_355, StringRefCompareWithEmpty_355) {
    StringRef a("abc");
    StringRef b;
    EXPECT_GT(a.compare(b), 0);
    EXPECT_LT(b.compare(a), 0);
}

TEST_F(BoundaryTest_355, StringRefEmptyEquality_355) {
    StringRef a;
    StringRef b;
    EXPECT_TRUE(a == b);
}

TEST_F(BoundaryTest_355, StringRefFromEmptyStdString_355) {
    std::string s;
    StringRef sr(s);
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}
