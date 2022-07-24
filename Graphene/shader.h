#ifndef __SHADER_H__
#define __SHADER_H__

/*******************************************************************************
 * 
 * Graphene::Shader
 * 
 ******************************************************************************/

class Graphene::Shader
{    
protected:
    GLuint m_Handle;
    std::string m_Log;
    std::filesystem::path m_Path = "";
    uint64_t m_LastError;

public:
    Shader(const ShaderType type);
    Shader(const Shader &) = delete;
    Shader(Shader &&) = default;
    virtual ~Shader();
    Shader &operator=(const Shader &) = delete;
    Shader &operator=(Shader &&) = default;
    virtual GLuint handle() const;
    virtual int loadSource(const std::filesystem::path &path);
    virtual void setSource(const std::string &shader);
    virtual int compile();
    virtual bool compiled() const;
    virtual bool deleted() const;
    virtual ShaderType type() const;
    virtual const GLuint shaderType(const ShaderType type) const;
    virtual const ShaderType shaderType(const GLuint type) const;
    virtual const char *log() const;
};

#endif // __SHADER_H__
