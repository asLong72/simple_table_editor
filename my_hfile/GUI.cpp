#include "GUI.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb-master/stb_image.h"

typedef struct MyCursor
{
	double x;
	double y;
	int key_press;
	int key_release;
}MyCursor;
MyCursor mycursor;
typedef unsigned ID;
ID progma_ID = 0;
ID VAO_ID = 0;
ID VBO_ID = 0;
ID EBO_ID = 0;

unsigned Loadprogma(const char vertex[], const char fragment[])
{
	int success;
	char infolog[512];
	long length;

	//编译顶点着色器
	FILE* vertexCode = fopen(vertex, "r");
	if (vertexCode == NULL)
	{
		printf("[ERROR]Failed to readin VertexProgmaCode\n");
		exit(-1);
	}
	fseek(vertexCode, 0, SEEK_END);
	length = ftell(vertexCode);
	char* vertexCode_str = (char*)malloc((length + 1) * sizeof(char));
	rewind(vertexCode);
	length = fread(vertexCode_str, 1, length, vertexCode);
	vertexCode_str[length] = '\0';
	unsigned vertex_ID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_ID, 1, &vertexCode_str, NULL);
	glCompileShader(vertex_ID);
	glGetShaderiv(vertex_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_ID, sizeof(infolog), NULL, infolog);
		printf("[ERROR]GL_VERTEX_SHADER:%s\n", infolog);
		exit(-1);
	}

	//编译片元着色器
	FILE* fragmentCode = fopen(fragment, "r");
	if (fragmentCode == NULL)
	{
		printf("[ERROR]Failed to readin FragmentProgmaCode\n");
		exit(-1);
	}
	fseek(fragmentCode, 0, SEEK_END);
	length = ftell(fragmentCode);
	char* fragmentCode_str = (char*)malloc((length + 1) * sizeof(char));
	rewind(fragmentCode);
	length = fread(fragmentCode_str, 1, length, fragmentCode);
	fragmentCode_str[length] = '\0';
	unsigned fragment_ID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_ID, 1, &fragmentCode_str, NULL);
	glCompileShader(fragment_ID);
	glGetShaderiv(fragment_ID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_ID, sizeof(infolog), NULL, infolog);
		printf("[ERROR]GL_FRAGMENT_SHADER:%s\n", infolog);
		exit(-1);
	}

	//链接着色器程序
	progma_ID = glCreateProgram();
	glAttachShader(progma_ID, vertex_ID);
	glAttachShader(progma_ID, fragment_ID);
	glLinkProgram(progma_ID);
	glGetProgramiv(progma_ID, GL_LINK_STATUS, &success);			//检查着色器程序是否链接成功
	if (!success)
	{
		glGetProgramInfoLog(progma_ID, 512, NULL, infolog);
		printf("[ERROR]glLinkProgram:%s\n", infolog);
		exit(-1);
	}
	//删除着色器程序
	glDeleteShader(vertex_ID);
	glDeleteShader(fragment_ID);

	return progma_ID;
}
unsigned LoadVAO()
{
	glGenVertexArrays(1, &VAO_ID);
	return VAO_ID;
}
unsigned LoadVBO()
{
	float vertex[]
	{
		0.0f,	0.0f,	0.0f,	0.0f,	0.0f,
		0.0f,	1.0f,	0.0f,	0.0f,	1.0f,
		1.0f,	0.0f,	0.0f,	1.0f,	0.0f,
		1.0f,	1.0f,	0.0f,	1.0f,	1.0f,
	};
	glBindVertexArray(VAO_ID);
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return VBO_ID;
}
unsigned LoadEBO()
{
	int indicat[]
	{
		0,1,2,
		1,2,3
	};

	glBindVertexArray(VAO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

	glGenBuffers(1, &EBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicat), indicat, GL_STATIC_DRAW);

	return EBO_ID;
}
void Load_all_normal()
{
	Loadprogma("my_shader/UIVS.glsl", "my_shader/UIFS.glsl");
	LoadVAO();
	LoadVBO();
	LoadEBO();
}
Texture2D Loadimage(const char* path)
{
	Texture2D newtexture;;
	glGenTextures(1, &newtexture.textID);
	glBindTexture(GL_TEXTURE_2D, newtexture.textID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	int width, height, nrChannels;
	GLenum format = 0;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	newtexture.width = width;
	newtexture.height = height;
	if (data)
	{
		switch (nrChannels)
		{
		case 1:
			format = GL_RED;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			break;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("[ERROR]Failed to load texture\n");
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, NULL);

	return newtexture;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void CursorPosCallback(GLFWwindow* window, double width, double height)
{
	mycursor.x = width;
	mycursor.y = height;
}
void CursorEnterCallback(GLFWwindow* window, int bool_type)
{
	if (bool_type == 0)
	{

	}
	else
	{

	}
}
void MouseButtonCallback(GLFWwindow* window, int key, int action, int mod)
{
	switch (action)
	{
	case GLFW_PRESS:
		mycursor.key_press = key;
		break;
	case GLFW_RELEASE:
		mycursor.key_release = key;
		break;
	default:
		break;
	}
}
void GLinit()
{
	if (glfwInit() == GLFW_FALSE)
	{
		printf("[ERROR]Failed to load GLFW\n");
		exit(-1);
	}
	else
	{
		printf("[INFO]Successfully loaded GLFW\n");
	}
	glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(720, 720, "name", NULL, NULL);
	if (window == NULL)
	{
		printf("[ERROR]Failed to creat window\n");
		exit(-1);
	}
	else
	{
		printf("[INFO]Successfully created window\n");
	}
	glfwMakeContextCurrent(window);
	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		printf("[ERROR]Failed to load GLAD\n");
		exit(-1);
	}
	else
	{
		printf("[INFO]Successfully loaded GLAD\n");
	}

	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSetCursorPosCallback(window, CursorPosCallback);
	glfwSetCursorEnterCallback(window, CursorEnterCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glClearColor(1, 1, 1, 1);
}
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == 1)
	{
		glfwSetWindowShouldClose(window, 1);
	}
}