#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/datasets.hpp"



using namespace Exiv2;



class IptcdatumTest_670 : public ::testing::Test {

protected:

    std::string testKey = "testKey";

    IptcKey key{testKey};

    Iptcdatum iptcdatum{key, nullptr};



    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(IptcdatumTest_670, TagName_ReturnsEmptyStringWhenNoKey_670) {

    Iptcdatum iptcdatumWithoutKey{IptcKey{}, nullptr};

    EXPECT_EQ(iptcdatumWithoutKey.tagName(), "");

}



TEST_F(IptcdatumTest_670, TagName_ReturnsCorrectTagName_670) {

    EXPECT_EQ(iptcdatum.tagName(), testKey);

}



// Boundary conditions

TEST_F(IptcdatumTest_670, TagName_HandlesEmptyStringKey_670) {

    IptcKey emptyKey{""};

    Iptcdatum iptcdatumWithEmptyKey{emptyKey, nullptr};

    EXPECT_EQ(iptcdatumWithEmptyKey.tagName(), "");

}



// Exceptional or error cases

// No observable exceptional/error cases for tagName() based on the provided interface



// Verification of external interactions

// No external interactions to verify for tagName()



```


