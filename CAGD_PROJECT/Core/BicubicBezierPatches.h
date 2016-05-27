#pragma once
/*
*-----------------------+1--------------------------*
|                 central widget                    |
|                                                   |
|  *---------------------------*-----------------*  |
|  |     rendering context     |   scroll area   |  |
|  |       OpenGL widget       | *-------------* |  |
-1 |                           | | side widget | |  -2
|  |                           | |             | |  |
|  |                           | |             | |  |
|  |                           | *-------------* |  |
|  *---------------------------*-----------------*  |
|                                                   |
*--------------------+2------------------------------*
*/

#include "TensorProductSurfaces3.h"
#include "Materials.h"
#include "TriangulatedMeshes3.h"
#include "ShaderPrograms.h"
#include "TriangularFaces.h"

namespace cagd
{
    class BicubicBezierPatch: public TensorProductSurface3
    {
    public:
        BicubicBezierPatch();
        // we have to implement pure virtual methods introduced in class TensorProductSurface3
        GLboolean UBlendingFunctionValues( GLdouble u_knot , RowMatrix<GLdouble>& blending_values) const ;
        GLboolean VBlendingFunctionValues( GLdouble v_knot , RowMatrix<GLdouble>& blending_values) const ;
        GLboolean CalculatePartialDerivatives( GLdouble u , GLdouble v , PartialDerivatives& pd ) const;
//        GLboolean Render(GLenum render_mode = GL_TRIANGLES) const;      //uj metodusok nem kellenek
    };

    struct Entity{
    public:
        BicubicBezierPatch *patch;
        Material           material;
        TriangulatedMesh3   *mesh;
        ShaderProgram      shader;
    protected:
        std::vector<BicubicBezierPatch*> _neighbours;
    public:
        DCoordinate3 getItem(GLuint i, GLuint j);
    };


    class CompositeBezierSurface
    {
    public:

        std::vector<Entity> _entities;    //ezen kell vegig menni, es kirajzolni  PATCHEKET

    public:
        Entity& operator [](unsigned int i);
        CompositeBezierSurface();
        void InsertNewPatch(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max);
        void InsertNewPatch(const Entity entity);
        //itt osszekotjuk , amit lerajzolt a lapon
        GLboolean JoinExistingTwoPatches(GLuint patch_1, GLuint boundary_1, GLuint patch_2, GLuint boundary_2);
      //  GLboolean JoinExistingTwoPatches(Entity &ent2 ,GLint boundary_1,GLint boundary_2);
        //ezt nem tudom...?
        GLboolean ContinuePatch(GLuint patch, GLuint boundary, const Matrix<DCoordinate3> &control_net_fragment);
        void TranslatePatch(const DCoordinate3 &direction, GLuint indexPatch);     //ennyivel toljuk el a kozepen megjelenitett patchet
        void Render() const;        //megjelenit
        std::vector<Entity>& getEntities();
        Entity getEntity(GLuint i);
    };
}
