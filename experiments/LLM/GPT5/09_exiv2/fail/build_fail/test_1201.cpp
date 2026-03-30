#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/bmffimage.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"
#include <sstream>
#include <string>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

namespace {

    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(int, open, (), (override));
        MOCK_METHOD(int, close, (), (override));
        MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
        MOCK_METHOD(int, getb, (), (override));
        MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
        MOCK_METHOD(size_t, size, (), (const, override));
    };

    class BmffImageTest : public ::testing::Test {
    protected:
        std::unique_ptr<MockBasicIo> mockIo_;
        std::unique_ptr<BmffImage> bmffImage_;

        void SetUp() override {
            mockIo_ = std::make_unique<MockBasicIo>();
            bmffImage_ = std::make_unique<BmffImage>(std::move(mockIo_), true, 5);
        }
    };

    TEST_F(BmffImageTest, PrintStructureBasicOption) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));
        
        bmffImage_->printStructure(out, kpsBasic, 0);
        EXPECT_FALSE(out.str().empty());
    }

    TEST_F(BmffImageTest, PrintStructureXmpOption) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));

#ifdef EXV_HAVE_XMP_TOOLKIT
        // XMP-related expectations
        EXPECT_CALL(*mockIo_, seek(_, _)).Times(AtLeast(1));
        EXPECT_CALL(*mockIo_, write(_, _)).Times(AtLeast(1));
#endif
        
        bmffImage_->printStructure(out, kpsXMP, 0);
        EXPECT_FALSE(out.str().empty());
    }

    TEST_F(BmffImageTest, PrintStructureErrorInXMP) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));
        
#ifdef EXV_HAVE_XMP_TOOLKIT
        // Simulating a failure in XMP encoding
        EXPECT_CALL(*mockIo_, seek(_, _)).Times(AtLeast(1));
        EXPECT_CALL(*mockIo_, write(_, _)).Times(AtLeast(1));
        EXPECT_CALL(*mockIo_, write(_, _)).WillOnce(Throw(Error(ErrorCode::kerErrorMessage, "Failed to serialize XMP data")));
        
        EXPECT_THROW(bmffImage_->printStructure(out, kpsXMP, 0), Error);
#endif
    }

    TEST_F(BmffImageTest, PrintStructureRecursiveOption) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));

        // Mocking openOrThrow behavior
        EXPECT_CALL(*mockIo_, seek(_, _)).WillOnce(Return(0));
        
        bmffImage_->printStructure(out, kpsRecursive, 1);
        EXPECT_FALSE(out.str().empty());
    }

    TEST_F(BmffImageTest, PrintStructureInvalidOption) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));
        
        bmffImage_->printStructure(out, static_cast<PrintStructureOption>(99), 0);  // Invalid option
        EXPECT_EQ(out.str().size(), 0);  // No output expected for invalid option
    }
    
    TEST_F(BmffImageTest, PrintStructureIccProfileOption) {
        std::ostringstream out;
        EXPECT_CALL(*mockIo_, size()).WillOnce(Return(100));
        
        bmffImage_->printStructure(out, kpsIccProfile, 0);
        EXPECT_FALSE(out.str().empty());
    }
}