#ifndef __SCENE_H__
#define __SCENE_H__

#include <set>

/*******************************************************************************
 * 
 * Graphene::Scene
 * 
 ******************************************************************************/

class Graphene::Scene
{
public:
    enum class Aspect {
        Geometry    = (uint16_t)1 << 0,
        Lights      = (uint16_t)1 << 1,
        Cameras     = (uint16_t)1 << 2,
        Environment = (uint16_t)1 << 3,
        Shaders     = (uint16_t)1 << 4,
        All         = (uint16_t)31
    };
    
protected:
    uint16_t m_Modified;
    std::set<std::shared_ptr<Graphene::Material>> m_Materials;
    std::vector<Graphene::Model> m_Models;
    std::vector<Graphene::Light> m_Lights;
    std::shared_ptr<Graphene::Camera> m_DefaultCamera;
    std::shared_ptr<Graphene::Camera> m_Camera;
    Graphene::Color m_Ambient;
    
public:
    Scene();
    virtual ~Scene() {
        SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Destoying scene");
    };
    virtual uint16_t modified() const;
    virtual bool modified(const Aspect &aspect) const;
    virtual void touch(const Aspect &aspect);
    virtual void depict(const Aspect &aspect);
    virtual void resetCamera();
    virtual std::shared_ptr<Graphene::Camera> camera() const;
    virtual void camera(std::shared_ptr<Graphene::Camera> &camera);
    virtual void addMaterial(std::shared_ptr<Material> material);
    virtual std::set<std::shared_ptr<Material>> &materials();
    virtual void addModel(const Model &model);
    virtual void addLight(const Graphene::Light &light);
    virtual Graphene::Color ambient() const;
    virtual void ambient(const Graphene::Color color);
    virtual size_t vertexCount() const;
    virtual size_t elementCount() const;
    virtual size_t lightCount() const;
    virtual size_t modelCount() const;
    virtual size_t VBOsize() const;
    virtual size_t EBOsize() const;
    virtual size_t UBOsize() const;
    virtual size_t SSBOsize() const;
    virtual size_t lightRangeSize() const;
    virtual size_t modelRangeSize() const;
    virtual size_t VBOdata(void *vertexBuffer) const;
    virtual size_t EBOdata(void *elementBuffer, std::shared_ptr<Material> material) const;
    virtual size_t UBOdata(void *unformBuffer) const;
    virtual size_t SSBOdata(void *storageBuffer) const;
    virtual size_t lightRangeData(void *storageBuffer) const;
    virtual size_t modelRangeData(void *storageBuffer) const;
    virtual fmat4 model() const;
};

#endif // __SCENE_H__
