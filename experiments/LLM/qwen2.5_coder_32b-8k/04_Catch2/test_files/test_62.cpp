#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_result_type.hpp"



using namespace Catch;



class ResultDispositionTest_62 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed.

};



TEST_F(ResultDispositionTest_62, OperatorOrReturnsCombinedFlags_62) {

    ResultDisposition::Flags flag1 = ResultDisposition::ContinueOnFailure;

    ResultDisposition::Flags flag2 = ResultDisposition::SuppressFailures;



    ResultDisposition::Flags result = flag1 | flag2;



    EXPECT_EQ(result, static_cast<ResultDisposition::Flags>(3));

}



TEST_F(ResultDispositionTest_62, OperatorOrWithZeroFlagReturnsOtherFlag_62) {

    ResultDisposition::Flags zeroFlag = static_cast<ResultDisposition::Flags>(0);

    ResultDisposition::Flags flag1 = ResultDisposition::ContinueOnFailure;



    ResultDisposition::Flags result = zeroFlag | flag1;



    EXPECT_EQ(result, flag1);

}



TEST_F(ResultDispositionTest_62, OperatorOrWithSameFlagsReturnsSameFlag_62) {

    ResultDisposition::Flags flag1 = ResultDisposition::ContinueOnFailure;

    ResultDisposition::Flags sameFlag1 = ResultDisposition::ContinueOnFailure;



    ResultDisposition::Flags result = flag1 | sameFlag1;



    EXPECT_EQ(result, flag1);

}



TEST_F(ResultDispositionTest_62, OperatorOrWithAllFlagsReturnsAllBitsSet_62) {

    ResultDisposition::Flags allFlags = static_cast<ResultDisposition::Flags>(

        ResultDisposition::ContinueOnFailure |

        ResultDisposition::SuppressFailures |

        ResultDisposition::Quiet |

        ResultDisposition::Normal |

        ResultDisposition::FalseTest |

        ResultDisposition::Message |

        ResultDisposition::ShouldExit);



    ResultDisposition::Flags result = allFlags | allFlags;



    EXPECT_EQ(result, allFlags);

}
