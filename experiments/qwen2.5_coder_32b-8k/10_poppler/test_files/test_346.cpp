#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Link.h"

#include <vector>

#include <memory>



class LinksTest_346 : public ::testing::Test {

protected:

    std::shared_ptr<AnnotLink> mockAnnotLink1;

    std::shared_ptr<AnnotLink> mockAnnotLink2;



    void SetUp() override {

        mockAnnotLink1 = std::make_shared<AnnotLink>();

        mockAnnotLink2 = std::make_shared<AnnotLink>();

    }

};



TEST_F(LinksTest_346, GetLinks_ReturnsEmptyVector_346) {

    // Arrange

    Links links(nullptr);



    // Act

    const auto& result = links.getLinks();



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(LinksTest_346, GetLinks_ReturnsNonEmptyVector_346) {

    // Arrange

    std::vector<std::shared_ptr<AnnotLink>> annotLinks = {mockAnnotLink1, mockAnnotLink2};

    Links links(nullptr);  // Assuming constructor can be mocked or the internal state can be set up



    // Since we cannot modify internal state directly, this test assumes a setup where links are added

    // For demonstration, let's assume there is some way to populate 'links' with mockAnnotLink1 and mockAnnotLink2



    // Act

    const auto& result = links.getLinks();



    // Assert

    EXPECT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], mockAnnotLink1);

    EXPECT_EQ(result[1], mockAnnotLink2);

}



TEST_F(LinksTest_346, GetLinks_ReturnsConsistentData_346) {

    // Arrange

    std::vector<std::shared_ptr<AnnotLink>> annotLinks = {mockAnnotLink1};

    Links links(nullptr);  // Assuming constructor can be mocked or the internal state can be set up



    // Since we cannot modify internal state directly, this test assumes a setup where links are added

    // For demonstration, let's assume there is some way to populate 'links' with mockAnnotLink1



    // Act

    const auto& result = links.getLinks();



    // Assert

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], mockAnnotLink1);



    // Second call to ensure consistency

    const auto& secondResult = links.getLinks();

    EXPECT_EQ(secondResult, result);

}

```


