/* Line clip implementation
    Click left mouse button for clipped line and right
    mouse button to come back to previous state */

#include<stdio.h>
#include<stdbool.h>
#include <GL/glut.h>
/*
** @param
** end1 is x y of one end
** end2 is x y of other end
**
*/
int end1[2],end2[2],extreme[4];
int wd,width,height,ax,bx,ay,by;
bool line_clip;
int getslope(int end1[2],int end2[2],double *slope)
{
    //Vertical line
    if(end1[0]==end2[0])
        return 1;

    *slope=(double)(end2[1]-end1[1])/(double)(end2[0]-end1[0]);
    return 0;
}
void swap()
{
    int c,i;
    for(i=0;i<2;i++)
    {
        c=end2[i];
        end2[i]=end1[i];
        end1[i]=c;
    }
}
/*
** @param
** slope is the slope of the line
** end is the point to be modified (outside clipping window)
** extreme is the new points on of x or y
** x if pos = 1 or 2
** y if pos = 3 or 4
*/
void clip(double slope,int end[2],int extreme,int pos)
{
    switch(pos)
    {
        case 1:
        case 2:
            end[1]=end[1]+slope*(extreme-end[0]);
            end[0]=extreme;
            break;
        case 3:
        case 4:
            end[0]=end[0]+(extreme-end[1])/slope;
            end[1]=extreme;
            break;
    }
}

/*
** @param
** end1 is x y of one end
** end2 is x y of other end
** extreme is the clipping window
** extreme[0] for left
** extreme[1] for right
** extreme[2] for bottom
** extreme[3] for top
**/
int clipline()
{
    double slope;
    if(getslope(end1,end2,&slope)==1)
    {
        if(end1[0]<extreme[0])
        return 1;

        if(end1[0]>extreme[1])
        return 1;

        if(end1[1]<extreme[2])
        {
            if(end2[1]<extreme[2])
            return 1;

            else
            end1[1]=extreme[2];
        }
        else if(end2[1]<extreme[2])
        end2[1]=extreme[2];

        if(end1[1]>extreme[3])
        {
            if(end2[1]>extreme[3])
            return 1;

            else
            end1[1]=extreme[3];
        }
        else if(end2[1]>extreme[3])
        end2[1]=extreme[3];


    }

    while(1)
    {
        //Left checking
        if(end1[0]<extreme[0])
        {
            if(end2[0]<extreme[0])
                return 1;
            else
            {
                clip(slope,end1,extreme[0],1);
                continue;
            }
        }
        else if(end2[0]<extreme[0])
        {
            clip(slope,end2,extreme[0],1);
            continue;
        }

        //Right checking
        if(end1[0]>extreme[1])
        {
            if(end1[0]>extreme[1])
            return 1;
            else
            {
                clip(slope,end1,extreme[1],2);
                continue;
            }
        }
        else if(end2[0]>extreme[1])
        {
            clip(slope,end2,extreme[1],2);
            continue;
        }

        //Bottom checking
        if(end1[1]<extreme[2])
        {
            if(end1[1]<extreme[2])
            return 1;
            else
            {
                clip(slope,end1,extreme[2],3);
                continue;
            }
        }
        else if(end2[1]<extreme[2])
        {
            clip(slope,end2,extreme[2],3);
            continue;
        }

        //Top checking
        if(end1[1]>extreme[3])
        {
            if(end1[1]>extreme[3])
            return 1;
            else
            {
                clip(slope,end1,extreme[3],4);
                continue;
            }
        }
        else if(end2[1]>extreme[3])
        {
            clip(slope,end2,extreme[3],4);
            continue;
        }
        break;
    }
    return 0;
}

void display()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_LINE_LOOP);
    glVertex2i(extreme[0],extreme[2]);
    glVertex2i(extreme[1],extreme[2]);
    glVertex2i(extreme[1],extreme[3]);
    glVertex2i(extreme[0],extreme[3]);
  glEnd();
  glColor3f(0.0, 1.0, 0.0);
  glPointSize(3.0);
  if(!line_clip)
  {
    glBegin(GL_LINES);
        glVertex2i(ax,ay);
        glVertex2i(bx,by);
    glEnd();
  }
  else
  {
    glBegin(GL_LINES);
        glVertex2i(end1[0],end1[1]);
        glVertex2i(end2[0],end2[1]);
    glEnd();
  }

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
   switch (button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            line_clip=true;
             glutPostRedisplay();
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            line_clip=false;
             glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc,char **argv)
{
    line_clip=false;
    width  = 1300;
    height = 700;
    printf("Enter the extreme windows:(left right bottom up)\n");
    scanf("%d %d %d %d",&extreme[0],&extreme[1],&extreme[2],&extreme[3]);
    printf("Enter the two end points:\n");
    scanf("%d %d %d %d",&end1[0],&end1[1],&end2[0],&end2[1]);
    ax=end1[0];
    ay=end1[1];
    bx=end2[0];
    by=end2[1];
    if(end1[0]>end2[0])
        swap();
    if(clipline()==1)
        printf("Rejected\n");
    else
    printf("Clipped Line:%d %d %d %d\n",end1[0],end1[1],end2[0],end2[1]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize((int) width, (int) height);
    wd = glutCreateWindow("Line Clipping");
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
