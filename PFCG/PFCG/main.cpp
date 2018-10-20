//Semestre 2019 - 1
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************		Carlos Alberto Basilio Torres		******//
//*************											******//
//*************		Luis Enrique Vite Aquino			******//
//************************************************************//
//************************************************************//

#include "camara.h";
#include "figuras.h";
#include "texturas.h";

CCamera objCamera;
GLfloat g_lookupdown = 0.0f;

int font = (int)GLUT_BITMAP_HELVETICA_18;

GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 27.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

//Declaracion de figuras
CFiguras sky;
CFiguras suelo;
CFiguras fig1;
//Declaracion de texturas
CTexture text1;
CTexture text2;

CTexture pasto;
CTexture madera;
CTexture metal_1;

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	/* setup blending */
	glEnable(GL_BLEND);			// Turn Blending On

	//Inicializacion de texturas
	text1.LoadBMP("Texturas/Ambiente/cielo.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("Texturas/Ambiente/piso.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	pasto.LoadBMP("Texturas/Jardines/pasto.bmp");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	madera.LoadBMP("Texturas/Jardines/madera.bmp");
	madera.BuildGLTexture();
	madera.ReleaseImage();

	metal_1.LoadBMP("Texturas/Edificio/metal_1.bmp");
	metal_1.BuildGLTexture();
	metal_1.ReleaseImage();
	//Carga de Figuras



	objCamera.Position_Camera(10, 50, 800, 10, 2.5f, 10, 0, 1, 0);
}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
	//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glPushMatrix();
		glRotatef(g_lookupdown, 1.0f, 0, 0);
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z, objCamera.mView.x, objCamera.mView.y, objCamera.mView.z, objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

		glPushMatrix(); //Creamos cielo
			glDisable(GL_LIGHTING);
			//glTranslatef(0, 60, 0);
			//fig1.skybox(130.0, 130.0, 130.0, text1.GLindex);
			glTranslatef(0, 1000, 0);
			sky.skybox(3000.0, 2000.0, 3000.0, text1.GLindex);
			glEnable(GL_LIGHTING);
		glPopMatrix();

		//Creamos el suelo
		glTranslatef(0, 0.1, 0);//hay que tener cuidado con este valor, todo lo que se dibuje estara localizado despues de este
		glPushMatrix();//debido al suelo es que se tuvo que establecer el valor anterior
			glScalef(3000.0, 0.1, 3000.0);
			glDisable(GL_LIGHTING);
			suelo.prisma3(text2.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();


		//Base del edificio
		glPushMatrix();
			glTranslatef(0, 25, -150);
			glScalef(400.0, 50, 300.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 25, 200);
			glScalef(400.0, 50, 400.0);
			fig1.prisma2(0, 0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-600, 25, 0);
			glScalef(800.0, 50, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 25, 0);
			glScalef(800.0, 50, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		//Edificio parte Central
		glPushMatrix();
			glTranslatef(0, 175, 150);
			glScalef(400.0, 250, 500.0);
			fig1.prisma2(0,0);
		glPopMatrix();

		//parte de arriba de parte central
		glPushMatrix();
			glTranslatef(0, 325, 2.5);
			glScalef(400.0, 50, 5.0);
			fig1.prisma2(0, 0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 325, 397.5);
			glScalef(400.0, 50, 5.0);
			fig1.prisma2(0, 0);
		glPopMatrix();
		
		
		//Planta baja
		glPushMatrix();
			glTranslatef(-600, 200, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 200, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		//Primera planta
		glPushMatrix();
			glTranslatef(-600, 500, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 500, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		//Segunda planta
		glPushMatrix();
			glTranslatef(-600, 800, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 800, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();
		//Tercera planta
		glPushMatrix();
			glTranslatef(-600, 1100, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 1100, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();
		//Cuarta planta
		glPushMatrix();
			glTranslatef(-600, 1400, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(600, 1400, 0);
			glScalef(800.0, 300, 800.0);
			fig1.prisma2(0, 0);
		glPopMatrix();

		//Edifico parte delantera
		glPushMatrix();
			glTranslatef(0, 115, 800);
			glScalef(200.0, 230, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 240, 800);
			glScalef(200.0, 20, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-150, 25, 800);
			glScalef(100.0, 50, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-150, 150, 800);
			glScalef(100.0, 200, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(150, 25, 800);
			glScalef(100.0, 50, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(150, 150, 800);
			glScalef(100.0, 200, 0.1);
			fig1.prisma2(0, 0);
		glPopMatrix();


		//Barras oscuras de parte delantera
		glPushMatrix();
			glTranslatef(-99.5, 125, 799.75);
			glScalef(1, 250, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(99.5, 125, 799.75);
			glScalef(1, 250, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 229.5, 799.75);
			glScalef(200, 1, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 249.5, 799.75);
			glScalef(400, 1, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(150, 49.5, 799.75);
			glScalef(100.0, 1, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-150, 49.5, 799.75);
			glScalef(100.0, 1, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(199.5, 125, 799.75);
			glScalef(1, 250, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-199.5, 125, 799.75);
			glScalef(1, 250, 1);
			fig1.prisma2(metal_1.GLindex, metal_1.GLindex);
		glPopMatrix();


		//escaleras parte delantera
		glPushMatrix();
			glTranslatef(0, 5, 425);
			glPushMatrix();
				glTranslatef(0, 10, -5);
				glPushMatrix();
					glTranslatef(0, 10, -5);
					glPushMatrix();
						glTranslatef(0, 10, -5);
						glPushMatrix();
							glTranslatef(0, 10, -5);
							glScalef(200.0, 10, 10.0);
							fig1.prisma2(0, 0);
						glPopMatrix();
						glScalef(200.0, 10, 20.0);
						fig1.prisma2(0, 0);
					glPopMatrix();
					glScalef(200.0, 10, 30.0);
					fig1.prisma2(0, 0);
				glPopMatrix();
				glScalef(200.0, 10, 40.0);
				fig1.prisma2(0, 0);
			glPopMatrix();
			glScalef(200.0, 10, 50.0);
			fig1.prisma2(0, 0);
		glPopMatrix();






		//escaleras parte trasera
		glPushMatrix();
			glTranslatef(0, 5, -350);
			glPushMatrix();
				glTranslatef(0, 10, 5);
				glPushMatrix();
					glTranslatef(0, 10, 5);
					glPushMatrix();
						glTranslatef(0, 10, 5);
						glPushMatrix();
							glTranslatef(0, 10, 5);
							glScalef(400.0, 10, 60.0);
							fig1.prisma2(0, 0);
						glPopMatrix();
						glScalef(400.0, 10, 70.0);
						fig1.prisma2(0, 0);
					glPopMatrix();
					glScalef(400.0, 10, 80.0);
					fig1.prisma2(0, 0);
				glPopMatrix();
				glScalef(400.0, 10, 90.0);
				fig1.prisma2(0, 0);
			glPopMatrix();
			glScalef(400.0, 10, 100.0);
			fig1.prisma2(0, 0);
		glPopMatrix();






	glPopMatrix();



	/*glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-12, 12.0, -14.0, (void *)font, "Practica 10");
	pintaTexto(-12, 10.5, -14, (void *)font, "Poner algo en Movimiento");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);*/

	glutSwapBuffers();
}

void animacion()//Declaramos animaciones
{
	glutPostRedisplay();
}

void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 5000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W':
		objCamera.Move_Camera(CAMERASPEED + 0.01);
		break;

	case 's':
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.01));
		break;

	case 'a':
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.01));
		break;

	case 'd':
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.01);
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED+1);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED-1);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)   // Main Function
{
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0, 0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	glutIdleFunc(animacion);
	glutMainLoop();          // 

	return 0;
}
