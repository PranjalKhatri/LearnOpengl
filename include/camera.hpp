#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pop::gfx {

class Camera {
   public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);
    glm::mat4 GetViewMatrix() const;

   protected:
    glm::vec3 position_;
    glm::vec3 back_;   // camera +Z (backward)
    glm::vec3 up_;     // camera +Y
    glm::vec3 right_;  // camera +X
};

class FlyCam : public Camera {
   public:
    using Camera::Camera;

    float movement_speed_ = 5.0f;
    float yaw_            = -90.0f;  // degrees
    float pitch_          = 0.0f;

    enum class CameraMovement { Forward, Backward, Right, Left };

    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset,
                              bool constrainPitch = true);

   private:
    void updateCameraVectors();
};

}  // namespace pop::gfx
