#define DEBUG_WRITE 0
#if _DEBUG && DEBUG_WRITE
#include <iostream>
#endif
#include "Animation.h"
#include "GLM.hpp"
#include "../GLM/ext/matrix_transform.hpp"
#include "Stream.h"
#include "MeshComp.h"
#include "Entity.h"

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

void Animation::Write(std::ofstream* s) 
{
	*s << "<Animation>\n ";
	*s << "<frameLength>\n  ";
	*s << frameLength << "\n ";

	*s << "<maxFrames>\n  ";
	*s << maxFrame << "\n ";
	*s << "<looping>\n  ";
	*s << looping << "\n ";
	*s << "<offset>\n  ";
	*s << frameOffset.x << " " << frameOffset.y << "\n ";
	*s << "<frameLength>\n  ";
	*s << frameLength << "\n ";
	*s << "<frameLength>\n  ";
	*s << frameLength << "\n ";
	*s << "<Columns>\n  ";
	*s << Columns << "\n ";
	*s << "<Rows>\n  ";
	*s << Rows << "\n ";
	*s << "</Animation>\n ";
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
	this->GetParent()->GetComponent<Mesh>()->SetMatrix(matrix);
}

void GetUVCoords(int frame, int frameX, int frameY, float* u, float*v)
{
	float uSize = 1.0f / frameX;
	float vSize = 1.0f / frameY;

	*u = uSize * (frame % frameX);
	*v = vSize * (frame / frameX);
}

void Animation::UpdateMesh() 
{
	float uSize = 1.0f/Columns;
	float vSize = 1.0f/Rows;

	float u, v;
	GetUVCoords(frame, Columns, Rows, &u, &v);
	matrix = glm::mat4x4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(u + (uSize * frameOffset.x), v + (vSize * frameOffset.y), 0));
	matrix = glm::scale(matrix, glm::vec3(uSize, vSize, 0));
	matrix = glm::transpose(matrix);
	this->GetParent()->GetComponent<Mesh>()->SetMatrix(matrix);
#if _DEBUG && DEBUG_WRITE
	std::cout << frame << std::endl;
#endif
}

