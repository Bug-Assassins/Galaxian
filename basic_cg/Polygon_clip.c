/* Polygon clip implementation
    Click left mouse button for clipped polygon and right
    mouse button to come back to previous state */

#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define INF 10000000
struct Vertex{
    float x,y;
} win[4],*out,*in_v,*inv;
int N,wd,width,height,in_num,out_num;
bool clip;
bool inside_win(struct Vertex v,int ind)
{
       switch(ind)
        {
            case 0:if(v.x>=win[0].x)
                    return true;
                    return false;
                    break;
            case 1:if(v.x<=win[1].x)
                     return true;
                     return false;
                     break;
            case 2:if(v.y>=win[1].y)
                     return true;
                     return false;
                     break;
            case 3:if(v.y<=win[2].y)
                     return true;
                     return false;
                     break;
        }
}


struct Vertex inter_point(struct Vertex s,struct Vertex p,int ind)
{
    struct Vertex in;
    float m;
    if(p.x==s.x)
        m=INF;
    else
        m=(s.y-p.y)/(s.x-p.x);
    switch(ind)
    {
        case 0:
        case 1:
                in.x=win[ind].x;
                in.y=(in.x-p.x)*m+p.y;
                break;

        case 2: in.y=win[0].y;
                in.x=(in.y-p.y)/m+p.x;
                break;

        case 3:
                in.y=win[ind].y;
                in.x=(in.y-p.y)/m+p.x;
                break;
    }
    return in;
}

void Polygon_clip()
{
    struct Vertex a,b,inter;
    int i,j;
    for(i=0;i<4;i++)
    {
        out_num=0;
        b=in_v[in_num-1];
        for(j=0;j<in_num;j++)
        {
            a=in_v[j];
            if(inside_win(a,i))
            {
                if(!inside_win(b,i))
                {
                    inter=inter_point(b,a,i);
                    out[out_num++]=inter;
                }
                out[out_num++]=a;
            }
            else if(inside_win(b,i))
            {
                    inter=inter_point(a,b,i);
                    out[out_num++]=inter;
            }

            b=a;
        }

        in_num=out_num;
        for(j=0;j<in_num;j++)
            in_v[j]=out[j];
    }

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

void display(void)
{
    int i;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glPointSize(3.0);
    glBegin(GL_LINE_LOOP);
    {
        for(i=0;i<4;i++)
        glVertex2f(win[i].x,win[i].y);
    }
    glEnd();
    glFlush();
    glPointSize(1.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    if(!clip)
    {
        for(i=0;i<N;i++)
        glVertex2f(inv[i].x,inv[i].y);
    }
    else
    {

        for(i=0;i<out_num;i++)
        glVertex2f(out[i].x,out[i].y);

    }
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
   switch (button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            clip=true;
             glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            clip=false;
             glutPostRedisplay();
         break;
      default:
         break;
   }
}


int main(int argc,char *argv[])
{
    width  = 1300.0;
    height = 700.0;
    int i;
    clip=false;
    printf("Enter the extreme windows:(left right bottom up)\n");
    scanf("%f %f %f %f",&win[0].x,&win[1].x,&win[1].y,&win[2].y);
    win[0].y=win[1].y;
    win[2].x=win[1].x;
    win[3].y=win[2].y;
    win[3].x=win[0].x;
    printf("Enter the number of sides of polygon:");
    scanf("%d",&in_num);
    N=in_num;
    printf("Enter the coordinates:\n");
    in_v=(struct Vertex *)malloc(2*in_num*sizeof(struct Vertex));
    out=(struct Vertex *)malloc(2*in_num*sizeof(struct Vertex));
    inv=(struct Vertex *)malloc(2*in_num*sizeof(struct Vertex));
    for(i=0;i<in_num;i++)
    {
        scanf("%f%f",&in_v[i].x,&in_v[i].y);
        inv[i].x=in_v[i].x;
        inv[i].y=in_v[i].y;
    }
    Polygon_clip();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize((int) width, (int) height);
    wd=glutCreateWindow("Polygon Clipping!");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
