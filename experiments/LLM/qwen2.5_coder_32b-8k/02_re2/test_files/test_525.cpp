#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace re2 {



class MockCharClassBuilder : public CharClassBuilder {

public:

    MOCK_METHOD(void, AddRangeFlags, (Rune lo, Rune hi, Regexp::ParseFlags parse_flags), (override));

    MOCK_METHOD(void, Negate, (), (override));

    MOCK_METHOD(void, AddCharClass, (CharClassBuilder* cc), (override));

};



struct TestURange16 {

    uint16_t lo;

    uint16_t hi;

};



struct TestUGroup {

    const char * name;

    int sign;

    const TestURange16 * r16;

    int nr16;

    const URange32 * r32;

    int nr32;

};



TEST_F(AddUGroupTest_525, PositiveSignSingleRange_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}};

    TestUGroup g = {"test", +1, ranges, 1, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(10, 20, Regexp::NoParseFlags)).Times(1);



    AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, PositiveSignMultipleRanges_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}, {30, 40}};

    TestUGroup g = {"test", +1, ranges, 2, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(10, 20, Regexp::NoParseFlags)).Times(1);

    EXPECT_CALL(cc, AddRangeFlags(30, 40, Regexp::NoParseFlags)).Times(1);



    AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, NegativeSignSingleRange_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}};

    TestUGroup g = {"test", -1, ranges, 1, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(0, 9, Regexp::NoParseFlags)).Times(1);

    EXPECT_CALL(cc, AddRangeFlags(21, Runemax, Regexp::NoParseFlags)).Times(1);



    AddUGroup(&cc, &g, -1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, NegativeSignMultipleRanges_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}, {30, 40}};

    TestUGroup g = {"test", -1, ranges, 2, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(0, 9, Regexp::NoParseFlags)).Times(1);

    EXPECT_CALL(cc, AddRangeFlags(21, 29, Regexp::NoParseFlags)).Times(1);

    EXPECT_CALL(cc, AddRangeFlags(41, Runemax, Regexp::NoParseFlags)).Times(1);



    AddUGroup(&cc, &g, -1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, NegativeSignWithFoldCaseAndClassNL_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}};

    TestUGroup g = {"test", -1, ranges, 1, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(10, 20, Regexp::FoldCase)).Times(1);

    EXPECT_CALL(cc, Negate()).Times(1);



    MockCharClassBuilder ccb1;

    EXPECT_CALL(ccb1, AddRange('\n', '\n')).Times(1);

    EXPECT_CALL(ccb1, Negate()).Times(1);

    EXPECT_CALL(cc, AddCharClass(&ccb1)).Times(1);



    AddUGroup(&cc, &g, -1, Regexp::FoldCase | Regexp::ClassNL);

}



TEST_F(AddUGroupTest_525, NegativeSignWithFoldCaseAndNeverNL_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{10, 20}};

    TestUGroup g = {"test", -1, ranges, 1, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(10, 20, Regexp::FoldCase)).Times(1);

    EXPECT_CALL(cc, Negate()).Times(1);



    MockCharClassBuilder ccb1;

    EXPECT_CALL(ccb1, Negate()).Times(1);

    EXPECT_CALL(cc, AddCharClass(&ccb1)).Times(1);



    AddUGroup(&cc, &g, -1, Regexp::FoldCase | Regexp::NeverNL);

}



TEST_F(AddUGroupTest_525, EdgeCaseNoRanges_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {};

    TestUGroup g = {"test", +1, ranges, 0, nullptr, 0};



    AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, EdgeCaseFullRangePositiveSign_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{0, Runemax}};

    TestUGroup g = {"test", +1, ranges, 1, nullptr, 0};



    EXPECT_CALL(cc, AddRangeFlags(0, Runemax, Regexp::NoParseFlags)).Times(1);



    AddUGroup(&cc, &g, +1, Regexp::NoParseFlags);

}



TEST_F(AddUGroupTest_525, EdgeCaseFullRangeNegativeSign_525) {

    MockCharClassBuilder cc;

    TestURange16 ranges[] = {{0, Runemax}};

    TestUGroup g = {"test", -1, ranges, 1, nullptr, 0};



    AddUGroup(&cc, &g, -1, Regexp::NoParseFlags);

}



} // namespace re2
