#define STB_IMAGE_IMPLEMENTATION



#include <stdio.h>

#include <string.h>

#include <cmath>

#include <vector>

#include <math.h>



#include <glew.h>

#include <glfw3.h>



#include <glm.hpp>

#include <gtc\matrix_transform.hpp>

#include <gtc\type_ptr.hpp>

//para probar el importer

//#include<assimp/Importer.hpp>



#include "Window.h"

#include "Mesh_tn.h"

#include "Shader_m.h"

#include "Camera.h"

#include "Sphere.h"

#include"Model.h"

#include "Skybox.h"



const float toRadians = 3.14159265f / 180.0f;

//float angulocola = 0.0f;

Window mainWindow;

std::vector<Mesh*> meshList; //solo recibe xyz

std::vector<MeshColor*> meshListColor; // recibe xyz rgb

std::vector<MeshModel*> meshListModel; // recibe xyz uv nx ny nz

std::vector<Shader> shaderList;



Camera camera;

//Lista de Modelos a importar

Model Rover_M;

Model patafrontizq_M;

Model patafrontder_M;

Model patamidizq_M;

Model patamidder_M;

Model patabackizq_M;

Model patabackder_M;

Model Brazo_M;

Model Cuerpo_M;

Model CuerpoHolocron_M;

Model EsquinaBackDerDown_M;

Model EsquinaBackDerUp_M;

Model EsquinaBackIzqDown_M;

Model EsquinaBackIzqUp_M;

Model EsquinaFrontDerDown_M;

Model EsquinaFrontDerUp_M;

Model EsquinaFrontIzqDown_M;

Model EsquinaFrontIzqUp_M;

Model CuerpoSonda_M;

Model AlaDer_M;

Model AlaIzq_M;

//Lista de Skybox a crear

Skybox skybox;



GLfloat deltaTime = 0.0f;

GLfloat lastTime = 0.0f;

static double limitFPS = 1.0 / 60.0;



// Vertex Shader

static const char* vShader = "shaders/shader_m.vert";



// Fragment Shader

static const char* fShader = "shaders/shader_m.frag";



void CreateObjects()

{

	unsigned int indices[] = {

	0, 3, 1,

	1, 3, 2,

	2, 3, 0,

	0, 1, 2

	};



	GLfloat vertices[] = {

		// x      y      z u   v nx   ny    nz

		-1.0f, -1.0f, -0.6f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,

		1.0f, -1.0f, -0.6f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f

	};



	unsigned int floorIndices[] = {

	0, 2, 1,

	1, 2, 3

	};



	GLfloat floorVertices[] = {

	-10.0f, 0.0f, -10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,

	10.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, -1.0f, 0.0f,

	-10.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, -1.0f, 0.0f,

	10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 0.0f, -1.0f, 0.0f

	};





	MeshModel* obj1 = new MeshModel();

	obj1->CreateMeshModel(vertices, indices, 32, 12);

	meshListModel.push_back(obj1);



	MeshModel* obj2 = new MeshModel();

	obj2->CreateMeshModel(vertices, indices, 32, 12);

	meshListModel.push_back(obj2);



	MeshModel* obj3 = new MeshModel();

	obj3->CreateMeshModel(floorVertices, floorIndices, 32, 6);

	meshListModel.push_back(obj3);



}



void CreateShaders()

{

	Shader* shader1 = new Shader();

	shader1->CreateFromFiles(vShader, fShader);

	shaderList.push_back(*shader1);

}







int main()

{

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768

	mainWindow.Initialise();



	CreateObjects();

	CreateShaders();



	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.3f);

	//Cargar modelos
	patafrontizq_M = Model();

	patafrontizq_M.LoadModel("Models/patafrontizq.obj");

	patafrontder_M = Model();

	patafrontder_M.LoadModel("Models/patafrontder.obj");

	patamidizq_M = Model();

	patamidizq_M.LoadModel("Models/patamidizq.obj");

	patamidder_M = Model();

	patamidder_M.LoadModel("Models/patamidder.obj");

	patabackizq_M = Model();

	patabackizq_M.LoadModel("Models/patabackizq.obj");

	patabackder_M = Model();

	patabackder_M.LoadModel("Models/patabackder.obj");

	Brazo_M = Model();

	Brazo_M.LoadModel("Models/Brazo.obj");

	Cuerpo_M = Model();

	Cuerpo_M.LoadModel("Models/Cuerpo.obj");

	CuerpoHolocron_M = Model();
	CuerpoHolocron_M.LoadModel("Models/CuerpoHolocron.obj");

	EsquinaBackDerDown_M = Model();
	EsquinaBackDerDown_M.LoadModel("Models/EsquinaBackDerDown.obj");

	EsquinaBackDerUp_M = Model();
	EsquinaBackDerUp_M.LoadModel("Models/EsquinaBackDerUp.obj");

	EsquinaBackIzqDown_M = Model();
	EsquinaBackIzqDown_M.LoadModel("Models/EsquinaBackIzqDown.obj");

	EsquinaBackIzqUp_M = Model();
	EsquinaBackIzqUp_M.LoadModel("Models/EsquinaBackIzqUp.obj");

	EsquinaFrontDerDown_M = Model();
	EsquinaFrontDerDown_M.LoadModel("Models/EsquinaFrontDerDown.obj");

	EsquinaFrontDerUp_M = Model();
	EsquinaFrontDerUp_M.LoadModel("Models/EsquinaFrontDerUp.obj");

	EsquinaFrontIzqDown_M = Model();
	EsquinaFrontIzqDown_M.LoadModel("Models/EsquinaFrontIzqDown.obj");

	EsquinaFrontIzqUp_M = Model();
	EsquinaFrontIzqUp_M.LoadModel("Models/EsquinaFrontIzqUp.obj");

	CuerpoSonda_M = Model();
	CuerpoSonda_M.LoadModel("Models/CuerpoSonda.obj");

	AlaDer_M = Model();
	AlaDer_M.LoadModel("Models/AlaDer.obj");

	AlaIzq_M = Model();
	AlaIzq_M.LoadModel("Models/AlaIzq.obj");


	//Crear Skybox con sus 6 texturas

	std::vector<std::string> skyboxFaces;

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");

	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");



	skybox = Skybox(skyboxFaces);





	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0, uniformColor = 0;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	glm::mat4 model(1.0);

	glm::mat4 modelaux(1.0);

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	// Crear e inicializar la esfera para las articulaciones
	Sphere sp = Sphere(1.0f, 20, 20);
	sp.init();
	sp.load();

	////Loop mientras no se cierra la ventana

	while (!mainWindow.getShouldClose())

	{

		GLfloat now = glfwGetTime();

		deltaTime = now - lastTime;

		deltaTime += (now - lastTime) / limitFPS;

		lastTime = now;

		//Recibir eventos del usuario

		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);

		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());


		// Clear the window

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Se dibuja el Skybox

		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);



		shaderList[0].UseShader();

		uniformModel = shaderList[0].GetModelLocation();

		uniformProjection = shaderList[0].GetProjectionLocation();

		uniformView = shaderList[0].GetViewLocation();

		uniformColor = shaderList[0].getColorLocation();


		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));



		// INICIA DIBUJO DEL PISO

		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris

		model = glm::mat4(1.0);

		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		meshListModel[2]->RenderMeshModel();


		//Cuerpo Rover Completo
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rover_M.RenderModel();
		glm::mat4 bodyMatrix = model;

		// Patas Front
		glm::vec3 pivotFrontDer = glm::vec3(2.2f, 4.4f, -3.0f);
		glm::vec3 pivotFrontIzq = glm::vec3(2.2f, 4.4f, 3.0f);

		// Patas Mid
		glm::vec3 pivotMidDer = glm::vec3(-3.2f, 3.3f, -3.0f);
		glm::vec3 pivotMidIzq = glm::vec3(-3.2f, 3.3f, 3.0f);

		// Patas Back
		glm::vec3 pivotBackDer = glm::vec3(-2.8f, 3.3f, -3.0f);
		glm::vec3 pivotBackIzq = glm::vec3(-2.8f, 3.3f, 3.0f);

		float giroFrontDer = 45.0f * abs(sin(glm::radians(mainWindow.getarticulacion1())));
		float giroFrontIzq = 45.0f * abs(sin(glm::radians(mainWindow.getarticulacion2())));
		float giroMidDer = 45.0f * abs(sin(glm::radians(mainWindow.getarticulacion3())));
		float giroMidIzq = 45.0f * abs(sin(glm::radians(mainWindow.getarticulacion4())));
		float giroBackDer = -45.0f * abs(sin(glm::radians(mainWindow.getarticulacion5())));
		float giroBackIzq = -45.0f * abs(sin(glm::radians(mainWindow.getarticulacion6())));

		//Llanta Frontal Derecha
		model = bodyMatrix;
		model = glm::translate(model, pivotFrontDer);
		model = glm::rotate(model, glm::radians(giroFrontDer), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointFrontDer = model;

		model = glm::scale(jointFrontDer, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointFrontDer;
		model = glm::translate(model, -pivotFrontDer);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patafrontder_M.RenderModel();

		//Llanta Frontal Izquierda
		model = bodyMatrix;
		model = glm::translate(model, pivotFrontIzq);
		model = glm::rotate(model, glm::radians(giroFrontIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointFrontIzq = model;

		model = glm::scale(jointFrontIzq, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointFrontIzq;
		model = glm::translate(model, -pivotFrontIzq);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patafrontizq_M.RenderModel();

		//Llanta Media Derecha
		model = bodyMatrix;
		model = glm::translate(model, pivotMidDer);
		model = glm::rotate(model, glm::radians(giroMidDer), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointMidDer = model;

		model = glm::scale(jointMidDer, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointMidDer;
		model = glm::translate(model, -pivotMidDer);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patamidder_M.RenderModel();

		//Llanta Media Izquierda
		model = bodyMatrix;
		model = glm::translate(model, pivotMidIzq);
		model = glm::rotate(model, glm::radians(giroMidIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointMidIzq = model;

		model = glm::scale(jointMidIzq, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointMidIzq;
		model = glm::translate(model, -pivotMidIzq);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patamidizq_M.RenderModel();

		//Llanta Trasera Derecha
		model = bodyMatrix;
		model = glm::translate(model, pivotBackDer);
		model = glm::rotate(model, glm::radians(giroBackDer), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointBackDer = model;

		model = glm::scale(jointBackDer, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointBackDer;
		model = glm::translate(model, -pivotBackDer);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patabackder_M.RenderModel();

		//Llanta Trasera Izquierda
		model = bodyMatrix;
		model = glm::translate(model, pivotBackIzq);
		model = glm::rotate(model, glm::radians(giroBackIzq), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 jointBackIzq = model;

		model = glm::scale(jointBackIzq, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointBackIzq;
		model = glm::translate(model, -pivotBackIzq);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patabackizq_M.RenderModel();

		// Brazo
		model = bodyMatrix;
		glm::vec3 offsetBrazo = glm::vec3(0.0f, 0.0f, 0.0f);
		model = glm::translate(model, offsetBrazo);
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		Brazo_M.RenderModel();


		//Cuerpo Rover
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_M.RenderModel();


		//Holocron
		glm::mat4 holoMatrix = glm::mat4(1.0);
		holoMatrix = glm::translate(holoMatrix, glm::vec3(8.0f, -0.5f, 0.0f));
		model = holoMatrix;
		color = glm::vec3(0.2f, 0.2f, 0.2f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoHolocron_M.RenderModel();

		//Esquinas
		float distH = 0.1f;
		float giroHolocron = glfwGetTime() * 50.0f;

		glm::vec3 pivFDU = glm::vec3(39.0f, 8.0f, 2.5f); // Frontal Der Arriba
		glm::vec3 pivFDD = glm::vec3(39.0f, 2.0f, 2.5f); // Frontal Der Abajo
		glm::vec3 pivFIU = glm::vec3(39.0f, 8.0f, -2.5f); // Frontal Izq Arriba
		glm::vec3 pivFID = glm::vec3(39.0f, 2.0f, -2.5f); // Frontal Izq Abajo
		glm::vec3 pivBDU = glm::vec3(31.0f, 8.0f, 2.5f); // Trasera Der Arriba
		glm::vec3 pivBDD = glm::vec3(31.0f, 2.0f, 2.5f); // Trasera Der Abajo
		glm::vec3 pivBIU = glm::vec3(31.0f, 8.0f, -2.5f); // Trasera Izq Arriba
		glm::vec3 pivBID = glm::vec3(31.0f, 2.0f, -2.5f); // Trasera Izq Abajo

		glm::vec3 pivotes[8] = { pivFDU, pivFDD, pivFIU, pivFID, pivBDU, pivBDD, pivBIU, pivBID };
		Model* esquinas[8] = {
			&EsquinaFrontDerUp_M, &EsquinaFrontDerDown_M, &EsquinaFrontIzqUp_M, &EsquinaFrontIzqDown_M,
			&EsquinaBackDerUp_M, &EsquinaBackDerDown_M, &EsquinaBackIzqUp_M, &EsquinaBackIzqDown_M
		};

		glm::vec3 centroHolocron = glm::vec3(35.0f, 5.0f, 0.0f);

		float girosEsquinas[8] = {
			mainWindow.getEsquinaFDU(),
			mainWindow.getEsquinaFDD(),
			mainWindow.getEsquinaFIU(),
			mainWindow.getEsquinaFID(),
			mainWindow.getEsquinaBDU(),
			mainWindow.getEsquinaBDD(),
			mainWindow.getEsquinaBIU(),
			mainWindow.getEsquinaBID()
		};

		for (int i = 0; i < 8; i++) {
			model = holoMatrix;
			glm::vec3 ejeDiagonal = glm::normalize(pivotes[i] - centroHolocron);
			float gradosRotacion = girosEsquinas[i];
			float distanciaSeparacion = glm::min(girosEsquinas[i] * 0.02f, 2.5f);
			model = glm::translate(model, ejeDiagonal * distanciaSeparacion);
			model = glm::translate(model, pivotes[i]);
			model = glm::rotate(model, glm::radians(gradosRotacion), ejeDiagonal);
			glm::mat4 jointEsquina = model;
			model = glm::scale(jointEsquina, glm::vec3(0.2f, 0.2f, 0.2f));
			color = glm::vec3(0.0f, 1.0f, 1.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			sp.render();
			model = jointEsquina;
			model = glm::translate(model, -pivotes[i]);
			color = glm::vec3(0.8f, 0.0f, 0.0f);
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			esquinas[i]->RenderModel();
		}

		//Sonda Espacial
		float giroCuerpoSonda = mainWindow.getarticulacion10();
		float giroAlaDer = mainWindow.getarticulacion11();
		float giroAlaIzq = mainWindow.getarticulacion12();

		glm::mat4 sondaMatrix = glm::mat4(1.0);
		sondaMatrix = glm::translate(sondaMatrix, glm::vec3(-8.0f, 2.0f, 0.0f));
		glm::vec3 pivotCuerpo = glm::vec3(30.0f, 8.0f, -1.0f);
		model = sondaMatrix;
		model = glm::translate(model, pivotCuerpo);
		model = glm::rotate(model, glm::radians(giroCuerpoSonda), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 jointCuerpoSonda = model;
		model = glm::scale(jointCuerpoSonda, glm::vec3(0.3f, 0.3f, 0.3f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		model = jointCuerpoSonda;
		model = glm::translate(model, -pivotCuerpo);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoSonda_M.RenderModel();

		//Alas
		glm::mat4 sondaBodyMatrix = model;
		glm::vec3 pivotAlaDer = glm::vec3(29.0f, 8.0f, -1.0f);
		glm::vec3 pivotAlaIzq = glm::vec3(31.0f, 8.0f, -1.0f);

		//Derecha
		model = sondaBodyMatrix;
		model = glm::translate(model, pivotAlaDer);
		model = glm::rotate(model, glm::radians(giroAlaDer), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 jointAlaDer = model;

		//Esfera Ala Derecha
		model = glm::scale(jointAlaDer, glm::vec3(0.2f, 0.2f, 0.2f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointAlaDer;
		model = glm::translate(model, -pivotAlaDer);
		color = glm::vec3(1.0f, 0.5f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaDer_M.RenderModel();

		//Izquierda
		model = sondaBodyMatrix;
		model = glm::translate(model, pivotAlaIzq);
		model = glm::rotate(model, glm::radians(giroAlaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 jointAlaIzq = model;

		//Esfera Ala Izquierda
		model = glm::scale(jointAlaIzq, glm::vec3(0.2f, 0.2f, 0.2f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();

		model = jointAlaIzq;
		model = glm::translate(model, -pivotAlaIzq);
		color = glm::vec3(1.0f, 0.5f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaIzq_M.RenderModel();

		glUseProgram(0);



		mainWindow.swapBuffers();

	}



	return 0;


}