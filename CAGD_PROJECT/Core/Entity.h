#ifndef ENTITY_H
#define ENTITY_H

#include "TensorProductSurfaces3.h"
#include "Materials.h"
#include "TriangulatedMeshes3.h"
#include "ShaderPrograms.h"
#include "TriangularFaces.h"
#include "BicubicBezierPatches.h"

namespace cagd
{
    class Entity{
    public:
        BicubicBezierPatch *patch;
        Material           material;
        TriangulatedMesh3   *mesh;
        ShaderProgram      shader;
    protected:
        std::vector<Entity*> _neighbours;
    public:
        Entity(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max);
        Entity(const Entity &entity);
        DCoordinate3 getItem(GLuint i, GLuint j);
        Entity& operator [](unsigned int i);
        std::vector<Entity>& getNeighbours();
        Entity getNeighbours(GLuint i);
    };
}

#endif // ENTITY_H
