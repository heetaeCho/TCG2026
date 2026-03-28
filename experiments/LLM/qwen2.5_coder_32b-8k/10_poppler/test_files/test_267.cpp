#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest : public ::testing::Test {

protected:

    XRef xref;

};



TEST_F(XRefTest_267, IsModified_DefaultValue_267) {

    EXPECT_FALSE(xref.isModified());

}



TEST_F(XRefTest_267, IsModified_AfterSetModified_267) {

    xref.setModified();

    EXPECT_TRUE(xref.isModified());

}
