#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

using namespace Catch;

// ========== StringRef Tests ==========

class StringRefTest_327 : public ::testing::Test {};

TEST_F(StringRefTest_327, DefaultConstructedIsEmpty_327) {
    StringRef sr;
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_327, ConstructFromCString_327) {
    StringRef sr("hello");
    EXPECT_FALSE(sr.empty());
    EXPECT_EQ(sr.size(), 5u);
}

TEST_F(StringRefTest_327, ConstructFromCStringWithSize_327) {
    StringRef sr("hello world", 5);
    EXPECT_EQ(sr.size(), 5u);
}

TEST_F(StringRefTest_327, ConstructFromStdString_327) {
    std::string s = "test string";
    StringRef sr(s);
    EXPECT_EQ(sr.size(), s.size());
    EXPECT_FALSE(sr.empty());
}

TEST_F(StringRefTest_327, EqualityOperator_327) {
    StringRef a("hello");
    StringRef b("hello");
    StringRef c("world");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
}

TEST_F(StringRefTest_327, InequalityOperator_327) {
    StringRef a("hello");
    StringRef b("world");
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != StringRef("hello"));
}

TEST_F(StringRefTest_327, IndexOperator_327) {
    StringRef sr("abcde");
    EXPECT_EQ(sr[0], 'a');
    EXPECT_EQ(sr[4], 'e');
}

TEST_F(StringRefTest_327, CompareEqual_327) {
    StringRef a("abc");
    StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST_F(StringRefTest_327, CompareLessThan_327) {
    StringRef a("abc");
    StringRef b("def");
    EXPECT_LT(a.compare(b), 0);
}

TEST_F(StringRefTest_327, CompareGreaterThan_327) {
    StringRef a("def");
    StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST_F(StringRefTest_327, LessThanOperator_327) {
    StringRef a("abc");
    StringRef b("def");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(StringRefTest_327, ExplicitConversionToStdString_327) {
    StringRef sr("hello");
    std::string s = static_cast<std::string>(sr);
    EXPECT_EQ(s, "hello");
}

TEST_F(StringRefTest_327, Substr_327) {
    StringRef sr("hello world");
    auto sub = sr.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
}

TEST_F(StringRefTest_327, DataPointer_327) {
    const char* raw = "hello";
    StringRef sr(raw);
    EXPECT_EQ(sr.data(), raw);
}

TEST_F(StringRefTest_327, BeginEnd_327) {
    StringRef sr("abc");
    auto it = sr.begin();
    EXPECT_EQ(*it, 'a');
    EXPECT_EQ(sr.end() - sr.begin(), 3);
}

TEST_F(StringRefTest_327, EmptyCString_327) {
    StringRef sr("");
    EXPECT_TRUE(sr.empty());
    EXPECT_EQ(sr.size(), 0u);
}

TEST_F(StringRefTest_327, ConcatenationOperator_327) {
    StringRef a("hello ");
    StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST_F(StringRefTest_327, PlusEqualsOperator_327) {
    std::string lhs = "hello ";
    StringRef rhs("world");
    lhs += rhs;
    EXPECT_EQ(lhs, "hello world");
}

// ========== SourceLineInfo Tests ==========

class SourceLineInfoTest_327 : public ::testing::Test {};

TEST_F(SourceLineInfoTest_327, Construction_327) {
    SourceLineInfo info("file.cpp", 42);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_327, EqualitySameValues_327) {
    SourceLineInfo a("file.cpp", 42);
    SourceLineInfo b("file.cpp", 42);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_327, EqualityDifferentFile_327) {
    SourceLineInfo a("file1.cpp", 42);
    SourceLineInfo b("file2.cpp", 42);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_327, EqualityDifferentLine_327) {
    SourceLineInfo a("file.cpp", 42);
    SourceLineInfo b("file.cpp", 43);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_327, LessThanDifferentFile_327) {
    SourceLineInfo a("aaa.cpp", 100);
    SourceLineInfo b("bbb.cpp", 1);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_327, LessThanSameFileDifferentLine_327) {
    SourceLineInfo a("file.cpp", 10);
    SourceLineInfo b("file.cpp", 20);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

// ========== unique_ptr Tests ==========

class UniquePtrTest_327 : public ::testing::Test {};

TEST_F(UniquePtrTest_327, DefaultConstructedIsNull_327) {
    Catch::Detail::unique_ptr<int> p;
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(p.get(), nullptr);
}

TEST_F(UniquePtrTest_327, NullptrConstructed_327) {
    Catch::Detail::unique_ptr<int> p(nullptr);
    EXPECT_FALSE(static_cast<bool>(p));
}

TEST_F(UniquePtrTest_327, ExplicitPtrConstruction_327) {
    Catch::Detail::unique_ptr<int> p(new int(42));
    EXPECT_TRUE(static_cast<bool>(p));
    EXPECT_EQ(*p, 42);
}

TEST_F(UniquePtrTest_327, DereferenceOperator_327) {
    Catch::Detail::unique_ptr<int> p(new int(100));
    EXPECT_EQ(*p, 100);
}

TEST_F(UniquePtrTest_327, ArrowOperator_327) {
    struct S { int x; };
    Catch::Detail::unique_ptr<S> p(new S{55});
    EXPECT_EQ(p->x, 55);
}

TEST_F(UniquePtrTest_327, GetReturnsRawPointer_327) {
    int* raw = new int(7);
    Catch::Detail::unique_ptr<int> p(raw);
    EXPECT_EQ(p.get(), raw);
}

TEST_F(UniquePtrTest_327, ReleaseRelinquishesOwnership_327) {
    Catch::Detail::unique_ptr<int> p(new int(33));
    int* raw = p.release();
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(*raw, 33);
    delete raw;
}

TEST_F(UniquePtrTest_327, ResetToNull_327) {
    Catch::Detail::unique_ptr<int> p(new int(10));
    p.reset();
    EXPECT_FALSE(static_cast<bool>(p));
    EXPECT_EQ(p.get(), nullptr);
}

TEST_F(UniquePtrTest_327, ResetToNewPointer_327) {
    Catch::Detail::unique_ptr<int> p(new int(10));
    int* newPtr = new int(20);
    p.reset(newPtr);
    EXPECT_EQ(p.get(), newPtr);
    EXPECT_EQ(*p, 20);
}

TEST_F(UniquePtrTest_327, MoveConstruction_327) {
    Catch::Detail::unique_ptr<int> p1(new int(42));
    Catch::Detail::unique_ptr<int> p2(std::move(p1));
    EXPECT_TRUE(static_cast<bool>(p2));
    EXPECT_EQ(*p2, 42);
}

TEST_F(UniquePtrTest_327, MoveAssignment_327) {
    Catch::Detail::unique_ptr<int> p1(new int(42));
    Catch::Detail::unique_ptr<int> p2;
    p2 = std::move(p1);
    EXPECT_TRUE(static_cast<bool>(p2));
    EXPECT_EQ(*p2, 42);
}

TEST_F(UniquePtrTest_327, PolymorphicMoveConstruction_327) {
    struct Base { virtual ~Base() = default; int val = 0; };
    struct Derived : Base { Derived(int v) { val = v; } };
    
    Catch::Detail::unique_ptr<Derived> d(new Derived(99));
    Catch::Detail::unique_ptr<Base> b(std::move(d));
    EXPECT_TRUE(static_cast<bool>(b));
    EXPECT_EQ(b->val, 99);
}

// ========== IGeneratorTracker Mock Tests ==========

class MockGeneratorTracker : public IGeneratorTracker {
public:
    MOCK_METHOD(bool, hasGenerator, (), (const, override));
    MOCK_METHOD(const Generators::GeneratorBasePtr&, getGenerator, (), (const, override));
    MOCK_METHOD(void, setGenerator, (Generators::GeneratorBasePtr&&), (override));
    ~MockGeneratorTracker() override = default;
};

class IGeneratorTrackerTest_327 : public ::testing::Test {};

TEST_F(IGeneratorTrackerTest_327, MockHasGeneratorReturnsFalse_327) {
    MockGeneratorTracker tracker;
    EXPECT_CALL(tracker, hasGenerator()).WillOnce(::testing::Return(false));
    EXPECT_FALSE(tracker.hasGenerator());
}

TEST_F(IGeneratorTrackerTest_327, MockHasGeneratorReturnsTrue_327) {
    MockGeneratorTracker tracker;
    EXPECT_CALL(tracker, hasGenerator()).WillOnce(::testing::Return(true));
    EXPECT_TRUE(tracker.hasGenerator());
}

// ========== make_unique Tests ==========

class MakeUniqueTest_327 : public ::testing::Test {};

TEST_F(MakeUniqueTest_327, CreatesObject_327) {
    auto p = Catch::Detail::make_unique<int>(42);
    EXPECT_TRUE(static_cast<bool>(p));
    EXPECT_EQ(*p, 42);
}

TEST_F(MakeUniqueTest_327, CreatesObjectWithDefaultCtor_327) {
    struct S { int x = 5; };
    auto p = Catch::Detail::make_unique<S>();
    EXPECT_EQ(p->x, 5);
}

TEST_F(MakeUniqueTest_327, CreatesObjectWithMultipleArgs_327) {
    struct S {
        int a;
        double b;
        S(int a_, double b_) : a(a_), b(b_) {}
    };
    auto p = Catch::Detail::make_unique<S>(10, 3.14);
    EXPECT_EQ(p->a, 10);
    EXPECT_DOUBLE_EQ(p->b, 3.14);
}
