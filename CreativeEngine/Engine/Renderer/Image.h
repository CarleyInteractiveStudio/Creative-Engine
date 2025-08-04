#pragma once

#include <vector>
#include <string>

namespace Creative {

// A simple struct to represent an RGB color.
struct Color
{
    unsigned char r = 0, g = 0, b = 0;
};

// The Image class represents our framebuffer, a 2D grid of pixels.
// It provides a way to set pixel colors and save the result to a file.
class Image
{
public:
    // Creates a blank image with the given dimensions.
    Image(unsigned int width, unsigned int height);
    // Loads an image from a file.
    Image(const std::string& filepath);

    // Sets the color of a single pixel at the given coordinates.
    // (0,0) is the top-left corner.
    void SetPixel(unsigned int x, unsigned int y, const Color& color);

    // Fills the entire image with a single color.
    void Clear(const Color& color);

    // Saves the image to a file in the PPM (P3) format.
    // PPM is a very simple, uncompressed, human-readable image format.
    // Returns true on success, false on failure.
    bool Save(const std::string& filepath) const;

    unsigned int GetWidth() const { return m_Width; }
    unsigned int GetHeight() const { return m_Height; }
    const Color* GetData() const { return m_PixelData.data(); }

private:
    unsigned int m_Width;
    unsigned int m_Height;
    std::vector<Color> m_PixelData;
};

} // namespace Creative
