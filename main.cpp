#include "Graphene/graphene.h"
#include <SDL.h>

#ifdef _WIN32
#   include <Windows.h>
#endif // _WIN32

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _WIN32
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main(int argc, char ** argv)
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
                                            SDL_WINDOW_OPENGL);
    if (!window)
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s", SDL_GetError());
        exit(3);
    }

    /* OpenGL context */
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Creating context");
    SDL_GLContext ctx = SDL_GL_CreateContext(window);
    if (ctx)
    {
        SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Setting current context");
        SDL_GL_MakeCurrent(window, ctx);
    }
    else
    {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Couldn't create OpenGL context: %s", SDL_GetError());
        exit(3);
    }
    /* Setting up GLEW */
#ifndef __APPLE__
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Initializing GLEW");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to init GLEW!");
        exit(3);
    }
#endif
    
    /* Initializing Graphene */
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Initializing Graphene");  
    Graphene *graphene = new Graphene;
    
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Loading shaders");
    graphene->addShader(Graphene::VertexShader, std::filesystem::path("../vertex.glsl"));
    graphene->addShader(Graphene::FragmentShader, std::filesystem::path("../fragment.glsl"));
    
    SDL_LogInfo(SDL_LOG_CATEGORY_VIDEO, "Populating scene");
//    graphene->addModel(Graphene::SimpleObjects::Triangle());
//    graphene->addModel(Graphene::SimpleObjects::Square());
    graphene->addModel(Graphene::SimpleObjects::Tetrahedron());
    graphene->addModel(Graphene::SimpleObjects::Cube());

    graphene->scene()->addLight(Graphene::Light::Omni({ -1, 2, -4 }, { 0.0, 0.5, 0.5 }, 20.f));
    graphene->scene()->addLight(Graphene::Light::Omni({  1, -2, 4 }, { 0.5, 0.0, 0.0 }, 20.f));
    graphene->scene()->ambient({0.01, 0.01, 0.01});

    graphene->camera(new Graphene::Camera::Targeted({0, 2, 2}, {0, 0, 0}, 1.25, M_PI_4));
    
    /* Main loop */
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Running event loop");
    graphene->start();
    while (!SDL_QuitRequested()) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_MOUSEMOTION:
                //SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Mouse moved by %+i %+i", event.motion.xrel, event.motion.yrel);
                if (event.motion.state & SDL_BUTTON_LMASK)
                {
                    graphene->scene()->camera()->orbit(fvec3(-event.motion.xrel, -event.motion.yrel, 0) / 100.f);
                    graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                }
                break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y)
                {
                    graphene->scene()->camera()->dolly(event.wheel.y / 10.f);
                    graphene->scene()->touch(Graphene::Scene::Aspect::Camera);
                }
                break;
            case SDL_KEYDOWN:
                SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Key %u pressed", event.key.keysym.scancode);
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
                }
                break;
            case SDL_KEYUP:
                //SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "Key %u %s", event.key.keysym.scancode, event.key.state == SDL_PRESSED ? "pressed" : "released");
                break;
            case SDL_QUIT:
                SDL_Quit();
                break;
            };
        }
        if (graphene->draw())
            SDL_Quit();
        SDL_GL_SwapWindow(window);
    }
    graphene->stop();

    /* Deinitialize everything */
    delete graphene;
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Sayonara");

    return 0;
}
