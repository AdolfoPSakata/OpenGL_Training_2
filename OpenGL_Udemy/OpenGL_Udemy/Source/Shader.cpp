#include <Shader.h>

Shader::Shader(UniformManager& uniformManager)
{
    m_ShaderID = glCreateProgram();
    m_UniformManager = uniformManager;
    Shader::PreCompileShaders(m_ShaderPath);
    Shader::CreateProgram("BasicVertex", "BasicFrag");
}

Shader::~Shader()
{
    DebugLog(glDeleteProgram(m_ShaderID));
}

//Relative path from the solution
void Shader::PreCompileShaders(const std::string& shaderFolderPath)
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
   // std::cout << stringsStream.str() << "------------------" << std::endl;

    currentSource.source = stringsStream.str();
    return currentSource;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLint codeLenght[1] = { strlen(src) };

    glShaderSource(id, 1, &src, codeLenght);
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


unsigned int Shader::CreateProgram(const std::string& vertexName, const std::string& fragName)
{
    ShaderComposition composition;
    
    composition.vertexSource = m_ShaderSources.at("vertex").at(vertexName).id;
    composition.vertexUniformCount = 1;
    composition.vertexStrings = {"u_MVP"};

   composition.fragmentSource = m_ShaderSources.at("fragment").at(fragName).id;
   composition.fragUniformCount = 2;
   composition.fragStrings = { "u_Color" , "u_Texture" };

   //composition.fragmentSource = m_ShaderSources.at("fragment").at(fragName).id;
   //composition.fragUniformCount = 2;
   //composition.fragStrings = {  };

    //TODO: Impement others shaders
    unsigned int program = ProgramSetup(composition);
    return program;
}

//TODO::
int Shader::ProgramSetup(const ShaderComposition& source)
{
    DebugLog(glAttachShader(m_ShaderID, source.vertexSource));
    DebugLog(glAttachShader(m_ShaderID, source.fragmentSource));
    DebugLog(glLinkProgram(m_ShaderID));
    
    //TODO:: MOVE it
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_ShaderID, 1024, NULL, eLog);
        printf("Error linking program: %s \n", eLog);
    }

    //DebugLog(glDetachShader(m_ShaderID, source.vertexSource));
    //DebugLog(glDetachShader(m_ShaderID, source.fragmentSource));
    
    DebugLog(glValidateProgram(m_ShaderID));

    glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(m_ShaderID, 1024, NULL, eLog);
        printf("Error linking program: %s \n", eLog);
    }
    std::cout << " VERTEX UNIFORM: " << std::endl;
    for (int i = 0; i < source.vertexUniformCount; i++)
    {
        m_ShaderSources["vertex"]["BasicVertex"].uniformLocation[source.vertexStrings[i]] =
            m_UniformManager.PreProcessUniforms(m_ShaderID, source.vertexStrings[i]);
    }
    std::cout << " FRAG UNIFORM: " << std::endl;
    for (int i = 0; i < source.fragUniformCount; i++)
    {
       m_ShaderSources["fragment"]["BasicFrag"].uniformLocation[source.fragStrings[i]] =
           m_UniformManager.PreProcessUniforms(m_ShaderID, source.fragStrings[i]); 
    }

    return m_ShaderID;
}