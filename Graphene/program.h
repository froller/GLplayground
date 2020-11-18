#ifndef __PROGRAM_H__
#define __PROGRAM_H__

/*******************************************************************************
 * 
 * Graphene::Program
 * 
 ******************************************************************************/

class Graphene::Program
{
protected:
    GLuint m_Handle;
    std::vector<Shader> m_Shaders;
    std::string m_Log;
    uint64_t m_LastError;

public:
    Program();
    Program(const Program &) = delete;
    virtual ~Program();
    Program &operator=(const Program &) = delete;
    virtual GLuint handle() const;
    virtual void addShader(Shader &shader);
    virtual int link();
    virtual int use();
    virtual bool linked() const;
    virtual bool deleted() const;
    virtual bool valid() const;
    virtual int shaders() const;
    virtual int attributes() const;
    virtual int uniforms() const;
    virtual int uniformMaxLen() const;
    virtual unsigned int uniformIndex(const char *name) const;
    virtual char *uniformName(const unsigned int index) const;
    virtual unsigned int uniformType(const unsigned int index) const;
    virtual int uniformSize(const unsigned int index) const;
    virtual int setUniformBuffer(const unsigned int index, void *buffer) const;
    virtual int setUniformBuffer(const char *name, void *buffer) const;

    template<typename T>
    void setUniform(const unsigned int index, T value) const;
    
    template<typename T>
    int setUniform(const char *name, T value) const
    {
        const int index = glGetUniformLocation(m_Handle, name);
        if (index < 0)
            return index;
        setUniform(index, value);
        return 0;
    }
    
    virtual const char* log() const;
};

#endif // __PROGRAM_H__
