#ifndef __SCENE_H__
#define __SCENE_H__

/*******************************************************************************
 * 
 * Graphene::Scene
 * 
 ******************************************************************************/

class Graphene::Scene
{
protected:
    std::vector<Graphene::Model> m_Models;
    std::vector<Graphene::Light> m_Lights;
    Graphene::Camera * const m_DefaultCamera;
    Graphene::Camera *m_Camera;
    Graphene::Color m_Ambient;
    
public:
    Scene();
    virtual ~Scene();
    virtual void resetCamera();
    virtual Graphene::Camera *camera() const;
    virtual void camera(Graphene::Camera *camera);
    virtual void addModel(const Graphene::Model &model);
    virtual void addLight(const Graphene::Light &light);
    virtual Graphene::Color ambient() const;
    virtual void ambient(const Graphene::Color color);
    virtual size_t vertexCount() const;
    virtual size_t elementCount() const;
    virtual size_t lightCount() const;
    virtual size_t VBOsize() const;
    virtual size_t EBOsize() const;
    virtual size_t lightsSize() const;
    virtual size_t VBOdata(void *vertexBuffer) const;
    virtual size_t EBOdata(void *elementBuffer) const;
    virtual size_t lightsData(void *lightsBuffer) const;
    virtual Graphene::Camera *camera();
    virtual fmat4 model() const;
};

#endif // __SCENE_H__
