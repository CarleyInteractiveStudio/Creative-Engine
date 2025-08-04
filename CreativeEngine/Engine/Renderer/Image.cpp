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
