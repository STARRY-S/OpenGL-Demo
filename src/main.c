#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <cglm/cglm.h>
#include <cglm/call.h>

#include "shader.h"
#include "texture.h"
#include "camera.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void key_callback(GLFWwindow *window, int key, int s, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_cursor_callback( GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f
};

float floorVertices[] = {
//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
     10.0f,  10.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     10.0f, -10.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -10.0f, -10.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -10.0f,  10.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,   // 左上
    -10.0f, -10.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    10.0f,  10.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f     // 右上
};

vec3 cubePositions[] = {
        { -3.0f,  -1.5f,  2.0f},
        { 1.0f,  01.5f, -1.0f},
        {-1.5f, 0.5f, 2.0f},
        {-3.5f, 2.5f, -4.0f},
        { 3.0f, 1.5f, -5.0f},

        {-1.5f,  -1.5f, -10.0f},
        { 0.5f, -1.5f, -8.5f},
        { 4.5f,  2.5f, -12.0f},
        { 6.5f,  -1.5f, -5.5f},
        {-1.5f,  -1.5f, 2.5f},

        {-1.5f,  -1.5f, -1.5f},
        {1.5f,  -1.5f, -4.5f},
        {-2.5f,  -1.5f, 4.5f},
        {-4.5f,  -1.5f, -2.5f},
        {-0.5f,  -1.5f, 2.5f}
};

vec3 lightPos = {-1.5f, -0.5f, -2.5f};

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

float lastX = 400, lastY = 300;
bool firstMouse = true;
bool fullScreenMode = false;

int textureNum;

const GLFWvidmode* mode;

int main(int argc, char **argv)
{
        if (argc == 2) {
                if (!strcmp(argv[1], "-h")) {
                        printf("使用说明：\n");
                        printf("%s -f 全屏运行\n", argv[0]);
                        printf("\tW S A D 移动摄像机\n");
                        printf("\tC 更换材质\n");
                        printf("\t使用鼠标滚轮进行缩放\n");
                        printf("\t按住左Ctrl建加快移动速度\n");
                        printf("\tESC 或 Q 退出游戏\n");

                        return EXIT_SUCCESS;
                }

                if (!strcmp(argv[1], "-f")) {
                        fullScreenMode = true;
                }
        }

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);


        GLFWwindow* window = NULL;
        if (fullScreenMode) {
                window = glfwCreateWindow(mode->width, mode->height,
                        "Hikari", glfwGetPrimaryMonitor(), NULL);
        } else {
                window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
                        "Hikari", NULL, NULL);
        }


        if (window == NULL)
        {
                fprintf(stderr, "Failed to create GLFW window.\n");
                glfwTerminate();
                return -1;
        }
        glfwSetWindowPos(window, (1920 - SCREEN_WIDTH) / 2,
                (1080 - SCREEN_HEIGHT) / 2 );
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
                fprintf(stderr, "Failed to initialize GLAD\n");
                glfwTerminate();
                return -1;
        }

        if (fullScreenMode)
                glViewport(0, 0, mode->width, mode->height);
        else
                glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        // glfwSetCursorPosCallback(window, mouse_cursor_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        GLuint cubeShader =
                load_program("cube.v.glsl", "cube.f.glsl");
        GLuint floorShader =
                load_program("floor.v.glsl", "floor.f.glsl");

        GLuint VBO, cubeVAO;
        glGenVertexArrays(1, &cubeVAO);
        glBindVertexArray(cubeVAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) (5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // unbind VAO, (unnecessary)
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        GLuint textures[10];
        textures[0] =  load_texture("../res/birch_planks.png", GL_RGB);
        textures[1] =  load_texture("../res/bookshell.png", GL_RGBA);
        textures[2] =  load_texture("../res/gravel.png", GL_RGB);
        textures[3] =  load_texture("../res/netherrack.png", GL_RGB);
        textures[4] =  load_texture("../res/dirt.png", GL_RGBA);
        textures[5] =  load_texture("../res/birch_trapdoor.png", GL_RGB);
        textures[6] =  load_texture("../res/light_blue_concrete.png", GL_RGBA);
        textures[7] =  load_texture("../res/purpur_pillar.png", GL_RGBA);
        textures[8] =  load_texture("../res/stone_bricks.png", GL_RGB);
        textures[9] =  load_texture("../res/bricks.png", GL_RGB);

        GLuint floorTexture = load_texture("../res/grass_floor.png", GL_RGBA);
        GLuint lightTexture =
                load_texture("../res/redstone_lamp_on.png", GL_RGBA);

        shaderSetInt(cubeShader, "texture0", 0);
        shaderSetInt(cubeShader, "texture1", 1);
        glUseProgram(cubeShader);
        shaderSetVec3(cubeShader, "lightPos", lightPos);
        shaderSetInt(cubeShader, "material.diffuse", 0);
        shaderSetFloat(cubeShader, "light.constant", 1.0f);
        shaderSetFloat(cubeShader, "light.linear", 0.09f);
        shaderSetFloat(cubeShader, "light.quadratic", 0.032f);

        glEnable(GL_DEPTH_TEST);

        // floor
        GLuint floorVAO, floorVBO;
        glGenVertexArrays(1, &floorVAO);
        glBindVertexArray(floorVAO);
        glGenBuffers(1, &floorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices),
                floorVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                8 * sizeof(float), (void*) (6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // camera
        struct Camera *camera = initCamera();

        vec3 lightAmbient = {0.2f, 0.2f, 0.2f};
        vec3 lightDiffuse = {0.8f, 0.8f, 0.8f};
        vec3 lightSpecular = {1.0f, 0.9f, 0.75f};
        // vec3 materialSpecular = {0.5f, 0.5f, 0.5f};
        float materialShininess = 64.0f;

        glUseProgram(floorShader);
        shaderSetInt(floorShader, "texture0", 0);
        glActiveTexture(GL_TEXTURE0);

        while (!glfwWindowShouldClose(window))
        {
                // input
                processInput(window);

                // render
                glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // time
                float currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;

                // hikari
                glUseProgram(cubeShader);
                shaderSetVec3(cubeShader, "light.position", lightPos);
                shaderSetVec3(cubeShader, "viewPos", camera->position);
                shaderSetVec3(cubeShader, "light.ambient", lightAmbient);
                shaderSetVec3(cubeShader, "light.diffuse", lightDiffuse);
                shaderSetVec3(cubeShader, "light.specular", lightSpecular);

                shaderSetInt(cubeShader,
                        "material.specular", 1);
                shaderSetFloat(cubeShader,
                        "material.shininess", materialShininess);

                // view and projection transform
                mat4 view;
                mat4 projection;
                glm_mat4_identity(view);
                glm_mat4_identity(projection);
                GetViewMatrix(&view);
                if (fullScreenMode)
                        glm_perspective(
                                glm_rad(camera->zoom),
                                (float)mode->width / (float)mode->height,
                                0.1, 100.0, projection
                        );
                else
                        glm_perspective(
                                glm_rad(camera->zoom),
                                (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
                                0.1, 100.0, projection
                        );

                shaderSetMat4(cubeShader, "view", view[0]);
                shaderSetMat4(cubeShader, "projection", projection[0]);

                // glBindBuffer(GL_ARRAY_BUFFER, VBO);
                // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

                // render 10 cubes
                for (int i = 0; i < 15; i++)
                {
                        // world transform
                        mat4 model;
                        glm_mat4_identity(model);
                        glm_translate(model, cubePositions[i]);
                        // rotate cube by time.
                        // vec4 axis = {0.0, 1.0f, 0.0};
                        // glm_rotate(model,
                                // glm_rad(currentFrame * 50 + 20 * i), axis);
                        shaderSetMat4(cubeShader, "model", model[0]);
                        shaderSetInt(cubeShader, "isLight", false);

                        // bind texture
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, textures[textureNum]);
                        // glActiveTexture(GL_TEXTURE1);
                        // glBindTexture(GL_TEXTURE_2D, texture1);

                        // render cube
                        glBindVertexArray(cubeVAO);
                        glDrawArrays(GL_TRIANGLES, 0, 36);
                }

                // lamp
                mat4 lightModel;
                glm_mat4_identity(lightModel);
                glm_translate(lightModel, lightPos);
                // lamp is smaller than cube
                glm_mat4_scale(lightModel, 0.1);
                shaderSetMat4(cubeShader, "model", lightModel[0]);
                // view and projection
                shaderSetMat4(cubeShader, "view", view[0]);
                shaderSetMat4(cubeShader, "projection", projection[0]);
                shaderSetInt(cubeShader, "isLight", true);
                // render lamp
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, lightTexture);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                // floor
                glUseProgram(floorShader);
                mat4 rockModel;
                glm_mat4_identity(rockModel);
                vec3 rockPosition = {0.0f, -2.0f, -5.0f};
                glm_translate(rockModel, rockPosition);
                vec4 axis = {1.0, 0.0f, 0.0};
                glm_rotate(rockModel,
                        glm_rad(90.0f), axis);
                // glm_mat4_scale(rockModel, 10.0f);
                shaderSetMat4(cubeShader, "model", rockModel[0]);
                shaderSetMat4(cubeShader, "view", view[0]);
                shaderSetMat4(cubeShader, "projection", projection[0]);

                glBindVertexArray(floorVAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, floorTexture);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                // unbind
                glBindVertexArray(0);
                // refresh
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glDeleteVertexArrays(1, &cubeVAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(cubeShader);

        glfwTerminate();
        return EXIT_SUCCESS;
}

void key_callback(GLFWwindow *window, int key, int s, int action, int mods)
{
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, GL_TRUE);
        }

        if (key == GLFW_KEY_C && action == GLFW_PRESS) {
                textureNum += 1;
                textureNum %= 10;
        }
}
void processInput(GLFWwindow *window)
{
        float speed = deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
                speed *= 2.0f;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_FORWARD, speed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_BACKWARD, speed);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_LEFT, speed);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_RIGHT, speed);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_DOWN, speed);
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                ProcessKeyboard(CAM_MOV_UP, speed);
        }
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
        if(firstMouse)
        {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // 这里是相反的，因为y坐标从底部往顶部依次增大
        lastX = xpos;
        lastY = ypos;

        ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
        ProcessMouseScroll(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
        glViewport(0, 0, width, height);
}
