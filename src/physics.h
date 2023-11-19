#ifndef PHYSICS_H
#define PHYSICS_H

#include "module.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <vector>

// constants
constexpr float EPSILON = 1e-8f;
constexpr float EARTH_GRAVITY = 9.80665f;
constexpr float PI_VALUE = 3.141592653589793f;

// directions in body space
constexpr glm::vec3 X_AXIS = {1.0f, 0.0f, 0.0f};
constexpr glm::vec3 Y_AXIS = {0.0f, 1.0f, 0.0f};
constexpr glm::vec3 Z_AXIS = {0.0f, 0.0f, 1.0f};

constexpr glm::vec3 FORWARD = +X_AXIS;
constexpr glm::vec3 UP = +Y_AXIS;
constexpr glm::vec3 RIGHT = +Z_AXIS;
constexpr glm::vec3 BACKWARD = -X_AXIS;
constexpr glm::vec3 DOWN = -Y_AXIS;
constexpr glm::vec3 LEFT = -Z_AXIS;

class RigidBody {
    private:
        glm::vec3 m_force{}; // world space
        glm::vec3 m_torque{}; // body space

    public:
        float mass = 1.0f;                                  // kg
        glm::vec3 position{};                               // world space
        glm::quat orientation{};                            // world space
        glm::vec3 velocity{};                               // world space, meter/second
        glm::vec3 angular_velocity{};                       // body space, radians/second
        glm::mat3 inertia{}, inverse_inertia{};             // inertia tensor, body space
        bool apply_gravity = true;

        // transform direction from body space to world space
        inline glm::vec3 transform_direction(const glm::vec3& direction) const
        { return orientation * direction; }

        // transform direction from world space to body space
        inline glm::vec3 inverse_transform_direction(const glm::vec3& direction) const
        { return glm::inverse(orientation) * direction;}

        // get velocity and angular velocity in body space
        inline glm::vec3 get_point_velocity(const glm::vec3& point) const
        { return inverse_transform_direction(velocity) + glm::cross(angular_velocity, point); }

        // force and point vectors are in body space
        inline void add_force_at_point(const glm::vec3& force, const glm::vec3& point)
        { m_force += transform_direction(force), m_torque += glm::cross(point, force); }

        // force vector in body space
        inline void add_relative_force(const glm::vec3& force)
        { m_force += transform_direction(force); }

        // integrate using the euler method
        virtual void update(float dt)
        {
            // integrate position
            glm::vec3 acceleration = m_force / mass;
            if (apply_gravity) acceleration.y -= 9.81f;
            velocity += acceleration * dt;
            position += velocity * dt;
            
            // integrate orientation
            angular_velocity += inverse_inertia *
                (m_torque - glm::cross(angular_velocity, inertia * angular_velocity)) * dt;
            orientation += (orientation * glm::quat(0.0f, angular_velocity)) * (0.5f * dt);
            orientation = glm::normalize(orientation);

            // reset accumulators
            m_force = glm::vec3(0.0f), m_torque = glm::vec3(0.0f);
        }
};


class Physics : public Module {
public:

    Physics(std::string name);
    virtual ~Physics();

    virtual bool LoadConfig(std::string config_file) override;
    virtual bool Start() override;
    virtual bool Update(double delta_time) override;
    virtual void Cleanup() override;
    
private:


};

#endif // PHYSICS_H
