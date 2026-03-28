#include <gtest/gtest.h>

#include "XRef.h"



class XRefTest_264 : public ::testing::Test {

protected:

    XRef* xref;



    void SetUp() override {

        xref = new XRef();

    }



    void TearDown() override {

        delete xref;

    }

};



TEST_F(XRefTest_264, GetRootGen_DefaultValue_264) {

    EXPECT_EQ(xref->getRootGen(), 0);

}



// Assuming there's a way to set rootGen externally or via constructor

// Since we cannot modify internal state, this is the best boundary condition we can test.

TEST_F(XRefTest_264, GetRootGen_BoundaryCondition_264) {

    EXPECT_EQ(xref->getRootGen(), 0);

}



// Assuming there's no exceptional case for getRootGen as it just returns an int value

// If there were any error codes or exceptions, they would need to be handled in the implementation.

TEST_F(XRefTest_264, GetRootGen_ExceptionalCase_264) {

    EXPECT_EQ(xref->getRootGen(), 0);

}
