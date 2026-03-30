#include <gtest/gtest.h>

#include "pcre.h"



using namespace re2;



class PCRETest_201 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize with a sample pattern for testing.

        pcre_instance = new PCRE("(a)(b(c))");

    }



    void TearDown() override {

        delete pcre_instance;

    }



    PCRE* pcre_instance;

};



TEST_F(PCRETest_201, NumberOfCapturingGroups_ValidPattern_201) {

    EXPECT_EQ(pcre_instance->NumberOfCapturingGroups(), 3);

}



TEST_F(PCRETest_201, NumberOfCapturingGroups_EmptyPattern_201) {

    PCRE empty_pcre("");

    EXPECT_EQ(empty_pcre.NumberOfCapturingGroups(), -1);

}



TEST_F(PCRETest_201, NumberOfCapturingGroups_NullPointer_201) {

    pcre_instance->re_partial_ = nullptr;

    EXPECT_EQ(pcre_instance->NumberOfCapturingGroups(), -1);

}



TEST_F(PCRETest_201, NumberOfCapturingGroups_NoMatch_201) {

    // Assuming no match error does not affect capturing groups count.

    PCRE no_match_pcre(".*x");

    EXPECT_EQ(no_match_pcre.NumberOfCapturingGroups(), 0); // Adjust based on actual behavior

}



TEST_F(PCRETest_201, NumberOfCapturingGroups_ComplexPattern_201) {

    PCRE complex_pcre("(a(b(c(d(e(f(g(h(i(j(k(l(m(n(o(p(q(r(s(t(u(v(w(x(y(z))))))))))))))");

    EXPECT_EQ(complex_pcre.NumberOfCapturingGroups(), 19);

}
