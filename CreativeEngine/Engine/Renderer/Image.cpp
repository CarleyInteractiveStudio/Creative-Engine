#include "Image.h"
#include "Engine/Core/Log.h"
#include <fstream>
#include <algorithm>

namespace Creative {

Image::Image(unsigned int width, unsigned int height)
    : m_Width(width)
    , m_Height(height)
{
    // Allocate the pixel buffer and initialize it to black.
    m_PixelData.resize(width * height, {0, 0, 0});
    Log::Core_Trace("Created an Image with dimensions " + std::to_string(width) + "x" + std::to_string(height));
}

Image::Image(const std::string& filepath)
    : m_Width(0)
    , m_Height(0)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        Log::Core_Error("Failed to open image file: " + filepath);
        return;
    }

    std::string magic;
    file >> magic;
    if (magic != "P3")
    {
        Log::Core_Error("Invalid PPM file format. Only P3 (ASCII) is supported. File: " + filepath);
        return;
    }

    int maxColorValue;
    file >> m_Width >> m_Height >> maxColorValue;

    if (m_Width == 0 || m_Height == 0)
    {
        Log::Core_Error("Image has zero dimensions: " + filepath);
        m_Width = 0;
        m_Height = 0;
        return;
    }

    m_PixelData.resize(m_Width * m_Height);

    int r, g, b;
    for (unsigned int i = 0; i < m_Width * m_Height; ++i)
    {
        if (file >> r >> g >> b)
        {
            m_PixelData[i].r = static_cast<unsigned char>(r);
            m_PixelData[i].g = static_cast<unsigned char>(g);
            m_PixelData[i].b = static_cast<unsigned char>(b);
        }
        else
        {
            Log::Core_Error("Failed to read pixel data from: " + filepath + ". File may be truncated.");
            m_Width = 0;
            m_Height = 0;
            m_PixelData.clear();
            break;
        }
    }

    file.close();
    if (m_Width > 0) {
        Log::Core_Info("Successfully loaded image: " + filepath + " (" + std::to_string(m_Width) + "x" + std::to_string(m_Height) + ")");
    }
}

void Image::SetPixel(unsigned int x, unsigned int y, const Color& color)
{
    // Basic bounds checking to prevent writing outside the buffer.
    if (x >= m_Width || y >= m_Height)
    {
        return;
    }
    // The pixel buffer is a 1D array, so we convert 2D coordinates to a 1D index.
    m_PixelData[y * m_Width + x] = color;
}

void Image::Clear(const Color& color)
{
    // Use std::fill to efficiently set all pixels to the same color.
    std::fill(m_PixelData.begin(), m_PixelData.end(), color);
}

bool Image::Save(const std::string& filepath) const
{
    std::ofstream file(filepath);
    if (!file.is_open())
    {
        Log::Core_Error("Failed to open file for writing: " + filepath);
        return false;
    }

    // --- PPM P3 Header ---
    // P3: Indicates this is an ASCII (human-readable) RGB PPM file.
    // Width Height: The dimensions of the image.
    // 255: The maximum value for each color component.
    file << "P3\n";
    file << m_Width << " " << m_Height << "\n";
    file << "255\n";

    // --- Pixel Data ---
    // Write out each pixel's RGB values, separated by spaces.
    for (const auto& pixel : m_PixelData)
    {
        file << static_cast<int>(pixel.r) << " "
             << static_cast<int>(pixel.g) << " "
             << static_cast<int>(pixel.b) << "\n";
    }

    file.close();
    Log::Core_Info("Image successfully saved to " + filepath);
    return true;
}

} // namespace Creative
