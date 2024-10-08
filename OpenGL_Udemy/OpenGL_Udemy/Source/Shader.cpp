#include <Shader.h>

Shader::Shader(std::string& paths) :
    m_ShaderID(0)
{
    ShaderSource shaderSource;
    Shader::PreCompileShaders(paths);
}

Shader::~Shader()
{
    DebugLog(glDeleteProgram(m_ShaderID));
}

//Relative path from the solution
void Shader::PreCompileShaders(std::string& shaderFolderPath)
{
     const std::filesystem::path finalPath{ SOLUTION_DIR + shaderFolderPath };
   
    for (const auto& entry : std::filesystem::directory_iterator(finalPath)) {
        std::string name = entry.path().filename().string();
        std::string path = entry.path().string();;
        SanitizeName(name);

        std::cout << "dir: " << name << " - " << path << std::endl; 
        ShaderSource currentShader = Shader::ParseShader( name, path);
        Shader::RegisterShaderSource(currentShader, m_ShaderSources);
    }
}

void Shader::SanitizeName(std::string& name)
{
    std::string key(".shader");

    std::size_t found = name.rfind(key);
    if (found != std::string::npos)
        name.replace(found, key.length(), "");
}

ShaderSource Shader::ParseShader(const std::string& name, const std::string& path)
{
    ShaderSource currentSource;
    currentSource.name = name;
    currentSource.type = ShaderType::NONE;

    std::stringstream stringsStream;
    std::ifstream stream(path);
    std::string line;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                currentSource.type = ShaderType::VERTEX;
            
            else if (line.find("fragment") != std::string::npos)
                currentSource.type = ShaderType::FRAGMENT;
            
           //TODO: Implement
           // else if (line.find("tesseletion") != std::string::npos)
           //     currentSource.type = ShaderType::TESSELETION;
           // 
           // else if (line.find("geometry") != std::string::npos)
           //     currentSource.type = ShaderType::GEOMETRY;
           // 
           // else if (line.find("postProcessing") != std::string::npos)
           //     currentSource.type = ShaderType::POSTPROCESSING;
        }
        else
        {
            if (currentSource.type == ShaderType::NONE)
            {
                std::cout << path << "\n" 
                    << "PARSE SHADER FAILED: COULD NOT FIND A TYPE" << std::endl;
                break;
            }

            stringsStream << line << "\n";
        }
    }
    std::cout << stringsStream.str() << "------------------" << std::endl;

    currentSource.source = stringsStream.str();
    return currentSource;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    DebugLog(glShaderSource(id, 1, &src, nullptr));
    DebugLog(glCompileShader(id));

    int result;
    DebugLog(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int lenght = 0;
        DebugLog(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
        char* message = (char*)malloc(lenght * sizeof(char));
        DebugLog(glGetShaderInfoLog(id, lenght, &lenght, message));
        std::cout << "FAIL TO COMPILE SHADER - " << message << std::endl;

        //if shader do not compile, delete beforehand
        DebugLog(glDeleteShader(id));
        return 0;
    }
    return id;
}

void Shader::RegisterShaderSource(ShaderSource& shader, SHADER_SOURCE_MAP& shadersMap)
{
    switch (shader.type)
    {
        case ShaderType::VERTEX:
            shader.id = CompileShader(GL_VERTEX_SHADER, shader.source);
            shadersMap["vertex"][shader.name] = shader;
            std::cout << "SHADER ID: VERT - " << shader.id << std::endl;
            break;
        case ShaderType::FRAGMENT:
            shader.id = CompileShader(GL_FRAGMENT_SHADER, shader.source);
            shadersMap["fragment"][shader.name] = shader;
            std::cout <<  "SHADER ID: FRAG - " << shader.id << std::endl;
            break;
        
        //TODO: Implement 
        //case ShaderType::TESSELETION:
        //    shadersMap["tesseletion"][shader.name] = shader.id;
        //    break;
        //case ShaderType::GEOMETRY:
        //    shadersMap["geometry"][shader.name] = shader.id;
        //    break;
        //case ShaderType::POSTPROCESSING:
        //    shadersMap["postProcessing"][shader.name] = shader.id;
        //    break;
    }
}

void Shader::Bind() const
{
    DebugLog(glUseProgram(m_ShaderID));
}

void Shader::Unbind() const
{
    DebugLog(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float r, float g, float b, float a)
{
    DebugLog(glUniform4f(GetUniformLocation(name), r, g, b, a));
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
    DebugLog(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniform1i(const std::string& name, int i)
{
    DebugLog(glUniform1i(GetUniformLocation(name), i));
}

void Shader::SetUniform1f(const std::string& name, float f)
{
    DebugLog(glUniform1f(GetUniformLocation(name), f));
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLint location = glGetUniformLocation(m_ShaderID, name.c_str());

    if (location == -1)
        std::cout << "Uniform location not found: " << name << std::endl;
    m_uniformLocationCache[name] = location;

    return location;
}

unsigned int Shader::CreateProgram(const std::string& vertexName, const std::string& fragName)
{
    ShaderComposition composition;
    
    composition.vertexSource = m_ShaderSources.at("vertex").at(vertexName).id;
    composition.fragmentSource = m_ShaderSources.at("fragment").at(fragName).id;
    //TODO: Impement others shaders
    unsigned int program = ProgramSetup(composition);
    return program;
}

int Shader::ProgramSetup(const ShaderComposition& source)
{
    unsigned int program = glCreateProgram();

    DebugLog(glAttachShader(program, source.vertexSource));
    DebugLog(glAttachShader(program, source.fragmentSource));
    
    DebugLog(glLinkProgram(program));
    
    DebugLog(glDetachShader(program, source.vertexSource));
    DebugLog(glDetachShader(program, source.fragmentSource));
    
    DebugLog(glValidateProgram(program));
    m_ShaderID = program;
    return program;
}