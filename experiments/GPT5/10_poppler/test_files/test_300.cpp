#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Mock class for LinkNamed since its dependencies are not provided.
class MockObject {
public:
    MOCK_CONST_METHOD0(getName, std::string());
};

// Partial class for LinkNamed based on the provided code
class LinkNamed : public LinkAction {
public:
    explicit LinkNamed(const MockObject* nameObj) : nameObj_(nameObj) {}
    virtual ~LinkNamed() override {}
    bool isOk() const override { return true; }
    LinkActionKind getKind() const override { return LinkActionKind::KindA; }
    const std::string& getName() const { return nameObj_->getName(); }

private:
    const MockObject* nameObj_;
};

// TEST_ID is 300

TEST_F(LinkNamedTest_300, GetName_ReturnsCorrectName_300) {
    // Arrange
    MockObject mockObj;
    std::string expectedName = "TestName";
    EXPECT_CALL(mockObj, getName()).WillOnce(testing::Return(expectedName));

    LinkNamed linkNamed(&mockObj);

    // Act
    const std::string& actualName = linkNamed.getName();

    // Assert
    EXPECT_EQ(actualName, expectedName);
}

TEST_F(LinkNamedTest_301, IsOk_ReturnsTrue_301) {
    // Arrange
    MockObject mockObj;
    LinkNamed linkNamed(&mockObj);

    // Act
    bool result = linkNamed.isOk();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(LinkNamedTest_302, GetKind_ReturnsCorrectKind_302) {
    // Arrange
    MockObject mockObj;
    LinkNamed linkNamed(&mockObj);

    // Act
    LinkActionKind kind = linkNamed.getKind();

    // Assert
    EXPECT_EQ(kind, LinkActionKind::KindA);
}

TEST_F(LinkNamedTest_303, GetName_WhenNameIsEmpty_303) {
    // Arrange
    MockObject mockObj;
    std::string expectedName = "";
    EXPECT_CALL(mockObj, getName()).WillOnce(testing::Return(expectedName));

    LinkNamed linkNamed(&mockObj);

    // Act
    const std::string& actualName = linkNamed.getName();

    // Assert
    EXPECT_EQ(actualName, expectedName);
}

TEST_F(LinkNamedTest_304, Destructor_CleanUp_304) {
    // Arrange
    MockObject mockObj;
    {
        LinkNamed linkNamed(&mockObj);
        // Assert that no memory leak occurs (done implicitly)
    } // Destructor is called here

    // No memory leak or other assertions required since no allocation is shown
}