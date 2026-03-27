#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Public headers from the target library
#include "catch2/catch_message.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_message_info.hpp"

// ----------------------
// Minimal forward decls
// ----------------------
namespace Catch {

// If your real IResultCapture has a different method signature for message emission,
// update the mock to match (the tests only rely on this external interaction).
struct IResultCapture {
    virtual ~IResultCapture() = default;
    virtual void captureMessage(MessageInfo const& info, std::string const& message) = 0;
};

// Global accessor used by Capturer's constructor; we override it in this TU.
IResultCapture& getResultCapture();

} // namespace Catch

// ----------------------
// Google Mock
// ----------------------
namespace {
struct MockResultCapture : Catch::IResultCapture {
    MOCK_METHOD(void, captureMessage,
                (Catch::MessageInfo const& info, std::string const& message), (override));
};

MockResultCapture* g_mock_capture = nullptr;

} // namespace

// Provide definition of the accessor to return our mock.
namespace Catch {
IResultCapture& getResultCapture() {
    return *g_mock_capture;
}
} // namespace Catch

using ::testing::AllOf;
using ::testing::Field;
using ::testing::HasSubstr;
using ::testing::Property;
using ::testing::StrEq;
using ::testing::InSequence;

// Helpers to build SourceLineInfo & enum easily
static inline Catch::SourceLineInfo SL(const char* f, std::size_t l) {
    return Catch::SourceLineInfo{f, l};
}

// Some compilers/namespaces place the enum inside ResultWas
namespace Catch { namespace ResultWas {
    enum OfType {
        Ok = 0,
        Info,
        Warning,
        Failure,
        ExplicitFailure,
        Exception,
    };
}}

// A small matcher for MessageInfo fields we care about (macro name & line)
MATCHER_P3(HasInfo, macro, file, line, "MessageInfo fields matcher") {
    return (std::string(arg.macroName) == macro) &&
           (std::string(arg.lineInfo.file) == file) &&
           (arg.lineInfo.line == line);
}

// --------------
// Test fixture
// --------------
class CapturerTest_1055 : public ::testing::Test {
protected:
    MockResultCapture mock_;
    void SetUp() override { g_mock_capture = &mock_; }
    void TearDown() override { g_mock_capture = nullptr; }
};

// ============================= TESTS =============================

TEST_F(CapturerTest_1055, SingleName_EmitsOneMessageOnCapture_1055) {
    // names = "x"  -> message text should start as "x := " and, after captureValue(0,"42"),
    // collaborator should receive "x := 42".
    const char* file = "t.cpp";
    const std::size_t line = 10;

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("x := 42")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info, Catch::StringRef{"x"}};
    cap.captureValue(0, std::string{"42"});
}

TEST_F(CapturerTest_1055, MultipleNames_SpacesTrimmed_EmitsInOrder_1055) {
    // names = "  a ,  b  "  -> trimmed to "a" and "b"
    // Expect captures happen in index order and messages match.
    const char* file = "multi.cpp";
    const std::size_t line = 20;

    InSequence seq; // verify ordering of external interactions

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("a := 1")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("b := 2")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{"  a ,  b  "}};
    cap.captureValue(0, std::string{"1"});
    cap.captureValue(1, std::string{"2"});
}

TEST_F(CapturerTest_1055, CommasInsideBrackets_DoNotSplitNames_1055) {
    // names = "vec[1,2], s" -> two names: "vec[1,2]" and "s"
    const char* file = "brackets.cpp";
    const std::size_t line = 30;

    InSequence seq;

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("vec[1,2] := V")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("s := W")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{"vec[1,2], s"}};
    cap.captureValue(0, std::string{"V"});
    cap.captureValue(1, std::string{"W"});
}

TEST_F(CapturerTest_1055, ParenthesesAndBraces_CommasIgnoredInside_OpenCloseBalanced_1055) {
    // names = "fn(a,b), map{ k1, k2 }, plain"
    const char* file = "parenbrace.cpp";
    const std::size_t line = 40;

    InSequence seq;

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("fn(a,b) := X")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("map{ k1, k2 } := Y")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("plain := Z")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{"fn(a,b), map{ k1, k2 }, plain"}};
    cap.captureValue(0, std::string{"X"});
    cap.captureValue(1, std::string{"Y"});
    cap.captureValue(2, std::string{"Z"});
}

TEST_F(CapturerTest_1055, Quotes_CommasInsideQuotesIgnored_EscapesHandled_1055) {
    // names = "'a,b', \"c\\\"d\", e"
    // Should parse into:  ["'a,b'", "c\"d", "e"] (without outer-quote chars in the name if StringRef exposes raw)
    // Observable message text should preserve the original name formatting from StringRef->std::string.
    const char* file = "quotes.cpp";
    const std::size_t line = 50;

    InSequence seq;

    // We expect the raw names (as given in the input substring) to be used in the "name := " part.
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("'a,b' := v1")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("c\\\"d := v2")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("e := v3")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{"'a,b', \"c\\\"d\", e"}};
    cap.captureValue(0, std::string{"v1"});
    cap.captureValue(1, std::string{"v2"});
    cap.captureValue(2, std::string{"v3"});
}

TEST_F(CapturerTest_1055, LeadingOrTrailingCommas_SkipEmpty_TrimNames_1055) {
    // names = ",  a  ,  , b ,"
    // Empty splits should be ignored by observable behavior; we expect only "a" and "b" to produce messages.
    const char* file = "edges.cpp";
    const std::size_t line = 60;

    InSequence seq;

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("a := 10")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("b := 20")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{",  a  ,  , b ,"}};
    // Indices correspond to the non-empty parsed names in order.
    cap.captureValue(0, std::string{"10"});
    cap.captureValue(1, std::string{"20"});
}

TEST_F(CapturerTest_1055, MixedWhitespaceAndNestedQuotes_1055) {
    // names = "  \"x, y\" ,  call('a,\\'b'),  z  "
    // Expected names (observably in messages):  ["\"x, y\"", "call('a,\\'b')", "z"]
    const char* file = "mixed.cpp";
    const std::size_t line = 70;

    InSequence seq;

    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("\"x, y\" := A")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("call('a,\\'b') := B")))
        .Times(1);
    EXPECT_CALL(mock_, captureMessage(HasInfo("CAPTURE", file, line), StrEq("z := C")))
        .Times(1);

    Catch::Capturer cap{"CAPTURE", SL(file, line), Catch::ResultWas::Info,
                        Catch::StringRef{"  \"x, y\" ,  call('a,\\'b'),  z  "}};
    cap.captureValue(0, std::string{"A"});
    cap.captureValue(1, std::string{"B"});
    cap.captureValue(2, std::string{"C"});
}
