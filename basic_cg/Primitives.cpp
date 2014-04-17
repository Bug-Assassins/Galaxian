#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<limits.h>
#define NENDS 2

GLdouble width, height;
int wd;
int ends[NENDS][2]; //End Points of Line
int circenx,circeny,cirrad; //Variables for circle
int ella,ellb,ellcenx,ellceny; //Variable for Ellipse

//Data for Scanline Polygon Fill Algorithm
struct edge{
    float ymin,ymax,x;
    //float xm;
    float m;
    struct edge* next;
};

int nov,gminy,gmaxy,scan;
struct edge **elist,*head,*temp1,*temp2,*newn,*aet=NULL;
struct edge* newnode(int ymini,int ymaxi,int xymini,int xymaxi)
{
    struct edge* tt = (struct edge*)malloc(sizeof(struct edge));
    tt->ymin=ymini;
    tt->ymax=ymaxi;
    tt->x=xymini;
    if(xymaxi==xymini) tt->m=0;
    else tt->m=((float)(xymaxi-xymini))/((float)(ymaxi-ymini));
    tt->next=NULL;
    return tt;
};
struct edge* newold(struct edge* ed)
{
    struct edge* tt = (struct edge*)malloc(sizeof(struct edge));
    tt->ymax=ed->ymax;
    tt->ymin=ed->ymin;
    tt->m=ed->m;
    tt->x=ed->x;
    tt->next=NULL;
    return tt;
};
void pri(struct edge* x)
{
    int k=0;
    while(x!=NULL)
    {
        printf("[%.1f,%.1f,%.1f,%.1f]->",x->ymin,x->x,x->ymax,x->m);
        fflush(stdout);
        k++;
        x=x->next;
        if(k>15) exit(0);
    }
    printf("NULL\n");
}

void init(void)
{
  width  = 1280.0;                 /* initial window width and height, */
  height = 800.0;                  /* within which we draw. */
  ends[0][0] = (int)(0.25*width);  /* (0,0) is the lower left corner */
  ends[0][1] = (int)(0.25*height);
  ends[1][0] = (int)(0.30*width);
  ends[1][1] = (int)(0.75*height);
  circenx=(int)(0.50*width);
  circeny=(int)(0.50*height);
  cirrad=(int)(0.25*height);
  ellcenx=(int)(0.50*width);
  ellceny=(int)(0.50*height);
  ella=(int)(0.25*width);
  ellb=(int)(0.25*height);
}
//Circle Display Fuctions
void cirsetpix(int x,int y)
{
	glVertex2i(circenx+x,circeny+y);
	glVertex2i(circenx+x,circeny-y);
	glVertex2i(circenx-x,circeny+y);
	glVertex2i(circenx-x,circeny-y);
	glVertex2i(circenx+y,circeny+x);
	glVertex2i(circenx+y,circeny-x);
	glVertex2i(circenx-y,circeny+x);
	glVertex2i(circenx-y,circeny-x);
}
void dispcir(void)
{
	int x = 0, y = cirrad;
	int dec = 1-cirrad;
	cirsetpix(x,y);
	while(y>x)
	{
		if(dec>=0)
		{
			dec+=2-(2*y);
			y--;
		}
		dec += 3 + (2*x);
		x++;
		cirsetpix(x,y);
	}
}

//Display Function for line
void displine(void)
{
    int dx = ends[1][0] - ends[0][0];
    int dy = ends[1][1] - ends[0][1];
    if(dx<0)
    {
        int t1 = ends[1][0],t2 = ends[1][1];
        ends[1][0]=ends[0][0]; ends[1][1]=ends[0][1];
        ends[0][0]=t1; ends[0][1]=t2;
        dx=-dx;
        dy=-dy;
    }
    int x=ends[0][0],y=ends[0][1];

    if(dy>=0 && dy<=dx)
    {
        for(int dec=(2*dy)-dx;x<=ends[1][0];)
        {
            if(dec>=0)
            {
                dec -= (dx<<1);
                y++;
            }
            dec+=(dy<<1);
            x++;
            glVertex2i(x,y);
        }
    }

    else if(dy>dx)
    {
        for(int dec=(2*dx)-dy;y<=ends[1][1];)
        {
            if(dec>=0)
            {
                dec -= (dy<<1);
                x++;
            }
            dec += (dx<<1);
            y++;
            glVertex2i(x,y);
        }
    }

    else if(dy<0 && (-dy)<=dx)
    {
        for(int dec=(dy*2)+dx;x<=ends[1][0];)
        {
            if(dec<0)
            {
                dec += (dx*2);
                y--;
            }
            dec += (dy*2);
            x++;
            glVertex2i(x,y);
        }
    }

    else
    {
        for(int dec=(dx*2)+dy;y>=ends[1][1];)
        {
            if(dec>=0)
            {
                dec+=(dy*2);
                x++;
            }
            dec += (dx*2);
            y--;
            glVertex2i(x,y);
        }
    }
}

//Display Function for Ellipse
void ellsetpix(int x,int y)
{
	glVertex2i(ellcenx+x,ellceny+y);
	glVertex2i(ellcenx+x,ellceny-y);
	glVertex2i(ellcenx-x,ellceny+y);
	glVertex2i(ellcenx-x,ellceny-y);
}
void dispell(void)
{
	int x=0,y=ellb,asq=ella*ella,bsq=ellb*ellb;
	float dec = bsq - (asq*ellb) +(((float)asq)*0.25);
	while(asq*y>bsq*x)
	{
		if(dec>=0)
		{
			dec -= 2*asq*(y-1);
			y--;
		}
		dec += bsq*((2*x)+3);
		x++;
		ellsetpix(x,y);
	}
	float aa = x+0.25;
	dec = (aa*bsq) + (asq*(1-(2*y)));
	while(y>0)
	{
		if(dec<=0)
		{
			dec += 2*bsq*(x+1);
			x++;
		}
		dec += asq*(3-(2*y));
		y--;
		ellsetpix(x,y);
	}
}

void scanline()
{
    int i,j;
    aet=NULL;
    printf("Starting Scaline");
    for(i=0;i<scan;i++)
    {

        //Deleting Edges whose ymax=current scanline
        head=aet;
        while(aet!=NULL && aet->ymax==(i+gminy))
        {
            head=aet;
            aet=aet->next;
            free(head);
        }
        temp1=aet;
        if(aet==NULL) head=NULL;
        else head=aet->next;
        while(head!=NULL)
        {
            if(head->ymax==(i+gminy))
            {
                temp1->next=head->next;
                free(head);
                head=temp1->next;
            }
            else
            {
                temp1=head;
                head=head->next;
            }
        }

        //Adding Edges whose ymin=current scanline
        temp1=elist[i];
        while(temp1!=NULL)
        {
            newn=newold(temp1);
            temp2=head=aet;
            if(head==NULL) aet=newn;
            else if(head->x>newn->x || (head->x==newn->x && (((newn->m>0 && head->m>0 && head->m>newn->m)||(newn->m<0 && head->m>0)||(head->m<0 && newn->m<0 && newn->m<head->m)))))
            {
                aet=newn;
                newn->next=head;
            }
            else
            {
                while(head!=NULL && (head->x<newn->x || (head->x==newn->x && ((newn->m>0 && head->m>0 && head->m<newn->m)||(newn->m>0 && head->m<0)||(head->m<0 && newn->m<0 && newn->m>head->m)))))
                {
                    temp2=head;
                    head=head->next;
                }
                temp2->next=newn;
                newn->next=head;
            }
            temp1=temp1->next;
        }

        printf("After Addition Deletion=\nAET(%d) =>",i+gminy);
        pri(aet);

        //Painting the Required Area on this scanline
        head=aet;
        while(head!=NULL)
        {
            for(j=head->x;j<=head->next->x;j++)
                glVertex2f(j,i+gminy);
            head=head->next->next;
        }

        //Updating the data in the AET Buckets
        head=aet;
        while(head!=NULL)
        {
            head->x += head->m;
            head=head->next;
        }
        printf("After Update and paint=\nAET(%d) =>",i+gminy);fflush(stdout);
        pri(aet);
    }
}
void maindisp()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    scanline();
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

int main(int argc, char *argv[])
{
    init();
    int i,next,headpos;
    printf("Enter the number of vertices:");
    scanf("%d",&nov);
    int arr[nov][2];
    for(i=0;i<nov;i++)
    {
        printf("Enter the x,y co-ordinate of vextex no %d :",i+1);
        scanf("%d%d",&arr[i][0],&arr[i][1]);
    }

    gminy=INT_MAX;gmaxy=INT_MIN;
    for(i=0;i<nov;i++)
    {
        if(arr[i][1]<gminy) gminy=arr[i][1];
        if(arr[i][1]>gmaxy) gmaxy=arr[i][1];
    }

    //Making the Sorted Edge Set
    scan = (gmaxy-gminy)+1;
    elist = (struct edge**)malloc(scan*sizeof(struct edge*));
    for(i=0;i<scan;i++) elist[i]=NULL;
    for(i=0;i<nov;i++)
    {
        next=(i+1)%nov;
        if(arr[i][1]==arr[next][1]) continue;
        else if(arr[i][1]<arr[next][1])
        {
            newn=newnode(arr[i][1],arr[next][1],arr[i][0],arr[next][0]);
            headpos=arr[i][1]-gminy;
        }
        else
        {
            newn=newnode(arr[next][1],arr[i][1],arr[next][0],arr[i][0]);
            headpos=arr[next][1]-gminy;
        }
        temp1=head=elist[headpos];
        if(head==NULL) elist[headpos]=newn;
        else if(head->x>newn->x || (head->x==newn->x && ((newn->m>0 && head->m>0 && head->m>newn->m)||(newn->m<0 && head->m>0)||(head->m<0 && newn->m<0 && newn->m<head->m))))
        //else if(head->x>newn->x || (head->x==newn->x && newn->ymax<head->ymax))
        {
            elist[headpos]=newn;
            newn->next=head;
        }
        else
        {
            while(head!=NULL && (head->x<newn->x || (head->x==newn->x && ((newn->m>0 && head->m>0 && head->m<newn->m)||(newn->m>0 && head->m<0)||(head->m<0 && newn->m<0 && newn->m>head->m)))))
            {
                temp1=head;
                head=head->next;
            }
            temp1->next=newn;
            newn->next=head;
        }
    }

    for(i=0;i<scan;i++)
    {
        printf("%d => ",i);
        pri(elist[i]);
    }
    //return 0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize((int) width, (int) height);
    wd = glutCreateWindow("Output Primitives");
    glutReshapeFunc(reshape);
    glutDisplayFunc(maindisp);
    glutMainLoop();
    return 0;
}
