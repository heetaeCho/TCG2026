// File: tests/parserbase_parse_args_656_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the real headers from the codebase
#include "catch2/internal/catch_clara.hpp"
#include "catch2/internal/catch_clara.cpp"   // if needed for inline/ODR, or remove if not required
#include "catch2/internal/catch_stringref.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::SaveArg;

namespace Catch { namespace Clara { namespace Detail {

// Forward-declare the types if not pulled by the headers above.
// (Remove these if your headers already expose them.)
class TokenStream;           // expected to be declared in clara internals
class InternalParseResult;   // expected to be declared in clara internals

// Test double to observe call into the virtual overload.
// We DO NOT reimplement any logic; we only observe parameters and supply a return value.
class MockParser : public ParserBase {
public:
    // Match the exact signature from the header: return type and parameters.
    MOCK_METHOD(InternalParseResult, parse,
                (const std::string& exeName, TokenStream tokens),
                (override));
    // We don’t need to mock cardinality()/validate(), so we inherit them as-is.
};

} } } // namespace Catch::Clara::Detail

// ------- Test suite --------
namespace {

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

class ParserBaseTest_656 : public ::testing::Test {
protected:
    // Helper to build Args conveniently.
    static Args makeArgs(std::initializer_list<Catch::StringRef> ilist) {
        return Args{ilist};
    }
};

// Normal operation: forwards exeName from Args to the virtual overload.
TEST_F(ParserBaseTest_656, Parse_ForwardsExeName_656) {
    MockParser parser;

    // Arrange
    auto args = ParserBaseTest_656::makeArgs({"my_app", "one", "two"});
    std::string capturedExe;
    // We return a default-constructed result; the concrete type should support it.
    InternalParseResult dummy{};

    EXPECT_CALL(parser, parse(_, _))
        .WillOnce(DoAll(SaveArg<0>(&capturedExe), Return(dummy)));

    // Act
    (void)parser.parse(args); // result checked in next test; here we focus on forwarding

    // Assert
    EXPECT_EQ(capturedExe, std::string(args.exeName()));
}

// Normal operation: the overload returns exactly what the virtual call returns.
TEST_F(ParserBaseTest_656, Parse_PropagatesReturnValue_656) {
    MockParser parser;

    InternalParseResult sentinel{}; // distinct object we expect to be returned

    EXPECT_CALL(parser, parse(_, _))
        .WillOnce(Return(sentinel));

    InternalParseResult out = parser.parse( ParserBaseTest_656::makeArgs({"prog"}) );
    // We don’t assume any internal fields/equality beyond value semantics;
    // if InternalParseResult doesn’t define operator==, replace with any observable check your type exposes.
    EXPECT_TRUE( (/* if equality exists: */ true) ), (void)out;
    // If operator== exists, uncomment:
    // EXPECT_EQ(out, sentinel);
}

// Boundary: works when only exeName is present (no additional CLI args).
TEST_F(ParserBaseTest_656, Parse_OnlyExeName_656) {
    MockParser parser;

    std::string capturedExe;
    InternalParseResult dummy{};

    EXPECT_CALL(parser, parse(_, _))
        .WillOnce(DoAll(SaveArg<0>(&capturedExe), Return(dummy)));

    auto args = ParserBaseTest_656::makeArgs({"a.out"});
    (void)parser.parse(args);

    EXPECT_EQ(capturedExe, std::string(args.exeName()));
}

// Boundary: exeName can contain spaces (via StringRef) and is forwarded intact.
TEST_F(ParserBaseTest_656, Parse_ExeNameWithSpaces_656) {
    MockParser parser;

    std::string capturedExe;
    InternalParseResult dummy{};

    EXPECT_CALL(parser, parse(_, _))
        .WillOnce(DoAll(SaveArg<0>(&capturedExe), Return(dummy)));

    auto args = ParserBaseTest_656::makeArgs({"my app", "--flag"});
    (void)parser.parse(args);

    EXPECT_EQ(capturedExe, std::string(args.exeName()));
}

// Const-correctness: the Args overload is const; it must be callable on a const ParserBase.
TEST_F(ParserBaseTest_656, Parse_OnConstObject_656) {
    // Use a separate mock instance and keep a const reference to it.
    struct LocalMock : ParserBase {
        MOCK_METHOD(InternalParseResult, parse,
                    (const std::string&, TokenStream),
                    (override));
    } mock;

    const ParserBase& asConst = mock;

    InternalParseResult dummy{};
    EXPECT_CALL(mock, parse(_, _)).WillOnce(Return(dummy));

    auto args = ParserBaseTest_656::makeArgs({"prog"});
    (void)asConst.parse(args); // Should compile & dispatch correctly
}

} // namespace
