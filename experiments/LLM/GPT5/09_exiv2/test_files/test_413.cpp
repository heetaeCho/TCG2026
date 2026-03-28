#include <gtest/gtest.h>
#include <memory>
#include <Exiv2/internal/tiffcomposite_int.hpp>

namespace Exiv2 {
namespace Internal {

class TiffComponentMock : public TiffComponent {
public:
    TiffComponentMock(uint16_t tag, IfdId group)
        : TiffComponent(tag, group) {}

    MOCK_CONST_METHOD0(tag, uint16_t());
    MOCK_CONST_METHOD0(idx, int());
};

} // namespace Internal
} // namespace Exiv2

using ::testing::_;
using ::testing::Return;

TEST_F(CmpTagLtTest_413, DifferentTags_ShouldReturnTrueWhenLeftTagIsLess_413) {
    // Arrange
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> lhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> rhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(200, 1);

    // Act & Assert
    EXPECT_TRUE(Exiv2::Internal::cmpTagLt(lhs, rhs));
}

TEST_F(CmpTagLtTest_413, DifferentTags_ShouldReturnFalseWhenRightTagIsLess_413) {
    // Arrange
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> lhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(200, 1);
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> rhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);

    // Act & Assert
    EXPECT_FALSE(Exiv2::Internal::cmpTagLt(lhs, rhs));
}

TEST_F(CmpTagLtTest_413, EqualTags_ShouldCompareIdxValues_413) {
    // Arrange
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> lhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> rhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);

    // Setup idx comparison
    EXPECT_CALL(*lhs, idx()).WillOnce(Return(1));
    EXPECT_CALL(*rhs, idx()).WillOnce(Return(2));

    // Act & Assert
    EXPECT_TRUE(Exiv2::Internal::cmpTagLt(lhs, rhs));
}

TEST_F(CmpTagLtTest_413, EqualTagsAndIdx_ShouldReturnFalse_413) {
    // Arrange
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> lhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);
    std::shared_ptr<Exiv2::Internal::TiffComponentMock> rhs = std::make_shared<Exiv2::Internal::TiffComponentMock>(100, 1);

    // Setup idx comparison
    EXPECT_CALL(*lhs, idx()).WillOnce(Return(2));
    EXPECT_CALL(*rhs, idx()).WillOnce(Return(2));

    // Act & Assert
    EXPECT_FALSE(Exiv2::Internal::cmpTagLt(lhs, rhs));
}