#ifndef CUBE_RUBE_H
#define CUBE_RUBE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstring>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#pragma once
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")         //gcc использует? надо в ковычки?
#pragma comment(lib, "glut32.lib")

#define ASSERT(i) assert(i >= 0 && i < type)
#define OSSERT(i, type) assert(i >= 0 && i < type)

//===========================================================================================================================================================
//                                                                                               Classes
//===========================================================================================================================================================

class Cube
    {
    private:

    unsigned char color_[4];

    public:

    unsigned int color[6];

    double edge;

    Cube();
    void rotX();
    void rotY();
    void rotZ();
    void DrawCube(int type);
    void DrawAll(double x, double y, double z, int type);
    void SetColor(int i, int color);
    unsigned char* at(int i);
    };

class CubeRube
    {
    public:

    int act_face, type;

    double size;

    unsigned int color[6];
    };

class CubeRube2x2 : public CubeRube
    {
    private:

    Cube cube[2][2][2];
    Cube tmp[2][2];

    int rot[2*3];

    bool ok[2][2][2];

    public:

    CubeRube2x2();
    void Clear(double size, unsigned int* col);
    void Draw();
    void rot90(int ix, int sign);
    void Rotate(int ix, int angle);
    };

class CubeRube3x3 : public CubeRube
    {
    private:

    Cube cube[3][3][3];
    Cube tmp[3][3];

    int rot[3*3];

    bool ok[3][3][3];

    public:

    CubeRube3x3();
    void Clear(double size, unsigned int* col);
    void Draw();
    void rot90(int ix, int sign);
    void Rotate(int ix, int angle);
    };

class CubeRube4x4 : public CubeRube
    {
    private:

    Cube cube[4][4][4];
    Cube tmp[4][4];

    int rot[4*3];

    bool ok[4][4][4];

    public:

    CubeRube4x4();
    void Clear(double size, unsigned int* col);
    void Draw();
    void rot90(int ix, int sign);
    void Rotate(int ix, int angle);
    };

class CubeRube5x5 : public CubeRube
    {
    private:

    Cube cube[5][5][5];
    Cube tmp[5][5];

    int rot[5*3];

    bool ok[5][5][5];

    public:

    CubeRube5x5();
    void Clear(double size, unsigned int* col);
    void Draw();
    void rot90(int ix, int sign);
    void Rotate(int ix, int angle);
    };

//===========================================================================================================================================================
//===========================================================================================================================================================
//===========================================================================================================================================================
//===========================================================================================================================================================
//===========================================================================================================================================================

Cube :: Cube()
    {
    memset(color, 0, sizeof(color));
    edge = 0;
    }

void Cube :: rotX()
    {
    unsigned int tmp = color[0];

    color[0] = color[4];
    color[4] = color[1];
    color[1] = color[5];
    color[5] = tmp;
    }

void Cube :: rotY()
    {
    unsigned int tmp = color[2];

    color[2] = color[1];
    color[1] = color[3];
    color[3] = color[0];
    color[0] = tmp;
    }

void Cube :: rotZ()
    {
    unsigned int tmp = color[5];

    color[5] = color[3];
    color[3] = color[4];
    color[4] = color[2];
    color[2] = tmp;
    }

void Cube :: DrawCube(int type)
    {
    glPushMatrix();

    #define a edge

    if(type == 2) glTranslatef(a/2, a/2, a/2);
    else if(type == 3) glTranslatef(0, 0, 0);
    else if(type == 4) glTranslatef(a/-2, a/-2, a/-2);
    else if(type == 5) glTranslatef(-a, -a, -a);
    else abort();

    glBegin(GL_QUADS);
        glColor3ubv(at(0));
        glNormal3f(0, 0, -1);
        glVertex3f(a, a, a);
        glVertex3f(0, a, a);
        glVertex3f(0, 0, a);
        glVertex3f(a, 0, a);

        glColor3ubv(at(1));
        glNormal3f(0, 0, -1);
        glVertex3f(a, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, a, 0);
        glVertex3f(a, a, 0);

        glColor3ubv(at(2));
        glNormal3f(0, -1, 0);
        glVertex3f(a, 0, a);
        glVertex3f(0, 0, a);
        glVertex3f(0, 0, 0);
        glVertex3f(a, 0, 0);

        glColor3ubv(at(3));
        glNormal3f(0, 1, 0);
        glVertex3f(a, a, 0);
        glVertex3f(0, a, 0);
        glVertex3f(0, a, a);
        glVertex3f(a, a, a);

        glColor3ubv(at(4));
        glNormal3f(-1, 0, 0);
        glVertex3f(0, a, a);
        glVertex3f(0, a, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, a);

        glColor3ubv(at(5));
        glNormal3f(1, 0, 0);
        glVertex3f(a, a, 0);
        glVertex3f(a, a, a);
        glVertex3f(a, 0, a);
        glVertex3f(a, 0, 0);
    glEnd();

    #undef a

    glPopMatrix();
    }

void Cube :: DrawAll(double x, double y, double z, int type)
    {
    glPushMatrix();

    glTranslated(x, y, z);
    DrawCube(type);

    glPopMatrix();
    }

void Cube :: SetColor(int i, int col)
    {
    OSSERT(i, 6);

    color[i] = col;
    }

unsigned char* Cube :: at(int i)
    {
    OSSERT(i, 6);

    color_[0] = color[i]>>16;
    color_[1] = color[i]>>8;
    color_[2] = color[i];

    return color_;
    }

//===========================================================================================================================================================
//                                                                                           CubeRube2x2
//===========================================================================================================================================================

CubeRube2x2 :: CubeRube2x2()
    {
    type = 2;
    }

void CubeRube2x2 :: Clear(double size, unsigned int* col)
    {
    memset(rot, 0, sizeof(rot));
    this->size = size;
    act_face = -1;

    for(int i = 0; i < 6; i++) {OSSERT(i, 6); color[i] = col[i];}

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[i][j][1].SetColor(0, color[0]);
            cube[i][j][0].SetColor(1, color[1]);
            }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[j][0][i].SetColor(2, color[2]);
            cube[j][1][i].SetColor(3, color[3]);
            }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[0][j][i].SetColor(4, color[4]);
            cube[1][j][i].SetColor(5, color[5]);
           }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            for(int k = 0; k < type; k++)
                {
                ASSERT(i);
                ASSERT(j);
                ASSERT(k);

                cube[i][j][k].edge = (size/3)*0.95;
                }
    }

void CubeRube2x2 :: Draw()
    {
    const double K = 0.65;

    memset(ok, true, sizeof(ok));
    if(act_face != -1)
        {
        glPushMatrix();
        int k;

        if(act_face == 0 || act_face == 1)
            {
            k = act_face & 1;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[i][j][k] = false;
                    }

            OSSERT(act_face, 6);
            glTranslated(size/2, size/2, 0);
            glRotatef(rot[act_face], 0, 0, 1);
            glTranslated(size/-2, size/-2, 0);

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k,  type);
                    }
            }
        else if(act_face == 2 || act_face == 3)
            {
            k = act_face & 1;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[i][k][j] = false;
                    }

            OSSERT(act_face, 6);
            glTranslated(size/2, 0, size/2);
            glRotatef(rot[act_face], 0, 1, 0);
            glTranslated(size/-2, 0, size/-2);

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    cube[i][k][j].DrawAll(size/3*i, size/3*k, size/3*j , type);
                    }
            }
        else if(act_face == 4 || act_face == 5)
            {
            k = act_face & 1;

            for(int j = 0; j < type; j++)
                for(int i = 0; i < type; i++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[k][j][i] = false;
                    }

            OSSERT(act_face, 6);
            glTranslated(0, size/2, size/2);
            glRotatef(rot[act_face], 1, 0, 0);
            glTranslated(0, size/-2, size/-2);

            for(int j = 0; j < type; j++)
                for(int i = 0; i < type; i++)
                    cube[k][j][i].DrawAll(size/3*k, size/3*j, size/3*i, type);
            }

        glPopMatrix();
		}

		for(int i = 0; i < type; i++)
			for(int j = 0; j < type; j++)
				for(int k = 0; k < type; k++)
					{
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    if(ok[i][j][k]) cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
					}
    }

void CubeRube2x2 :: rot90(int ix, int sign)
    {
    int k;

    if(sign == -1) sign = 3;

    while(sign--)
        {
        if(ix == 0 || ix == 1)
            {
            if(ix == 1) k = 1;
            else         k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[i][j][k];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                     {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    tmp[i][j].rotZ(),
                    cube[i][j][k] = tmp[i][j];
                     }
            }
        else if(ix == 2 || ix == 3)
            {
            if(ix == 3) k = 1;
            else          k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[i][k][j];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                     {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    tmp[i][j].rotX(),
                    cube[i][k][j] = tmp[i][j];
                     }
            }
        else if(ix == 4 || ix == 5)
            {
            if(ix == 5) k = 1;
            else          k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[k][i][j];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                     {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                   tmp[i][j].rotY(),
                   cube[k][i][j] = tmp[i][j];
                     }
            }
        }
    }

void CubeRube2x2 :: Rotate(int ix, int angle)
    {
    OSSERT(ix, 6);

    if(act_face == -1 || act_face == ix)
        {
        rot[ix] += angle;

        if(rot[ix]%90 != 0) act_face = ix;
        else
            {
            if((rot[ix] < 0) ^ (act_face == 2 || act_face == 3)) rot90(ix,  1);
            else                                                                    rot90(ix, -1);

            rot[ix] = 0;
            act_face = -1;
            }
        }
    }

//===========================================================================================================================================================
//                                                                                           CubeRube3x3
//===========================================================================================================================================================

CubeRube3x3 :: CubeRube3x3()
    {
    type = 3;
    }

void CubeRube3x3 :: Clear(double size, unsigned int* col)
   {
    memset(rot, 0, sizeof(rot));
    this->size = size;
    act_face = -1;

    for(int i = 0; i < 6; i++) color[i] = col[i];

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[i][j][2].SetColor(0, color[0]);
            cube[i][j][0].SetColor(1, color[1]);
            }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[j][0][i].SetColor(2, color[2]);
            cube[j][2][i].SetColor(3, color[3]);
            }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            {
            ASSERT(i);
            ASSERT(j);

            cube[0][j][i].SetColor(4, color[4]);
            cube[2][j][i].SetColor(5, color[5]);
            }

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            for(int k = 0; k < type; k++)
                {
                ASSERT(i);
                ASSERT(j);
                ASSERT(k);

                cube[i][j][k].edge = (size/3)*0.95;
                }
    }

void CubeRube3x3 :: Draw()
    {
    const double K = 0.65;

    memset(ok, true, sizeof(ok));
    if(act_face != -1)
        {
        glPushMatrix();

        int k;

        if(act_face == 0 || act_face == 1 || act_face == 6)
            {
            if       (act_face == 1) k = 2;
            else if(act_face == 6) k = 1 ;
            else                           k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[i][j][k] = false;
                    }

            OSSERT(act_face, 9);
            glTranslated(size/2, size/2, size/2);
            glRotatef(rot[act_face], 0, 0, 1);
            glTranslated(size/-2, size/-2, size/-2);

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
                    }
            }
        else if(act_face == 2 || act_face == 3 || act_face == 7)
            {
            if       (act_face == 3) k = 2;
            else if(act_face == 7) k = 1;
            else                           k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[i][k][j] = false;
                    }

            OSSERT(act_face, 9);
            glTranslated(size/2, 0, size/2);
            glRotatef(rot[act_face], 0, 1, 0);
            glTranslated(size/-2, 0, size/-2);

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    cube[i][k][j].DrawAll(size/3*i, size/3*k, size/3*j, type);
                    }
            }
        else if(act_face == 4 || act_face == 5 || act_face == 8)
            {
            if       (act_face == 5) k = 2;
            else if(act_face == 8) k = 1;
            else                           k = 0;

            for(int j = 0; j < type; j++)
                for(int i = 0; i < type; i++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    ok[k][j][i] = false;
                    }

            OSSERT(act_face, 9);
            glTranslated(0, size/2, size/2);
            glRotatef(rot[act_face], 1, 0, 0);
            glTranslated(0, size/-2, size/-2);

            for(int j = 0; j < type; j++)
                for(int i = 0; i < type; i++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    cube[k][j][i].DrawAll(size/3*k, size/3*j, size/3*i, type);
                    }
            }

        glPopMatrix();
		}

		for(int i = 0; i < type; i++)
			for(int j = 0; j < type; j++)
				for(int k = 0; k < type; k++)
					{
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    if(ok[i][j][k]) cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
					}
	}

void CubeRube3x3 :: rot90(int ix, int sign)
    {
    int k;

    if(sign == -1) sign = 3;

    while(sign--)
        {
        if(ix == 0 || ix == 1 || ix == 6)
            {
            if       (ix == 1)  k = 2;
            else if(ix == 6) k = 1;
            else                 k = 0;

            for(int i = 0; i < type;  i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[i][j][k];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    tmp[i][j].rotZ(),
                    cube[i][j][k] = tmp[i][j];
                    }
            }
        else if(ix == 2 || ix == 3 || ix == 7)
            {
            if       (ix == 3) k = 2;
            else if(ix == 7) k = 1;
            else                 k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[i][k][j];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    tmp[i][j].rotX(),
                    cube[i][k][j] = tmp[i][j];
                    }
            }
        else if(ix == 4 || ix == 5 || ix == 8)
            {
            if       (ix == 5) k = 2;
            else if(ix == 8) k = 1;
            else                 k = 0;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);
                    ASSERT(type - 1 - i);

                    tmp[j][type - 1 - i] = cube[k][i][j];
                    }

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    {
                    ASSERT(i);
                    ASSERT(j);
                    ASSERT(k);

                    tmp[i][j].rotY(),
                    cube[k][i][j] = tmp[i][j];
                    }
            }
        }
    }

void CubeRube3x3 :: Rotate(int ix, int angle)
    {
    OSSERT(ix, 9);

    if(act_face == -1 || act_face == ix)
        {
        rot[ix] += angle;

        if(rot[ix]%90 != 0) act_face = ix;
        else
            {
            if(rot[ix] < 0 || act_face == 2 || act_face == 3 || act_face == 7) rot90(ix,  1);
            else                                                                                          rot90(ix, -1);

            rot[ix] = 0;
            act_face = -1;
            }
        }
    }

//===========================================================================================================================================================
//                                                                                           CubeRube4x4
//===========================================================================================================================================================

CubeRube4x4 :: CubeRube4x4()
    {
    type = 4;
    }

void CubeRube4x4 :: Clear(double size, unsigned int* col)
   {
    memset(rot, 0, sizeof(rot));
    this->size = size;
    act_face = -1;

    for(int i = 0; i < 6; i++) color[i] = col[i];

    for(int i = 0; i < 4; i++)                         // Белый
        for(int j = 0; j < 4; j++)
            cube[i][j][3].SetColor(0, color[0]);

    for(int i = 0; i < 4; i++)                         // Жёлтый
        for(int j = 0; j < 4; j++)
            cube[i][j][0].SetColor(1, color[1]);

    for(int i = 0; i < 4; i++)                          // Синий
        for(int j = 0; j < 4; j++)
           cube[j][0][i].SetColor(2, color[2]);

    for(int i = 0; i < 4; i++)                          // Зелёный
        for(int j = 0; j < 4; j++)
            cube[j][3][i].SetColor(3, color[3]);

    for(int i = 0; i < 4; i++)                         // Красный
        for(int j = 0; j < 4; j++)
            cube[0][j][i].SetColor(4, color[4]);

    for(int i = 0; i < 4; i++)                          // Оранжевый
        for(int j = 0; j < 4; j++)
            cube[3][j][i].SetColor(5, color[5]);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                cube[i][j][k].edge = (size/3)*0.95;
    }

void CubeRube4x4 :: Draw()
    {
    const double K = 0.65;

    memset(ok, true, sizeof(ok));
    if(act_face != -1)
        {
        glPushMatrix();
        int k;

        if(act_face == 0 || act_face == 1)
            {
            k = (act_face & 1)*2;

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    ok[i][j][k] = false;

            glTranslated(size/2, size/2, size/2);
            glRotatef(rot[act_face], 0, 0, 1);
            glTranslated(size/-2, size/-2, size/-2);

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
            }
        else if(act_face == 2 || act_face == 3)
            {
            k = (act_face & 1)*2;

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    ok[i][k][j] = false;

            glTranslated(size/2, 0, size/2);
            glRotatef(rot[act_face], 0, 1, 0);
            glTranslated(size/-2, 0, size/-2);

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    cube[i][k][j].DrawAll(size/3*i, size/3*k, size/3*j, type);
            }
        else if(act_face == 4 || act_face == 5)
            {
            k = (act_face & 1)*2;

            for(int j = 0; j < 4; j++)
                for(int i = 0; i < 4; i++)
                    ok[k][j][i] = false;

            glTranslated(0, size/2, size/2);
            glRotatef(rot[act_face], 1, 0, 0);
            glTranslated(0, size/-2, size/-2);

            for(int j = 0; j < 4; j++)
                for(int i = 0; i < 4; i++)
                    cube[k][j][i].DrawAll(size/3*k, size/3*j, size/3*i, type);
            }

        glPopMatrix();
		}

		for(int i = 0; i < 4; i++)
			for(int j = 0; j < 4; j++)
				for(int k = 0; k < 4; k++)
					if(ok[i][j][k])
						cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
	}

void CubeRube4x4 :: rot90(int ix, int sign)
    {
    int k;

    if(sign == -1) sign = 3;

    while(sign--)
        {
        if(ix == 0 || ix == 1)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[j][3 - i] = cube[i][j][k];

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[i][j].rotZ(),
                    cube[i][j][k] = tmp[i][j];
            }
        else if(ix == 2 || ix == 3)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[j][3 - i] = cube[i][k][j];

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[i][j].rotX(),
                    cube[i][k][j] = tmp[i][j];
            }
        else if(ix == 4 || ix == 5)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[j][3 - i] = cube[k][i][j];

            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    tmp[i][j].rotY(),
                    cube[k][i][j] = tmp[i][j];
            }
        }
    }

void CubeRube4x4 :: Rotate(int ix, int angle)
    {
    assert(ix < 9);

    if(act_face == -1 || act_face == ix)
        {
        rot[ix] += angle;

        if(rot[ix]%90 != 0) act_face = ix;
        else
            {
            if((rot[ix] < 0) ^ (act_face == 2 || act_face == 3)) rot90(ix,  1);
            else                                                                    rot90(ix, -1);

            rot[ix] = 0;
            act_face = -1;
            }
        }
    }

//===========================================================================================================================================================
//                                                                                           CubeRube5x5
//===========================================================================================================================================================

CubeRube5x5 :: CubeRube5x5()
    {
    type = 5;
    }

void CubeRube5x5 :: Clear(double size, unsigned int* col)
   {
    memset(rot, 0, sizeof(rot));
    this->size = size;
    act_face = -1;

    for(int i = 0; i < 6; i++) color[i] = col[i];

    for(int i = 0; i < type; i++)                         // Белый
        for(int j = 0; j < type; j++)
            cube[i][j][4].SetColor(0, color[0]);

    for(int i = 0; i < type; i++)                         // Жёлтый
        for(int j = 0; j < type; j++)
            cube[i][j][0].SetColor(1, color[1]);

    for(int i = 0; i < type; i++)                          // Синий
        for(int j = 0; j < type; j++)
           cube[j][0][i].SetColor(2, color[2]);

    for(int i = 0; i < type; i++)                          // Зелёный
        for(int j = 0; j < type; j++)
            cube[j][4][i].SetColor(3, color[3]);

    for(int i = 0; i < type; i++)                         // Красный
        for(int j = 0; j < type; j++)
            cube[0][j][i].SetColor(4, color[4]);

    for(int i = 0; i < type; i++)                          // Оранжевый
        for(int j = 0; j < type; j++)
            cube[4][j][i].SetColor(5, color[5]);

    for(int i = 0; i < type; i++)
        for(int j = 0; j < type; j++)
            for(int k = 0; k < type; k++)
                cube[i][j][k].edge = (size/3)*0.95;
    }

void CubeRube5x5 :: Draw()
    {
    const double K = 0.65;

    memset(ok, true, sizeof(ok));
    if(act_face != -1)
        {
        glPushMatrix();
        int k;

        if(act_face == 0 || act_face == 1)
            {
            k = (act_face & 1)*2;

            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    ok[i][j][k] = false;

            glTranslated(size/2, size/2, 0);
            glRotatef(rot[act_face], 0, 0, 1);
            glTranslated(size/-2, size/-2, 0);

            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
            }
        else if(act_face == 2 || act_face == 3)
            {
            k = (act_face & 1)*2;

            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    ok[i][k][j] = false;

            glTranslated(size/2, 0, size/2);
            glRotatef(rot[act_face], 0, 1, 0);
            glTranslated(size/-2, 0, size/-2);

            for(int i = 0; i < 5; i++)
                for(int j = 0; j < 5; j++)
                    cube[i][k][j].DrawAll(size/3*i, size/3*k, size/3*j, type);
            }
        else if(act_face == 4 || act_face == 5)
            {
            k = (act_face & 1)*2;

            for(int j = 0; j < 5; j++)
                for(int i = 0; i < 5; i++)
                    ok[k][j][i] = false;

            glTranslated(0, size/2, size/2);
            glRotatef(rot[act_face], 1, 0, 0);
            glTranslated(0, size/-2, size/-2);

            for(int j = 0; j < 5; j++)
                for(int i = 0; i < 5; i++)
                    cube[k][j][i].DrawAll(size/3*k, size/3*j, size/3*i, type);
            }

        glPopMatrix();
		}

		for(int i = 0; i < 5; i++)
			for(int j = 0; j < 5; j++)
				for(int k = 0; k < 5; k++)
					if(ok[i][j][k])
						cube[i][j][k].DrawAll(size/3*i, size/3*j, size/3*k, type);
	}

void CubeRube5x5 :: rot90(int ix, int sign)
    {
    int k;

    if(sign == -1) sign = 3;

    while(sign--)
        {
        if(ix == 0 || ix == 1)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[j][type - 1 - i] = cube[i][j][k];

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[i][j].rotZ(),
                    cube[i][j][k] = tmp[i][j];
            }
        else if(ix == 2 || ix == 3)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[j][type - 1 - i] = cube[i][k][j];

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[i][j].rotX(),
                    cube[i][k][j] = tmp[i][j];
            }
        else if(ix == 4 || ix == 5)
            {
            k = (ix & 1)*2;

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[j][type - 1 - i] = cube[k][i][j];

            for(int i = 0; i < type; i++)
                for(int j = 0; j < type; j++)
                    tmp[i][j].rotY(),
                    cube[k][i][j] = tmp[i][j];
            }
        }
    }

void CubeRube5x5 :: Rotate(int ix, int angle)
    {
    assert(ix < 9);

    if(act_face == -1 || act_face == ix)
        {
        rot[ix] += angle;

        if(rot[ix]%90 != 0) act_face = ix;
        else
            {
            if((rot[ix] < 0) ^ (act_face == 2 || act_face == 3)) rot90(ix,  1);
            else                                                                    rot90(ix, -1);

            rot[ix] = 0;
            act_face = -1;
            }
        }
    }

#endif // CUBE_H
