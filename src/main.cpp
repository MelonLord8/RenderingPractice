#include "main.h"
using namespace std;

int main(){
    GLFWwindow* window;
    //Initialising glfw
    if(!glfwInit()){
        cout << "GLFW couldn't start" << endl;
        return -1;
    }

    //Creates a window and binds it to the thread
    window = glfwCreateWindow(1000, 1000, "Spheres", NULL, NULL);
    glfwMakeContextCurrent(window);

    //Initialises pointers for the functions
    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        cout<< "GLAD couldn't start" << endl;
        glfwTerminate();
        return -1;
    }
    
    //Sets Needed Config:
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Creates Shader Program
    unsigned int shader_program = make_shader_program(
        "src/shaders/vertex.vert",
        "src/shaders/fragment.frag"
    );

    vector<Sphere *> spheres;
    for (int i = 0; i < NUM_SPHERES; i++)
    {
        vector<float> coords = {random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), random_float(-1.0f, 0.0f)};
        spheres.push_back(new Sphere(coords, RADIUS, LOD));
    }


    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);
        for (Sphere* sphere : spheres){
            sphere-> draw();
        }
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader_program);
    glfwTerminate();
    return 0;
}

unsigned int make_shader_program(const string& vertex_shader_filepath, const string& fragment_shader_filepath){
    vector<unsigned int> shader_modules;
    shader_modules.push_back(make_module(vertex_shader_filepath, GL_VERTEX_SHADER));
    shader_modules.push_back(make_module(fragment_shader_filepath, GL_FRAGMENT_SHADER));

    unsigned int program = glCreateProgram();
    for (unsigned int shader : shader_modules){
        glAttachShader(program ,shader);
    }

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success){
        char errorLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, errorLog);
        cout << "Shader Linking Error: \n" << errorLog << endl;  
    }

    for (unsigned int shader : shader_modules){
        glDeleteShader(shader);
    }

    return program;
}

unsigned int make_module(const string& filepath, unsigned int module_type){
    ifstream file;
    stringstream combinedLines;
    string line;
    file.open(filepath);

    while(getline(file, line)){
        combinedLines << line << "\n";
    }
    string shaderSource = combinedLines.str();
    const char * shaderSource_c = shaderSource.c_str();
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSource_c, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success){
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        cout << "Shader Module Compilation Error: \n" << errorLog << endl;  
    }

    return shaderModule;
}


float random_float(const float &min, const float &max){

    std::mt19937 rng(static_cast<unsigned int>(
    std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<float> dist(min, max);

    return dist(rng);
}