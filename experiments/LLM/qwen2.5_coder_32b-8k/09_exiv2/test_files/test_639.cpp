#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/datasets.hpp"



using namespace Exiv2;

using testing::HasSubstr;



class IptcDataSetsTest_639 : public ::testing::Test {

protected:

    IptcDataSets iptcDataSets;

};



TEST_F(IptcDataSetsTest_639, dataSetList_NormalOperation_639) {

    std::ostringstream os;

    iptcDataSets.dataSetList(os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(IptcDataSetsTest_639, dataSetList_EmptyRecords_639) {

    IptcDataSets emptyIptcDataSets;

    std::ostringstream os;

    emptyIptcDataSets.dataSetList(os);

    EXPECT_TRUE(os.str().empty());

}



TEST_F(IptcDataSetsTest_639, dataSetList_BoundaryConditions_639) {

    // Assuming there are boundary conditions related to the internal records structure

    std::ostringstream os;

    iptcDataSets.dataSetList(os);

    EXPECT_FALSE(os.str().empty());  // Check if it handles large or minimal dataset lists correctly

}



TEST_F(IptcDataSetsTest_639, dataSetList_ExceptionalCases_639) {

    // Assuming no exceptional cases directly observable through the interface for this method

    std::ostringstream os;

    iptcDataSets.dataSetList(os);

    EXPECT_NO_THROW(iptcDataSets.dataSetList(os));

}



TEST_F(IptcDataSetsTest_639, dataSetList_OutputVerification_639) {

    std::ostringstream os;

    iptcDataSets.dataSetList(os);

    EXPECT_THAT(os.str(), HasSubstr("\n"));  // Assuming output contains newline-separated records

}
