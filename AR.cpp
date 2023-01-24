#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ARObject {
private:
    glm::vec3 position; // position
    glm::vec3 velocity; // velocity
    float mass; // mass
    float friction; // friction constant

public:
    ARObject(glm::vec3 position, float mass) {
        this->position = position;
        this->mass = mass;
        friction = 0.1f;
    }

    void update(float dt) {
        velocity *= (1.0f - friction); // apply friction
        position += velocity * dt; // update position
    }

    void applyForce(glm::vec3 force) {
        velocity += force / mass; // apply force
    }

    glm::mat4 getModelMatrix(glm::mat4 cameraMatrix) {
        return cameraMatrix * glm::translate(glm::mat4(1.0f), position);
    }
};

int main() {
    glm::mat4 cameraMatrix = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    ARObject obj(glm::vec3(0, 0, 0), 1); // create object at (0, 0, 0) with mass 1

    obj.applyForce(glm::vec3(1, 1, 0)); // apply force to object

    for (float t = 0; t <= 1; t += 0.1f) {
        obj.update(0.1f); // update object's position
        glm::mat4 modelMatrix = obj.getModelMatrix(cameraMatrix);
        std::cout << "Time: " << t << ", Model Matrix: " << glm::to_string(modelMatrix) << std::endl;
    }

    return 0;
}

