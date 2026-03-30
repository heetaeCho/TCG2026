#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"  // Assuming the class is defined here
#include "tiffvisitor_int.hpp"    // Assuming visitor class is defined here

namespace Exiv2 { namespace Internal {

// Mock class for the TiffVisitor to test interaction with TiffDirectory
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visitDirectory, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory* object), (override));
    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory* object), (override));
    MOCK_METHOD(bool, go, (GoEvent event), (const, override));
};

} }  // namespace Exiv2::Internal

// Test Fixture for TiffDirectory
class TiffDirectoryTest : public ::testing::Test {
protected:
    Exiv2::Internal::TiffDirectory directory;
    MockTiffVisitor visitor;

    TiffDirectoryTest()
        : directory(100, Exiv2::Internal::IfdId::ifd0, true) {}

    // Helper method to simulate 'accept' method call
    void testAcceptVisitor() {
        directory.doAccept(visitor);
    }
};

// Test normal operation - visitor should visit the directory
TEST_F(TiffDirectoryTest, DoAcceptVisitor_VisitsDirectory_342) {
    EXPECT_CALL(visitor, visitDirectory(&directory)).Times(1);
    testAcceptVisitor();
}

// Test normal operation - visitor should visit directory next
TEST_F(TiffDirectoryTest, DoAcceptVisitor_VisitsDirectoryNext_343) {
    EXPECT_CALL(visitor, visitDirectoryNext(&directory)).Times(1);
    testAcceptVisitor();
}

// Test boundary condition - visitor goes back when asked
TEST_F(TiffDirectoryTest, DoAcceptVisitor_GoesBackWhenGoIsFalse_344) {
    EXPECT_CALL(visitor, go(Exiv2::Internal::geTraverse)).WillOnce(testing::Return(false));
    EXPECT_CALL(visitor, visitDirectoryNext(&directory)).Times(0);
    EXPECT_CALL(visitor, visitDirectoryEnd(&directory)).Times(0);
    testAcceptVisitor();
}

// Test boundary condition - visitor goes to the next element
TEST_F(TiffDirectoryTest, DoAcceptVisitor_GoesToNextElement_345) {
    EXPECT_CALL(visitor, go(Exiv2::Internal::geTraverse)).WillOnce(testing::Return(true));
    EXPECT_CALL(visitor, visitDirectoryNext(&directory)).Times(1);
    testAcceptVisitor();
}

// Test exceptional case - visitor does not visit the directory
TEST_F(TiffDirectoryTest, DoAcceptVisitor_FailsOnVisitor_346) {
    EXPECT_CALL(visitor, go(Exiv2::Internal::geTraverse)).WillOnce(testing::Return(false));
    EXPECT_CALL(visitor, visitDirectoryNext(&directory)).Times(0);
    EXPECT_CALL(visitor, visitDirectoryEnd(&directory)).Times(0);
    testAcceptVisitor();
}

// Test for hasNext condition
TEST_F(TiffDirectoryTest, HasNext_ReturnsTrue_347) {
    EXPECT_TRUE(directory.hasNext());
}

// Test for hasNext condition when there is no next
TEST_F(TiffDirectoryTest, HasNext_ReturnsFalse_348) {
    // Set hasNext_ to false
    directory = Exiv2::Internal::TiffDirectory(100, Exiv2::Internal::IfdId::ifd0, false);
    EXPECT_FALSE(directory.hasNext());
}

// Test boundary condition for empty directory (e.g., no components)
TEST_F(TiffDirectoryTest, DoAcceptVisitor_EmptyDirectory_349) {
    EXPECT_CALL(visitor, visitDirectory(&directory)).Times(1);
    EXPECT_CALL(visitor, visitDirectoryEnd(&directory)).Times(1);
    testAcceptVisitor();
}

}  // namespace Exiv2::Internal