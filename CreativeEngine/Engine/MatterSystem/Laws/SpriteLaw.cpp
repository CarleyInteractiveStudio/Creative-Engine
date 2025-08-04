#include "SpriteLaw.h"

namespace Creative {

// The constructor for SpriteLaw takes a file path to the sprite image.
// It uses a member initializer list to call the Image constructor that
// takes a file path, which in turn handles the loading of the image data.
SpriteLaw::SpriteLaw(const std::string& spritePath)
    : spriteImage(spritePath)
{
    // The spriteImage member is now constructed and, if the path was valid,
    // contains the pixel data. There's nothing more to do in the constructor body for now.
}

} // namespace Creative
