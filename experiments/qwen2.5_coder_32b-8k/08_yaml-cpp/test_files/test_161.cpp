#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "scanscalar.h"

#include "stream.h"

#include <sstream>



using namespace YAML;

using ::testing::Return;



class StreamMock : public Stream {

public:

    MOCK_METHOD0(operator bool, const bool());

    MOCK_METHOD0(peek, const char());

    MOCK_METHOD0(get, char());

    MOCK_METHOD1(get, std::string(int));

    MOCK_METHOD1(eat, void(int));

    MOCK_CONST_METHOD0(mark, const Mark());

    MOCK_CONST_METHOD0(pos, int());

    MOCK_CONST_METHOD0(line, int());

    MOCK_CONST_METHOD0(column, int());



    StreamMock(std::istream& input) : Stream(input) {}

};



class ScanScalarTest_161 : public ::testing::Test {

protected:

    std::istringstream iss;

    StreamMock stream;

    ScanScalarParams params;



    ScanScalarTest_161() : iss(""), stream(iss), params() {}



    void SetUp() override {

        // Default setup for tests

        ON_CALL(stream, operator bool()).WillByDefault(Return(true));

        ON_CALL(stream, get()).WillByDefault(testing::InvokeWithoutArgs([&]() -> char { return '\n'; }));

        ON_CALL(stream, peek()).WillByDefault(testing::Return('\n'));

        ON_CALL(stream, eat(testing::_)).WillByDefault(testing::Return());

        params.end = &Exp::Empty();

    }

};



TEST_F(ScanScalarTest_161, NormalOperation_SimpleString_161) {

    iss.str("simple\n");

    EXPECT_CALL(stream, get()).WillOnce(Return('s')).WillOnce(Return('i')).WillOnce(Return('m'))

                               .WillOnce(Return('p')).WillOnce(Return('l')).WillOnce(Return('e'))

                               .WillOnce(Return('\n'));

    EXPECT_EQ(ScanScalar(stream, params), "simple");

}



TEST_F(ScanScalarTest_161, BoundaryCondition_EmptyString_161) {

    iss.str("");

    ON_CALL(stream, operator bool()).WillByDefault(Return(false));

    params.eatEnd = true;

    EXPECT_THROW(ScanScalar(stream, params), ParserException);

}



TEST_F(ScanScalarTest_161, ExceptionalCase_DocIndicatorInScalar_161) {

    iss.str("---\n");

    ON_CALL(stream, peek()).WillOnce(Return('-')).WillOnce(Return(' '));

    params.onDocIndicator = THROW;

    EXPECT_THROW(ScanScalar(stream, params), ParserException);

}



TEST_F(ScanScalarTest_161, ExceptionalCase_EOFInScalar_161) {

    iss.str("eof");

    ON_CALL(stream, operator bool()).WillByDefault(Return(false));

    params.eatEnd = true;

    EXPECT_THROW(ScanScalar(stream, params), ParserException);

}



TEST_F(ScanScalarTest_161, NormalOperation_TabInIndentation_Allowed_161) {

    iss.str("   \tindented\n");

    ON_CALL(stream, peek()).WillOnce(Return(' ')).WillOnce(Return(' '))

                            .WillOnce(Return(' ')).WillOnce(Return('\t'))

                            .WillOnce(Return('i')).WillOnce(Return('n'))

                            .WillOnce(Return('d')).WillOnce(Return('e'))

                            .WillOnce(Return('n')).WillOnce(Return('t'))

                            .WillOnce(Return('e')).WillOnce(Return('d'))

                            .WillOnce(Return('\n'));

    params.detectIndent = true;

    params.onTabInIndentation = NONE;

    EXPECT_EQ(ScanScalar(stream, params), "indented");

}



TEST_F(ScanScalarTest_161, ExceptionalCase_TabInIndentation_NotAllowed_161) {

    iss.str("   \tindented\n");

    ON_CALL(stream, peek()).WillOnce(Return(' ')).WillOnce(Return(' '))

                            .WillOnce(Return(' ')).WillOnce(Return('\t'))

                            .WillOnce(Return('i')).WillOnce(Return('n'))

                            .WillOnce(Return('d')).WillOnce(Return('e'))

                            .WillOnce(Return('n')).WillOnce(Return('t'))

                            .WillOnce(Return('e')).WillOnce(Return('d'))

                            .WillOnce(Return('\n'));

    params.detectIndent = true;

    params.onTabInIndentation = THROW;

    EXPECT_THROW(ScanScalar(stream, params), ParserException);

}



TEST_F(ScanScalarTest_161, NormalOperation_EscapeCharacterHandling_161) {

    iss.str("esc\\aped\n");

    ON_CALL(stream, peek()).WillOnce(Return('e')).WillOnce(Return('s'))

                            .WillOnce(Return('c')).WillOnce(Return('\\'))

                            .WillOnce(Return('a')).WillOnce(Return('p'))

                            .WillOnce(Return('e')).WillOnce(Return('d'))

                            .WillOnce(Return('\n'));

    ON_CALL(stream, get()).WillOnce(Return('e')).WillOnce(Return('s'))

                          .WillOnce(Return('c')).WillOnce(Return('\\'))

                          .WillOnce(Return('a')).WillOnce(Return('p'))

                          .WillOnce(Return('e')).WillOnce(Return('d'))

                          .WillOnce(Return('\n'));

    params.escape = '\\';

    EXPECT_EQ(ScanScalar(stream, params), "escaped");

}



TEST_F(ScanScalarTest_161, NormalOperation_FoldBlockHandling_161) {

    iss.str("line\n line\n  more indented\n");

    ON_CALL(stream, peek()).WillOnce(Return('l')).WillOnce(Return('i'))

                            .WillOnce(Return('n')).WillOnce(Return('e'))

                            .WillOnce(Return('\n')).WillOnce(Return(' '))

                            .WillOnce(Return('l')).WillOnce(Return('i'))

                            .WillOnce(Return('n')).WillOnce(Return('e'))

                            .WillOnce(Return('\n')).WillOnce(Return(' '))

                            .WillOnce(Return('m')).WillOnce(Return('o'))

                            .WillOnce(Return('r')).WillOnce(Return('e'))

                            .WillOnce(Return(' ')).WillOnce(Return('i'))

                            .WillOnce(Return('n')).WillOnce(Return('d'))

                            .WillOnce(Return('e')).WillOnce(Return('n'))

                            .WillOnce(Return('t')).WillOnce(Return('e'))

                            .WillOnce(Return('d')).WillOnce(Return('\n'));

    ON_CALL(stream, get()).WillOnce(Return('l')).WillOnce(Return('i'))

                          .WillOnce(Return('n')).WillOnce(Return('e'))

                          .WillOnce(Return('\n')).WillOnce(Return(' '))

                          .WillOnce(Return('l')).WillOnce(Return('i'))

                          .WillOnce(Return('n')).WillOnce(Return('e'))

                          .WillOnce(Return('\n')).WillOnce(Return(' '))

                          .WillOnce(Return('m')).WillOnce(Return('o'))

                          .WillOnce(Return('r')).WillOnce(Return('e'))

                          .WillOnce(Return(' ')).WillOnce(Return('i'))

                          .WillOnce(Return('n')).WillOnce(Return('d'))

                          .WillOnce(Return('e')).WillOnce(Return('n'))

                          .WillOnce(Return('t')).WillOnce(Return('e'))

                          .WillOnce(Return('d')).WillOnce(Return('\n'));

    params.fold = FOLD_BLOCK;

    EXPECT_EQ(ScanScalar(stream, params), "line\n line\n  more indented");

}



TEST_F(ScanScalarTest_161, NormalOperation_FoldFlowHandling_161) {

    iss.str("flow folded ");

    ON_CALL(stream, peek()).WillOnce(Return('f')).WillOnce(Return('l'))

                            .WillOnce(Return('o')).WillOnce(Return('w'))

                            .WillOnce(Return(' ')).WillOnce(Return('f'))

                            .WillOnce(Return('o')).WillOnce(Return('l'))

                            .WillOnce(Return('d')).WillOnce(Return('e'))

                            .WillOnce(Return('d'));

    ON_CALL(stream, get()).WillOnce(Return('f')).WillOnce(Return('l'))

                          .WillOnce(Return('o')).WillOnce(Return('w'))

                          .WillOnce(Return(' ')).WillOnce(Return('f'))

                          .WillOnce(Return('o')).WillOnce(Return('l'))

                          .WillOnce(Return('d')).WillOnce(Return('e'))

                          .WillOnce(Return('d'));

    params.fold = FOLD_FLOW;

    EXPECT_EQ(ScanScalar(stream, params), "flow folded ");

}



TEST_F(ScanScalarTest_161, NormalOperation_ChopHandling_161) {

    iss.str("chop\nmore\nlines\n");

    ON_CALL(stream, peek()).WillOnce(Return('c')).WillOnce(Return('h'))

                            .WillOnce(Return('o')).WillOnce(Return('p'))

                            .WillOnce(Return('\n')).WillOnce(Return('m'))

                            .WillOnce(Return('o')).WillOnce(Return('r'))

                            .WillOnce(Return('e')).WillOnce(Return('\n'))

                            .WillOnce(Return('l')).WillOnce(Return('i'))

                            .WillOnce(Return('n')).WillOnce(Return('e'))

                            .WillOnce(Return('s')).WillOnce(Return('\n'));

    ON_CALL(stream, get()).WillOnce(Return('c')).WillOnce(Return('h'))

                          .WillOnce(Return('o')).WillOnce(Return('p'))

                          .WillOnce(Return('\n')).WillOnce(Return('m'))

                          .WillOnce(Return('o')).WillOnce(Return('r'))

                          .WillOnce(Return('e')).WillOnce(Return('\n'))

                          .WillOnce(Return('l')).WillOnce(Return('i'))

                          .WillOnce(Return('n')).WillOnce(Return('e'))

                          .WillOnce(Return('s')).WillOnce(Return('\n'));

    params.chomp = CHOMP::CLIP;

    EXPECT_EQ(ScanScalar(stream, params), "chop\nmore\nlines");

}



TEST_F(ScanScalarTest_161, NormalOperation_StripHandling_161) {

    iss.str("strip\nmore\nlines\n");

    ON_CALL(stream, peek()).WillOnce(Return('s')).WillOnce(Return('t'))

                            .WillOnce(Return('r')).WillOnce(Return('i'))

                            .WillOnce(Return('p')).WillOnce(Return('\n'))

                            .WillOnce(Return('m')).WillOnce(Return('o'))

                            .WillOnce(Return('r')).WillOnce(Return('e'))

                            .WillOnce(Return('\n')).WillOnce(Return('l'))

                            .WillOnce(Return('i')).WillOnce(Return('n'))

                            .WillOnce(Return('e')).WillOnce(Return('s'))

                            .WillOnce(Return('\n'));

    ON_CALL(stream, get()).WillOnce(Return('s')).WillOnce(Return('t'))

                          .WillOnce(Return('r')).WillOnce(Return('i'))

                          .WillOnce(Return('p')).WillOnce(Return('\n'))

                          .WillOnce(Return('m')).WillOnce(Return('o'))

                          .WillOnce(Return('r')).WillOnce(Return('e'))

                          .WillOnce(Return('\n')).WillOnce(Return('l'))

                          .WillOnce(Return('i')).WillOnce(Return('n'))

                          .WillOnce(Return('e')).WillOnce(Return('s'))

                          .WillOnce(Return('\n'));

    params.chomp = CHOMP::STRIP;

    EXPECT_EQ(ScanScalar(stream, params), "strip\nmore\nlines");

}
