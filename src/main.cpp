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
        vector<float> coords = {random_float(-1.0f, 1.0f), random_float(-1.0f, 0.0f), random_float(-1.0f, 1.0f)};
        spheres.push_back(new Sphere(coords, RADIUS, LOD));
    }

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int num_elements;

    send_data_to_gpu(spheres, VAO, VBO, EBO, num_elements);


    using clock = std::chrono::high_resolution_clock;

    auto lastTime = clock::now();
    while (!glfwWindowShouldClose(window)){
        auto currentTime = clock::now();

        std::chrono::duration<float> delta = currentTime - lastTime;
        float deltaTime = delta.count();

        std::cout << "Delta time: " << deltaTime << " seconds, FPS: " << 1/deltaTime <<std::endl;
        lastTime = currentTime;

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_program);

        draw(VAO, num_elements);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader_program);
    deallocate_buffers(VAO, VBO, EBO);
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

void send_data_to_gpu(const vector<Sphere*> &spheres, unsigned int &VAO, unsigned int &VBO, unsigned int &EBO, unsigned int &num_elements){
    vector<float> data{};
    vector<unsigned int> elements{};
    unsigned int offset = 0;
    for (const Sphere* sphere: spheres){
        data.insert(data.end(), sphere->vertex_data.begin(), sphere->vertex_data.end());
        for (unsigned int element : sphere->triangle_elements){
            elements.push_back(element + offset);
        }
        
        offset = data.size() / 6;
    }
    num_elements = elements.size();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
}

void draw(const unsigned int &VAO, const unsigned int &num_elements){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, num_elements, GL_UNSIGNED_INT, 0);
}

void deallocate_buffers(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}