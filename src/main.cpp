#include <iostream>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class BayuApp{
    public:
    BayuApp();
    SDL_Window* m_window;
    SDL_Surface* m_screensurface;
    SDL_Surface* m_helloworld;
    bool init();
    bool load_media();
    void close();
};

BayuApp::BayuApp() :
        m_window(0),
        m_screensurface(0),
        m_helloworld(0){
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

bool BayuApp::load_media(){
    bool success = true;
    //Load splash image
	m_helloworld = SDL_LoadBMP( "hello_world.bmp" );
	if( m_helloworld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
		success = false;
	}
    return success;
}

void BayuApp::close(){
    SDL_FreeSurface(m_helloworld);
    m_helloworld = NULL;
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
            SDL_BlitSurface(ulala.m_helloworld, NULL, ulala.m_screensurface, NULL);
            SDL_UpdateWindowSurface(ulala.m_window);
            SDL_Event e;
            bool quit = false;
            while(quit == false){
                while(SDL_PollEvent(&e)){
                    if( e.type == SDL_QUIT ) quit = true;
                }
            }
        }
    }
    ulala.close();

    return 0;
}