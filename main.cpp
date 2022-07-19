#include "Graphene/graphene.h"
#include <SDL.h>

#ifdef _WIN32
#   include <Windows.h>
#   define __builtin_trap __debugbreak
#endif // _WIN32

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <glm/gtc/quaternion.hpp>

#ifdef _WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main(int argc, char **argv)
#endif
{
    /* Initializing SDL */
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Initializing SDL");
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL: %s", SDL_GetError());
        exit(3);
    }

    /* Setting up logging */
#ifdef DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#else
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);
#endif

    /* Setting up OpenGL */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

    /* Window */
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Creating window");
    SDL_Window *window = SDL_CreateWindow("GLplayground",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s", SDL_GetError());
        exit(3);
    }

    /* OpenGL context */
    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Creating context");
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (ctx)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Setting current context");
        SDL_GL_MakeCurrent(window, ctx);
    }
    else
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Couldn't create OpenGL context: %s", SDL_GetError());
        exit(3);
    }
    /* Setting up GLEW */
#ifndef __APPLE__
    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Initializing GLEW");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to init GLEW!");
        exit(3);
    }
#endif

    /* Initializing Graphene */
    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Initializing Graphene");
    std::unique_ptr<Graphene> graphene = std::make_unique<Graphene>();

    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Creating materials");
    std::shared_ptr<Graphene::Material::Default> defaultMaterial = std::make_shared<Graphene::Material::Default>();
    std::shared_ptr<Graphene::Material::Blinn> blinn = std::make_shared<Graphene::Material::Blinn>();

    std::shared_ptr<Graphene::Texture> flatLime = std::make_shared<Graphene::Texture::Color>(Graphene::Color(0.f, 1.f, 0.f));
    std::shared_ptr<Graphene::Texture> flatBlue = std::make_shared<Graphene::Texture::Color>(Graphene::Color(0.f, 0.2, 0.9));
    std::shared_ptr<Graphene::Texture> checker = std::make_shared<Graphene::Texture::Checker>(
        Graphene::Color(0.6, 0.6, 0.6),
        Graphene::Color(0.f, 0.f, 1.f)
    );
    blinn->setTexture(Graphene::Material::Blinn::TextureChannel::Diffuse, checker);

    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Populating scene");
    //    graphene->addModel(Graphene::SimpleObjects::Triangle());
    //    graphene->addModel(Graphene::SimpleObjects::Square());

    graphene->scene()->addModel(Graphene::SimpleObjects::Tetrahedron(
        fvec3(0.87, -0.25 / sqrt(3), 0.5),
        fquat(fvec3(0.f, 0.f, 0.f)), // fquat({0, -M_PI_2, 0})
        fvec3(1.f, 1.f, 1.f),
        blinn
    ));
    graphene->scene()->addModel(Graphene::SimpleObjects::Cube(
        fvec3(-0.87, 0, 0.5),
        fquat(fvec3(0.f, 0.f, 0.f)),
        fvec3(0.7, 0.7, 0.7),
        blinn
    ));
    graphene->scene()->addModel(Graphene::SimpleObjects::UVSphere(
        fvec3(0.0, 0.0, -1.f),
        fquat(fvec3(0.f, 0.f, 0.f)),
        fvec3(0.5, 0.5, 0.5),
        blinn
    ));

    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Adding lights");
    graphene->scene()->addLight(Graphene::Light::Omni(fvec3( 4.f,  4.f, -4.f), Graphene::Color(0.9, 1.0, 1.0), 20.f));
    graphene->scene()->addLight(Graphene::Light::Omni(fvec3(-4.f, -4.f,  4.f), Graphene::Color(1.0, 1.0, 0.9), 20.f));
    graphene->scene()->ambient(Graphene::Color(0.1, 0.1, 0.1));

    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Adding cameras");
    std::shared_ptr<Graphene::Camera> camera[4] = {
        std::make_shared<Graphene::Camera::Targeted>(fvec3(2.f, 0.f, 2.f), fvec3(0.f, 0.f, 0.f)),
        std::make_shared<Graphene::Camera::Targeted>(fvec3(0.5, 0.f, 2.f), fvec3(0.5, 0.f, 0.f)),
        std::make_shared<Graphene::Camera>(fvec3(2.f, 2.f, 2.f), fquat(fvec3(M_PI / -5, M_PI / 4, 0.f))),
        std::make_shared<Graphene::Camera>(fvec3(0.5, 0.f, 2.f), fquat(0.f, 0.f, 0.f, 1.f))
    };

    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Setting default camera");
    graphene->camera(camera[0]);

    /* Main loop */
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Running event loop");

    bool quit = false;
    bool fly = false;
    unsigned int modifiers = 0;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            const unsigned char *keyboardState = SDL_GetKeyboardState(nullptr);
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    SDL_LogInfo(
                        SDL_LOG_CATEGORY_INPUT,
                        "Window %d resized to %dx%d",
                        event.window.windowID,
                        event.window.data1,
                        event.window.data2
                    );
                    // Здесь баг: размер изображения зависит от высоты, но не от ширины
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    graphene->scene()->camera()->aspectRatio(float(event.window.data1) / float(event.window.data2));
                    graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                //SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Mouse moved by %+i %+i", event.motion.xrel, event.motion.yrel);
                if (event.motion.state & SDL_BUTTON_LMASK)
                {
                    if (graphene->scene()->camera()->type() == Graphene::Camera::Type::Free)
                        graphene->scene()->camera()->rotate(fvec3(-event.motion.yrel, -event.motion.xrel, 0) / 100.f);
                    else if (graphene->scene()->camera()->type() == Graphene::Camera::Type::Targeted)
                        graphene->scene()->camera()->orbit(fvec3(-event.motion.yrel, -event.motion.xrel, 0) / 100.f);
                    graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                }
                break;
            case SDL_MOUSEWHEEL:
                if (keyboardState[SDL_SCANCODE_LCTRL] || keyboardState[SDL_SCANCODE_RCTRL])
                {
                    if (event.wheel.y)
                    {
                        graphene->scene()->camera()->zoom(event.wheel.y / 20.f);
                        graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                    }
                }
                else
                {
                    if (event.wheel.y)
                    {
                        graphene->scene()->camera()->dolly(event.wheel.y / 10.f);
                        graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    SDL_Event quitEvent;
                    quitEvent.type = SDL_QUIT;
                    SDL_PushEvent(&quitEvent); // FIXME потенциально опасно пихать указатель на объект со стека
                    break;
                case SDLK_SPACE:
                    // сбросить камеру
                    break;
                case SDLK_1:
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Targeted camera 1");
                    graphene->camera(camera[0]);
                    break;
                case SDLK_2:
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Targeted camera 2");
                    graphene->camera(camera[1]);
                    break;
                case SDLK_3:
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Free camera 1");
                    graphene->camera(camera[2]);
                    break;
                case SDLK_4:
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Free camera 2");
                    graphene->camera(camera[3]);
                    break;
                case SDLK_c:
                {
                    bool cull = !graphene->cull();
                    graphene->cull(cull);
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Culling %s", cull ? "enabled" : "disabled");
                }
                break;
                case SDLK_f:
                {
                    fly = !fly;
                    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fly mode %s", fly ? "ON" : "OFF");
                }
                break;
                case SDLK_g:
                {
                    bool gc = !graphene->gammaCorrection();
                    graphene->gammaCorrection(gc);
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Gamma correction %s", gc ? "enabled" : "disabled");
                }
                break;
                case SDLK_w:
                {
                    bool wf = !graphene->wireframe();
                    graphene->wireframe(wf);
                    SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "%s rendering", wf ? "Wireframe" : "Shaded");
                }
                break;
                default:
                    SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Key %s pressed (scancode: %u)", SDL_GetKeyName(event.key.keysym.sym), event.key.keysym.scancode);
                }
                break;
            case SDL_QUIT:
                SDL_LogDebug(SDL_LOG_CATEGORY_SYSTEM, "Quit requested");
                quit = true;
                break;
            };
        }
        if (fly)
        {
            fvec3 step(0.f, 0.005, 0.f);
            fvec3 euler = graphene->scene()->camera()->euler();
            if ((euler + step).x > M_PI_2)
                step.x = -step.x;
            //if ((euler + step).y > M_PI_4)
            //    step.y = -step.y;
            //if ((euler + step).z > M_PI_4)
            //    step.z = -step.z;
            graphene->scene()->camera()->orbit(step);
            graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
        }
        if (graphene->drawScene())
        {
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Draw failed");
            __builtin_trap();
        }
        SDL_GL_SwapWindow(window);
    }
    
    /* Deinitialize everything */
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Sayonara");

    return 0;
}
