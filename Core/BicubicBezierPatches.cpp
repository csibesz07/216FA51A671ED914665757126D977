#include "BicubicBezierPatches.h"

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

    // b l e n d i n g f u n c t i o n v a l u e s and t h e i r d e r i v a t i v e s i n u??d i r e c t i o n
    RowMatrix<GLdouble> u_blending_values(4), d1_u_blending_values(4);
    GLdouble u2 = u*u , u3 = u2*u , wu = 1.0 - u , wu2 = wu*wu , wu3 = wu2*wu ;

    u_blending_values(0) = wu3 ;
    u_blending_values(1) = 3.0*wu2*u ;
    u_blending_values(2) = 3.0*wu*u2 ;
    u_blending_values(3) = u3 ;

    d1_u_blending_values(0) = -3.0*wu2 ;
    d1_u_blending_values(1)= -6.0*wu * u + 3.0* wu2 ;
    d1_u_blending_values(2) = -3.0 *u2 + 6.0 * wu * u ;
    d1_u_blending_values(3) = 3.0 * u2 ;

    // b l e n d i n g f u n c t i o n v a l u e s and t h e i r d e r i v a t i v e s i n v??d i r e c t i o n
    RowMatrix<GLdouble> v_blending_values(4), d1_v_blending_values(4);
    GLdouble v2 = v * v , v3 = v2 *v , wv = 1.0- v , wv2 = wv* wv , wv3 = wv2 *wv ;
    //homework
    v_blending_values(0)= wv3;
    v_blending_values(1)= 3.0*wv2*v ;
    v_blending_values(2)= 3.0*wv*v2 ;
    v_blending_values(3)= v3 ;

    d1_v_blending_values(0) = -3.0*wv2 ;
    d1_v_blending_values(1) = -6.0*wv * v + 3.0* wv2 ;
    d1_v_blending_values(2) = -3.0 *v2 + 6.0 * wv * v ;
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

//void CompositeBezierSurface::InsertNewPatch(const Matrix<DCoordinate3>& control_net)
//{

//}

void CompositeBezierSurface::InsertNewPatch(const Entity entity)
{
    _entities.insert(_entities.end(),entity);
    //    _entities.push_back(entity);
}

GLboolean CompositeBezierSurface::JoinExistingTwoPatches(GLuint patch_1, GLuint boundary_1, GLuint patch_2, GLuint boundary_2)
{
    Entity &_ent1 = _entities[0];
    Entity &_ent2 = _entities[1];

    GLdouble x1,y1,z1, x2, y2, z2;

//    if(boundary_1 == 1 && boundary_2 == 3)
    {
        for (GLuint i = 0 ; i < 4 ; ++i)
        {
            _ent1.patch->GetData(1,i,x1,y1,z1);
            _ent2.patch->GetData(2,i,x2,y2,z2);
            _ent2.patch->SetData(3,i,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
            _ent1.patch->SetData(0,i,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);

//            std::cout << "x1: " << x2 << " y1: " << y2 << "\n" ;
//            _entities.at(patch_1) = _ent1;
//            _entities.at(patch_2) = _ent2;
            //            _ent1.patch->GetData(2,i,x2,y2,z2);
            //            _ent2.patch->SetData(0,i,x1,y1,z1);
            //            _ent2.patch->SetData(1,i,(2*x1-x2),(2*y1-y2),(2*z1-z2));

            //            _ent2.patch->GetData(i,3,k,l,m);
            //            _ent1.patch->SetData(i,0,k,l,m);
            //            _ent2.patch->SetData(i,1,2 * (_ent1.patch(i,3)) - (_ent1.patch(i,2)));
            _ent1.mesh = _ent1.patch->GenerateImage(50,50);
            _ent2.mesh = _ent2.patch->GenerateImage(50,50);
            _ent1.patch->UpdateVertexBufferObjectsOfData();
            _ent2.patch->UpdateVertexBufferObjectsOfData();
            _ent1.mesh->UpdateVertexBufferObjects();
            _ent2.mesh->UpdateVertexBufferObjects();
//            _ent2.patch->UpdateVertexBufferObjectsOfData();
//            _ent2.mesh = _ent2.patch->GenerateImage(50, 50);
//            _ent2.mesh->UpdateVertexBufferObjects();

        }
    }
//    else if(boundary_1 == 0 && boundary_2 == 2)
//    {

//        for (GLuint i = 0 ; i < 4 ; ++i)
//        {
//            _ent2.patch->_data(i,0) = _ent1.patch->_data(i,3);
//            _ent2.patch->_data(i,1) = (2 * _ent1.patch->_data(i,3)) - _ent1.patch->_data(i,2);
//            _ent2.patch->UpdateVertexBufferObjectsOfData();
//            //            _ent1.patch->SetData(3,i,_ent2.patch(0,i));

//        }
//    }
//    else if(boundary_1 == 2 && boundary_2 == 0)
//    {
//        for (GLuint i = 0 ; i < 4 ; ++i)
//        {
//            _ent2.patch->_data(i,0) = _ent1.patch->_data(i,3);
//            _ent2.patch->_data(i,1) = (2 * _ent1.patch->_data(i,3)) - _ent1.patch->_data(i,2);
//            _ent2.patch->UpdateVertexBufferObjectsOfData();

//            //            _ent1.patch->SetData(0,i,_ent2.patch(3,i));

//        }
//    }
//    else if(boundary_1 == 3 && boundary_2 == 1)
//    {
//        for (GLuint i = 0 ; i < 4 ; ++i)
//        {
//            _ent2.patch->_data(3,i) = _ent1.patch->_data(0,i);
//            _ent2.patch->_data(2,i) = (2 * _ent1.patch->_data(0,i)) - _ent1.patch->_data(1,i);
//            _ent2.patch->UpdateVertexBufferObjectsOfData();

//            //            _ent1.patch->SetData(i,0,_ent2.patch(i,3));
//            //            _ent2.patch->SetData(i,2,2 * (_ent1.patch(i,0)) - (_ent1.patch(i,1)));
//        }
//    }

}

GLboolean CompositeBezierSurface::ContinuePatch(GLuint patch, GLuint boundary, const Matrix<DCoordinate3> &control_net_fragment)
{

}

//DCoordinate3 Entity::getItem(GLuint i, GLuint j)
//{
//    return patch(i,j);
//}

//void CompositeBezierSurface::TranslatePatch(const DCoordinate3 &direction, GLuint indexPatch)
//{
//    Entity _e;
//    _e = _entities.at(indexPatch);
//    DCoordinate3 coord;
//    for (GLuint i = 0; i < 4; ++i)
//    {

//        for (GLuint j = 0; j < 4; ++j)
//        {
//            //            coord = _e.patch(i,j);
//            coord+=direction;

//        }
//    }

//}
Entity& CompositeBezierSurface::operator [](unsigned int i)
{
    return _entities.at(i);
}

CompositeBezierSurface::CompositeBezierSurface(unsigned int i)
{
    _entities.resize(i);
}
