#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>

// Include necessary Catch2 headers
#include "catch2/generators/catch_generators.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

using namespace Catch;
using namespace testing;

// Mock for IResultCapture
class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef, const SourceLineInfo&, Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&&), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef, const SourceLineInfo&), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo&, const ITransientExpression&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo&, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo&, ResultWas::OfType, AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Tests for StringRef which is a dependency used by acquireGeneratorTracker
class StringRefTest_354 : public ::testing::Test {};

TEST_F(StringRefTest_354, DefaultConstructor_354) {
    Catch::StringRef ref;
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

TEST_F(StringRefTest_354, ConstructFromCString_354) {
    Catch::StringRef ref("hello");
    EXPECT_FALSE(ref.empty());
    EXPECT_EQ(ref.size(), 5u);
}

TEST_F(StringRefTest_354, ConstructFromStdString_354) {
    std::string s = "test string";
    Catch::StringRef ref(s);
    EXPECT_EQ(ref.size(), s.size());
    EXPECT_FALSE(ref.empty());
}

TEST_F(StringRefTest_354, ConstructFromCharPtrAndSize_354) {
    const char* str = "hello world";
    Catch::StringRef ref(str, 5);
    EXPECT_EQ(ref.size(), 5u);
    EXPECT_FALSE(ref.empty());
}

TEST_F(StringRefTest_354, EmptyStringRef_354) {
    Catch::StringRef ref("");
    EXPECT_TRUE(ref.empty());
    EXPECT_EQ(ref.size(), 0u);
}

TEST_F(StringRefTest_354, Equality_354) {
    Catch::StringRef a("test");
    Catch::StringRef b("test");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST_F(StringRefTest_354, Inequality_354) {
    Catch::StringRef a("hello");
    Catch::StringRef b("world");
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST_F(StringRefTest_354, IndexOperator_354) {
    Catch::StringRef ref("abc");
    EXPECT_EQ(ref[0], 'a');
    EXPECT_EQ(ref[1], 'b');
    EXPECT_EQ(ref[2], 'c');
}

TEST_F(StringRefTest_354, DataPointer_354) {
    const char* str = "hello";
    Catch::StringRef ref(str);
    EXPECT_EQ(ref.data(), str);
}

TEST_F(StringRefTest_354, Substr_354) {
    Catch::StringRef ref("hello world");
    auto sub = ref.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'h');
    EXPECT_EQ(sub[4], 'o');
}

TEST_F(StringRefTest_354, SubstrFromMiddle_354) {
    Catch::StringRef ref("hello world");
    auto sub = ref.substr(6, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub[0], 'w');
}

TEST_F(StringRefTest_354, CompareEqual_354) {
    Catch::StringRef a("abc");
    Catch::StringRef b("abc");
    EXPECT_EQ(a.compare(b), 0);
}

TEST_F(StringRefTest_354, CompareLess_354) {
    Catch::StringRef a("abc");
    Catch::StringRef b("abd");
    EXPECT_LT(a.compare(b), 0);
}

TEST_F(StringRefTest_354, CompareGreater_354) {
    Catch::StringRef a("abd");
    Catch::StringRef b("abc");
    EXPECT_GT(a.compare(b), 0);
}

TEST_F(StringRefTest_354, LessThanOperator_354) {
    Catch::StringRef a("abc");
    Catch::StringRef b("abd");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST_F(StringRefTest_354, ExplicitConversionToString_354) {
    Catch::StringRef ref("hello");
    std::string s = static_cast<std::string>(ref);
    EXPECT_EQ(s, "hello");
}

TEST_F(StringRefTest_354, BeginEnd_354) {
    Catch::StringRef ref("abc");
    std::string constructed(ref.begin(), ref.end());
    EXPECT_EQ(constructed, "abc");
}

TEST_F(StringRefTest_354, PlusOperator_354) {
    Catch::StringRef a("hello ");
    Catch::StringRef b("world");
    std::string result = a + b;
    EXPECT_EQ(result, "hello world");
}

TEST_F(StringRefTest_354, PlusEqualsOperator_354) {
    std::string s = "hello ";
    Catch::StringRef ref("world");
    s += ref;
    EXPECT_EQ(s, "hello world");
}

TEST_F(StringRefTest_354, StreamOutput_354) {
    Catch::StringRef ref("test");
    std::ostringstream oss;
    oss << ref;
    EXPECT_EQ(oss.str(), "test");
}

// Tests for SourceLineInfo
class SourceLineInfoTest_354 : public ::testing::Test {};

TEST_F(SourceLineInfoTest_354, Construction_354) {
    Catch::SourceLineInfo info("file.cpp", 42);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 42u);
}

TEST_F(SourceLineInfoTest_354, EqualityOperator_354) {
    Catch::SourceLineInfo a("file.cpp", 42);
    Catch::SourceLineInfo b("file.cpp", 42);
    EXPECT_TRUE(a == b);
}

TEST_F(SourceLineInfoTest_354, InequalityDifferentFile_354) {
    Catch::SourceLineInfo a("file1.cpp", 42);
    Catch::SourceLineInfo b("file2.cpp", 42);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_354, InequalityDifferentLine_354) {
    Catch::SourceLineInfo a("file.cpp", 42);
    Catch::SourceLineInfo b("file.cpp", 43);
    EXPECT_FALSE(a == b);
}

TEST_F(SourceLineInfoTest_354, LessThanByFile_354) {
    Catch::SourceLineInfo a("a.cpp", 100);
    Catch::SourceLineInfo b("b.cpp", 1);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_354, LessThanByLine_354) {
    Catch::SourceLineInfo a("file.cpp", 10);
    Catch::SourceLineInfo b("file.cpp", 20);
    EXPECT_TRUE(a < b);
}

TEST_F(SourceLineInfoTest_354, StreamOutput_354) {
    Catch::SourceLineInfo info("file.cpp", 42);
    std::ostringstream oss;
    oss << info;
    std::string result = oss.str();
    // The output should contain the file name and line number
    EXPECT_NE(result.find("file.cpp"), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
}

TEST_F(SourceLineInfoTest_354, ZeroLine_354) {
    Catch::SourceLineInfo info("file.cpp", 0);
    EXPECT_STREQ(info.file, "file.cpp");
    EXPECT_EQ(info.line, 0u);
}

TEST_F(SourceLineInfoTest_354, LargeLineNumber_354) {
    Catch::SourceLineInfo info("file.cpp", 999999);
    EXPECT_EQ(info.line, 999999u);
}

// Test the IResultCapture interface contract via mock
class IResultCaptureTest_354 : public ::testing::Test {
protected:
    MockResultCapture mockCapture;
};

TEST_F(IResultCaptureTest_354, AcquireGeneratorTrackerReturnsNullptr_354) {
    EXPECT_CALL(mockCapture, acquireGeneratorTracker(_, _))
        .WillOnce(Return(nullptr));

    Catch::StringRef name("gen1");
    Catch::SourceLineInfo lineInfo("test.cpp", 10);
    IGeneratorTracker* result = mockCapture.acquireGeneratorTracker(name, lineInfo);
    EXPECT_EQ(result, nullptr);
}

TEST_F(IResultCaptureTest_354, AcquireGeneratorTrackerReturnsTracker_354) {
    // We can't create a real IGeneratorTracker, but we can verify the mock returns what we set
    IGeneratorTracker* fakeTracker = reinterpret_cast<IGeneratorTracker*>(0x1234);
    EXPECT_CALL(mockCapture, acquireGeneratorTracker(_, _))
        .WillOnce(Return(fakeTracker));

    Catch::StringRef name("gen2");
    Catch::SourceLineInfo lineInfo("test.cpp", 20);
    IGeneratorTracker* result = mockCapture.acquireGeneratorTracker(name, lineInfo);
    EXPECT_EQ(result, fakeTracker);
}

TEST_F(IResultCaptureTest_354, AcquireGeneratorTrackerCalledWithCorrectParams_354) {
    EXPECT_CALL(mockCapture, acquireGeneratorTracker(
        Catch::StringRef("myGenerator"),
        _))
        .WillOnce(Return(nullptr));

    Catch::SourceLineInfo lineInfo("source.cpp", 55);
    mockCapture.acquireGeneratorTracker(Catch::StringRef("myGenerator"), lineInfo);
}

TEST_F(IResultCaptureTest_354, AcquireGeneratorTrackerMultipleCalls_354) {
    EXPECT_CALL(mockCapture, acquireGeneratorTracker(_, _))
        .Times(3)
        .WillRepeatedly(Return(nullptr));

    Catch::SourceLineInfo lineInfo("test.cpp", 1);
    mockCapture.acquireGeneratorTracker(Catch::StringRef("gen1"), lineInfo);
    mockCapture.acquireGeneratorTracker(Catch::StringRef("gen2"), lineInfo);
    mockCapture.acquireGeneratorTracker(Catch::StringRef("gen3"), lineInfo);
}

TEST_F(IResultCaptureTest_354, AcquireGeneratorTrackerEmptyName_354) {
    EXPECT_CALL(mockCapture, acquireGeneratorTracker(_, _))
        .WillOnce(Return(nullptr));

    Catch::StringRef emptyName("");
    Catch::SourceLineInfo lineInfo("test.cpp", 0);
    IGeneratorTracker* result = mockCapture.acquireGeneratorTracker(emptyName, lineInfo);
    EXPECT_EQ(result, nullptr);
}

// Test StringRef boundary conditions
class StringRefBoundaryTest_354 : public ::testing::Test {};

TEST_F(StringRefBoundaryTest_354, SingleCharacter_354) {
    Catch::StringRef ref("x");
    EXPECT_EQ(ref.size(), 1u);
    EXPECT_EQ(ref[0], 'x');
    EXPECT_FALSE(ref.empty());
}

TEST_F(StringRefBoundaryTest_354, SubstrFullString_354) {
    Catch::StringRef ref("hello");
    auto sub = ref.substr(0, 5);
    EXPECT_EQ(sub.size(), 5u);
    EXPECT_EQ(sub.data(), ref.data());
}

TEST_F(StringRefBoundaryTest_354, SubstrZeroLength_354) {
    Catch::StringRef ref("hello");
    auto sub = ref.substr(0, 0);
    EXPECT_EQ(sub.size(), 0u);
    EXPECT_TRUE(sub.empty());
}

TEST_F(StringRefBoundaryTest_354, CompareWithSelf_354) {
    Catch::StringRef ref("test");
    EXPECT_EQ(ref.compare(ref), 0);
    EXPECT_TRUE(ref == ref);
    EXPECT_FALSE(ref != ref);
}

TEST_F(StringRefBoundaryTest_354, CompareDifferentLengths_354) {
    Catch::StringRef shorter("abc");
    Catch::StringRef longer("abcd");
    EXPECT_LT(shorter.compare(longer), 0);
    EXPECT_GT(longer.compare(shorter), 0);
}

TEST_F(StringRefBoundaryTest_354, EmptyCompareWithEmpty_354) {
    Catch::StringRef a;
    Catch::StringRef b("");
    EXPECT_EQ(a.compare(b), 0);
    EXPECT_TRUE(a == b);
}

TEST_F(StringRefBoundaryTest_354, EmptyCompareWithNonEmpty_354) {
    Catch::StringRef empty;
    Catch::StringRef nonEmpty("a");
    EXPECT_LT(empty.compare(nonEmpty), 0);
    EXPECT_GT(nonEmpty.compare(empty), 0);
}
