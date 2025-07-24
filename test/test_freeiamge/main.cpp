#include <FreeImage.h>
#include <iostream>
#include <string>

// 打印 FreeImage 版本信息
void PrintFreeImageVersion() {
    std::cout << "FreeImage Version: " << FreeImage_GetVersion() << std::endl;
    std::cout << "FreeImage License: " << FreeImage_GetCopyrightMessage() << std::endl;
}

// 加载图像文件
FIBITMAP* LoadImage(const std::string& filepath) {
    // 获取文件格式（自动检测）
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filepath.c_str(), 0);
    if (format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(filepath.c_str());
    }
    if (format == FIF_UNKNOWN) {
        std::cerr << "Error: Unknown images format!" << std::endl;
        return nullptr;
    }

    // 加载图像
    FIBITMAP* image = FreeImage_Load(format, filepath.c_str(), 0);
    if (!image) {
        std::cerr << "Error: Failed to load images!" << std::endl;
        return nullptr;
    }

    return image;
}

// 保存图像文件
bool SaveImage(FIBITMAP* image, const std::string& filepath) {
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(filepath.c_str());
    if (format == FIF_UNKNOWN) {
        std::cerr << "Error: Unsupported output format!" << std::endl;
        return false;
    }

    // 保存为 24 位 RGB 图像（自动转换）
    FIBITMAP* saveImage = FreeImage_ConvertTo24Bits(image);
    if (!saveImage) {
        std::cerr << "Error: Failed to convert images to 24-bit!" << std::endl;
        return false;
    }

    bool success = FreeImage_Save(format, saveImage, filepath.c_str(), 0);
    FreeImage_Unload(saveImage);

    if (!success) {
        std::cerr << "Error: Failed to save images!" << std::endl;
        return false;
    }

    return true;
}

int main() {
    // 初始化 FreeImage 库
    FreeImage_Initialise();

    // 打印版本信息
    PrintFreeImageVersion();

    // 输入/输出文件路径
    const std::string inputFile = "input.jpg";  // 替换为你的输入文件
    const std::string outputFile = "output.png"; // 输出文件

    // 1. 加载图像
    FIBITMAP* image = LoadImage(inputFile);
    if (!image) {
        FreeImage_DeInitialise();
        std::cout<<"Load Failed!"<<std::endl;
        return 1;
    }

    // 2. 获取图像信息
    int width = FreeImage_GetWidth(image);
    int height = FreeImage_GetHeight(image);
    int bpp = FreeImage_GetBPP(image);
    std::cout << "Image Info: " << width << "x" << height << ", " << bpp << " bpp" << std::endl;

    // 3. 简单处理（示例：旋转 90 度）
    FIBITMAP* processedImage = FreeImage_Rotate(image, 90.0, nullptr);
    FreeImage_Unload(image); // 释放原始图像

    if (!processedImage) {
        std::cerr << "Error: Failed to rotate images!" << std::endl;
        FreeImage_DeInitialise();
        return 1;
    }

    // 4. 保存处理后的图像
    if (!SaveImage(processedImage, outputFile)) {
        FreeImage_Unload(processedImage);
        FreeImage_DeInitialise();
        return 1;
    }

    std::cout << "Image saved to: " << outputFile << std::endl;

    // 释放资源
    FreeImage_Unload(processedImage);
    FreeImage_DeInitialise();

    return 0;
}