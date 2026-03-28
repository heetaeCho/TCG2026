#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;

using ::testing::_;

using ::testing::ElementsAre;



class FactorAlternationImplTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common test resources here

    }



    void TearDown() override {

        // Cleanup any common test resources here

    }

};



TEST_F(FactorAlternationImplTest, Round3_EmptySubArray_508) {

    Regexp** sub = nullptr;

    int nsub = 0;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

}



TEST_F(FactorAlternationImplTest, Round3_SingleLiteral_508) {

    Regexp* re1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp** sub = new Regexp*[1];

    sub[0] = re1;

    int nsub = 1;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

    re1->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_TwoDifferentLiterals_508) {

    Regexp* re1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);

    Regexp** sub = new Regexp*[2];

    sub[0] = re1;

    sub[1] = re2;

    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

    re1->Decref();

    re2->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_TwoSameLiterals_508) {

    Regexp* re1 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('a', Regexp::NoParseFlags);

    Regexp** sub = new Regexp*[2];

    sub[0] = re1;

    sub[1] = re2;

    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 1);

    EXPECT_EQ(splices[0].newre->op(), kRegexpCharClass);

    re1->Decref();

    re2->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_CharClassAndLiteral_508) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'c');

    CharClass* cc = ccb.GetCharClass();



    Regexp* re1 = Regexp::NewCharClass(cc, Regexp::NoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('d', Regexp::NoParseFlags);



    Regexp** sub = new Regexp*[2];

    sub[0] = re1;

    sub[1] = re2;



    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

    re1->Decref();

    re2->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_CharClassAndSameLiteral_508) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'c');

    CharClass* cc = ccb.GetCharClass();



    Regexp* re1 = Regexp::NewCharClass(cc, Regexp::NoParseFlags);

    Regexp* re2 = Regexp::NewLiteral('b', Regexp::NoParseFlags);



    Regexp** sub = new Regexp*[2];

    sub[0] = re1;

    sub[1] = re2;



    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 1);

    EXPECT_EQ(splices[0].newre->op(), kRegexpCharClass);

    re1->Decref();

    re2->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_CharClasses_508) {

    CharClassBuilder ccb1;

    ccb1.AddRange('a', 'c');

    CharClass* cc1 = ccb1.GetCharClass();



    CharClassBuilder ccb2;

    ccb2.AddRange('b', 'd');

    CharClass* cc2 = ccb2.GetCharClass();



    Regexp* re1 = Regexp::NewCharClass(cc1, Regexp::NoParseFlags);

    Regexp* re2 = Regexp::NewCharClass(cc2, Regexp::NoParseFlags);



    Regexp** sub = new Regexp*[2];

    sub[0] = re1;

    sub[1] = re2;



    int nsub = 2;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_EQ(splices.size(), 1);

    EXPECT_EQ(splices[0].newre->op(), kRegexpCharClass);

    re1->Decref();

    re2->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_LiteralWithFoldCase_508) {

    Regexp* re1 = Regexp::NewLiteral('a', Regexp::FoldCase);

    Regexp** sub = new Regexp*[1];

    sub[0] = re1;

    int nsub = 1;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

    re1->Decref();

    delete[] sub;

}



TEST_F(FactorAlternationImplTest, Round3_CharClassWithFoldCase_508) {

    CharClassBuilder ccb;

    ccb.AddRange('a', 'c');

    ccb.AddRangeFlags('A', 'C', Regexp::FoldCase);

    CharClass* cc = ccb.GetCharClass();



    Regexp* re1 = Regexp::NewCharClass(cc, Regexp::NoParseFlags);

    Regexp** sub = new Regexp*[1];

    sub[0] = re1;

    int nsub = 1;

    Regexp::ParseFlags flags = Regexp::NoParseFlags;

    std::vector<Splice> splices;



    FactorAlternationImpl().Round3(sub, nsub, flags, &splices);



    EXPECT_TRUE(splices.empty());

    re1->Decref();

    delete[] sub;

}
