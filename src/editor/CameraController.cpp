#include "CameraController.h"
#include "../renderer/Camera.h"
#include "../core/Vector3.h"

CameraController::CameraController(Camera* camera)
    : m_camera(camera)
{
}

CameraController::~CameraController()
{
}

void CameraController::on_event(SDL_Event& event)
{
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.keysym.sym == SDLK_w) m_w_pressed = true;
        if (event.key.keysym.sym == SDLK_a) m_a_pressed = true;
        if (event.key.keysym.sym == SDLK_s) m_s_pressed = true;
        if (event.key.keysym.sym == SDLK_d) m_d_pressed = true;
    }
    if (event.type == SDL_EVENT_KEY_UP) {
        if (event.key.keysym.sym == SDLK_w) m_w_pressed = false;
        if (event.key.keysym.sym == SDLK_a) m_a_pressed = false;
        if (event.key.keysym.sym == SDLK_s) m_s_pressed = false;
        if (event.key.keysym.sym == SDLK_d) m_d_pressed = false;
    }
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        if (event.motion.state & SDL_BUTTON_RMASK) {
            // This is a simplified implementation. A real implementation would
            // use the mouse delta to rotate the camera.
        }
    }
}

void CameraController::update(float dt)
{
    Vector3 forward = m_camera->get_forward();
    Vector3 right = m_camera->get_right();

    if (m_w_pressed) {
        m_camera->set_position(m_camera->get_position() + forward * m_speed * dt);
    }
    if (m_s_pressed) {
        m_camera->set_position(m_camera->get_position() - forward * m_speed * dt);
    }
    if (m_a_pressed) {
        m_camera->set_position(m_camera->get_position() - right * m_speed * dt);
    }
    if (m_d_pressed) {
        m_camera->set_position(m_camera->get_position() + right * m_speed * dt);
    }
}
