#include "Maths.hpp"

#include <glm/gtc/matrix_transform.hpp>

glm::mat4 createTransformationMatrix(const glm::vec3 &translation, const glm::vec3 &rotation, const float scale)
{
    glm::mat4 tmatrix(1);
    tmatrix = glm::scale(tmatrix, glm::vec3(scale, scale, scale));
    tmatrix = glm::translate(tmatrix, translation);

    tmatrix = glm::rotate(tmatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    tmatrix = glm::rotate(tmatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    tmatrix = glm::rotate(tmatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

    return tmatrix;
}

glm::mat4 crateViewMatrix(const Camera &camera)
{
    glm::mat4 viewMatrix(1);
    viewMatrix = glm::translate(viewMatrix, -camera.position);
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-camera.rotation.x), glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-camera.rotation.y), glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, glm::radians(-camera.rotation.z), glm::vec3(0, 0, 1));
    //viewMatrix = glm::scale(viewMatrix, glm::vec3(1,1,1));

    //viewMatrix = glm::lookAt(camera.position, camera.position + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    return viewMatrix;
}
