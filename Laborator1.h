#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Laborator1 : public SimpleScene
{
	public:
		Laborator1();
		~Laborator1();
		glm::mat4 modelMatrix = glm::mat4(1);
		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void ciocniri_viteze2(int i, int j, float deltaT);
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void RenderMeshCue(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, float time);
		float ciocniri(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float time);
		void ciocniri_viteze(int i, int j, float time);

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void Gauri(int iy);

	protected:
		Tema::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;


};
