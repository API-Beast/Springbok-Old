// Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
//
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
// 0. You just DO WHAT THE FUCK YOU WANT TO.

#include "RenderContext2D.h"
#include "GLES2.h"

#include <Springbok/Foundation/PointerGuard.h>
#include <Springbok/Utils/Functions.h>

#include <iostream>

RenderContext2D::RenderContext2D(RenderTarget* target)
{
	glEnable(GL_BLEND);
	//glEnable(0x92E0);
	glDisable(GL_CULL_FACE);
	setRenderTarget(target);
	setShader      (mShader);
	PrintGLError();
}

void RenderContext2D::setShader(ShaderProgram shader)
{
	mShader = shader;
	glUseProgram(mShader.Handle);
	PrintGLError();
}

void RenderContext2D::setRenderTarget(RenderTarget* target)
{
	mRenderTarget = target;
	if(target)
		mRenderTarget->bind();
	PrintGLError();
}

void RenderContext2D::clear(Vec3F clr)
{
	glClearColor(clr.X, clr.Y, clr.Z, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	PrintGLError();
}

