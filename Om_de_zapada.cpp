
/*
Programul afiseaza un om de zapada
*/
#include "glos.h"
#include <GL/glaux.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>
void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);
void CALLBACK rot_z_up(void);
void CALLBACK rot_z_down(void);
void CALLBACK Scale_up(void);
void CALLBACK Scale_down(void);
void CALLBACK rotate_left(void);
void CALLBACK rotate_right(void);

static GLfloat x = 0;
static GLfloat y = 0;
static GLfloat z = 0;
static GLfloat x_s = 1;
static GLfloat y_s = 1;
static GLfloat z_s = 1;
static GLfloat alfa = 270;
static GLfloat beta = 0; 

GLUquadricObj* qobj;

GLfloat ctrlpoints[4][3] = {
    { -40.0, -40.0, 0.0}, { -24.0, 40.0, 0.0},
    {24.0, -40.0, 0.0}, {40.0, 40.0, 0.0} };

void CALLBACK MutaStanga(void)
{
    x = x - 10;
}

void CALLBACK MutaDreapta(void)
{
    x = x + 10;
}

void CALLBACK MutaSus(void)
{
    z = z + 10;
}

void CALLBACK MutaJos(void)
{
    z = z - 10;
}

void CALLBACK rot_z_up(void)
{
    alfa = alfa + 30;
}

void CALLBACK rot_z_down(void) {
    alfa = alfa - 30;
}

void CALLBACK rotate_left(void)
{
    beta = beta + 30;
}

void CALLBACK rotate_right(void) {
    beta = beta - 30;
}


void CALLBACK Scale_up(void)
{
    x_s = x_s + 0.2;
    y_s = y_s + 0.2;
    z_s = z_s + 0.2;

}
void CALLBACK Scale_down(void)
{
    x_s = x_s - 0.2;
    y_s = y_s - 0.2;
    z_s = z_s - 0.2;
}


void myinit(void) {
    glClearColor(0.5, 0.5, 0.5, 1.0);

    // coeficientii de reflexie pentru reflexia ambientala 
    // si cea difuza sunt cei impliciti
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    /*  rflectanta speculara si exponentul de reflexie speculara
        nu sunt la valorile implicite (0.0)   */
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    //setãri pentru sursa de luminã
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };//intensitatea componentei ambientale din sursa 0 este nula
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//intensitatea componentei difuze din sursa 0 este maxima pentru fiecrae compopnenta de culoare
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//intensitatea componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de culoare

    GLfloat light_position[] = { 1.0, 1.0, 0.0, 0.0 };
    //sursa de lumina pe axa x la infinit
    GLfloat global_ambient[] = { 0.75, 0.75, 0.75, 1.0 };


    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    //glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    //lumina ambientala in scena

    //glFrontFace(GL_CW);//orientarea implicit[ a vârfurilor în sensul rotirii acelor
    glEnable(GL_LIGHTING); //activare iluminare
    glEnable(GL_LIGHT0); //activare sursa 0

    glEnable(GL_AUTO_NORMAL); //activare calculare normale daca vârfurile 
    //s-au determinat cu GL_MAP2_VERTEX_3 sau GL_MAP2_VERTEX_4
    glEnable(GL_NORMALIZE); //activare normalizare (vectori unitari) vectori
    
    glDepthFunc(GL_LESS); //comparaþia la ascunderea suprafeþelor
    glEnable(GL_DEPTH_TEST); //activare test adâncime

    glEnable(GL_COLOR_MATERIAL); // se activeaza setarea culorilor prin glColor()
 
    // Curba bezier
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);	//se valideaza un anumit tip de evaluare
    //glShadeModel(GL_FLAT); 	//umbrire constanta pe poligoane
    glLineStipple(1, 0x0F0F);

}

void CALLBACK display(void)
{
    GLfloat low_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat more_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat most_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_eyes[] = { 0.2, 0.0, 0.9, 1.0 };
    GLfloat mat_std_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    qobj = gluNewQuadric();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(alfa, 1, 0, 0);
    glTranslatef(x, y, z);
    glScalef(x_s, y_s, z_s);

    glTranslatef(50, 0, 0);
    glRotatef(beta, 0, 0, 1);
    //glTranslatef(-50, 0, 0); //Daca nu este comentata figura se roteste in jurul axei z (y) 

    //glColor3f(0.0, 0.0, 0.0);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, more_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_eyes);

    //Ochi dreapta
    glPushMatrix();
        glColor3f(0, 0, 1);
        glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(10, 150, 20);
        gluDisk(qobj, 2, 4, 20, 20);
    glPopMatrix();

    //Ochi stanga
    glPushMatrix();
        glColor3f(0, 0, 1);
        glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(-10, 150, 20);
        gluDisk(qobj, 2, 4, 20, 20);
    glPopMatrix();

    //nasturi

    // primul de sus
    glMaterialfv(GL_FRONT, GL_AMBIENT, low_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_std_diffuse);
    glColor3f(0.0, 0.0, 0.0); //black 
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.0, 110.0, 40.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();
    glPopMatrix();

    //al 2-lea de sus
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.0, 70.0, 40.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();
    glPopMatrix();

    // al 2-lea de jos
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.0, 20.0, 50.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();
    glPopMatrix();

    // 1 de jos
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0.0, -20.0, 50.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(0.0, 0.0);
    glEnd();
    glPopMatrix();

    //Corp
    glMaterialfv(GL_FRONT, GL_AMBIENT, low_ambient);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glPushMatrix();
    glColor4f(1.0,1.0,1.0, 0.3);
        auxSolidSphere(50);
    glPopMatrix();

    glTranslatef(0.0,0.0,90.0);
    glPushMatrix();
        auxSolidSphere(40);
    glPopMatrix();
    
    glTranslatef(0.0, 0.0,60.0);
    glPushMatrix();
        auxSolidSphere(20);
    glPopMatrix();

    
    //Con -Palarie
    glPushMatrix();
    glColor3f(0.0,0.0,0.8);
        glTranslatef(0.0, 0.0, 10.0);
        gluCylinder(qobj, 30, 0, 50, 20, 20);
    glPopMatrix();


    //Brate
    glPushMatrix();
    glColor3f(0.36, 0.168, 0.137);
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(80,-30,0);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);		//se deseneaza curba prin segmente de dreapta
    for (int i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0); //pentru cele 30 varfuri determinate de 
                                // functia glEvalCoord1f
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.36, 0.168, 0.137);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glTranslatef(-80, 30, 0);
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);		//se deseneaza curba prin segmente de dreapta
    for (int i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0); //pentru cele 30 varfuri determinate de 
                                // functia glEvalCoord1f
    glEnd();
    glPopMatrix();

    auxSwapBuffers();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-320.0, 320.0, 320.0 * (GLfloat)h / (GLfloat)w,
            -320.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
    else
        glOrtho(-320.0 * (GLfloat)w / (GLfloat)h,
            320.0 * (GLfloat)w / (GLfloat)h, -320.0, 320.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH16);
    //auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);

    auxInitPosition(500, 0, 600, 500);
    auxInitWindow("Om de zapada");
    myinit();
    auxKeyFunc(AUX_LEFT, MutaStanga);
    auxKeyFunc(AUX_RIGHT, MutaDreapta);
    auxKeyFunc(AUX_UP, MutaSus);
    auxKeyFunc(AUX_DOWN, MutaJos);
    auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
    auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);
    auxKeyFunc(AUX_1, Scale_up);
    auxKeyFunc(AUX_2, Scale_down);
    auxKeyFunc(AUX_3, rotate_left);
    auxKeyFunc(AUX_4, rotate_right);


    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return(0);
}