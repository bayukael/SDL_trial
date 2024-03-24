#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

class BayuApp{
    enum KeyPressSurfaces{
        KEY_PRESS_SURFACE_DEFAULT,
        KEY_PRESS_SURFACE_UP,
        KEY_PRESS_SURFACE_DOWN,
        KEY_PRESS_SURFACE_LEFT,
        KEY_PRESS_SURFACE_RIGHT,
        KEY_PRESS_SURFACE_TOTAL
    };
    SDL_Surface* load_optimized_surface(std::string path);
    public:
    BayuApp();
    SDL_Window* m_window;
    SDL_Surface* m_screensurface;
    SDL_Surface* m_backsurface;
    std::vector<SDL_Surface*> m_surfaces;
    bool init();
    bool load_media();
    bool run();
    void close();
};

BayuApp::BayuApp() :
        m_window(0),
        m_screensurface(0),
        m_backsurface(0),
        m_surfaces(KEY_PRESS_SURFACE_TOTAL){
    ;
}

bool BayuApp::init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        //Create window
		m_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( m_window == NULL ){
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else{
			//Get window surface
			m_screensurface = SDL_GetWindowSurface( m_window );
		}
    }
    return success;
}

SDL_Surface* BayuApp::load_optimized_surface(std::string path){
    SDL_Surface* original_surface = IMG_Load(path.c_str());
    // SDL_Surface* original_surface = SDL_LoadBMP(path.c_str());
    
    SDL_Surface* optimized_surface = NULL;
    if(original_surface != NULL){
        optimized_surface = SDL_ConvertSurface(original_surface, m_screensurface->format, 0);
        if( optimized_surface == NULL ){
            printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface(original_surface);
    }
    else{
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }    
    
    return optimized_surface;
}

bool BayuApp::load_media(){
    bool success = true;

    m_surfaces[KEY_PRESS_SURFACE_DEFAULT] = load_optimized_surface("images/loaded.png"); // converting 24 bit file to 32 bit file
    if( m_surfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "images/press.bmp", SDL_GetError() );
		success = false;
	}

    m_surfaces[KEY_PRESS_SURFACE_UP] = load_optimized_surface("images/up.bmp");
    if( m_surfaces[KEY_PRESS_SURFACE_UP] == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "images/up.bmp", SDL_GetError() );
		success = false;
	}

    m_surfaces[KEY_PRESS_SURFACE_DOWN] = load_optimized_surface("images/down.bmp");
    if( m_surfaces[KEY_PRESS_SURFACE_DOWN] == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "images/down.bmp", SDL_GetError() );
		success = false;
	}

    m_surfaces[KEY_PRESS_SURFACE_LEFT] = load_optimized_surface("images/left.bmp");
    if( m_surfaces[KEY_PRESS_SURFACE_LEFT] == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "images/left.bmp", SDL_GetError() );
		success = false;
	}

    m_surfaces[KEY_PRESS_SURFACE_RIGHT] = load_optimized_surface("images/right.bmp");
    if( m_surfaces[KEY_PRESS_SURFACE_RIGHT] == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "images/right.bmp", SDL_GetError() );
		success = false;
	}
    return success;
}

bool BayuApp::run(){
    SDL_Event e;
    bool quit = false;
    m_backsurface = m_surfaces[KEY_PRESS_SURFACE_DEFAULT];
    while(quit == false){
        while(SDL_PollEvent(&e)){
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_UP:
                        m_backsurface = m_surfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    
                    case SDLK_DOWN:
                        m_backsurface = m_surfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    
                    case SDLK_LEFT:
                        m_backsurface = m_surfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    
                    case SDLK_RIGHT:
                        m_backsurface = m_surfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;

                    default:
                        m_backsurface = m_surfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
        }

        // SDL_BlitSurface(m_backsurface, NULL, m_screensurface, NULL);
        SDL_Rect stretchRect;
        stretchRect.x = 512;
        stretchRect.y = 384;
        stretchRect.w = 480;
        stretchRect.h = 360;
        SDL_BlitScaled( m_backsurface, NULL, m_screensurface, &stretchRect );
        SDL_UpdateWindowSurface(m_window);
    }

    return true;
}

void BayuApp::close(){
    SDL_FreeSurface(m_backsurface);
    m_backsurface = NULL;
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
	{
		SDL_FreeSurface( m_surfaces[ i ] );
		m_surfaces[ i ] = NULL;
	}
    SDL_DestroyWindow(m_window);
    m_window = NULL;
    SDL_Quit();
}

int main(int argc, char* args[]){
    BayuApp ulala;
    if(!ulala.init()){
        printf( "Failed to initialize!\n" );
    }
    else{
        if(!ulala.load_media()){
            printf( "Failed to load media!\n" );
        }
        else{
            ulala.run();
        }
    }
    ulala.close();

    return 0;
}