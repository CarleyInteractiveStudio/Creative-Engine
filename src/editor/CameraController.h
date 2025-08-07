#pragma once

#include <SDL3/SDL_events.h>

class Camera;

class CameraController {
public:
    CameraController(Camera* camera);
    ~CameraController();

    void on_event(SDL_Event& event);
    void update(float dt);

private:
    Camera* m_camera;
    float m_speed = 5.0f;
    float m_sensitivity = 0.1f;
    bool m_w_pressed = false;
    bool m_a_pressed = false;
    bool m_s_pressed = false;
    bool m_d_pressed = false;
};
