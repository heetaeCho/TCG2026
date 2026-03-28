#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;

using ::testing::Return;



class PreviewImageTest_1210 : public ::testing::Test {

protected:

    PreviewProperties properties_;

    DataBuf data_;



    void SetUp() override {

        properties_.mimeType_ = "image/jpeg";

        properties_.extension_ = "jpg";

        // Assuming DataBuf can be constructed with some default data

        data_ = DataBuf();

    }

};



TEST_F(PreviewImageTest_1210, MimeTypeReturnsCorrectValue_1210) {

    PreviewImage preview(properties_, std::move(data_));

    EXPECT_EQ(preview.mimeType(), "image/jpeg");

}



TEST_F(PreviewImageTest_1210, ExtensionReturnsCorrectValue_1210) {

    PreviewImage preview(properties_, std::move(data_));

    EXPECT_EQ(preview.extension(), "jpg");

}



TEST_F(PreviewImageTest_1210, CopyFunctionalityWorks_1210) {

    PreviewImage original(properties_, std::move(data_));

    DataBuf copy = original.copy();

    // Assuming DataBuf has some way to compare content

    EXPECT_EQ(copy.size(), original.preview_.size());

}



TEST_F(PreviewImageTest_1210, ConstCopyFunctionalityWorks_1210) {

    const PreviewImage original(properties_, std::move(data_));

    DataBuf copy = original.copy();

    // Assuming DataBuf has some way to compare content

    EXPECT_EQ(copy.size(), original.preview_.size());

}



TEST_F(PreviewImageTest_1210, SizeReturnsCorrectValue_1210) {

    PreviewImage preview(properties_, std::move(data_));

    // Assuming we know the size of data_

    EXPECT_EQ(preview.size(), static_cast<uint32_t>(data_.size()));

}



TEST_F(PreviewImageTest_1210, ConstSizeReturnsCorrectValue_1210) {

    const PreviewImage preview(properties_, std::move(data_));

    // Assuming we know the size of data_

    EXPECT_EQ(preview.size(), static_cast<uint32_t>(data_.size()));

}



TEST_F(PreviewImageTest_1210, pDataReturnsValidPointer_1210) {

    PreviewImage preview(properties_, std::move(data_));

    EXPECT_NE(preview.pData(), nullptr);

}



TEST_F(PreviewImageTest_1210, ConstPDataReturnsValidPointer_1210) {

    const PreviewImage preview(properties_, std::move(data_));

    EXPECT_NE(preview.pData(), nullptr);

}



// Assuming writeFile writes to a file and returns the number of bytes written

class MockFileSystem {

public:

    MOCK_METHOD(size_t, writeToFile, (const std::string& path, const DataBuf& data), (const));

};



TEST_F(PreviewImageTest_1210, WriteFileWritesDataCorrectly_1210) {

    MockFileSystem mockFs;

    PreviewImage preview(properties_, std::move(data_));

    EXPECT_CALL(mockFs, writeToFile(::testing::_, ::testing::_)).WillOnce(Return(data_.size()));

    size_t bytesWritten = preview.writeFile("test.jpg");

    EXPECT_EQ(bytesWritten, data_.size());

}



TEST_F(PreviewImageTest_1210, WriteFileReturnsZeroOnFailure_1210) {

    MockFileSystem mockFs;

    PreviewImage preview(properties_, std::move(data_));

    EXPECT_CALL(mockFs, writeToFile(::testing::_, ::testing::_)).WillOnce(Return(0));

    size_t bytesWritten = preview.writeFile("test.jpg");

    EXPECT_EQ(bytesWritten, 0);

}



TEST_F(PreviewImageTest_1210, AssignmentOperatorCopiesData_1210) {

    PreviewImage original(properties_, std::move(data_));

    PreviewImage copy;

    copy = original;

    EXPECT_EQ(copy.mimeType(), original.mimeType());

    // Assuming DataBuf has some way to compare content

    EXPECT_EQ(copy.copy().size(), original.copy().size());

}



TEST_F(PreviewImageTest_1210, CopyConstructorCopiesData_1210) {

    PreviewImage original(properties_, std::move(data_));

    PreviewImage copy(original);

    EXPECT_EQ(copy.mimeType(), original.mimeType());

    // Assuming DataBuf has some way to compare content

    EXPECT_EQ(copy.copy().size(), original.copy().size());

}
