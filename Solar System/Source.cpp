//Include necessary header files
#include "glut.h"
#include <cstdlib>

//Link with necessary libraries.
//This needs to be written in at least one .cpp file in the project
#pragma comment (lib, "glut32.lib")

void render(void);
void KeyPress(unsigned char key, int x, int y);
void SpecialKeys(int key, int x, int y);
void ChangeWindow(GLsizei w, GLsizei h);

#define ESC_ASCII 27
int g_Win;
int g_LastTime;
GLfloat g_theta;
int theta_c[4] = {8, 5, 7, 3};
GLfloat AmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat DiffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat SpecularLight[] = { 5.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecRef[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat LightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };
GLubyte Shine = 128;
GLfloat Px, Py, Pz = 20;

void ChangeWindow(GLsizei w, GLsizei h){
	GLfloat Ratio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	Ratio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, Ratio, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(Px, Py, Pz, Px, Py, 0, 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}
void Init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_SHADE_MODEL);
	glShadeModel(GL_SMOOTH);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
}

void KeyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
		Py += 0.1f;
		break;
	case 'S':
		Py -= 0.1f;
		break;

	case 'A':
		Px -= 0.1f;
		break;

	case 'D':
		Px += 0.1f;
		break;

	case 'w':
		Py += 0.1f;
		break;
	case 's':
		Py -= 0.1f;
		break;

	case 'a':
		Px -= 0.1f;
		break;

	case 'd':
		Px += 0.1f;
		break;
	
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}
void SpecialKeys(int key, int x, int y){
	if (key == GLUT_KEY_UP)
	{
		Pz += 5.0f;
	}


	if (key == GLUT_KEY_DOWN)
	{
		Pz -= 5.0f;
	}
	glutPostRedisplay();
}
void onFrame()
{
	int time = glutGet(GLUT_ELAPSED_TIME);
	g_theta += 0.01f * (time - g_LastTime);

	g_LastTime = time;
	glutPostRedisplay();
}
void animate(void){
	g_theta += ((double)rand() / (RAND_MAX)) + 1;
	
}

void drawPlanet(GLdouble radius, GLint slices, GLint stacks, GLfloat red, GLfloat green, GLfloat blue, GLfloat tX, GLfloat tY, GLfloat tZ, GLint theta_c){
	
		glPushMatrix();
		glRotatef(g_theta * theta_c, 0.0f, 1.0f, 0.0f);
		glTranslatef(tX, tY, tZ);
		glColor3f(red, green, blue);
		glutSolidSphere(radius, slices, stacks);
		glPopMatrix();
		glutPostRedisplay();
}

void render(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(Px, Py, Pz, Px, Py, 0, 0, 1, 0);
	//Draw the Sun
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3f(255.0, 255.0, 0.0);
	glutSolidSphere(2.0, 20.0, 20.0);
	glPopMatrix();

	//Draw Mercury
	drawPlanet(2.0, 20.0, 20.0, 255.0, 0.0, 0.0, 15.0, 0.0, 0.0, theta_c[1]);

	//Draw Venus
	drawPlanet(0.6, 20.0, 20.0, 0.0, 255.0, 0.0, -10.5, 0.0, 0.0, theta_c[2]);
	
	//Draw Earth independently since the moon rotates around it
	glRotatef(g_theta * theta_c[3], 0.0f, 1.0f, 0.0f);
	glTranslatef(-5.5, 0.0, 0.0);
	glPushMatrix();
	glColor3f(0.0, 0.0, 255.0);
	glutSolidSphere(0.5, 20.0, 20.0);
	glPopMatrix();

	//Draw the Moon
	glPushMatrix();
	glRotatef(g_theta * 8, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.9, 0.0, 0.0);
	glColor3f(255.0, 255.0, 255.0);
	glutSolidSphere(0.3, 20.0, 20.0);
	glPopMatrix();

	//Draw Mars
	drawPlanet(1.0, 20.0, 20.0, 0.0, 255.0, 255.0, 8.0, 0.0, 0.0, theta_c[0]);

	glutSwapBuffers();
}
void main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	g_Win = glutCreateWindow("Solar System");
	Init();
	glutReshapeFunc(ChangeWindow);
	glutKeyboardFunc(KeyPress);                        
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(render);
	glutIdleFunc(onFrame);
	glutMainLoop();
}
