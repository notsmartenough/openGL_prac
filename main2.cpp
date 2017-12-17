
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
//#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
//using namespace glm;
  
//GLfloat viewangle = 0, tippangle = 0, traj[120][3];
 
GLfloat d[3] = {0.1, 0.1, 0.1};
 
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;


void init(void)
{
glClearColor(0,0,0,0);
 glShadeModel(GL_FLAT);
    /* set up depth-buffering */
   glEnable(GL_DEPTH_TEST);
       glShadeModel( GL_SMOOTH );
         glEnable( GL_COLOR_MATERIAL );
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*void DrawCube(void)
{

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        //glTranslatef(0.0,0.0,-25.5);
        glTranslatef (d[0], d[1], -25.5 + d[2]); 
    glRotatef(xAngle,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yAngle,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zAngle,0.0,0.0,1.0);
  glBegin(GL_QUADS);        
    glColor3f(0.0f,1.0f,0.0f);    // top
    glVertex3f( 6.0f, 6.0f,-6.0f);   
    glVertex3f(-6.0f, 6.0f,-6.0f);   
    glVertex3f(-6.0f, 6.0f, 6.0f);   
    glVertex3f( 6.0f, 6.0f, 6.0f);

    glColor3f(1.0f,0.5f,0.0f);    // bottom
    glVertex3f( 6.0f,-6.0f, 6.0f);   
    glVertex3f(-6.0f,-6.0f, 6.0f);   
    glVertex3f(-6.0f,-6.0f,-6.0f);   
    glVertex3f( 6.0f,-6.0f,-6.0f);

    glColor3f(1.0f,0.0f,0.0f);    // front    
    glVertex3f( 6.0f, 6.0f, 6.0f);   
    glVertex3f(-6.0f, 6.0f, 6.0f);   
    glVertex3f(-6.0f,-6.0f, 6.0f);   
    glVertex3f( 6.0f,-6.0f, 6.0f);   
    
    glColor3f(1.0f,6.0f,0.0f);    // back
    glVertex3f( 6.0f,-6.0f,-6.0f);   
    glVertex3f(-6.0f,-6.0f,-6.0f);   
    glVertex3f(-6.0f, 6.0f,-6.0f);    
    glVertex3f( 6.0f, 6.0f,-6.0f);    
    
       
    
    glColor3f(1.0f,0.0f,6.0f);    //right
    glVertex3f( 6.0f, 6.0f,-6.0f);    
    glVertex3f( 6.0f, 6.0f, 6.0f);    
    glVertex3f( 6.0f,-6.0f, 6.0f);    
    glVertex3f( 6.0f,-6.0f,-6.0f);    
  
  glEnd();            
  glFlush();
}

 */



GLuint LoadTexture( const char * filename )
{
        GLuint texture;

        int width, height;

        unsigned char * data;

        FILE * file;

        file = fopen( filename, "rb" );

        if ( file == NULL ) return 0;
        width = 256;
        height = 256;
        data = (unsigned char *)malloc( width * height * 3 );
        //int size = fseek(file,);
        fread( data, width * height * 3, 1, file );
        fclose( file );

        for(int i = 0; i < width * height ; ++i)
        {
                int index = i*3;
                unsigned char B,R,G;
                B = data[index+2];
                R = data[index];
                G = data[index+1];

                 data[index] = R;
                 data[index+2] = B;
                 data[index+1] = G;


        }
        glGenTextures( 1, &texture );
        glBindTexture( GL_TEXTURE_2D, texture );
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
        free( data );

        return texture;
}


void animation(void)
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    //glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
        //glTranslatef(0.0,0.0,-25.5);
        glTranslatef (d[0], d[1], -7.0 + d[2]); 
    glRotatef(xAngle,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yAngle,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zAngle,0.0,0.0,1.0);


   float x= 2.5; float y=1; float z=2;
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    GLuint texture = LoadTexture("floor2.bmp");
   glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
        /* Floor */
        glTexCoord2f(0.0, 0.0); glVertex3f(-x,-y,-z);
         glTexCoord2f(0.0, 1.0); glVertex3f(x,-y,-z);
        glTexCoord2f(1.0, 1.0); glVertex3f(x,-y,z);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x,-y,z);
        glEnd();

        texture = LoadTexture("images.bmp");
   glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);

   /* glVertex3f( 6.0f,-6.0f,-6.0f);  glTexCoord2f(0.0f,0.0f); 
    glVertex3f(-6.0f,-6.0f,-6.0f);  glTexCoord2f(0.0f,1.0f);
    glVertex3f(-6.0f, 6.0f,-6.0f);  glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 6.0f, 6.0f,-6.0f);  glTexCoord2f( 1.0f, 0.0f);  
    */
//Ceiling 
        glTexCoord2f(0.0, 0.0); glVertex3f(-x,y,-z);
         glTexCoord2f(0.0, 1.0); glVertex3f(x,y,-z);
        glTexCoord2f(1.0, 1.0); glVertex3f(x,y,z);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x,y,z);
            /* Walls */
        glTexCoord2f(0.0, 0.0); glVertex3f(-x,-y,z);
         glTexCoord2f(0.0, 1.0);glVertex3f(x,-y,z);
        glTexCoord2f(1.0, 1.0); glVertex3f(x,y,z);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x,y,z);

        
       glTexCoord2f(0.0, 0.0); glVertex3f(x,y,z);
         glTexCoord2f(0.0, 1.0); glVertex3f(x,-y,z);
        glTexCoord2f(1.0, 1.0); glVertex3f(x,-y,-z);
        glTexCoord2f(1.0, 0.0); glVertex3f(x,y,-z);

        glTexCoord2f(0.0, 0.0); glVertex3f(x,y,-z);
         glTexCoord2f(0.0, 1.0); glVertex3f(x,-y,-z);
        glTexCoord2f(1.0, 1.0); glVertex3f(-x,-y,-z);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x,y,-z);

        glTexCoord2f(0.0, 0.0); glVertex3f(-x,y,z);
         glTexCoord2f(0.0, 1.0); glVertex3f(-x,-y,z);
        glTexCoord2f(1.0, 1.0); glVertex3f(-x,-y,-z);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x,y,-z); 
        glEnd(); 

//door
        texture = LoadTexture("wood.bmp");
   glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex3f(-x/4,-y,z+0.02);
        glTexCoord2f(0.0, 1.0);glVertex3f(x/4,-y,z+0.02);
        glTexCoord2f(1.0, 1.0); glVertex3f(x/4,y/1.5,z+0.02);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x/4,y/1.5,z+0.02);

        glTexCoord2f(0.0, 0.0); glVertex3f(-x/4,-y,z-0.02);
        glTexCoord2f(0.0, 1.0);glVertex3f(x/4,-y,z-0.02);
        glTexCoord2f(1.0, 1.0); glVertex3f(x/4,y/1.5,z-0.02);
        glTexCoord2f(1.0, 0.0); glVertex3f(-x/4,y/1.5,z-0.02);


glEnd();
//object
texture = LoadTexture("wood.bmp");
   glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0, 0.0); glVertex3f((-x+2)/4,(-y-14)/15,z/4);
        glTexCoord2f(0.0, 1.0);glVertex3f((x+7)/4,(-y-14)/15,z/4);
        glTexCoord2f(1.0, 1.0); glVertex3f((x+7)/4,(y-14)/15,z/4);
        glTexCoord2f(1.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,z/4);

        
        glTexCoord2f(0.0, 0.0); glVertex3f((x+7)/4,(y-14)/15,z/4);
        glTexCoord2f(0.0, 1.0); glVertex3f((x+7)/4,(-y-14)/15,z/4);
        glTexCoord2f(1.0, 1.0); glVertex3f((x+7)/4,(-y-14)/15,-z/4);
        glTexCoord2f(1.0, 0.0); glVertex3f((x+7)/4,(y-14)/15,-z/4);

        glTexCoord2f(0.0, 0.0); glVertex3f((x+7)/4,(y-14)/15,-z/4);
        glTexCoord2f(0.0, 1.0); glVertex3f((x+7)/4,(-y-14)/15,-z/4);
        glTexCoord2f(1.0, 1.0); glVertex3f((-x+2)/4,(-y-14)/15,-z/4);
        glTexCoord2f(1.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,-z/4);

        glTexCoord2f(0.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,z/4);
        glTexCoord2f(0.0, 1.0); glVertex3f((-x+2)/4,(-y-14)/15,z/4);
        glTexCoord2f(1.0, 1.0); glVertex3f((-x+2)/4,(-y-14)/15,-z/4);
        glTexCoord2f(1.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,-z/4); 
        glEnd(); 

        texture = LoadTexture("bed.bmp");
   glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS); 
        glTexCoord2f(0.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,-z/4);
        glTexCoord2f(0.0, 1.0); glVertex3f((x+7)/4,(y-14)/15,-z/4);
        glTexCoord2f(1.0, 1.0); glVertex3f((x+7)/4,(y-14)/15,z/4);
        glTexCoord2f(1.0, 0.0); glVertex3f((-x+2)/4,(y-14)/15,z/4);
        glEnd();

       //DrawCube();
        //glTranslatef( 0.9,-1, -0.98 );
   // glScalef(0.7,0.7,0.7);
    //glRotatef(-45,0,1,0);
    //glPushMatrix();
    //glColor3ub( 120, 120, 120 );

    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_NORMAL_ARRAY );
    
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState( GL_NORMAL_ARRAY );

    glPopMatrix();

  //  glutSwapBuffers();

   glFlush();
    //glutSwapBuffers();
    
}

/*void Special_Keys (int key, int x, int y)
{
    switch (key) {
 
       case GLUT_KEY_LEFT :  viewangle -= 5;  break;
       case GLUT_KEY_RIGHT:  viewangle += 5;  break;
       case GLUT_KEY_UP   :  tippangle -= 5;  break;
       case GLUT_KEY_DOWN :  tippangle += 5;  break;
 
       default: printf ("   Special key %c == %d\n", key, key);
    }
 
    glutPostRedisplay();
}*/
 
    
 

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 27   :  exit(0);    break; 
      case 'l' : d[0] += 0.1;  break;
      case 'i' : d[1] += 0.1;  break;
      case 'o' : d[2] += 0.1;  break;
      case 'j' : d[0] += -0.1;  break;
      case 'k' : d[1] += -0.1;  break;
      case 'p' : d[2] += -0.1;  break;
 
      case 's' : xAngle += 5;  break;
      case 'w' : xAngle += -5;  break;
      case 'a' : yAngle += 5;  break;
      case 'd' : yAngle += -5;  break;
      case 'z' : zAngle += 5;  break;
      default:
         break;
   }
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();
    
     
    gluPerspective(45.0,(GLdouble)x/(GLdouble)y,0.5,1000000.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  
}



int main(int argc, char** argv){

glutInit(&argc, argv);

glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(1000, 1000);
glutInitWindowPosition(100, 100);
glutCreateWindow(argv[0]);
init();

   
  
glutDisplayFunc(animation);
glutReshapeFunc(reshape);
glutKeyboardFunc(keyboard);
//glutSpecialFunc(Special_Keys);
glutIdleFunc(animation);
glutMainLoop();
return 0;
}





