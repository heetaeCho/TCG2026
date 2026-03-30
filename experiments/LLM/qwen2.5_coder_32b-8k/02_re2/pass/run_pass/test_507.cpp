#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;

using ::testing::ElementsAre;



class FactorAlternationImplTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or objects

        sub = new Regexp*[3];

        splices = new std::vector<Splice>();

    }



    void TearDown() override {

        // Clean up after each test

        for (int i = 0; i < 3; i++) {

            if (sub[i]) {

                sub[i]->Decref();

                sub[i] = nullptr;

            }

        }

        delete[] sub;

        delete splices;

    }



    Regexp** sub;

    std::vector<Splice>* splices;

};



TEST_F(FactorAlternationImplTest, Round2_EmptySubs_507) {

    int nsub = 0;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_TRUE(splices->empty());

}



TEST_F(FactorAlternationImplTest, Round2_SingleSub_507) {

    sub[0] = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    int nsub = 1;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_TRUE(splices->empty());

}



TEST_F(FactorAlternationImplTest, Round2_TwoSubsSameOp_507) {

    sub[0] = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    sub[1] = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_EQ(splices->size(), 1);

}



TEST_F(FactorAlternationImplTest, Round2_TwoSubsDifferentOps_507) {

    sub[0] = Regexp::NewLiteral('a', Regexp::ParseFlags(0));

    sub[1] = Regexp::NewLiteral('b', Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_TRUE(splices->empty());

}



TEST_F(FactorAlternationImplTest, Round2_MultipleSubsSamePrefix_507) {

    sub[0] = Regexp::Concat(new Regexp*[2]{Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::NewLiteral('b', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    sub[1] = Regexp::Concat(new Regexp*[2]{Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::NewLiteral('c', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_EQ(splices->size(), 1);

}



TEST_F(FactorAlternationImplTest, Round2_MultipleSubsDifferentPrefixes_507) {

    sub[0] = Regexp::Concat(new Regexp*[2]{Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::NewLiteral('b', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    sub[1] = Regexp::Concat(new Regexp*[2]{Regexp::NewLiteral('c', Regexp::ParseFlags(0)), Regexp::NewLiteral('d', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_TRUE(splices->empty());

}



TEST_F(FactorAlternationImplTest, Round2_MultipleSubsSamePrefixWithRepeats_507) {

    sub[0] = Regexp::Concat(new Regexp*[2]{Regexp::Repeat(Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::ParseFlags(0), 1, 1), Regexp::NewLiteral('b', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    sub[1] = Regexp::Concat(new Regexp*[2]{Regexp::Repeat(Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::ParseFlags(0), 1, 1), Regexp::NewLiteral('c', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_EQ(splices->size(), 1);

}



TEST_F(FactorAlternationImplTest, Round2_MultipleSubsSamePrefixWithDifferentRepeats_507) {

    sub[0] = Regexp::Concat(new Regexp*[2]{Regexp::Repeat(Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::ParseFlags(0), 1, 1), Regexp::NewLiteral('b', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    sub[1] = Regexp::Concat(new Regexp*[2]{Regexp::Repeat(Regexp::NewLiteral('a', Regexp::ParseFlags(0)), Regexp::ParseFlags(0), 2, 2), Regexp::NewLiteral('c', Regexp::ParseFlags(0))}, 2, Regexp::ParseFlags(0));

    int nsub = 2;

    FactorAlternationImpl impl;

    impl.Round2(sub, nsub, Regexp::ParseFlags(0), splices);

    EXPECT_TRUE(splices->empty());

}
