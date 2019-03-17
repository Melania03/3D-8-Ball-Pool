#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3D.h"


using namespace std;
float x_tac=-4.8, y_tac=0, z_tac=-3.5, val=0, timp=0;
bool first = true, rotire = false, tac = false, plecare_bila = false, alb_disparitie = false, lines = false, space = false;
bool nextt = false, aparitie_tac = true, ciocnire = false, tac_inainte = true, incarcare = false, continuare1=false, continuare2=false;
float deltaTimeSecondss = 2.1;
int prima_bila = 16, alts = 0, jucator = 0, neagra = 0, galbena = 0, rosie = 0, prima_data=0, bile=15, k=0;
char player1[4], player2[4], first_contact[6] = "nimic";

struct Bila {
	float xx;
	float zz;
	float vx;
	float vz;
	bool randare ;
	int r = 0;
	char color[4];
};
Bila v[16];

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	camera = new Tema::Camera();
	//camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
	camera->Set(glm::vec3(0, 3, 4), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "matase.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* mesh2 = new Mesh("box2");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "woodtable.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("cue");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "10522_Pool_Cue_v1_L3.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

		Mesh* mesh4 = new Mesh("perete");
		mesh4->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "wall.obj");
		meshes[mesh4->GetMeshID()] = mesh4;

		Mesh* mesh5 = new Mesh("parchet");
		mesh5->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "floor.obj");
		meshes[mesh5->GetMeshID()] = mesh5;

		Mesh* mesh7 = new Mesh("leu");
		mesh7->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "12144_MountedLionHead_v2_L2.obj");
		meshes[mesh7->GetMeshID()] = mesh7;

		Mesh* mesh8 = new Mesh("usa");
		mesh8->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "10057_wooden_door_v3_iterations-2.obj");
		meshes[mesh8->GetMeshID()] = mesh8;

		Mesh* mesh9 = new Mesh("picior");
		mesh9->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "picior.obj");
		meshes[mesh9->GetMeshID()] = mesh9;

		Mesh* mesh10 = new Mesh("masuta");
		mesh10->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "table.obj");
		meshes[mesh10->GetMeshID()] = mesh10;

		Mesh* mesh11 = new Mesh("deco");
		mesh11->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "CANDLES.obj");
		meshes[mesh11->GetMeshID()] = mesh11;

		Mesh* mesh12 = new Mesh("bila_alba");
		mesh12->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "whiteball.obj");
		meshes[mesh12->GetMeshID()] = mesh12;

		Mesh* meshr = new Mesh("bila_r");
		meshr->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "rosia.obj");
		meshes[meshr->GetMeshID()] = meshr;

		Mesh* meshg = new Mesh("bila_g");
		meshg->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "galbenn.obj");
		meshes[meshg->GetMeshID()] = meshg;

		Mesh* meshb = new Mesh("bila_b");
		meshb->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "black.obj");
		meshes[meshb->GetMeshID()] = meshb;
		
		Mesh* mesh13 = new Mesh("hole");
		mesh13->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "hole.obj");
		meshes[mesh13->GetMeshID()] = mesh13;

		Mesh* mesh14 = new Mesh("light");
		mesh14->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "light.obj");
		meshes[mesh14->GetMeshID()] = mesh14;

		Mesh* mesh15 = new Mesh("lines");
		mesh15->LoadMesh(RESOURCE_PATH::MODELS + "Pool", "lines.obj");
		meshes[mesh15->GetMeshID()] = mesh15;

		v[0].xx = 1.1; v[0].zz = 0; strcpy(v[0].color, "red");
		v[1].xx = 1.23; v[1].zz = 0.065; strcpy(v[1].color, "red");
		v[2].xx = 1.23; v[2].zz = -0.065; strcpy(v[2].color, "yel");
		v[3].xx = 1.36; v[3].zz = 0; strcpy(v[3].color, "blk");
		v[4].xx = 1.36; v[4].zz = 0.13; strcpy(v[4].color, "yel");
		v[5].xx = 1.36; v[5].zz = -0.13; strcpy(v[5].color, "red");
		v[6].xx = 1.49; v[6].zz = 0.065; strcpy(v[6].color, "red");
		v[7].xx = 1.49; v[7].zz = -0.065; strcpy(v[7].color, "red");
		v[8].xx = 1.49; v[8].zz = 0.195; strcpy(v[8].color, "yel");
		v[9].xx = 1.49; v[9].zz = -0.195; strcpy(v[9].color, "yel");
		v[10].xx = 1.62; v[10].zz = 0; strcpy(v[10].color, "yel");
		v[11].xx = 1.62; v[11].zz = 0.13; strcpy(v[11].color, "red");
		v[12].xx = 1.62; v[12].zz = -0.13; strcpy(v[12].color, "yel");
		v[13].xx = 1.62; v[13].zz = -0.26; strcpy(v[13].color, "red");
		v[14].xx = 1.62; v[14].zz = 0.26; strcpy(v[14].color, "yel");
		v[15].xx = -1.3; v[15].zz = 0; strcpy(v[15].color, "whi");

		for (int i = 0; i < 16; i++) {
			v[i].vx = 0;
			v[i].vz = 0;
			v[i].randare = true;
		}


		// Create a shader program for drawing face polygon with the color of the normal
		{
			Shader *shader = new Shader("ShaderCue");
			shader->AddShader("Source/Laboratoare/Laborator1/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
			shader->AddShader("Source/Laboratoare/Laborator1/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			shader->CreateAndLink();
			shaders[shader->GetName()] = shader;
		}
		 
		printf("\n\n                                             Wellcome to THE eight-ball billiard game.\nWaiting for the players' colors.\n\n");

	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);


	RenderMesh(meshes["box"], shaders["Simple"], glm::mat4(1));
	RenderMesh(meshes["box2"], shaders["Simple"], glm::mat4(1));
	RenderMesh(meshes["parchet"], shaders["Simple"], glm::mat4(1));
	RenderMesh(meshes["perete"], shaders["Simple"], glm::mat4(1));


	modelMatrix = Transform::Translate(4, 0, -4);
	modelMatrix *= Transform::RotateOY(RADIANS(180));
	modelMatrix *= Transform::Scale(0.0000012, 0.0000015, 0.000001);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["masuta"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(4, 1, -4);
	modelMatrix *= Transform::Scale(0.012, 0.012, 0.012);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["deco"], shaders["Simple"], modelMatrix);

	/*modelMatrix = Transform::Translate(4, 0, 2.5);
	modelMatrix *= Transform::RotateOY(RADIANS(-60));
	modelMatrix *= Transform::Scale(0.026, 0.015, 0.026);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["brad"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(2.5, 2, -5);
	modelMatrix *= Transform::Scale(0.015, 0.015, 0.015);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["deco1"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(-2.5, 2, -5);
	modelMatrix *= Transform::Scale(0.015, 0.015, 0.015);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["deco1"], shaders["Simple"], modelMatrix);*/

	modelMatrix = Transform::Translate(0, 0.567, 0.99);
	modelMatrix *= Transform::Scale(0.0065, 0.0068, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(1.96, 0.567, 0.96);
	modelMatrix *= Transform::Scale(0.007, 0.007, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(-1.96, 0.567, 0.96);
	modelMatrix *= Transform::Scale(0.007, 0.007, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(1.96, 0.567, -0.96);
	modelMatrix *= Transform::Scale(0.007, 0.007, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(-1.96, 0.567, -0.96);
	modelMatrix *= Transform::Scale(0.007, 0.007, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(0, 0.567, -0.99);
	modelMatrix *= Transform::Scale(0.0065, 0.0068, 0.007);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["hole"], shaders["Simple"], modelMatrix);


	modelMatrix = Transform::Translate(0, 1.8, 0);
	modelMatrix *= Transform::Scale(0.018, 0.018, 0.018);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["light"], shaders["Simple"], modelMatrix);


	modelMatrix = Transform::Translate(-1.75, 0, 0.8);
	modelMatrix *= Transform::Translate(-0.1, 0, 0.07);
	modelMatrix *= Transform::Scale(0.01, 0.014, 0.01);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["picior"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::RotateOY(RADIANS(180));
	modelMatrix *= Transform::Translate(-1.75, 0, 0.8);
	modelMatrix *= Transform::Translate(-0.1, 0, 0.07);
	modelMatrix *= Transform::Scale(0.01, 0.014, 0.01);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["picior"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(1.75, 0, 0.8);
	modelMatrix *= Transform::Translate(-0.1, 0, 0.07);
	modelMatrix *= Transform::Scale(0.01, 0.014, 0.01);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["picior"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::RotateOY(RADIANS(180));
	modelMatrix *= Transform::Translate(1.75, 0, 0.8);
	modelMatrix *= Transform::Translate(-0.1, 0, 0.07);
	modelMatrix *= Transform::Scale(0.01, 0.014, 0.01);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["picior"], shaders["Simple"], modelMatrix);

	if (rotire == true && lines == true) {
		modelMatrix = Transform::Translate(x_tac, y_tac, z_tac);
		modelMatrix *= Transform::Scale(0.007, 0.007, 0.007);
		modelMatrix *= Transform::RotateOY(val);
		modelMatrix *= Transform::RotateOX(RADIANS(3));
		modelMatrix *= Transform::RotateOX(RADIANS(90));
		modelMatrix *= Transform::Translate(1.9, 0, -9.5);
		RenderMesh(meshes["lines"], shaders["Simple"], modelMatrix);
	}

	if (tac == false) {
		modelMatrix = Transform::Translate(x_tac, y_tac, z_tac);
		modelMatrix *= Transform::RotateOZ(RADIANS(10));
		modelMatrix *= Transform::RotateOX(RADIANS(-90));
	}
	if (rotire == true) {
		modelMatrix = Transform::Translate(x_tac, y_tac, z_tac);
		// rotire pe oy
		modelMatrix *= Transform::RotateOY(val);
		modelMatrix *= Transform::RotateOX(RADIANS(5));
		modelMatrix *= Transform::Translate(0, 0, -2.7);
	}
	modelMatrix *= Transform::Scale(0.018, 0.018, 0.018);
	if(aparitie_tac == true)
		if (incarcare == true) {
			RenderMeshCue(meshes["cue"], shaders["ShaderCue"], modelMatrix, deltaTimeSecondss);
			if (tac_inainte)
				deltaTimeSecondss += deltaTimeSeconds * 10;
			else deltaTimeSecondss -= deltaTimeSeconds * 10;

			if (deltaTimeSecondss > 30)
				tac_inainte = false;
			else if (deltaTimeSecondss < 2)
				tac_inainte = true;
		}
		else RenderMeshCue(meshes["cue"], shaders["ShaderCue"], modelMatrix, 2);

	modelMatrix = Transform::Translate(0, 1.3, 5.07);
	modelMatrix *= Transform::RotateOY(RADIANS(-180));
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	modelMatrix *= Transform::Scale(0.017, 0.017, 0.017);
	RenderMesh(meshes["leu"], shaders["Simple"], modelMatrix);

	modelMatrix = Transform::Translate(-5.0, 0, -1.0);
	modelMatrix *= Transform::RotateOY(RADIANS(-90));
	modelMatrix *= Transform::Scale(0.016, 0.014, 0.014);
	modelMatrix *= Transform::RotateOX(RADIANS(-90));
	RenderMesh(meshes["usa"], shaders["Simple"], modelMatrix);

	if (alb_disparitie == false) {
		modelMatrix = Transform::Translate(v[15].xx, 0.6, v[15].zz);
		modelMatrix *= Transform::Scale(0.003, 0.003, 0.003);
		modelMatrix *= Transform::RotateOX(RADIANS(-90));
		RenderMesh(meshes["bila_alba"], shaders["Simple"], modelMatrix);
	}
	for (int i = 0; i < 15; i++) {
		if (v[i].randare) {
			modelMatrix = Transform::Translate(v[i].xx, 0.6, v[i].zz);
			modelMatrix *= Transform::Scale(0.003, 0.003, 0.003);
			modelMatrix *= Transform::RotateOX(RADIANS(-90));
			if (strstr(v[i].color, "yel"))
				RenderMesh(meshes["bila_g"], shaders["Simple"], modelMatrix);
			if (strstr(v[i].color, "red"))
				RenderMesh(meshes["bila_r"], shaders["Simple"], modelMatrix);
			if (strstr(v[i].color, "bl"))
				RenderMesh(meshes["bila_b"], shaders["Simple"], modelMatrix);
		}
	}


	//coliziuni manta
	for (int i = 0; i < 16; i++) {
		if (v[i].randare){
			if (v[i].xx < -1.9) {
				v[i].xx = -1.9;
				v[i].vx = -v[i].vx;
			}
			if (v[i].xx > 1.9) {
				v[i].xx = 1.9;
				v[i].vx = -v[i].vx;
			}
			if (v[i].zz < -0.9) {
				v[i].zz = -0.9;
				v[i].vz = -v[i].vz;
			}
			if (v[i].zz > 0.9) {
				v[i].zz = 0.9;
				v[i].vz = -v[i].vz;
			}
		}
	}

	if (alb_disparitie == true && plecare_bila == false){
		if (timp < 1.5)
			timp += deltaTimeSeconds;
		else {
			alb_disparitie = false;
			plecare_bila = false;
			v[15].xx = -0.5;
			v[15].zz = 0;
			nextt = true;
			ciocnire = false;
			timp = 0;
		}
	}

	for (int i = 0; i < 16; i ++)
		if (v[i].randare)
			Gauri(i);

	if (plecare_bila == true) {
		for (int i = 0; i < 16; i++) {
			if (v[i].randare) {

				v[i].xx += v[i].vx * deltaTimeSeconds;
				v[i].zz += v[i].vz * deltaTimeSeconds;
				float accel_x, accel_z;
				accel_x = deltaTimeSeconds * abs(v[i].vx) / (abs(v[i].vx) + abs(v[i].vz));
				accel_z = deltaTimeSeconds * abs(v[i].vz) / (abs(v[i].vx) + abs(v[i].vz));
				if (v[i].vx != 0) {
					if (v[i].vx > 0) {
						if (v[i].vx - accel_x >= 0)
							v[i].vx -= accel_x;
						else
							v[i].vx = 0;
					}
					else {
						if (v[i].vx + accel_x <= 0)
							v[i].vx += accel_x;
						else
							v[i].vx = 0;
					}
				}

				if (v[i].vz != 0) {
					if (v[i].vz > 0) {
						if (v[i].vz - accel_z >= 0)
							v[i].vz -= accel_z;
						else
							v[i].vz = 0;
					}
					else {
						if (v[i].vz + accel_z <= 0)
							v[i].vz += accel_z;
						else
							v[i].vz = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < 15; i++) {
		for (int j = i + 1; j < 16; j++)
		{
			if (v[i].randare && v[j].randare){
				float aux = ciocniri(glm::vec3(v[i].xx, 0, v[i].zz), glm::vec3(v[j].xx, 0, v[j].zz), glm::vec3(v[i].vx, 0, v[i].vz), glm::vec3(v[j].vx, 0, v[j].vz), deltaTimeSeconds);
				if (aux != 1){
					v[i].xx += v[i].vx * deltaTimeSeconds * aux;
					v[i].zz += v[i].vz * deltaTimeSeconds * aux;
					v[j].xx += v[j].vx * deltaTimeSeconds * aux;
					v[j].zz += v[j].vz * deltaTimeSeconds * aux;
					ciocniri_viteze2(i, j, deltaTimeSeconds);

					if (j == 15) {
						// bila alba a ciocnit ceva
						// verifici v[i].color
						// doar daca e primul contact de la fiecare lovitura
						
						if (strcmp(first_contact, "nimic")==0) {
							strcpy(first_contact, v[i].color);

						}
						
					}
				}
			}
		}
	}

	bool control = true;
	if (plecare_bila) {
		for (int i = 0; i < 16; i++)
		{
			if (v[i].vx || v[i].vz) {
				control = false;
				break;
			}
		}
		if (control == true) {
			ciocnire = true;
			nextt = false;
			plecare_bila = false;
			if (jucator % 2 == 0) {
				if (jucator == 0)
					printf("Next player...\n");
				else {
					if (strcmp(player2, first_contact) != 0) {
						jucator++;
						printf("Fault. Player 2 touched the wrong ball first or did not touch any ball at all.\nPlayer 1's turn...\n");
					}
					else {
						if (strcmp(player2, "red") == 0)
							if (rosie == 0) {
								printf("Player 1's turn...\n");
								jucator++;
							}
						if (strcmp(player2, "yel") == 0)
							if (galbena == 0) {
								jucator++;
								printf("Player 1's turn...\n");
							}
					}
				}
			}
			else if (jucator % 2 == 1) {
				if (prima_data == 1) {
					if (strcmp(player1, first_contact) != 0) {
						jucator++;
						printf("Fault. Player 1 touched the wrong ball first or did not touch any ball at all.\nPlayer 2's turn...\n");
					}

					else {
						if (strcmp(player1, "red") == 0)
							if (rosie == 0) {
								jucator++;
								printf("Player 2's turn...\n");
							}
						if (strcmp(player1, "yel") == 0)
							if (galbena == 0) {
								jucator++;
								printf("Player 2's turn...\n");
							}
					}
				}
			}
			strcpy(first_contact, "nimic");
			rosie = 0;
			galbena = 0;
		}
	}

	if (prima_bila == 16) {
		for (int i = 0; i < 15; i++) {
			if (v[i].randare == false)
			{
				bile--;
				if (strcmp(v[i].color, "blk") == 0) {
					v[i].xx = 1.5;
					v[i].zz = 0;
					v[i].randare = true;
					printf("FAULT!!! Black ball back, please! Do not do it again.\n");
					bile++;
					break;
				}
				else {
					prima_bila = i;
					strcpy(player1, v[i].color);
					if (strcmp(v[i].color, "yel") == 0) {
						printf("So... First player is color yellow.\n");
						jucator++;
						v[i].r++;
						strcpy(player2, "red");
						printf("Second player is color red.\nPlayer 1's turn...\n");
					}
					else {
						printf("So... First player is color red.\n");
						jucator++;
						v[i].r++;
						strcpy(player2, "yel");
						printf("Second player is color yellow.\nPlayer 1's turn...\n");
					}
				}
			}
		}
	}
	if (bile <= 14) {
		if (k == 2)
			prima_data = 1;
		k++;
	}

	for (int i = 0; i < 15; i++) {
		if (v[i].randare == false && v[i].r == 0) {
			v[i].r++;
			bile--;
			if (strcmp(v[i].color, "red") == 0)
				rosie++;
			if (strcmp(v[i].color, "yel") == 0)
				galbena++;
			if (jucator % 2 == 0) {
				if (strcmp(player2, v[i].color) == 0) {
					printf("Point for player 2\n");
					break;
				}
				else {
					if ((strcmp(v[i].color, "blk") == 0)) {
						if (bile == 0)
							printf("CONGRATSULATIONS! Player 2 won! WOW!!! MERRY CHRISTMAS <3\n");
						else {
							printf("Fault. Player 2 sank the black ball.\n Player 1 wins. Congrats!\n");
							break;
						}
					}
					else {
						printf("Tragic. Player 2 sank the opponent's ball.\nPlayer 1's turn...\n");
						jucator++;
						break;
					}
				}
			}
			else {
				if (strcmp(player1, v[i].color) == 0 ){
					printf("Point for player 1\n");
					break;
				}
				else {

					if ((strcmp(v[i].color, "blk") == 0)) {
						if (bile == 0) {
							printf("CONGRATSULATIONS! Player 1 won! WOW!!! MERRY CHRISTMAS <3\n");
							break;
						}
						else {
							printf("Fault. Player 1 sank the black ball.\n Player 2 wins. Congrats!\n");
							break;
						}
					}
					else {
						printf("Tragic. Player 1 sank the opponent's ball.\nPlayer 2's turn...\n");
						jucator++;
						break;
					}
					
				}
			}
			
		}
	}

	
}
void Laborator1::ciocniri_viteze2(int i, int j, float deltaT)
{
	glm::vec3 n = glm::vec3(v[i].xx - v[j].xx, 0, v[i].zz - v[j].zz);
	n = normalize(n);

	glm::vec3 v1 = glm::vec3(v[i].vx, 0, v[i].vz); // vectorii de miscare
	glm::vec3 v2 = glm::vec3(v[j].vx, 0, v[j].vz);

	float a1 = dot(n, v1);
	float a2 = dot(n, v2);

	float p = a1 - a2;

	glm::vec3 newV1 = v1 - p * n;
	glm::vec3 newV2 = v2 + p * n;

	v[i].vx = newV1.x;
	v[i].vz = newV1.z;
	v[j].vx = newV2.x;
	v[j].vz = newV2.z;

}


float Laborator1::ciocniri(glm::vec3 a, glm::vec3 b, glm::vec3 va, glm::vec3 vb, float deltaT) {
	va = va * deltaT;
	vb = vb * deltaT;
	glm::vec3 movement = va - vb;
	float moveDist = sqrt(pow(movement.x, 2) + pow(movement.z, 2));
	if (moveDist + 0.119 < sqrt(pow(a.x - b.x, 2) + pow(a.z - b.z, 2)))
		return 1;
	
	glm::vec3 nMovement = normalize(movement);
	glm::vec3 c = b - a;
	float d = dot(c, nMovement);
	if (d <= 0)
		return 1;

	float cLength = sqrt(pow(c.x, 2) + pow(c.z, 2));
	float f = (cLength * cLength) - (d * d);
	if (f >= 0.12 * 0.12)
		return 1;

	double t = 0.12 * 0.12 - f;
	if (t < 0)
		return 1;

	float dist = d - sqrt(t); // distance
	float mag = moveDist;
	if (mag < dist)
		return 1;

	nMovement *= dist - 0.12;
	float segment = (movement.x / nMovement.x);

	return segment;


}

void Laborator1::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Laborator1::Gauri(int i) {
	float x = v[i].xx, z = v[i].zz;
	if (pow((x - (-1.9)), 2) + pow((z - (-0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (1.9)), 2) + pow((z - (0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (0)), 2) + pow((z - (0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (0)), 2) + pow((z - (-0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (0)), 2) + pow((z - (0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (-1.9)), 2) + pow((z - (0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	if (pow((x - (1.9)), 2) + pow((z - (-0.9)), 2) <= 0.01)
	{
		if (i != 15)
			v[i].randare = false;
		else 
			alb_disparitie = true;
		v[i].vx = 0;
		v[i].vz = 0;
		return;
	}
	
}

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	float x_alb = v[15].xx;
	float z_alb = v[15].zz;

	if (first == true) {
		if (window->KeyHold(GLFW_KEY_W)) {
			/*	if (variabila > 3)
					variabila = 3;*/
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (x_alb <= -0.8)
				x_alb += deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			/*if (variabila > 3)
				variabila = 3;*/
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (x_alb >= -1.8)
				x_alb -= deltaTime;
			if (x_alb >= -1.9 && z_alb >= -0.8  && z_alb <= 0.8)
				x_alb -= deltaTime;
			
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			/*if (variabila > 3)
				variabila = 3;*/
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (z_alb >= -0.9 && x_alb >=-1.8)
				z_alb -= deltaTime;
			if (z_alb >= -0.8)
				z_alb -= deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			/*if (variabila > 3)
				variabila = 3;*/
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (z_alb <= 0.9 && x_alb >=-1.8)
				z_alb += deltaTime;
			if (z_alb <= 0.8)
				z_alb += deltaTime;
		}
	
	}
	if (nextt == true) {
		if (window->KeyHold(GLFW_KEY_W)) {
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (x_alb <= 1.9)
				x_alb += deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (x_alb >= -1.9)
				x_alb -= deltaTime;
		

		}

		if (window->KeyHold(GLFW_KEY_A)) {
			
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (z_alb >= -0.9)
				z_alb -= deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			camera->Set(glm::vec3(-2.9, 3, 0), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));
			if (z_alb <= 0.9)
				z_alb += deltaTime;
		}

	}
	bool test_coliziune = true;
	for (int i = 0; i < 15; i++) {
		if (v[i].randare) {
			if (pow(x_alb - v[i].xx, 2) + pow(z_alb - v[i].zz, 2) < 0.12 * 0.12)
				test_coliziune = false;
		}
	}
	if (test_coliziune) {
		v[15].xx = x_alb;
		v[15].zz = z_alb;
	}
}



void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_RIGHT_ALT) {
		alts++;
		if (alts % 2 == 0)
			lines = false;
		else
			lines = true;
	}
	if (key == GLFW_KEY_SPACE && (first == true || nextt == true|| ciocnire == true)) {
		float x_alb = v[15].xx, z_alb = v[15].zz;
		space = true;
		aparitie_tac = true;
		first = false;
		nextt = false;
		tac = true;
		y_tac = 0.68;
		x_tac = x_alb;
		z_tac = z_alb;
		float x = 0.5, z = 0.5;
		if (x_alb)
			x = x_alb + x_alb / abs(x_alb) * 0.5;
		if (z_alb)
			z = z_alb + z_alb / abs(z_alb) * 0.5;
		camera->Set(glm::vec3(x, 0.9, z), glm::vec3(x_alb, 0.6, z_alb), glm::vec3(0, 1, 0));
		rotire = true;
		if (x_alb < 0) {
			if (z_alb < 0)
				val = (45 - 90) * M_PI / 180;
			else val = (45 - 180) * M_PI / 180;
		}
		else {
			if (z_alb < 0)
				val = (45) * M_PI / 180;
			else val = (45 - 270) * M_PI / 180;
		}
		
	}
	if (key == GLFW_KEY_LEFT_ALT ) {
		incarcare = true;
	}

};

void Laborator1::OnKeyRelease(int key, int mods)
{
	if (key == GLFW_KEY_LEFT_ALT ) {
		alts = 0;
		incarcare = false;
		plecare_bila = true;
		aparitie_tac = false;
		v[15].vx = camera->forward.x * deltaTimeSecondss / 5;
		v[15].vz = camera->forward.z * deltaTimeSecondss / 5;
		camera->Set(glm::vec3(0, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0 , -1));
		deltaTimeSecondss = 2.1;
		lines = false;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event	
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOY = 0.001f;
		
		if (rotire == true && plecare_bila == false) {
			camera->RotateThirdPerson_OY(sensivityOY * deltaX);
			val -= sensivityOY * deltaX;
		}
	}

};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{ 
	//
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}


void Laborator1::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}


void Laborator1::RenderMeshCue(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, float time)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	int t = glGetUniformLocation(shader->program, "Time");
	glUniform1f(t, time);

	mesh->Render();
}



