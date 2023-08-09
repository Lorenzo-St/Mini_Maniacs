#include "Animation.h"
#include "GLM.hpp"
#include "Backend.h"
#include "../GLM/ext/matrix_transform.hpp"
#include "Stream.h"

Animation::Animation(Animation const* ml) 
{
	frameTime = ml->frameTime;
	frame = ml->frame;
	maxFrame = ml->maxFrame;
	frameLength = ml->frameLength;
	looping = ml->looping;
	Columns = ml->Columns;
	Rows = ml->Rows;
	frameOffset = ml->frameOffset;
}

void Animation::Read(Stream* s) 
{
	// <Animation>
	//  <frameTime>
	//   .25
	//  <frame>
	//   5
	//  <max
	//
	while (true) 
	{
		std::string token = s->ReadString();
		if (token == "<frameLength>")
			frameLength = s->ReadFloat();
		else if (token == "<maxFrames>")
			maxFrame = s->ReadInt();
		else if (token == "<looping>")
			looping = s->ReadBool();
		else if (token == "<offset>")
			frameOffset = s->ReadVector();
		else if (token == "<Columns>")
			Columns = s->ReadInt();
		else if (token == "<Rows>")
			Rows = s->ReadInt();
		else if (token == "</Animation>")
			break;
	}
}

void Animation::Update(void) 
{
	frameTime -= Time.deltaTime();

	if (frameTime <= 0) 
	{
		frameTime += frameLength;
		++frame;
		if (frame >= maxFrame)
		{
			if (looping)
				frame = 0;
			else
				frame = maxFrame - 1;
		}
		UpdateMesh();
	}
	api.SetUVMatrix(matrix);
}

void GetUVCoords(int frame, int frameX, int frameY, float* u, float*v)
{
	float uSize = 1.0f / frameX;
	float vSize = 1.0f / frameY;

	*u = uSize * (frame % frameX);
	*v = vSize * (static_cast<float>(frame) / frameX);
}

void Animation::UpdateMesh() 
{
	float uSize = 1.0f/Columns;
	float vSize = 1.0f/Rows;

	float u, v;
	GetUVCoords(frame, Columns, Rows, &u, &v);
	matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(u + (u * frameOffset.x), v + (v * frameOffset.y), 0));
	matrix = glm::scale(matrix, glm::vec3(uSize, vSize, 0));
	api.SetUVMatrix(matrix);
}

