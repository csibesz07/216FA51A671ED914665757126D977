#pragma once
/*
*-----------------------+2--------------------------*
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
*--------------------+1-----------------------------*
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
        GLboolean UBlendingFunctionValues( GLdouble u_knot , RowMatrix<GLdouble>& blending_values) const ;
        GLboolean VBlendingFunctionValues( GLdouble v_knot , RowMatrix<GLdouble>& blending_values) const ;
        GLboolean CalculatePartialDerivatives( GLdouble u , GLdouble v , PartialDerivatives& pd ) const;
    };
}
