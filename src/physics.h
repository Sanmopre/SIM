#ifndef PHYSICS_H
#define PHYSICS_H

#include "module.h"
#include <glm/glm.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <vector>

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
