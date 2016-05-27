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

void CompositeBezierSurface::InsertNewPatch(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max)
{
    Entity *newEntity=new Entity();
    BicubicBezierPatch *newPatch=new BicubicBezierPatch();

    (*newEntity).patch=newPatch;

    GLdouble step_u = (u_max - u_min) / 3;
    GLdouble step_v = (v_max - v_min) / 3;

    for (GLuint i = 0; i < 4; ++i)
    {
        GLdouble u = u_min + i * step_u;

        for (GLuint j = 0; j < 4; ++j)
        {
            GLdouble v = v_min + j * step_v;

            DCoordinate3 &ref = (*newPatch)(i,j);

            ref[0] = u;
            ref[1] = v;
            ref[2] = (v+u)/2;
        }
    }

    try
    {
        if (!newPatch->UpdateVertexBufferObjectsOfData())
            throw Exception("Could not update the VBO of the control net!");
        (*newEntity).mesh = newPatch->GenerateImage(50, 50);
        if (!(*newEntity).mesh)
        {
            throw "Mesh error";
        }
        if (!(*newEntity).mesh->UpdateVertexBufferObjects())
        {
            throw "VBO error";
        }
        _entities.push_back(*newEntity);
    }
    catch (Exception &e)
    {
        std::cout << e << std::endl;
    }
}

void CompositeBezierSurface::InsertNewPatch(const Entity entity)
{
    _entities.insert(_entities.end(),entity);
}

/*
#define TOP_SIDE 1
#define BOTTOM_SIDE 2
#define LEFT_SIDE -1
#define RIGHT_SIDE -2*/

GLboolean CompositeBezierSurface::JoinExistingTwoPatches(Entity &_ent2 ,GLint boundary_1,GLint boundary_2)
{
//    Entity &_ent1 = _entities[0];
    Entity &_ent1 =this;

    GLdouble x1,y1,z1, x2, y2, z2;

//    if(boundary_1 == 1 && boundary_2 == 3)
   // {

    if((boundary_1 < 3 ) && (boundary_2 < 3 )){


        for (GLuint i = 0 ; i < 4 ; ++i)
        {

            // + -  sor vagy oszlop az i vel  utanna  abs( melleirni  )
            // mod hozzaadni ha 0 akk  hozzad 1  ha nem akkor -1 .
            if(boundary_1 < 0){             //  ELSO folt i a masodik parameter
                _ent1.patch->GetData(abs(boundary_1),i,x1,y1,z1);
            }else{                          // ELSO folt i az elso parameter
                _ent1.patch->GetData(i,abs(boundary_1) ,x1,y1,z1);
            }
            if(boundary_2 < 0){             // MASODIK folt i a masodik parameter
                _ent2.patch->GetData(abs(boundary_2) ,i,x1,y1,z1);
            }else{                          // MASODIK folti az elso parameter
                _ent2.patch->GetData(i,abs(boundary_2),x1,y1,z1);
            }

            if(boundary_1 < 0){             //  ELSO folt i a masodik parameter
                _ent1.patch->SetData((boundary_1 % 2 == 0) ? abs(boundary_1)+1 : abs(boundary_1)-1,i,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
            }else{                          // ELSO folt i az elso parameter
                _ent1.patch->SetData(i,(boundary_1 % 2 == 0) ? abs(boundary_1)+1 : abs(boundary_1)-1 ,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
            }


            if(boundary_2 < 0){             //  MASODIK folt i a masodik parameter
                _ent1.patch->SetData((boundary_2 % 2 == 0) ? abs(boundary_2)+1 : abs(boundary_2)-1,i,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
            }else{                          // MASOIDK folt i az elso parameter
                _ent1.patch->SetData(i,(boundary_2 % 2 == 0) ? abs(boundary_2)+1 : abs(boundary_2)-1 ,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
            }

            _ent1.mesh = _ent1.patch->GenerateImage(50,50);
            _ent2.mesh = _ent2.patch->GenerateImage(50,50);
            _ent1.patch->UpdateVertexBufferObjectsOfData();
            _ent2.patch->UpdateVertexBufferObjectsOfData();
            _ent1.mesh->UpdateVertexBufferObjects();
            _ent2.mesh->UpdateVertexBufferObjects();
        }

    }
    else{
        if(((boundary_1 > 2 ) && (boundary_2 < 3 )) || ((boundary_1 < 3 ) && (boundary_2 >2))){
            // ha nem megfelelo a bemeno adat
            throw new Exception("Oldalt es atlot nem tudok osszevonni");
        }else {

            //APOR KOD
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

CompositeBezierSurface::CompositeBezierSurface()
{
}
