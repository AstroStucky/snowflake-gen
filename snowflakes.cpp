#include <iostream>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
 
#include "HexGrid.h"

static const bool DEBUG = true;

void show_usage(void) {
	std::cout<<"./snowflakes "<<std::endl;
}

void display() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
 
   // Draw a Red 1x1 Square centered at origin
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.5f, -0.5f);    // x, y
      glVertex2f( 0.5f, -0.5f);
      glVertex2f( 0.5f,  0.5f);
      glVertex2f(-0.5f,  0.5f);
   glEnd();
 
   glFlush();  // Render now
}


int main(int argc, char* argv[]) {
	float init_condition = 1.0;

	HexGrid grid(init_condition);	

	if (DEBUG) grid.print();

	for (int i = 0; i < 100; i++ ) {
		// Record start time
		auto start = std::chrono::high_resolution_clock::now();
		grid.process_all();
		// Record end time
		auto end = std::chrono::high_resolution_clock::now();
		if (DEBUG) grid.print();
		std::chrono::duration<double> elapsed = end - start;
		if (DEBUG) std::cout<<"Elapsed time: "<<elapsed.count()<<"s"<<std::endl;
	}
	
   //// Visualize snowflake in hexgrid using OpenGL
   // initialize glut window
   glutInit(&argc, argv);
   glutCreateWindow("Snowflake Generation");
   glutInitWindowSize(1000, 1000);
   glutInitWindowPosition(50, 50);

   // display snowflake visualizaiton
   glutDisplayFunc(display);
   glutMainLoop();


	return 0;

}