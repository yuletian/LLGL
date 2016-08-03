/*
 * GLHardwareShader.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __LLGL_GL_HARDWARE_SHADER_H__
#define __LLGL_GL_HARDWARE_SHADER_H__


#include "OpenGL.h"


namespace LLGL
{


class GLHardwareShader
{

    public:

        GLHardwareShader(const GLHardwareShader&) = delete;
        GLHardwareShader& operator = (const GLHardwareShader&) = delete;

        GLHardwareShader(GLenum shaderType);
        ~GLHardwareShader();

        //! Returns the hardware shader ID.
        inline GLuint GetID() const
        {
            return id_;
        }

    private:

        GLuint id_ = 0;

};


} // /namespace LLGL


#endif



// ================================================================================