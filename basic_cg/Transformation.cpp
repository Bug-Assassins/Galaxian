
/* 3D Transformations implementation
    Click left mouse button for transformation and right
    mouse button to come back to previous state */

#include<cstdio>
#include<climits>
#include<cmath>
#include<stack>
#include<GL/glut.h>
using namespace std;
stack<float **> s;
bool effect;
GLdouble width, height;
int wd;
float **res,*ans;
inline float to_rad(float deg)
{
    return deg*M_PI/180.0;
};
void translate(float x,float y,float z)
{
    float **mat;
    int i,j;
    mat=new float*[4];
    for(i=0;i<4;i++)
        mat[i]=new float[4];
    for(i=0;i<4;i++)
        for(j=0;j<3;j++)
        {
            if(i==j)
                mat[i][j]=1;
            else
                mat[i][j]=0;
        }
        mat[0][3]=x;
        mat[1][3]=y;
        mat[2][3]=z;
        mat[3][3]=1;
        s.push(mat);
}

void scale(float sx,int sy,int sz)
{
    float **mat;
    int i,j;
    mat=new float*[4];
    for(i=0;i<4;i++)
        mat[i]=new float[4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            mat[i][j]=0;

        mat[0][0]=sx;
        mat[1][1]=sy;
        mat[2][2]=sz;
        mat[3][3]=1;
        s.push(mat);
}
void rotate(float ang,char axis)
{
    float **mat,x,y;
    int i,j;
    mat=new float*[4];
    for(i=0;i<4;i++)
        mat[i]=new float[4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            mat[i][j]=0;
        x=cos(ang);
        y=sin(ang);
        switch(axis)
        {
            case 'x':mat[0][0]=1;
                     mat[1][1]=x;
                     mat[1][2]=-y;
                     mat[2][1]=y;
                     mat[2][2]=x;
                     mat[3][3]=1;
                     break;
            case 'y':mat[0][0]=x;
                     mat[1][1]=1;
                     mat[0][2]=y;
                     mat[2][0]=-y;
                     mat[2][2]=x;
                     mat[3][3]=1;
                     break;
            case 'z':mat[0][0]=x;
                     mat[1][1]=x;
                     mat[0][1]=-y;
                     mat[1][0]=y;
                     mat[2][2]=1;
                     mat[3][3]=1;
                     break;
            default:printf("Wrong parameters!!");
                    exit(0);
        }
        s.push(mat);
}

float **matmul(float **a,float **b)
{
    float **c;
    int i,j,k;
    c=new float*[4];
    for(i=0;i<4;i++)
        c[i]=new float[4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            c[i][j]=0;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            for(k=0;k<4;k++)
                c[i][j]+=a[i][k]*b[k][j];
    return c;
}

void compute()
{
    int i,j;
    float **mat;
    res[0][0]=1;
    res[1][1]=1;
    res[2][2]=1;
    res[3][3]=1;
    while(!s.empty())
    {
        mat=s.top();
        s.pop();
        res=matmul(res,mat);
    }
    /*for(i=0;i<4;i++)
    {for(j=0;j<4;j++)
    printf("%f ",res[i][j]);
    printf("\n");}*/
}
void new_coord(float x,float y,float z)
{
    int i;
    for(i=0;i<4;i++)
    ans[i]=res[i][0]*x+res[i][1]*y+res[i][2]*z+res[i][3];
}

void display()
{

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 1.0, 0.0);
  glPointSize(3.0);
  glBegin(GL_POLYGON);
    if(effect)
    {
        new_coord(500,100,0);
        glVertex3f(ans[0],ans[1],ans[2]);
        new_coord(500,200,0);
        glVertex3f(ans[0],ans[1],ans[2]);
        new_coord(600,200,0);
        glVertex3f(ans[0],ans[1],ans[2]);
        new_coord(600,100,0);
        glVertex3f(ans[0],ans[1],ans[2]);
    }
    else
    {
        glVertex3f(500,100,0);
        glVertex3f(500,200,0);
        glVertex3f(600,200,0);
        glVertex3f(600,100,0);
    }
  glEnd();
  glFlush();
}

void reshape(int w, int h)
{

  width = (GLdouble) w;
  height = (GLdouble) h;
  glViewport(0, 0, (GLsizei) width, (GLsizei) height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0, width, 0.0, height);
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            effect=true;
             glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            effect=false;
             glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc, char *argv[])
{
    int i,j,deg;
    float rad;
    res=new float*[4];
    ans=new float[4];
    for(i=0;i<4;i++)
    res[i]=new float[4];
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            res[i][j]=0;
    width  = 1300.0;
    height = 700.0;
    /*  Transformations */
    translate(-550,-150,0);
    scale(2,2,0);
    rotate(to_rad(45),'z');
    translate(550,150,0);
    compute();
    effect=false;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize((int) width, (int) height);
    wd = glutCreateWindow("Transformations");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}


