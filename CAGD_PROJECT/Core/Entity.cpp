#include "BicubicBezierPatches.h"
#include "../Core/Exceptions.h"
#include "Entity.h"

using namespace cagd;

Entity::Entity(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max)
{
    BicubicBezierPatch *newPatch=new BicubicBezierPatch();

    patch=newPatch;

    GLdouble step_u = (u_max - u_min) / 3;
    GLdouble step_v = (v_max - v_min) / 3;

    for (GLuint i = 0; i < 4; ++i)
    {
        GLdouble u = u_min + i * step_u;

        for (GLuint j = 0; j < 4; ++j)
        {
            GLdouble v = v_min + j * step_v;

            DCoordinate3 &ref = (*patch)(i,j);

            ref[0] = u;
            ref[1] = v;
            ref[2] = (v+u)/2;
        }
    }

    try
    {
        if (!patch->UpdateVertexBufferObjectsOfData())
            throw Exception("Could not update the VBO of the control net!");
        mesh = patch->GenerateImage(50, 50);
        if (!mesh)
        {
            throw "Mesh error";
        }
        if (!mesh->UpdateVertexBufferObjects())
        {
            throw "VBO error";
        }
    }
    catch (Exception &e)
    {
        std::cout << e << std::endl;
    }
}

Entity& Entity::operator [](unsigned int i)
{
    return (*_neighbours.at(i));
}
