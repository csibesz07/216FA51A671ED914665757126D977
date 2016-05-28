#include "BicubicBezierPatches.h"
#include "../Core/Exceptions.h"
#include "Entity.h"
#include "cmath"

using namespace cagd;
using namespace std;

const int Entity::SIDE_TOP;
const int Entity::SIDE_RIGHT_TOP;
const int Entity::SIDE_RIGHT;
const int Entity::SIDE_RIGHT_BOTTOM;
const int Entity::SIDE_BOTTOM;
const int Entity::SIDE_LEFT_BOTTOM;
const int Entity::SIDE_LEFT;
const int Entity::SIDE_LEFT_TOP;
const int Entity::UPDATE;
const int Entity::NOT_UPDATE;


Entity::Entity() {
    Entity(0,0,1,1);
}

Entity::Entity(Material m) {
    Entity(0,0,1,1,m);
}

Entity::Entity(GLdouble u_min,GLdouble u_max,GLdouble v_min,GLdouble v_max,Material m)
{
    material.setMaterial(m);

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

    real2Internal[SIDE_LEFT_TOP]=0;
    real2Internal[SIDE_TOP]=1;
    real2Internal[SIDE_RIGHT_TOP]=2;
    real2Internal[SIDE_RIGHT]=3;
    real2Internal[SIDE_RIGHT_BOTTOM]=4;
    real2Internal[SIDE_BOTTOM]=5;
    real2Internal[SIDE_LEFT_BOTTOM]=6;
    real2Internal[SIDE_LEFT]=7;

    internal2Real[0]=SIDE_LEFT_TOP;
    internal2Real[1]=SIDE_TOP;
    internal2Real[2]=SIDE_RIGHT_TOP;
    internal2Real[3]=SIDE_RIGHT;
    internal2Real[4]=SIDE_RIGHT_BOTTOM;
    internal2Real[5]=SIDE_BOTTOM;
    internal2Real[6]=SIDE_LEFT_BOTTOM;
    internal2Real[7]=SIDE_LEFT;
}

GLboolean Entity::JoinExistingTwoPatches( Entity &_ent2 ,GLint boundary_1,GLint boundary_2,int flag)
{
    Entity &_ent1 =*(this);

    GLdouble x1,y1,z1, x2, y2, z2;

    if((boundary_1 < 3 ) && (boundary_2 < 3 )){

        for (GLuint i = 0 ; i < 4 ; ++i)
        {
            GLint j=boundary_1*boundary_2<0?3-i:i;
            if (flag==NOT_UPDATE) {
                //forditott bejaras ha SIDE_LEFT/SIDE_RIGHT-ot akarjuk SIDE_BOTTOM vagy SIDE_TOP osszeilleszteni
                // + -  sor vagy oszlop az i vel  utanna  abs( melleirni  )
                // mod hozzaadni ha 0 akk  hozzad 1  ha nem akkor -1 .
                if(boundary_1 < 0){             //  ELSO folt i a masodik parameter
                    _ent1.patch->GetData(fabs(boundary_1),i,x1,y1,z1);
                }else{                          // ELSO folt i az elso parameter
                    _ent1.patch->GetData(i,fabs(boundary_1) ,x1,y1,z1);
                }
                if(boundary_2 < 0){             // MASODIK folt i a masodik parameter
                    _ent2.patch->GetData(fabs(boundary_2) ,j,x2,y2,z2);
                }else{                          // MASODIK folti az elso parameter
                    _ent2.patch->GetData(j,fabs(boundary_2),x2,y2,z2);
                }

                if(boundary_1 < 0){             //  ELSO folt i a masodik parameter
                    _ent1.patch->SetData((boundary_1 % 2 == 0) ? fabs(boundary_1)+1 : fabs(boundary_1)-1,i,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
                }else{                          // ELSO folt i az elso parameter
                    _ent1.patch->SetData(i,(boundary_1 % 2 == 0) ? fabs(boundary_1)+1 : fabs(boundary_1)-1 ,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
                }


                if(boundary_2 < 0){             //  MASODIK folt i a masodik parameter
                    _ent2.patch->SetData((boundary_2 % 2 == 0) ? fabs(boundary_2)+1 : fabs(boundary_2)-1,j,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
                }else{                          // MASOIDK folt i az elso parameter
                    _ent2.patch->SetData(j,(boundary_2 % 2 == 0) ? fabs(boundary_2)+1 : fabs(boundary_2)-1 ,(x1+x2)/2,(y1+y2)/2,(z1+z2)/2);
                }

                _ent1.mesh = _ent1.patch->GenerateImage(50,50);
                _ent2.mesh = _ent2.patch->GenerateImage(50,50);
                _ent1.patch->UpdateVertexBufferObjectsOfData();
                _ent2.patch->UpdateVertexBufferObjectsOfData();
                _ent1.mesh->UpdateVertexBufferObjects();
                _ent2.mesh->UpdateVertexBufferObjects();
            }
            else {
                if(boundary_2 < 0){             // MASODIK folt i a masodik parameter
                    _ent2.patch->GetData((boundary_2 % 2 == 0) ? fabs(boundary_2)+1 : fabs(boundary_2)-1 ,j,x2,y2,z2);
                }else{                          // MASODIK folti az elso parameter
                    _ent2.patch->GetData(j,(boundary_2 % 2 == 0) ? fabs(boundary_2)+1 : fabs(boundary_2)-1,x2,y2,z2);
                }

                if(boundary_1 < 0){             //  ELSO folt i a masodik parameter
                    _ent1.patch->SetData((boundary_1 % 2 == 0) ? fabs(boundary_1)+1 : fabs(boundary_1)-1,i,x2,y2,z2);
                }else{                          // ELSO folt i az elso parameter
                    _ent1.patch->SetData(i,(boundary_1 % 2 == 0) ? fabs(boundary_1)+1 : fabs(boundary_1)-1 ,x2,y2,z2);
                }
                _ent1.mesh = _ent1.patch->GenerateImage(50,50);
                _ent1.patch->UpdateVertexBufferObjectsOfData();
                _ent1.mesh->UpdateVertexBufferObjects();
            }
        }
    }
    else{
        if(((boundary_1 > 2 ) && (boundary_2 < 3 )) || ((boundary_1 < 3 ) && (boundary_2 >2))){
            // ha nem megfelelo a bemeno adat
            throw new Exception("Oldalt es atlot nem tudok osszevonni");
            return GL_FALSE;
        }else {

            //APOR KOD
        }
    }


    if (flag==NOT_UPDATE){
        _ent1._neighbours[boundary_1]=&_ent2;
        _ent2._neighbours[boundary_2]=this;
        _ent2.updateNeighbours(_ent1);
        _ent1.updateNeighbours(_ent2);
    }
    return GL_TRUE;
}

GLint Entity::whichNeighbour(Entity &e) {
    typedef std::map<int,Entity*>::iterator it_type;
    for(it_type iterator = _neighbours.begin(); iterator != _neighbours.end(); iterator++) {
        if (&e==iterator->second) return iterator->first;
    }
    return 0;
}


GLboolean Entity::updateNeighbours(Entity &kivalto) {
    int real=whichNeighbour(kivalto);
    int interval=real2Internal[real]+8;

    JoinExistingTwoPatches(kivalto,real,kivalto.whichNeighbour((*this)),UPDATE);

    //atlo
    if (interval%2==0) {
        if (_neighbours[internal2Real[(interval-1)%8]])
            _neighbours[internal2Real[(interval-1)%8]]->updateNeighbours((*this));
        if (_neighbours[internal2Real[(interval+1)%8]])
            _neighbours[internal2Real[(interval+1)%8]]->updateNeighbours((*this));
    }
    //oldalak
    else {
        if (_neighbours[internal2Real[(interval-2)%8]])
            _neighbours[internal2Real[(interval-2)%8]]->updateNeighbours((*this));
        if (_neighbours[internal2Real[(interval-1)%8]])
            _neighbours[internal2Real[(interval-1)%8]]->updateNeighbours((*this));
        if (_neighbours[internal2Real[(interval+1)%8]])
            _neighbours[internal2Real[(interval+1)%8]]->updateNeighbours((*this));
        if (_neighbours[internal2Real[(interval+2)%8]])
            _neighbours[internal2Real[(interval+2)%8]]->updateNeighbours((*this));
    }
    return GL_TRUE;
}

void Entity::materialApply() {
     material.Apply();
}

void Entity::setMaterial(Material m) {
    material.setMaterial(m);
}

Material& Entity::getMaterial() {
    return material;
}

Entity& Entity::operator [](unsigned int i)
{
    return (*_neighbours.at(i));
}
