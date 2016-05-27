#include "BicubicBezierPatches.h"
#include "../Core/Exceptions.h"

#define TOP_SIDE 1
#define BOTTOM_SIDE 2
#define LEFT_SIDE -1
#define RIGHT_SIDE -2

using namespace cagd;


BicubicBezierPatch::BicubicBezierPatch(): TensorProductSurface3(0.0 , 1.0 , 0.0 , 1.0 , 4 , 4)
{
}

GLboolean BicubicBezierPatch::UBlendingFunctionValues(GLdouble u_knot , RowMatrix<GLdouble>& blending_values ) const
{
    if ( u_knot < 0.0 || u_knot > 1.0 )
        return GL_FALSE ;

    blending_values.ResizeColumns(4);

    GLdouble u = u_knot , u2 = u * u , u3 = u2 * u , w = 1.0 - u , w2 = w * w, w3 = w2 * w;

    blending_values( 0 ) = w3 ;
    blending_values( 1 ) = 3.0*w2*u ;
    blending_values( 2 ) = 3.0*w*u2 ;
    blending_values( 3 ) = u3 ;

    return GL_TRUE ;
}

GLboolean BicubicBezierPatch::VBlendingFunctionValues(GLdouble v_knot, RowMatrix<GLdouble> &blending_values) const
{
    //homework
    if ( v_knot < 0.0 || v_knot > 1.0 )
        return GL_FALSE ;

    blending_values.ResizeColumns(4);

    GLdouble v = v_knot , v2 = v * v , v3 = v2 * v , w = 1.0 - v , w2 = w * w, w3 = w2 * w;

    blending_values( 0 ) = w3 ;
    blending_values( 1 ) = 3.0*w2*v ;
    blending_values( 2 ) = 3.0*w*v2 ;
    blending_values( 3 ) = v3 ;

    return GL_TRUE ;
}

GLboolean BicubicBezierPatch::CalculatePartialDerivatives(GLdouble u, GLdouble v, PartialDerivatives &pd) const
{
    if ( u < 0.0 || u > 1.0 || v < 0.0 ||  v > 1.0 )
        return GL_FALSE;

    RowMatrix<GLdouble> u_blending_values(4), d1_u_blending_values(4);
    GLdouble u2 = u*u , u3 = u2*u , iu = 1.0 - u , iu2 = iu*iu , iu3 = iu2*iu ;

    u_blending_values(0) = iu3 ;
    u_blending_values(1) = 3.0*iu2*u ;
    u_blending_values(2) = 3.0*iu*u2 ;
    u_blending_values(3) = u3 ;

    d1_u_blending_values(0) = -3.0*iu2 ;
    d1_u_blending_values(1)= -6.0*iu * u + 3.0* iu2 ;
    d1_u_blending_values(2) = -3.0 *u2 + 6.0 * iu * u ;
    d1_u_blending_values(3) = 3.0 * u2 ;

    RowMatrix<GLdouble> v_blending_values(4), d1_v_blending_values(4);
    GLdouble v2 = v * v , v3 = v2 *v , iv = 1.0- v , iv2 = iv* iv , iv3 = iv2 *iv ;

    v_blending_values(0)= iv3;
    v_blending_values(1)= 3.0*iv2*v ;
    v_blending_values(2)= 3.0*iv*v2 ;
    v_blending_values(3)= v3 ;

    d1_v_blending_values(0) = -3.0*iv2 ;
    d1_v_blending_values(1) = -6.0*iv * v + 3.0* iv2 ;
    d1_v_blending_values(2) = -3.0 *v2 + 6.0 * iv * v ;
    d1_v_blending_values(3) = 3.0 * v2 ;

    pd.LoadNullVectors();
    for ( GLuint row = 0 ; row < 4 ; ++row )
    {
        DCoordinate3 aux_d0_v , aux_d1_v ;
        for ( GLuint column = 0 ; column < 4 ; ++column )
        {
            aux_d0_v += _data(row , column ) * v_blending_values(column);
            aux_d1_v += _data(row , column ) * d1_v_blending_values(column);
        }
        pd.point += aux_d0_v * u_blending_values(row);
        pd.diff1u += aux_d0_v * d1_u_blending_values(row);
        pd.diff1v += aux_d1_v * u_blending_values(row);
    }

    return GL_TRUE;

}
