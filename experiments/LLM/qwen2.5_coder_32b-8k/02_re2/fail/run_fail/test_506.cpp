#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"

#include "parse.cc"



using namespace re2;



class FactorAlternationImplTest : public ::testing::Test {

protected:

    FactorAlternationImpl factor_alternation_impl_;

};



TEST_F(FactorAlternationImplTest, Round1_EmptySubArray_506) {

    Regexp* sub[] = {};

    int nsub = 0;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 0);

}



TEST_F(FactorAlternationImplTest, Round1_SingleSubArray_506) {

    Regexp* sub[] = {Regexp::LiteralString(nullptr, 0, Regexp::NoParseFlags)};

    int nsub = 1;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 0);

}



TEST_F(FactorAlternationImplTest, Round1_TwoSubArray_NoCommonPrefix_506) {

    Regexp* sub[] = {

        Regexp::LiteralString(nullptr, 0, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abc", 3, Regexp::NoParseFlags)

    };

    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 0);

}



TEST_F(FactorAlternationImplTest, Round1_TwoSubArray_CommonPrefix_506) {

    Regexp* sub[] = {

        Regexp::LiteralString((Rune*)"abc", 3, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abcd", 4, Regexp::NoParseFlags)

    };

    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 1);

    EXPECT_EQ(splices[0].prefix->nrunes(), 3);

}



TEST_F(FactorAlternationImplTest, Round1_MultipleSubArray_Complex_506) {

    Regexp* sub[] = {

        Regexp::LiteralString((Rune*)"abc", 3, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abcd", 4, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abce", 4, Regexp::NoParseFlags)

    };

    int nsub = 3;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 2);

    EXPECT_EQ(splices[0].prefix->nrunes(), 3);

    EXPECT_EQ(splices[1].prefix->nrunes(), 2);

}



TEST_F(FactorAlternationImplTest, Round1_FlagDifferences_506) {

    Regexp* sub[] = {

        Regexp::LiteralString((Rune*)"abc", 3, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abc", 3, Regexp::FoldCase)

    };

    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 0);

}



TEST_F(FactorAlternationImplTest, Round1_LongestCommonPrefix_506) {

    Regexp* sub[] = {

        Regexp::LiteralString((Rune*)"abcdef", 6, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abcde", 5, Regexp::NoParseFlags),

        Regexp::LiteralString((Rune*)"abcd", 4, Regexp::NoParseFlags)

    };

    int nsub = 3;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 2);

    EXPECT_EQ(splices[0].prefix->nrunes(), 4);

    EXPECT_EQ(splices[1].prefix->nrunes(), 3);

}



TEST_F(FactorAlternationImplTest, Round1_BoundaryCondition_MaxInt_506) {

    Regexp* sub[] = {};

    int nsub = std::numeric_limits<int>::max();

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    // This test is more about ensuring no overflow or crash

    factor_alternation_impl_.Round1(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 0);

}
