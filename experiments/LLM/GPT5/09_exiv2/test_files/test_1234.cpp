#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "basicio.hpp"
#include "tgaimage.hpp"

// Mock BasicIo class to simulate file reading operations
class MockBasicIo : public Exiv2::BasicIo {
public:
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(void, seek, (long offset, int origin), (override));
    MOCK_METHOD(void, read, (byte* buf, size_t size), (override));
    MOCK_METHOD(bool, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
};

class TgaImageTest_1234 : public ::testing::Test {
protected:
    MockBasicIo mockIo;
};

// Test case for normal operation where the file path ends with ".tga"
TEST_F(TgaImageTest_1234, IsTgaType_FileEndsWithTga) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.tga")));
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_TRUE(result);
}

// Test case for normal operation where the file path ends with ".TGA"
TEST_F(TgaImageTest_1234, IsTgaType_FileEndsWithUppercaseTGA) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.TGA")));
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_TRUE(result);
}

// Test case for boundary condition when the file path is an empty string
TEST_F(TgaImageTest_1234, IsTgaType_EmptyPath) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("")));
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_FALSE(result);
}

// Test case for boundary condition when the file is too small (less than 26 bytes)
TEST_F(TgaImageTest_1234, IsTgaType_FileTooSmall) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.tga")));
    EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(10)); // File size smaller than 26 bytes
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_FALSE(result);
}

// Test case for exceptional case when seeking fails
TEST_F(TgaImageTest_1234, IsTgaType_SeekError) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.tga")));
    EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(30)); // File large enough
    EXPECT_CALL(mockIo, seek(-26, Exiv2::BasicIo::end)).WillOnce(testing::Throw(std::runtime_error("Seek error")));
    
    // Act & Assert
    EXPECT_THROW(Exiv2::isTgaType(mockIo, false), std::runtime_error);
}

// Test case for normal operation when the file content matches the "TRUEVISION-XFILE" signature
TEST_F(TgaImageTest_1234, IsTgaType_MatchesSignature) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.tga")));
    EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(30)); // File large enough
    EXPECT_CALL(mockIo, seek(-26, Exiv2::BasicIo::end)).WillOnce(testing::Return());
    byte buf[26] = {0};
    std::copy("TRUEVISION-XFILE", "TRUEVISION-XFILE" + 16, buf + 8); // Fill signature in the buffer
    EXPECT_CALL(mockIo, read(testing::_, sizeof(buf))).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(buf, buf + sizeof(buf)), testing::Return()));
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_TRUE(result);
}

// Test case for exceptional case when read fails
TEST_F(TgaImageTest_1234, IsTgaType_ReadError) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.tga")));
    EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(30)); // File large enough
    EXPECT_CALL(mockIo, seek(-26, Exiv2::BasicIo::end)).WillOnce(testing::Return());
    EXPECT_CALL(mockIo, read(testing::_, 26)).WillOnce(testing::Return(false)); // Simulate read failure
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_FALSE(result);
}

// Test case for normal operation when file ends with uppercase "TGA" and contains the correct signature
TEST_F(TgaImageTest_1234, IsTgaType_UppercaseTgaWithCorrectSignature) {
    // Arrange
    EXPECT_CALL(mockIo, path()).WillOnce(testing::ReturnRefOfCopy(std::string("image.TGA")));
    EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(30)); // File large enough
    EXPECT_CALL(mockIo, seek(-26, Exiv2::BasicIo::end)).WillOnce(testing::Return());
    byte buf[26] = {0};
    std::copy("TRUEVISION-XFILE", "TRUEVISION-XFILE" + 16, buf + 8); // Fill signature in the buffer
    EXPECT_CALL(mockIo, read(testing::_, sizeof(buf))).WillOnce(testing::DoAll(testing::SetArrayArgument<0>(buf, buf + sizeof(buf)), testing::Return()));
    
    // Act
    bool result = Exiv2::isTgaType(mockIo, false);
    
    // Assert
    EXPECT_TRUE(result);
}