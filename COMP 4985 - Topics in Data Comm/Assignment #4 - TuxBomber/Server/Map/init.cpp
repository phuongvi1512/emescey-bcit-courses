#include "user_map.h"
#include "init.h"
#include "statusbar.h"

SDL_Surface *screen;

using namespace std;
#define TOTAL_TILES 306

/*----------------------------------------------------------------------
-- METHOD:		genRandomMap
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	Alin Albu
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	unsigned char** genRandomMap(int rowNum, int colNum)
--
-- RETURNS:		void.
--
-- NOTES:
-- Generates a random map contained within a 2D array with sizes
-- specified by rowNum and colNum which are number of rows and columns
-- respectivly. 
----------------------------------------------------------------------*/
unsigned char** genRandomMap(int rowNum, int colNum)
{
	int tile,row;
	
	int sTime;
	long lTime;
	unsigned char **map;
	int i;
	lTime = time(NULL);
	sTime = (unsigned)lTime/2;
	srand(sTime);

	//Initialize map	
	map = (unsigned char**)malloc(rowNum * sizeof(unsigned char *));

	for(i = 0; i < rowNum; i++)
		map[i] = (unsigned char*)malloc(colNum * sizeof(unsigned char));

	//generate random map
	for(tile = 0, row = -1  ;tile < 306; tile++ )
	{
		// Places indestructables along left side.
		if(tile % 18 == 0)
		{
			row++;
			map[row][tile%18] = 0 ;
			continue;
		}
		// Places indestructables along the right side.
		if(tile % 18 == 16 || tile % 18 == 17 )
		{
			map[row][tile % 18] = 0;
			continue;
		}

		// Places indestructables along top and bottom.
		if((tile < 18 || tile > TOTAL_TILES -19))
		{
			map[row][tile%18] = 0;
			continue;
		}
		// Place indestructables at every second row and second column
		if( row % 2 == 0 && tile % 2 == 0)
		{
			map[row][tile%18] = 0;
			continue;
		}
		// Places either emprow or destructable in every open location.
		map[row][tile%18] = (rand()%2 + 1);	
	}
	
	//Clear spaces for player start positions
	
	//Player 1 (top left)
	map[1][1] = map[1][2] = map[2][1] = 2; 
	
	//Player 2(Top right)
	map[1][colNum - 3] = map[1][colNum - 4] = map[2][colNum - 3] = 2;
	
	//Player 3(Bot Left)
	map[rowNum - 2][1] = map[rowNum - 2][2] = map[rowNum - 3][1] = 2;
	
	//Player 4(Bot right)
	map[rowNum - 2][colNum - 3] = map[rowNum - 3][colNum - 3] 
		= map[rowNum - 2][colNum - 4] = 2;
	
	return map;
}

/*----------------------------------------------------------------------
-- METHOD:		load_image
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	Alin Albu
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	SDL_Surface *load_image( std::string filename )
--
-- RETURNS:		SDL_Surface *
--
-- NOTES:
-- Load an image into an SDL_Surface and then optimize and set 
-- transparancy.
----------------------------------------------------------------------*/
SDL_Surface *load_image( std::string filename )
{
	printf("insode load image");
	SDL_RWops *rwop;
	rwop=SDL_RWFromFile(filename.c_str(), "rb");
	
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
	
	if(IMG_isGIF(rwop))
		loadedImage = IMG_LoadGIF_RW(rwop);
    else
        //Load the image
    	loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, 
				SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
	if(optimizedImage == NULL)
		printf("Image is NULL!\n");
    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

/*------------------------------------------------------------------------------
-- METHOD:		sdl_init
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	void sdl_init()
--
-- RETURNS:
--
-- NOTES:
-- Initialize the screen SDL_Surface.
------------------------------------------------------------------------------*/
void sdl_init()
{
    SDL_Init( SDL_INIT_EVERYTHING );

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //turn video on
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);
    
    //video settings
    screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF);

    if (screen == NULL)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        exit(2);
    }

    SDL_WM_SetCaption( "Tux Bomber", NULL ); 
}

