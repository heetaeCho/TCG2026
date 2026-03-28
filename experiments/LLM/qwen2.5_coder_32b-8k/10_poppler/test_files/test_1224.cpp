#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



using namespace testing;



class TextOutputDevTest_1224 : public Test {

protected:

    TextOutputDev* textOutputDev;



    void SetUp() override {

        textOutputDev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete textOutputDev;

    }

};



TEST_F(TextOutputDevTest_1224, SetTextEOL_NormalOperation_1224) {

    textOutputDev->setTextEOL(eolUnix);

    // No observable effect to verify directly, but the method should not crash.

}



TEST_F(TextOutputDevTest_1224, SetTextEOL_BoundaryConditions_1224) {

    textOutputDev->setTextEOL(static_cast<EndOfLineKind>(-1)); // Invalid value

    textOutputDev->setTextEOL(static_cast<EndOfLineKind>(3));  // Assuming eolMax is 2, this is invalid

    // No observable effect to verify directly, but the method should not crash.

}



TEST_F(TextOutputDevTest_1224, SetTextEOL_ExceptionalCases_1224) {

    // Since there are no exceptional cases defined in the interface that would throw an exception,

    // we only ensure that invalid values do not cause crashes.

    textOutputDev->setTextEOL(static_cast<EndOfLineKind>(-1));

    textOutputDev->setTextEOL(static_cast<EndOfLineKind>(3));

}
