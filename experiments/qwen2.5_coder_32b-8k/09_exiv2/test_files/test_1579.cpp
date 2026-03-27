#include <gtest/gtest.h>

#include "rw2image.hpp"

#include "basicio.hpp"

#include "imagefactory.hpp"

#include "previewmanager.hpp"

#include "error.hpp"



namespace Exiv2 {



class MockBasicIo : public BasicIo {

public:

    MockBasicIo() = default;



    int open() override { return 0; }

    int close() override { return 0; }

    size_t write(const byte* data, size_t wcount) override { return wcount; }

    int putb(byte data) override { return data; }

    DataBuf read(size_t rcount) override {

        if (rcount > data_.size()) rcount = data_.size();

        DataBuf buf(rcount);

        std::memcpy(buf.pData_, data_.data(), rcount);

        position_ += rcount;

        return buf;

    }

    size_t read(byte* buf, size_t rcount) override {

        if (rcount > data_.size()) rcount = data_.size();

        std::memcpy(buf, data_.data() + position_, rcount);

        position_ += rcount;

        return rcount;

    }

    int getb() override { return position_ < data_.size() ? data_[position_++] : -1; }

    void transfer(BasicIo& src) override {}

    int seek(int64_t offset, Position pos) override {

        switch (pos) {

            case beg:

                if (offset < 0 || static_cast<size_t>(offset) > data_.size()) return -1;

                position_ = static_cast<size_t>(offset);

                break;

            case cur:

                if (position_ + offset < 0 || position_ + offset > data_.size()) return -1;

                position_ += offset;

                break;

            case end:

                if (static_cast<ssize_t>(data_.size()) + offset < 0) return -1;

                position_ = data_.size() + offset;

                break;

        }

        return 0;

    }

    byte* mmap(bool isWriteable) override { return nullptr; }

    int munmap() override { return 0; }

    size_t tell() const override { return position_; }

    size_t size() const override { return data_.size(); }

    bool isopen() const override { return true; }

    int error() const override { return 0; }

    bool eof() const override { return position_ >= data_.size(); }

    const std::string& path() const override { return path_; }



    void setData(const std::vector<byte>& data) {

        data_ = data;

        position_ = 0;

    }



private:

    std::vector<byte> data_;

    size_t position_{0};

    std::string path_{"mock_path"};

};



class Rw2ImageTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo_ = std::make_unique<MockBasicIo>();

        rw2Image_ = std::make_unique<Rw2Image>(std::move(mockIo_));

    }



    void TearDown() override {}



    std::unique_ptr<MockBasicIo> mockIo_;

    std::unique_ptr<Rw2Image> rw2Image_;

};



TEST_F(Rw2ImageTest, OpenInvalidData) {

    std::vector<byte> invalidData = {0x01, 0x02, 0x03}; // Not a valid RW2 file

    mockIo_->setData(invalidData);



    EXPECT_THROW(rw2Image_->readMetadata(), Error);

}



TEST_F(Rw2ImageTest, OpenValidRw2Data) {

    std::vector<byte> rw2Data = { /* Add valid RW2 data here */ };

    mockIo_->setData(rw2Data);



    EXPECT_NO_THROW(rw2Image_->readMetadata());

}



TEST_F(Rw2ImageTest, GetPreviewProperties) {

    std::vector<byte> rw2DataWithPreview = { /* Add valid RW2 data with preview here */ };

    mockIo_->setData(rw2DataWithPreview);

    rw2Image_->readMetadata();



    PreviewManager previewManager(*rw2Image_);

    PreviewPropertiesList properties = previewManager.getPreviewProperties();



    EXPECT_FALSE(properties.empty());

}



TEST_F(Rw2ImageTest, GetNonExistentPreview) {

    std::vector<byte> rw2DataWithoutPreview = { /* Add valid RW2 data without preview here */ };

    mockIo_->setData(rw2DataWithoutPreview);

    rw2Image_->readMetadata();



    PreviewManager previewManager(*rw2Image_);

    PreviewPropertiesList properties = previewManager.getPreviewProperties();



    EXPECT_TRUE(properties.empty());

}



TEST_F(Rw2ImageTest, GetPreviewImageData) {

    std::vector<byte> rw2DataWithPreview = { /* Add valid RW2 data with preview here */ };

    mockIo_->setData(rw2DataWithPreview);

    rw2Image_->readMetadata();



    PreviewManager previewManager(*rw2Image_);

    PreviewPropertiesList properties = previewManager.getPreviewProperties();

    if (!properties.empty()) {

        PreviewImage previewImage = previewManager.getPreviewImage(properties.front());

        EXPECT_NE(previewImage.size(), 0u);

    }

}



} // namespace Exiv2
