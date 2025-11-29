#pragma once


#ifdef __linux__
#include <GL/glx.h>

inline PFNGLGENERATEMIPMAPPROC glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glXGetProcAddress((const GLubyte*)"glGenerateMipmap");
inline PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glXGetProcAddress((const GLubyte*)"glGenVertexArrays");
inline PFNGLGENBUFFERSPROC glGenBuffers= (PFNGLGENBUFFERSPROC)glXGetProcAddress((const GLubyte*)"glGenBuffers");
inline PFNGLBINDVERTEXARRAYPROC glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glXGetProcAddress((const GLubyte*)"glBindVertexArray");
inline PFNGLBINDBUFFERPROC glBindBuffer = (PFNGLBINDBUFFERPROC)glXGetProcAddress((const GLubyte*)"glBindBuffer");
inline 

PFNGLBUFFERDATAPROC glBufferData = (PFNGLBUFFERDATAPROC)glXGetProcAddress((const GLubyte*)"glBufferData");
inline PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glXGetProcAddress((const GLubyte*)"glVertexAttribPointer");
inline PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glXGetProcAddress((const GLubyte*)"glEnableVertexAttribArray");
inline PFNGLDELETEBUFFERSPROC glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glXGetProcAddress((const GLubyte*)"glDeleteBuffers");
inline PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glXGetProcAddress((const GLubyte*)"glDeleteVertexArrays");
inline PFNGLCREATESHADERPROC   glCreateShader = (PFNGLCREATESHADERPROC) glXGetProcAddress((const GLubyte*)"glCreateShader");
inline PFNGLSHADERSOURCEPROC   glShaderSource = (PFNGLSHADERSOURCEPROC) glXGetProcAddress((const GLubyte*)"glShaderSource");
inline PFNGLCOMPILESHADERPROC    glCompileShader = (PFNGLCOMPILESHADERPROC) glXGetProcAddress((const GLubyte*)"glCompileShader");
inline PFNGLCREATEPROGRAMPROC   glCreateProgram = (PFNGLCREATEPROGRAMPROC) glXGetProcAddress((const GLubyte*)"glCreateProgram");
inline PFNGLATTACHSHADERPROC    glAttachShader = (PFNGLATTACHSHADERPROC) glXGetProcAddress((const GLubyte*)"glAttachShader");
inline PFNGLLINKPROGRAMPROC   glLinkProgram = (PFNGLLINKPROGRAMPROC) glXGetProcAddress((const GLubyte*)"glLinkProgram");
inline PFNGLUSEPROGRAMPROC   glUseProgram = (PFNGLUSEPROGRAMPROC) glXGetProcAddress((const GLubyte*)"glUseProgram");
inline PFNGLGETUNIFORMLOCATIONPROC    glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC) glXGetProcAddress((const GLubyte*)"glGetUniformLocation");
inline PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC) glXGetProcAddress((const GLubyte*)"glUniformMatrix4fv");
inline PFNGLGETATTRIBLOCATIONPROC   glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC) glXGetProcAddress((const GLubyte*)"glGetAttribLocation");
inline PFNGLBINDATTRIBLOCATIONPROC    glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC) glXGetProcAddress((const GLubyte*)"glBindAttribLocation");
inline 
PFNGLDELETESHADERPROC   glDeleteShader = (PFNGLDELETESHADERPROC) glXGetProcAddress((const GLubyte*)"glDeleteShader");
inline PFNGLGETSHADERIVPROC    glGetShaderiv = (PFNGLGETSHADERIVPROC) glXGetProcAddress((const GLubyte*)"glGetShaderiv");
inline PFNGLGETSHADERINFOLOGPROC    glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) glXGetProcAddress((const GLubyte*)"glGetShaderInfoLog");
inline PFNGLUNIFORM1IPROC    glUniform1i = (PFNGLUNIFORM1IPROC) glXGetProcAddress((const GLubyte*)"glUniform1i");
inline PFNGLUNIFORM1FPROC    glUniform1f = (PFNGLUNIFORM1FPROC) glXGetProcAddress((const GLubyte*)"glUniform1f");
inline PFNGLUNIFORM3FVPROC    glUniform3fv = (PFNGLUNIFORM3FVPROC) glXGetProcAddress((const GLubyte*)"glUniform3fv");
inline PFNGLDELETEPROGRAMPROC    glDeleteProgram = (PFNGLDELETEPROGRAMPROC) glXGetProcAddress((const GLubyte*)"glDeleteProgram");
 
#endif