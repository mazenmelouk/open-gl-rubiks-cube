//////////////////////////////////////////////////////////////////////////////
//
//  --- Angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_H__
#define __ANGEL_H__

//----------------------------------------------------------------------------
//
// --- Include system headers ---
//

#include <cmath>
#include <iostream>
#include <stdio.h>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846f
#endif

//----------------------------------------------------------------------------
//
// --- Include OpenGL header files and helpers ---
//
//   The location of these files vary by operating system.  We've included
//     copies of open-soruce project headers in the "GL" directory local
//     this this "include" directory.
//

#ifdef __APPLE__  // include Mac OS X verions of headers
#  include <OpenGL/OpenGL.h>
#  include <GLUT/glut.h>
#else // non-Mac OS X operating systems
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/freeglut_ext.h>
#endif  // __APPLE__

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Include our class libraries and constants ---
//

namespace Angel {

//  Helper function to load vertex and fragment shader files
GLuint InitShader( const char* vertexShaderFile,
		   const char* fragmentShaderFile /*,
		   const char* geometryShaderFile,
		   const char* tesselationControlShaderFile,
		   const char* tesselationEvaluationShaderFile*/);

//  Defined constant for when numbers are too small to be used in the
//    denominator of a division operation.  This is only used if the
//    DEBUG macro is defined.
const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant
const GLfloat  DegreesToRadians = M_PI / 180.0f;

}  // namespace Angel

#include "vec.h"
#include "mat.h"
#include "CheckError.h"

#define Print(x)  do { std::cerr << #x " = " << (x) << std::endl; } while(0)

//  Globally use our namespace in our example programs.
using namespace Angel;

typedef vec3 color3;
typedef vec4 color4;
typedef vec4 point4;

#endif // __ANGEL_H__