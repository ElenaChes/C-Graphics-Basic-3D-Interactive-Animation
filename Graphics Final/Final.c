/*
* @author Elena Chestnov
*/

#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
GLUquadricObj *t;
int submenu1, submenu2;
int xo=0;
int xn = 0;
int rl = 0; //rotation flag left
int rr = 0; //rotation flag right
int temp;
int l = 0;
int walk = 0; //walking flag
int walk_start;
int left = 0; //left leg moving
int right = 0; //right leg moving
int stand = 0; //standing flag
int start = 1; //not started walking flag
int flipped = 0; //screen is flipped
float h_body = 0; //height of snowman
float lh_legs = 0; //height of left knee
float rh_legs = 0; //height of right knee
float lz_legs = 0; //z of left knee
float rz_legs = 0; //z of right knee
float x = 1;
float y = 1;
float z = 1;
float d = 0; //depth
int la = 50; //left leg angle a=50
int ra = 50; //right leg angle a=50
int alfa = 0; //rotation angle
void init(void)
{
	GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };
	float fogColor[4] = { 0.53, 0.85, 1, 0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, fogColor);

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_START, 6.0);
	glFogf(GL_FOG_END, 9);
	glFogf(GL_FOG_DENSITY, 0.8);
	glClearColor(0.53, 0.85, 1, 0.0);
	t = gluNewQuadric();
	gluQuadricDrawStyle(t, GLU_FILL);
}
void sphere(float s,float x, float y, float z,float r,float g,float b) //all spheres
{
	GLfloat mat_ambient[] = { r, g, b,1 };
	GLfloat mat_diffuse[] = { r, g, b,1 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat mat_emission[] = { r-0.5,g- 0.5, b-0.5, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glPushMatrix();
	glTranslated(x,y,z);
	glutSolidSphere(s, 30, 30);
	glPopMatrix();
}
void cube(void) //floor
{
	GLfloat mat_ambient[] = { 0.05, 0.15, 0.05,1 };
	GLfloat mat_diffuse[] = { 0.05, 0.15, 0.05,1 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { 1 - 0.5,1 - 0.5, 1 - 0.5, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glPushMatrix();
	glTranslated(0, -19, -13);
	glRotatef(45, 1, 0, 0);
	glutSolidCube(40);
	glPopMatrix();
}
void limb(float s,float x, float y, float z, float r, float g, float b,int side,float a) //legs
{
	GLfloat mat_ambient[] = { r, g, b,1 };
	GLfloat mat_diffuse[] = { r, g, b,1 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat mat_emission[] = { r - 0.5,g - 0.5, b - 0.5, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glPushMatrix();
	glTranslated(-x*side, y-s, z);
	glRotatef(-5*side, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glRotatef(-a, 1, 0, 0);
	sphere(0.3, 0, 0, 0, r, g, b);
	gluCylinder(t, 0.2, 0.2, s, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-x*side, y - s, z);
	glRotatef(5 * side, 0, 1, 0);
	glRotatef(a, 1, 0, 0);
	glRotatef(-90, -1, 0, 0);
	gluCylinder(t, 0.2, 0.2, s, 10, 10);
	glPopMatrix();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (x > 0.4) {
		glPushMatrix();
		glScalef(x, y, z);

		glRotatef(20, 1, 0, 0);
		if (alfa == 360 || alfa == -360)
			alfa = 0;
		glRotatef(alfa, 0, 1, 0);
		glTranslatef(0, h_body, 0);
		glTranslatef(0, -d *2.5, d*2);
		//---------------------Body-------------------------
		sphere(2.2, 0, 6.5, 0, 0.9, 0.9, 1.0);
		sphere(2.9, 0, 2.8, 0, 0.9, 0.9, 1.0);
		sphere(3.5, 0, -1.5, 0, 0.9, 0.9, 1.0);
		//---------------------Face-------------------------
		sphere(0.3, -0.8, 7.7, 1.7, 0.1, 0.1, 0);
		sphere(0.3, 0.8, 7.7, 1.7, 0.1, 0.1, 0);
		glTranslatef(0, -h_body + 8, 0);

		glTranslatef(0, 0, 0);
		//---------------------limbs-------------------------
		limb(3, 1, -6.8 + lh_legs, 2 - lz_legs, 0.1, 0.1, 0, 1, la);
		limb(3, 1, -6.8 + rh_legs, 2 - rz_legs, 0.1, 0.1, 0, -1, ra);
		glPopMatrix();
	}
	//-------------------Background----------------------
	cube();
	glFlush();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 20, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glutReshapeWindow(500, 750);
}

void rotation()
{
	if (rr == 1&&walk==0) {
		alfa += 3;
		glutPostRedisplay();
		glutTimerFunc(80, rotation, 0);
	}
	if (rl == 1 && walk == 0) {
		alfa -= 3;
		glutPostRedisplay();
		glutTimerFunc(80, rotation, 0);
	}
	if (alfa == 360 || alfa == -360)
		alfa = 0;
}
void reset_rotation() {
	if (alfa < 0) {  //rotation to face forward
		alfa++;
		glutPostRedisplay();
		glutTimerFunc(20, reset_rotation, 0);
	}
	if (alfa > 0) {  //rotation to face forward
		alfa--;
		glutPostRedisplay();
		glutTimerFunc(20, reset_rotation, 0);
	}
	if (alfa == 360 || alfa == -360)
		alfa = 0;
}
void walking()
{
	if (walk == 1) {
	start_walk:
		if (right == 1) {
			if (lh_legs < 2.5) { //raising left leg, lowering right leg
				ra--;
				la++;
				rh_legs -= 0.025;
				lh_legs += 0.025;
				rz_legs += lh_legs / 100;
				lz_legs -= rh_legs / 100;
				h_body += 0.01;
				if (l == 1) {
					x = y = z -= 0.001;
					d -= 0.02;
				}
			}
			else {
				right = 0;
				left = 1;
			}
		}
		else if (left == 1) {
			if (rh_legs < 2.5) { //raising right leg, lowering left leg
				la--;
				ra++;
				lh_legs -= 0.025;
				rh_legs += 0.025;
				lz_legs += lh_legs / 100;
				rz_legs -= rh_legs / 100;
				h_body -= 0.01;
				if (l == 1) {
					x = y = z -= 0.001;
					d -= 0.01;
				}
			}
			else {
				left = 0;
				right = 1;
			}
		}
		else if (start == 1) {
			if (lh_legs < 2.5) { //raising first leg
				la++;
				lh_legs += 0.025;
				lz_legs -= lh_legs / 100;
				h_body += 0.01;
			}
			else {
				left = 1;
				start = 0;
			}
		}

		if (alfa < 90 && stand == 1 && l == 0) //rotation to face right
			alfa = alfa + 3;
		if (alfa > 90 && stand == 1 && l == 0) //rotation to face left
			alfa = alfa - 3;
	}
	glutPostRedisplay();
	glutTimerFunc(10, walking, 0);


}
void up()//stand up
{
	if (h_body < 6) {
		h_body = h_body + 0.2;
		lh_legs = rh_legs = lh_legs + 0.05;
		lz_legs = rz_legs = lz_legs + lh_legs / 25;
		la = ra = la - 1;
		glutPostRedisplay();
		glutTimerFunc(80, up, 0);
	}
	else {
		stand = 1;
		if (walk_start == 1) {
			walk = 1;
			glutTimerFunc(10, walking, 0);
		}
	}
}
void down()//sit
{
	if (h_body > 0) {
		h_body = h_body - 0.2;
	if (lh_legs>0)
		lh_legs =  lh_legs - 0.05;
	if (rh_legs>0)
		rh_legs = rh_legs - 0.05;
	if (rz_legs>0)
		 rz_legs = rz_legs - rh_legs / 25;
	if (lz_legs>0)
		lz_legs = lz_legs - lh_legs / 25;
	if (ra<50)
		ra++;
	if (la<50)
		la++;

		glutPostRedisplay();
		glutTimerFunc(80, down, 0);
	}
	else {
		if (flipped == 1) {  //flipping back screen if flipped
			glScalef(-1.0, 1.0, 1.0);
			flipped = 0;
		}
	}
}

void DragFunc(int xx, int yy) {
	int i;
	if (xx < xo) {
		if (flipped == 0)
			alfa = alfa - 3;
		else
			alfa = alfa + 3;
	}
	else {
		if (flipped == 0)
			alfa = alfa + 3;
		else
			alfa = alfa - 3;
	}
	glutPostRedisplay();
	xo = xx;
}
void MouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
			glutMotionFunc(DragFunc);	
}	
void select1(int what)
{
	switch (what)
	{
	case 1:
		if (flipped == 0) {
			rr = 1;
			rl = 0;
		}
		else
		{
			rl = 1;
			rr = 0;
		}
		glutTimerFunc(80, rotation, 0);
		break;
	case 2:
		if (flipped == 1) {
			rr = 1;
			rl = 0;
		}
		else
		{
			rl = 1;
			rr = 0;
		}
		glutTimerFunc(80, rotation, 0);
		break;
	case 3:
		rr = rl= 0;
		break;
	}
}
void select2(int what)
{
	switch (what)
	{
	case 1: //walk left
		glScalef(-1.0, 1.0, 1.0); //flipping screen to walk left
		flipped = 1;
		rr = rl = 0;
		walk_start = 1;
		if (start == 1) {
			glutTimerFunc(100, up, 0);
		}
		break;
	case 2: //walk right
		if (flipped == 1) {  //flipping back screen if flipped
			glScalef(-1.0, 1.0, 1.0);
			flipped = 0;
		}
		rr = rl = 0;
		walk_start = 1;
		if (start == 1)
			glutTimerFunc(100, up, 0);
		break;
	}
}
void main_menu(int value)
{
	switch (value) {
	case 1:
		up();
		break;
	case 2:	// reset
		if (l == 1)
			alfa = 0;
		right = left = walk =walk_start= stand = 0;
		start = 1; //not walking yet
		rr = rl = 0; //rotation flag
		l =d= 0;
		x = y = z = 1;
		down();
		reset_rotation();
		break;
	case 3: //leave
		alfa = 180;
		l = 1;
		if (start == 1) {
			walk_start = 1;
			glutTimerFunc(100, up, 0);
		}
		break;
	case 4: exit(0);break;
		break;
	}
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 750);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutMouseFunc(MouseFunc);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	submenu1 = glutCreateMenu(select1);
		glutAddMenuEntry("Right", 1);
		glutAddMenuEntry("Left", 2);
		glutAddMenuEntry("Stop", 3);

	submenu2 = glutCreateMenu(select2);
		glutAddMenuEntry("Left", 1);
		glutAddMenuEntry("Right", 2);

	glutCreateMenu(main_menu);

	glutAddMenuEntry("Stand up", 1);
	glutAddSubMenu("Rotate", submenu1);
	glutAddSubMenu("Walk", submenu2);
	glutAddMenuEntry("Reset", 2);
	glutAddMenuEntry("Leave", 3);
	glutAddMenuEntry("Quit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
	return 0;
}