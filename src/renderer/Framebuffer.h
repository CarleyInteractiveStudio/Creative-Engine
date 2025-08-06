#pragma once

#include <cstdint>

class Framebuffer {
public:
    Framebuffer(uint32_t width, uint32_t height);
    ~Framebuffer();

    void Invalidate();
    void Bind() const;
    void Unbind() const;

    void Resize(uint32_t width, uint32_t height);

    uint32_t GetColorAttachmentRendererID() const { return m_color_attachment; }

private:
    uint32_t m_renderer_id = 0;
    uint32_t m_color_attachment = 0;
    uint32_t m_depth_attachment = 0;
    uint32_t m_width = 0;
    uint32_t m_height = 0;
};
