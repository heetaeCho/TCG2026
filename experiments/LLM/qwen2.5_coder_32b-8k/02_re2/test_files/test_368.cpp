#include <gtest/gtest.h>

#include "re2/regexp.h"

#include <string>



using namespace re2;



class RegexpTest_368 : public ::testing::Test {

protected:

    void SetUp() override {

        prefix = new std::string();

        foldcase = new bool(false);

        suffix = nullptr;

    }



    void TearDown() override {

        delete prefix;

        delete foldcase;

        if (suffix != nullptr) {

            suffix->Decref();

        }

    }



    Regexp* CreateRegexp(const std::string& pattern, ParseFlags flags) {

        RegexpStatus status;

        return Regexp::Parse(pattern, flags, &status);

    }



    std::string* prefix;

    bool* foldcase;

    Regexp** suffix;

};



TEST_F(RegexpTest_368, RequiredPrefix_NormalOperation_368) {

    Regexp* re = CreateRegexp("^hello.*", NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "h");

    EXPECT_FALSE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_NoPrefix_368) {

    Regexp* re = CreateRegexp("hello.*", NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "");

    EXPECT_FALSE(*foldcase);

    EXPECT_EQ(suffix, nullptr);



    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_BoundaryCondition_EmptyString_368) {

    Regexp* re = CreateRegexp("^", NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "");

    EXPECT_FALSE(*foldcase);

    EXPECT_EQ(suffix, nullptr);



    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_BoundaryCondition_SingleCharLiteral_368) {

    Regexp* re = CreateRegexp("^a", NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "a");

    EXPECT_FALSE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_BoundaryCondition_MultipleConcatenations_368) {

    Regexp* re = CreateRegexp("^abc", NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "a");

    EXPECT_FALSE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_BoundaryCondition_LiteralString_368) {

    Regexp* re = CreateRegexp("^hello", NoParseFlags);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "h");

    EXPECT_FALSE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_ErrorCase_NoConcatenation_368) {

    Regexp* re = CreateRegexp("hello|world", NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "");

    EXPECT_FALSE(*foldcase);

    EXPECT_EQ(suffix, nullptr);



    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_ErrorCase_EmptyConcatenation_368) {

    Regexp* re = CreateRegexp("^", NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "");

    EXPECT_FALSE(*foldcase);

    EXPECT_EQ(suffix, nullptr);



    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_ErrorCase_NoLiteralAtStart_368) {

    Regexp* re = CreateRegexp("^\\dabc", NoParseFlags);

    EXPECT_FALSE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "");

    EXPECT_FALSE(*foldcase);

    EXPECT_EQ(suffix, nullptr);



    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_CaseFold_368) {

    Regexp* re = CreateRegexp("^hello", FoldCase);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "h");

    EXPECT_TRUE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}



TEST_F(RegexpTest_368, RequiredPrefix_Latin1_368) {

    Regexp* re = CreateRegexp("^hello", Latin1);

    EXPECT_TRUE(re->RequiredPrefix(prefix, foldcase, &suffix));

    EXPECT_EQ(*prefix, "h");

    EXPECT_FALSE(*foldcase);

    EXPECT_NE(suffix, nullptr);



    suffix->Decref();

    delete re;

}
