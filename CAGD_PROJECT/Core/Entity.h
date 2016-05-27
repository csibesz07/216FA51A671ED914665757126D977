#ifndef ENTITY_H
#define ENTITY_H

#include "TensorProductSurfaces3.h"
#include "Materials.h"
#include "TriangulatedMeshes3.h"
#include "ShaderPrograms.h"
#include "TriangularFaces.h"
#include "BicubicBezierPatches.h"
#include <map>

namespace cagd
{
    class Entity{
    public:
        BicubicBezierPatch *patch;
        Material           material;
        TriangulatedMesh3   *mesh;
        ShaderProgram      shader;
        const static int SIDE_TOP=2;
        const static int SIDE_RIGHT_TOP=123;
        const static int SIDE_RIGHT=-2;
        const static int SIDE_RIGHT_BOTTOM=231;
        const static int SIDE_BOTTOM=1;
        const static int SIDE_LEFT_BOTTOM=214;
        const static int SIDE_LEFT=-1;
        const static int SIDE_LEFT_TOP=124;
        const static int UPDATE=1;
        const static int NOT_UPDATE=0;


        std::map< int , int > real2Internal;
        std::map< int , int > internal2Real;

    protected:
        std::map< int , Entity* > _neighbours;
    public:
        Entity();
        Entity(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max);
        Entity(const Entity &entity);
        DCoordinate3 getItem(GLuint i, GLuint j);
        Entity& operator [](unsigned int i);
        std::vector<Entity>& getNeighbours();
        Entity getNeighbours(GLuint i);
        GLint whichNeighbour(Entity &e);
        GLboolean JoinExistingTwoPatches(Entity &_ent2 ,GLint boundary_1,GLint boundary_2,int flag=NOT_UPDATE);
        GLboolean updateNeighbours(Entity &kivalto);
    };
}

#endif // ENTITY_H
