## Header files

``` c++
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h> // in some versions of opengl the headers 
                    //above are not present so best to include them anyways
```

## Entry point to the program

``` c++
void display()  {}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    // glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200, 100);               // specify window position
    glutInitWindowSize(500, 500);                   // width and height of window in px

    glutCreateWindow("Demo");                       // create the window
    glutDisplayFunc(display);
    
    glutMainLoop();
}
```        

This section defines the main function, which serves as the entry point of any C/C++ program using the OpenGL Utility Toolkit (GLUT). It sets up the environment and creates the main window for rendering.    

### Function: ``` int main(int argc, char **argv) ```
The main function is responsible for initialising GLUT, configuring the display mode, setting window properties, registering the display callback, and starting the main event loop.    
``` c++
glutInit(&argc, argv);
```
Initialises the GLUT library. This must be the first GLUT call in any program. It processes any command-line arguments intended for GLUT.      
``` c++
glutInitDisplayMode(GLUT_RGB);
```   
Specifies the display mode for the window.
* ```GLUT_RGB``` indicates the use of an RGB colour model.
* The commented ```GLUT_DOUBLE``` (if enabled) would turn on double buffering to prevent flickering during animations.    
  
``` c++
glutInitWindowPosition(200, 100);
```   
Sets the initial position of the window on the screen, with the top-left corner placed at coordinates (200, 100).      

``` c++
glutInitWindowSize(500, 500);
```   
Defines the width and height of the window in pixels.

``` c++
glutCreateWindow("Demo");
```   
Creates a window with the specified title ("Demo") and makes it the current window.

``` c++
glutDisplayFunc(display);
```   
Registers the display function as the callback for rendering the window contents. GLUT will call this function whenever the window needs to be redrawn.

``` c++
glutMainLoop();
```  
Starts the GLUT event processing loop. This function never returns and keeps the application running, responding to user input and redrawing as needed.

<br>

## The GLUT library
All the functions in the glut library have prefix 'glut' such as 'glutInit()'.    
__glutInit()__ function requires command line arguments to be passed:
``` c++
    glutInit(&argc, argv);
```
