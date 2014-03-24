//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once
#include <Springbok/Graphics/Image.h>
#include <Springbok/Containers/List.h>
#include <Springbok/Animation/KeyframeList.h>

struct ParticleDefinition
{
	Image Sprite;
	float LifeTime = 1;
	
	KeyframeList<Vec4F> Color = {Colors::White};
	KeyframeList<Vec2F> Scale = {1};
};

struct Particle
{
	ParticleDefinition* Definition = nullptr;
	float Age = 0.f;
	Vec2F Position = 0;
	Vec2F Velocity = 0;
	Vec2F Accleration = 0;
};

struct ParticleSystem
{
	List<Particle> Particles;
	int OverwriteIndex = 0;
	ParticleSystem(int size);
	void addParticle(Particle particle);
	void cleanUp();
};