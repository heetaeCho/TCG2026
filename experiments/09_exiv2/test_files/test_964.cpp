#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class CanonMakerNoteTest_964 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue;

};



TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NormalOperation_964) {

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(150));

    CanonMakerNote makerNote;

    std::ostream& result = makerNote.printSi0x0018(oss, mockValue, nullptr);

    EXPECT_EQ(result.str(), "15");

}



TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_ZeroValue_964) {

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(0));

    CanonMakerNote makerNote;

    std::ostream& result = makerNote.printSi0x0018(oss, mockValue, nullptr);

    EXPECT_EQ(result.str(), "0");

}



TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_NegativeValue_964) {

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(-50));

    CanonMakerNote makerNote;

    std::ostream& result = makerNote.printSi0x0018(oss, mockValue, nullptr);

    EXPECT_EQ(result.str(), "-5");

}



TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_BoundaryConditionPositive_964) {

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(9));

    CanonMakerNote makerNote;

    std::ostream& result = makerNote.printSi0x0018(oss, mockValue, nullptr);

    EXPECT_EQ(result.str(), "0");

}



TEST_F(CanonMakerNoteTest_964, PrintSi0x0018_BoundaryConditionNegative_964) {

    EXPECT_CALL(mockValue, toInt64()).WillOnce(Return(-9));

    CanonMakerNote makerNote;

    std::ostream& result = makerNote.printSi0x0018(oss, mockValue, nullptr);

    EXPECT_EQ(result.str(), "0");

}

```



**Explanation:**

- The test cases cover normal operations by verifying the expected output for a typical input.

- Boundary conditions are checked with zero and values just below the threshold to ensure correct rounding/truncation behavior.

- Negative values are tested to ensure that the function handles them correctly, producing the appropriate negative result.
