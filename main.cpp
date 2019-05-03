#include <iostream>
#include <string>
#include <vector>
#include "src/rsdl.hpp"
#include <fstream>
 
using namespace std;

class WindowControl;

class MarioDieException {};
class MarioWinException {};

const string BACKGROUND_IMAGE = "./assets/background_image.png" ;
const vector<string> A_BRICK_IMAGES_ADDRESS = {"./assets/sprites/objects/bricks_blocks/question-1.png",
"./assets/sprites/objects/bricks_blocks/question-2.png","./assets/sprites/objects/bricks_blocks/question-3.png",
"./assets/sprites/objects/bricks_blocks/question-empty.png"};
const vector<string> S_BRICK_IMAGES_ADDRESS = {"./assets/sprites/objects/bricks_blocks/brick.png",
"./assets/sprites/objects/bricks_blocks/brick-debris.png"};
const vector<string> BLOCK_IMAGES_ADDRESS = {"./assets/sprites/objects/bricks_blocks/clay.png",
"./assets/sprites/objects/bricks_blocks/block.png"};
const vector<string> PIPE_HEAD_IMAGES_ADDRESS = {"./assets/sprites/objects/pipe/head-left.png",
"./assets/sprites/objects/pipe/head-right.png"};
const vector<string> PIPE_BODY_IMAGES_ADDRESS = {"./assets/sprites/objects/pipe/left.png",
"./assets/sprites/objects/pipe/right.png"};
const vector<string> FLAG_IMAGES_ADDRESS = {"./assets/sprites/objects/flag/body.png",
"./assets/sprites/objects/flag/head.png"};
const vector<string> GOOMBA_IMAGES_ADDRESS = {"./assets/sprites/enemies/little_goomba/dead.png",
"./assets/sprites/enemies/little_goomba/walking-1.png","./assets/sprites/enemies/little_goomba/walking-2.png"};
const string SHEEL_IMAGES_ADDRESS = "./assets/sprites/enemies/koopa_troopa/dead.png";
const vector<string> TURTLE_IMAGES_ADDRESS = {"./assets/sprites/enemies/koopa_troopa/walking-left-1.png",
"./assets/sprites/enemies/koopa_troopa/walking-left-2.png","./assets/sprites/enemies/koopa_troopa/walking-right-1.png",
"./assets/sprites/enemies/koopa_troopa/walking-right-2.png"};
const string COIN_IMAGES_ADDRESS = "./assets/sprites/objects/coin.png";
const vector<string> MUSHROOMS_IMAGES_ADDRESS = {"./assets/sprites/objects/mushroom/health.png",
"./assets/sprites/objects/mushroom/red.png"};

const string MARIO_NORMAL_IMAGE = "./assets/sprites/mario/normal/" ;
const string MARIO_BIG_IMAGE = "./assets/sprites/mario/big/" ;
const string MARIO_DEAD_IMAGE = "dead.png" ;
const vector<string> MARIO_JUMPING_IMAGE = {"jumping-left.png","jumping-right.png"} ;
const vector<string> MARIO_SLIDING_IMAGE = {"sliding-left.png","sliding-right.png"} ;
const vector<string> MARIO_STANDING_IMAGE = {"standing-left.png","standing-right.png"} ;
const vector<string> MARIO_WALKING_IMAGE = {"walking-left-1.png","walking-left-2.png","walking-left-3.png",
"walking-right-1.png","walking-right-2.png","walking-right-3.png"} ;

const string BACKGROUND_MUSIC = "./assets/sounds/Super Mario Bros. theme music.mp3" ;
const string BRICK_SMASH_SOUND = "./assets/sounds/sound_effects/brick-smash.wav" ;
const string BUMP_SOUND = "./assets/sounds/sound_effects/bump.wav";
const string COIN_SOUND = "./assets/sounds/sound_effects/coin.wav";
const string ENEMY_STOMP_SOUND = "./assets/sounds/sound_effects/enemy-stomp.wav";
const string GAMEOVER_SOUND = "./assets/sounds/sound_effects/gameover.wav";
const string JUMP_SOUND = "./assets/sounds/sound_effects/jump-super.wav";
const string LEVEL_CLEAR_SOUND = "./assets/sounds/sound_effects/level-clear.wav";
const string MARIO_DEATH_SOUND = "./assets/sounds/sound_effects/mario-death.wav";
const string POWERUP_SOUND = "./assets/sounds/sound_effects/powerup.wav";
const string LIVES_UP_SOUND = "./assets/sounds/sound_effects/1-up.wav";
const string POWERUP_APPEARES_SOUND = "./assets/sounds/sound_effects/powerup-appears.wav";

const int COIN_JUMP_SPEED = -30 ;
const int PIPE_HEAd = 0 ;
const int PIPE_BODY = 1 ;
const int MARIO_JUMP_SPEED = -55 ;
const int GRAVITY = -10 ;
const int MOMENT_SIZE = 10 ;
const int RIGHT_SIDE = 1 ;
const int LEFT_SIDE = 0 ;
const int MAP_ROOM_SIZE = 40 ;
const int WINDOW_WIDTH = 800 ;
const char MARIO = 'M' ;
const char AMAZING_BRICK[3] = {'?','m','h'} ;
const char COIN_BRICK = '?' ;
const char RED_MUSHROOM_BRICK = 'm' ;
const char HE_MUSHROOM_BRICK = 'h' ;
const char RED_MUSHROOM = 'm' ;
const char HEALTH_MUSHROOM = 'h' ;
const char SIMPLE_BRICK = 'b' ;
const char BLOCK[2] = {'@','#'} ;
const char SIMPLE_BLOCK = '@' ;
const char GRAND_BLOCK = '#' ;
const char PIPE = '|' ;
const char FLAG = 'f' ;
const char GOOMBA = 'l' ;
const char TURTLE = 'k' ;
const char RIGHT_MOVE_KEY = 'd' ;
const char LEFT_MOVE_KEY = 'a' ;
const char JUMP_KEY = 'w' ;



class GameMap
{
public:
	GameMap();
	void read_map_line(int row_num, ifstream &map_file);
	void read_all_the_map(string file_name);
	vector<Point> find_objects_in_map();
	vector<Point> find_objects_in_column(int column_num);
	char get_object_symbole(Point object_place);
	int get_map_row_num();
private:
	vector < vector<char> > map_columns;
	int map_row_num;
};

GameMap::GameMap()
{
	map_row_num = 0 ;
}

char GameMap::get_object_symbole(Point object_place)
{
	return map_columns[object_place.x/MAP_ROOM_SIZE][object_place.y/MAP_ROOM_SIZE];
}

int GameMap::get_map_row_num()
{
	return map_row_num;
}

void GameMap::read_map_line(int row_num, ifstream &map_file)
{
	string line;
	getline(map_file,line);
	for(int column_num = 0; column_num < line.size() ; column_num++)
	{
		
		if(row_num == 0)
		{
			vector<char> row;
			map_columns.push_back(row);
		}
		map_columns[column_num].push_back(line[column_num]);
	}
}

void GameMap::read_all_the_map(string file_name)
{
	ifstream map_file;
	map_file.open(file_name);
	while(true)
	{
		read_map_line(map_row_num,map_file);
		if (map_file.eof())
			break;
		map_row_num++;
	}
	map_file.close();
}

vector<Point> GameMap::find_objects_in_column(int column_num)
{
	vector <Point> column_objects ;
	for(int row_num = 0; row_num < map_columns[0].size(); row_num++)	
		if(map_columns[column_num][row_num] != '.')
			column_objects.push_back(Point(MAP_ROOM_SIZE*column_num,MAP_ROOM_SIZE*row_num));
	return column_objects;
}

vector<Point> GameMap::find_objects_in_map()
{
	vector <Point> objects_place;
	for(int column_num = 0; column_num < map_columns.size(); column_num++)
	{
		vector <Point> column_objects = find_objects_in_column(column_num);
		for(int object_num = 0 ; object_num < column_objects.size() ; object_num++)
			objects_place.push_back(column_objects[object_num]);
	}
	return objects_place;
}

class Background
{
public:
	Background(int _image_width,int _image_height, Window* _win);
	void draw_background();
	void shift_background_to_left();
	void show_texts(int live_num, int coin_num);

private:
	int image_x_coord;
	int image_y_coord;
	int image_width;
	int image_height;
	Window* win;
};

Background::Background(int _image_width,int _image_height, Window* _win)
{
	image_x_coord = 0;
	image_y_coord = WINDOW_WIDTH/2;
	image_width = _image_width;
	image_height = _image_height;
	win = _win ;
}

void Background::show_texts(int live_num, int coin_num)
{
	win->show_text("COINS",Point(WINDOW_WIDTH/2 - MAP_ROOM_SIZE*2,MAP_ROOM_SIZE),WHITE);
	win->show_text("LIVES",Point(WINDOW_WIDTH/2 + MAP_ROOM_SIZE*(1.5),MAP_ROOM_SIZE),WHITE);
	win->show_text(to_string(coin_num),Point(WINDOW_WIDTH/2 - MAP_ROOM_SIZE,MAP_ROOM_SIZE*2),WHITE);
	win->show_text(to_string(live_num),Point(WINDOW_WIDTH/2 + MAP_ROOM_SIZE*2,MAP_ROOM_SIZE*2),WHITE);
}


void Background::draw_background()
{
	win->draw_img(BACKGROUND_IMAGE,Rectangle(0,0,image_width,image_height),Rectangle(image_x_coord,image_y_coord,image_width,image_height));
	if(image_x_coord>2000-WINDOW_WIDTH)
		win->draw_img(BACKGROUND_IMAGE,Rectangle(image_width,0,WINDOW_WIDTH-image_width,image_height),Rectangle(0,image_y_coord,WINDOW_WIDTH-image_width,image_height));
}
void Background::shift_background_to_left()
{
	image_x_coord += MOMENT_SIZE;
	if(image_x_coord>2000-WINDOW_WIDTH)
		image_width -= MOMENT_SIZE;
	if(image_width==0)
	{
		image_x_coord=0;
		image_width = WINDOW_WIDTH;
	}
}


class WindowControl
{
public:
	WindowControl(int _width,int row_num, Window* _win, Background* _background);
	void draw_medium_image(Point image_place, string image_address);
	void draw_big_image(Point image_place, string image_address);
	bool is_mario_pass_the_camera(Point mario_plase);
	void make_background();
	Point get_place_in_window(Point object_place);
	bool is_object_in_camera_view(Point object_place);
	int get_camera_place();
	void update_camera_place(Point mario_plase);
	int get_window_height();
	Window* win;
private:
	Background* background;
	int camera_place;
	int width;
	int height;
	
};

WindowControl::WindowControl(int _width,int row_num , Window* _win , Background* _background)
	: background(_background)
{
	camera_place = WINDOW_WIDTH/2 ;
	width =_width;
	height = row_num * MAP_ROOM_SIZE ;
	win = _win;
}

int WindowControl::get_window_height()
{
	return height ;
}

bool WindowControl::is_object_in_camera_view(Point object_place)
{
	if(object_place.x < (camera_place + WINDOW_WIDTH/2) && object_place.x >= (camera_place - WINDOW_WIDTH/2 - MAP_ROOM_SIZE) )
		return true;
	return false;
}

int WindowControl::get_camera_place()
{
	return camera_place ;
}

Point WindowControl::get_place_in_window(Point object_place)
{
	return Point(object_place.x + WINDOW_WIDTH/2 - camera_place, object_place.y) ;
}

void WindowControl::draw_medium_image(Point image_place, string image_address)
{
	win->draw_img(image_address,Rectangle(image_place.x,image_place.y,MAP_ROOM_SIZE,MAP_ROOM_SIZE));
}

void WindowControl::draw_big_image(Point image_place, string image_address)
{
	win->draw_img(image_address,Rectangle(image_place.x,image_place.y-MAP_ROOM_SIZE,MAP_ROOM_SIZE,MAP_ROOM_SIZE*2));
}

bool WindowControl::is_mario_pass_the_camera(Point mario_plase)
{
	if(mario_plase.x > camera_place)
		return true;
	return false;
}

void WindowControl::update_camera_place(Point mario_plase)
{
	if(is_mario_pass_the_camera(mario_plase))
	{
		camera_place += MOMENT_SIZE*2 ;
		background->shift_background_to_left();
	}
}

class Mario
{
public:
	Mario(Point object_place) ;
	string give_image_address();
	void make_movemevt();
	void grow_up();
	void get_small();
	void get_shrink();
	string get_the_physique();
	void change_speed(int x_change, int y_change);
	void change_mario_direction(int mario_side);
	Point get_mario_speed();
	bool is_mario_in_ghost_state();
	void set_to_ghost_state();
	void change_place(int x_change, int y_change);
	Point get_place() {return mario_map_place ;}
	bool are_you_in_window() {return mario_map_place.x;}
private:
	Point mario_map_place;
	Point mario_speed;
	string mario_physique;
	int mario_direction;
	int mario_step_num;
	int mario_ghost_state;

};

Mario::Mario (Point object_place)
	: mario_map_place(object_place),mario_speed(Point(0,0))
{	
	mario_physique = "medium";
	mario_direction = RIGHT_SIDE ;
	mario_step_num = 2 ;
	mario_ghost_state = 0;
}

void Mario::set_to_ghost_state()
{
	mario_ghost_state = 10;
}

bool Mario::is_mario_in_ghost_state()
{
	if(mario_ghost_state != 0)
		return true;
	return false;
}

void Mario::change_place(int x_change, int y_change)
{
	mario_map_place.x += x_change;
	mario_map_place.y += y_change;
}

Point Mario::get_mario_speed()
{
	return mario_speed ;
}

void Mario::change_mario_direction(int mario_side)
{
	mario_direction = mario_side ;
}

void Mario::change_speed(int x_change, int y_change)
{
	mario_speed.x = x_change ;
	mario_speed.y = y_change ;
}

string Mario::get_the_physique()
{
	return mario_physique ;
}

void Mario::grow_up()
{
	mario_physique = "big";
}

void Mario::get_small()
{
	mario_physique = "medium";
}

void Mario::make_movemevt()
{
	mario_map_place += mario_speed ;
	if(mario_speed.y != 0)
		mario_speed.y += -GRAVITY ;
	if(mario_ghost_state != 0)
		mario_ghost_state--;

}

string Mario::give_image_address()
{
	string first_part;
	if(mario_physique == "medium")
		first_part = MARIO_NORMAL_IMAGE ;
	else
		first_part = MARIO_BIG_IMAGE ;

	string second_part ;
	if(mario_speed.x == 0 &&  mario_speed.y == 0 )
		second_part = MARIO_STANDING_IMAGE[mario_direction] ;
	if(mario_speed.y != 0)
		second_part = MARIO_JUMPING_IMAGE[mario_direction] ;
	if(mario_speed.y == 0 && mario_speed.x != 0)
	{
		mario_step_num = (1 + mario_step_num)%3 ;
		second_part = MARIO_WALKING_IMAGE[mario_direction*3 + mario_step_num] ;
	}
	return first_part + second_part ;
}

class AmazingBrick
{
public:
	AmazingBrick(Point object_place,char object_symbole);
	Point get_place();
	string give_image_address();
	char get_brick_kind();
	int get_strike_num();
	void increase_strike_num();
private:
	Point map_position;
	char brick_kind;
	int strike_num;
	int brick_color_num;
};

AmazingBrick::AmazingBrick(Point object_place,char object_symbole)
	: map_position(object_place)
{
	brick_kind = object_symbole ;
	strike_num = 0 ;
	brick_color_num = 0 ;
}

string AmazingBrick::give_image_address()
{
	if(strike_num != 0)
		return A_BRICK_IMAGES_ADDRESS[3];
	brick_color_num = (1 + brick_color_num)%4 ;
	if( brick_color_num < 2)
		return A_BRICK_IMAGES_ADDRESS[0] ;
	if(brick_color_num < 3)
		return A_BRICK_IMAGES_ADDRESS[1] ;
	if(brick_color_num < 4)
		return A_BRICK_IMAGES_ADDRESS[2] ;
}

Point AmazingBrick::get_place()
{
	return map_position ;
}

void AmazingBrick::increase_strike_num()
{
	strike_num++;
}

int AmazingBrick::get_strike_num()
{
	return strike_num;
}

char AmazingBrick::get_brick_kind()
{
	return brick_kind;
}

class SimpleBrick
{
public:
	SimpleBrick(Point object_place);
	void break_the_brick();
	void slip_up();
	Point get_place();
	string give_image_address();
	bool is_brick_broken();

private:
	Point map_position;
	int broken_brick;
};

SimpleBrick::SimpleBrick(Point object_place)
	: map_position(object_place)
{
	broken_brick = 0;
}

string SimpleBrick::give_image_address()
{
	if(broken_brick == 1)
		return S_BRICK_IMAGES_ADDRESS[1];
	return S_BRICK_IMAGES_ADDRESS[0];
}

Point SimpleBrick::get_place()
{
	return map_position ;
}

void SimpleBrick::break_the_brick()
{
	broken_brick = 1;
}

bool SimpleBrick::is_brick_broken()
{
	return broken_brick ;
}

class Block
{
public:
	Block(Point object_place,char object_symbole);
	Point get_place();
	string give_image_address();
	char get_block_kind();

private:
	Point map_position;
	char block_kind;
};

Block::Block(Point object_place,char object_symbole)
	: map_position(object_place)
{
	block_kind = object_symbole ;
}

string Block::give_image_address()
{
	if(block_kind == GRAND_BLOCK)
		return BLOCK_IMAGES_ADDRESS[0];
	return BLOCK_IMAGES_ADDRESS[1] ;
}

char Block::get_block_kind()
{
	return block_kind;
}

Point Block::get_place()
{
	return map_position ;
}

class Pipe
{
public:
	Pipe(Point object_place);
	Point get_place();
	string give_image_address(Pipe* next_pipe);
	char get_pipe_type();

private:
	Point map_position;
	int pipe_side;
	int pipe_type;
};

Pipe::Pipe(Point object_place)
	: map_position(object_place)
{
	pipe_side = LEFT_SIDE ;
	pipe_type = PIPE_HEAd ;
}

char Pipe::get_pipe_type()
{
	return pipe_type;
}

string Pipe::give_image_address(Pipe* next_pipe)
{
	string image_address;
	if(pipe_type == PIPE_HEAd)
		image_address = PIPE_HEAD_IMAGES_ADDRESS[pipe_side] ;
	else
		image_address = PIPE_BODY_IMAGES_ADDRESS[pipe_side] ;
	if(map_position.x == next_pipe->map_position.x)
	{
		next_pipe->pipe_type = PIPE_BODY ;
		next_pipe->pipe_side = pipe_side ;
	}
	else
		next_pipe->pipe_side = (LEFT_SIDE + RIGHT_SIDE) - pipe_side ;
	return image_address;
}

Point Pipe::get_place()
{
	return map_position ;
}

class Flag
{
public:
	Flag(Point object_place);
	Point get_place();
	string give_image_address(int flag_num);

private:
	Point map_position;
};

Flag::Flag(Point object_place)
	: map_position(object_place)
{
}

string Flag::give_image_address(int flag_num)
{
	if(flag_num == 0)
		return FLAG_IMAGES_ADDRESS[1];
	return FLAG_IMAGES_ADDRESS[0];
}

Point Flag::get_place()
{
	return map_position ;
}

class Goomba
{
public:
	Goomba(Point object_place);
	void make_movemevt();
	Point get_place();
	Point get_speed();
	string give_image_address();
	void start_moving();
	void get_to_die_mood();
	bool is_goomba_in_die_mood();
	void change_goomba_speed(int x_change , int y_change);

private:
	Point goomba_map_place;
	Point goomba_speed;
	vector<string> images_address;
	int goomba_step_num;
	int die_mood ;
};

Goomba::Goomba(Point object_place)
	: goomba_map_place(object_place), goomba_speed(Point(0,0))
{
	goomba_step_num = 2 ;
	die_mood = 0 ;
}

bool Goomba::is_goomba_in_die_mood()
{
	return die_mood ;
}

string Goomba::give_image_address()
{
	if(die_mood)
		return GOOMBA_IMAGES_ADDRESS[0] ;
	goomba_step_num = goomba_step_num%2 + 1 ;
	return GOOMBA_IMAGES_ADDRESS[goomba_step_num] ;
}

void Goomba::get_to_die_mood()
{
	die_mood = 1 ;
}

void Goomba::change_goomba_speed(int x_change , int y_change)
{
	goomba_speed.x = x_change ;
	goomba_speed.y = y_change ;
}

void Goomba::start_moving()
{
	if(goomba_speed.x == 0)
		goomba_speed.x = -MOMENT_SIZE ;
}

void Goomba::make_movemevt()
{
	goomba_map_place += goomba_speed ;
	if(goomba_speed.y == 0)
		goomba_speed.y = MAP_ROOM_SIZE ;
}

Point Goomba::get_speed()
{
	return goomba_speed ;
}

Point Goomba::get_place()
{
	return goomba_map_place ;
}

class Turtle
{
public:
	Turtle(Point object_place);
	void make_movemevt();
	Point get_place();
	Point get_speed();
	string give_image_address();
	void start_moving();
	void go_into_home();
	string get_the_state();
	void change_turtle_speed(int x_change , int y_change);
	void distroction();

private:
	Point turtle_map_place;
	Point turtle_speed;
	int turtle_direction;
	int turtle_step_num;
};

Turtle::Turtle(Point object_place)
	: turtle_map_place(object_place), turtle_speed(Point(0,0))
{
	turtle_direction = LEFT_SIDE ;
	turtle_step_num = 0 ;
}

string Turtle::give_image_address()
{
	turtle_step_num = (turtle_step_num + 1)%2 ;
	return TURTLE_IMAGES_ADDRESS[turtle_direction*2 + turtle_step_num];
}

void Turtle::change_turtle_speed(int x_change , int y_change)
{
	turtle_speed.x = x_change ;
	turtle_speed.y = y_change ;
}

Point Turtle::get_speed()
{
	return turtle_speed;
}

void Turtle::start_moving()
{
	if(turtle_speed.x == 0)
		turtle_speed.x = -MOMENT_SIZE ;
}

void Turtle::make_movemevt()
{
	turtle_map_place += turtle_speed ;
	if(turtle_speed.y == 0)
		turtle_speed.y = MAP_ROOM_SIZE ;
}

Point Turtle::get_place()
{
	return turtle_map_place ;
}

class Coin
{
public:
	Coin(Point coin_place);
	void make_movement();
	string give_image_address();
	Point get_place();

private:
	Point map_position;
	Point coin_speed;
	string image_address;
};

Coin::Coin(Point coin_place)
	: map_position(coin_place), coin_speed(Point(0,COIN_JUMP_SPEED))
{
	image_address = COIN_IMAGES_ADDRESS ;
}

void Coin::make_movement()
{
	map_position += coin_speed;
	coin_speed.y += -GRAVITY ;
}

string Coin::give_image_address()
{
	return image_address;
}

Point Coin::get_place()
{
	return map_position ;
}

class Mushroom
{
public:
	Mushroom(Point mushroom_place ,int _mushroom_type);
	void make_movement();
	string give_image_address();
	Point get_place();
	Point get_speed();
	void come_out();
	int get_grow_time();
	char get_mushroom_type();
	void change_mushroom_speed(int x_change ,int y_change);

private:
	Point map_position;
	Point mushroom_speed;
	int grow_time;
	char mushroom_type;
};

Mushroom::Mushroom(Point mushroom_place ,int _mushroom_type)
	: map_position(mushroom_place), mushroom_speed(Point(MOMENT_SIZE,0))
{
	grow_time = 0;
	mushroom_type = _mushroom_type;
}

int Mushroom::get_grow_time()
{
	return grow_time;
}

char Mushroom::get_mushroom_type()
{
	return mushroom_type ;
}

void Mushroom::come_out()
{
	map_position.y -= MOMENT_SIZE ;
	grow_time++ ;
}

void Mushroom::make_movement()
{
	map_position += mushroom_speed;
	if(mushroom_speed.y == 0)
		mushroom_speed.y = MAP_ROOM_SIZE;
}

string Mushroom::give_image_address()
{
	if(mushroom_type == HEALTH_MUSHROOM)
		return MUSHROOMS_IMAGES_ADDRESS[0];
	return MUSHROOMS_IMAGES_ADDRESS[1] ;
}

Point Mushroom::get_place()
{
	return map_position ;
}

void Mushroom::change_mushroom_speed(int x_change ,int y_change)
{
	mushroom_speed.x = x_change;
	mushroom_speed.y = y_change;
}

Point Mushroom::get_speed()
{
	return mushroom_speed;
}

class Sheel
{
public:
	Sheel(Point object_place);
	Point get_place();
	string give_image_address();
	Point get_speed();
	void change_sheel_speed(int x_change, int y_change);
	void make_movement();

private:
	Point map_position ;
	Point sheel_speed;
};

Sheel::Sheel(Point object_place)
	: map_position(object_place) , sheel_speed(Point(0,0))
{
}

Point Sheel::get_speed()
{
	return sheel_speed;
}

void Sheel::change_sheel_speed(int x_change, int y_change)
{
	sheel_speed.x = x_change;
	sheel_speed.y = y_change;
}

Point Sheel::get_place()
{
	return map_position ;
}

string Sheel::give_image_address()
{
	return SHEEL_IMAGES_ADDRESS ;
}

void Sheel::make_movement()
{
	map_position += sheel_speed ;
	if(sheel_speed.y == 0)
		sheel_speed.y = MAP_ROOM_SIZE;
}

	
class Process
{
public:
	Process(WindowControl* _windowcontrol,int* _lives_num);
	void delete_all_classes();
	void make_objects_of_game(GameMap* game_map);
	void make_object(char object_symbole, Point object_place);
	int get_coin_num();
	void process_objects_state();
	void process_mario_state();
	void process_amazing_bricks_state();
	void process_simple_bricks_state();
	void process_blocks_state();
	void process_pipes_state();
	void process_goombas_state();
	void process_turtles_state();
	void process_flags_state();
	void process_coins_state();
	void process_mushrooms_state();
	void process_sheels_state();
	void convert_turtle_to_sheel(int turtle_num);
	void increase_lives_num();
	void make_a_brick_content(char brick_kind,Point brick_place);
	void delete_mushroom(int mushroom_num);
	void delete_sheel(int sheel_num);
	void delete_coin(int coin_num);
	void apply_keys_press_effect();
	void hit_the_sheel_to_move(Sheel* sheel);
	void apply_left_key_effect();
	void apply_right_key_effect();
	void apply_top_key_effect();

	Mario* mario;
	vector <AmazingBrick*> amazing_brick_list;
	vector <SimpleBrick*> simple_brick_list;
	vector <Block*> block_list;
	vector <Pipe*> pipe_list;
	vector <Flag*> flags_list;
	vector <Goomba*> goomba_list;
	vector <Turtle*> turtle_list;
	vector <Coin*> coin_list;
	vector <Mushroom*> mushroom_list;
	vector <Sheel*> sheel_list ;
	WindowControl* window_control;

private:
	int* lives_num;
	int coin_num;
};

Process::Process(WindowControl* _windowcontrol,int* _lives_num)
	:window_control(_windowcontrol)
{
	lives_num = _lives_num;
}

int Process::get_coin_num()
{
	return coin_num;
}

void Process::convert_turtle_to_sheel(int turtle_num)
{
	sheel_list.push_back(new Sheel(turtle_list[turtle_num]->get_place())) ;
	delete turtle_list[turtle_num] ;
	turtle_list.erase(turtle_list.begin()+turtle_num);
}

void Process::make_a_brick_content(char brick_kind , Point brick_place)
{
	if(brick_kind == COIN_BRICK)
	{
		coin_list.push_back(new Coin(brick_place+Point(0,-MAP_ROOM_SIZE)));
		window_control->win->play_sound_effect(COIN_SOUND);
		coin_num ++ ;
	}
	if(brick_kind == RED_MUSHROOM_BRICK || brick_kind == HE_MUSHROOM_BRICK)
	{
		mushroom_list.push_back(new Mushroom(brick_place, brick_kind));
		window_control->win->play_sound_effect(POWERUP_APPEARES_SOUND);
	}
}

void Process::increase_lives_num()
{
	(*lives_num)++ ;
}

void Process::hit_the_sheel_to_move(Sheel* sheel)
{
	window_control->win->play_sound_effect(ENEMY_STOMP_SOUND);
	mario->change_place(0,-MAP_ROOM_SIZE);
	if(mario->get_mario_speed().x > 0 )
	{
		sheel->change_sheel_speed(MOMENT_SIZE*2 , 0);
		mario->change_speed(-MOMENT_SIZE*2,-25);
	}
	else
	{
		sheel->change_sheel_speed(-MOMENT_SIZE*2 , 0);
		mario->change_speed(MOMENT_SIZE*2,-25);
	}
}

void Process::delete_all_classes()
{
	delete mario ;
	for(int brick_num = 0; brick_num < amazing_brick_list.size(); brick_num++)
		delete amazing_brick_list[brick_num] ;
	for(int brick_num = 0; brick_num < simple_brick_list.size(); brick_num++)
		delete simple_brick_list[brick_num] ;
	for(int block_num = 0; block_num < block_list.size(); block_num++)
		delete block_list[block_num] ;
	for(int pipe_num = 0; pipe_num < pipe_list.size(); pipe_num++)
		delete pipe_list[pipe_num] ;
	for(int flag_num = 0; flag_num < flags_list.size(); flag_num++)
		delete flags_list[flag_num] ;
	for(int pipe_num = 0; pipe_num < pipe_list.size(); pipe_num++)
		delete goomba_list[pipe_num] ;
	for(int turtle_num = 0; turtle_num < turtle_list.size(); turtle_num++)
		delete turtle_list[turtle_num] ;
	for(int coin_num = 0; coin_num < coin_list.size(); coin_num++)
		delete coin_list[coin_num] ;
	for(int mushroom_num = 0; mushroom_num < mushroom_list.size(); mushroom_num++)
		delete mushroom_list[mushroom_num] ;
	for(int sheel_num = 0; sheel_num < sheel_list.size(); sheel_num++)
		delete sheel_list[sheel_num] ;
	delete window_control ;
}

void Process::delete_mushroom(int mushroom_num)
{
	delete mushroom_list[mushroom_num] ;
	mushroom_list.erase(mushroom_list.begin() + mushroom_num) ;
}

void Process::delete_coin(int coin_num)
{
	delete coin_list[coin_num] ;
	coin_list.erase(coin_list.begin() + coin_num) ;
}

void Process::delete_sheel(int sheel_num)
{
	delete sheel_list[sheel_num] ;
	sheel_list.erase(sheel_list.begin() + sheel_num) ;
}

void Process::process_mario_state()
{
	if(mario->get_the_physique() == "medium")
		window_control->draw_medium_image(window_control->get_place_in_window(mario->get_place()),mario->give_image_address());
	else
		window_control->draw_big_image(window_control->get_place_in_window(mario->get_place()),mario->give_image_address());
	mario->make_movemevt();
	if(mario->get_place().y > window_control->get_window_height())
		throw MarioDieException();
}

void Process::process_goombas_state()
{
	for(int goomba_num = 0; goomba_num < goomba_list.size(); goomba_num++)
	{
		if(window_control->is_object_in_camera_view(goomba_list[goomba_num]->get_place()))
		{
			goomba_list[goomba_num]->start_moving();
			window_control->draw_medium_image(window_control->get_place_in_window(goomba_list[goomba_num]->get_place()),goomba_list[goomba_num]->give_image_address());
		}
		goomba_list[goomba_num]->make_movemevt();
		if(goomba_list[goomba_num]->is_goomba_in_die_mood() || goomba_list[goomba_num]->get_place().y > window_control->get_window_height())
		{
			delete goomba_list[goomba_num];
			goomba_list.erase(goomba_list.begin()+goomba_num) ;
			goomba_num--;
		}
	}
}

void Process::process_turtles_state()
{
	for(int turtle_num = 0; turtle_num < turtle_list.size(); turtle_num++)
	{
		if(window_control->is_object_in_camera_view(turtle_list[turtle_num]->get_place()))
		{
				turtle_list[turtle_num]->start_moving();
				window_control->draw_big_image(window_control->get_place_in_window(turtle_list[turtle_num]->get_place()),turtle_list[turtle_num]->give_image_address());
		}
		turtle_list[turtle_num]->make_movemevt();
		if(turtle_list[turtle_num]->get_place().y > window_control->get_window_height())
			convert_turtle_to_sheel(turtle_num);
	}
	
}

void Process::process_coins_state()
{
	for(int coin_num = 0; coin_num < coin_list.size(); coin_num++)
	{
		window_control->draw_medium_image(window_control->get_place_in_window(coin_list[coin_num]->get_place()),coin_list[coin_num]->give_image_address());
		coin_list[coin_num]->make_movement();
	}
}

void Process::process_mushrooms_state()
{
	for(int mushroom_num = 0; mushroom_num < mushroom_list.size(); mushroom_num++)
	{
		window_control->draw_medium_image(window_control->get_place_in_window(mushroom_list[mushroom_num]->get_place()),mushroom_list[mushroom_num]->give_image_address());
		if(mushroom_list[mushroom_num]->get_grow_time() < 4)
			mushroom_list[mushroom_num]->come_out();
		else
			mushroom_list[mushroom_num]->make_movement();
		if(mushroom_list[mushroom_num]->get_place().y > window_control->get_window_height())
			delete_mushroom(mushroom_num);
	}
}

void Process::process_pipes_state()
{
	for(int pipe_num = 0; pipe_num < pipe_list.size(); pipe_num++)
	{
		if(window_control->is_object_in_camera_view(pipe_list[pipe_num]->get_place()))
		{
			if(pipe_num == pipe_list.size() -1)
				window_control->draw_medium_image(window_control->get_place_in_window(pipe_list[pipe_num]->get_place()),PIPE_BODY_IMAGES_ADDRESS[RIGHT_SIDE]);
			else
				window_control->draw_medium_image(window_control->get_place_in_window(pipe_list[pipe_num]->get_place()),pipe_list[pipe_num]->give_image_address(pipe_list[pipe_num +1]));
		}
	}
}

void Process::process_blocks_state()
{
	for(int block_num = 0; block_num < block_list.size(); block_num++)
	{
		if(window_control->is_object_in_camera_view(block_list[block_num]->get_place()))
			window_control->draw_medium_image(window_control->get_place_in_window(block_list[block_num]->get_place()),block_list[block_num]->give_image_address());
	}
}

void Process::process_amazing_bricks_state()
{
	for(int brick_num = 0; brick_num < amazing_brick_list.size(); brick_num++)
	{
		if(window_control->is_object_in_camera_view(amazing_brick_list[brick_num]->get_place()))
			window_control->draw_medium_image(window_control->get_place_in_window(amazing_brick_list[brick_num]->get_place()),amazing_brick_list[brick_num]->give_image_address());
	}
}

void Process::process_simple_bricks_state()
{
	for(int brick_num = 0; brick_num < simple_brick_list.size(); brick_num++)
	{
		if(window_control->is_object_in_camera_view(simple_brick_list[brick_num]->get_place()))
			window_control->draw_medium_image(window_control->get_place_in_window(simple_brick_list[brick_num]->get_place()),simple_brick_list[brick_num]->give_image_address());
		if(simple_brick_list[brick_num]->is_brick_broken())
		{
			delete simple_brick_list[brick_num];
			simple_brick_list.erase(simple_brick_list.begin()+brick_num) ;
			brick_num--;
		}
	}
}

void Process::process_flags_state()
{
	for(int flag_num = 0; flag_num < flags_list.size(); flag_num++)
	{
		if(window_control->is_object_in_camera_view(flags_list[flag_num]->get_place()))
			window_control->draw_medium_image(window_control->get_place_in_window(flags_list[flag_num]->get_place()),flags_list[flag_num]->give_image_address(flag_num));
	}
}

void Process::process_sheels_state()
{
	for(int sheel_num = 0; sheel_num < sheel_list.size(); sheel_num++)
	{
		if(window_control->is_object_in_camera_view(sheel_list[sheel_num]->get_place()))
			window_control->draw_medium_image(window_control->get_place_in_window(sheel_list[sheel_num]->get_place()),sheel_list[sheel_num]->give_image_address());
		sheel_list[sheel_num]->make_movement();
		if(sheel_list[sheel_num]->get_place().y > window_control->get_window_height())
			delete_sheel(sheel_num);
	}
	
}

void Process::process_objects_state()
{
	process_mario_state();
	process_coins_state();
	process_sheels_state();
	process_mushrooms_state();
	process_amazing_bricks_state();
	process_simple_bricks_state();
	process_blocks_state();
	process_pipes_state();
	process_goombas_state();
	process_turtles_state();
	process_flags_state();

}

void Process::make_objects_of_game(GameMap* game_map)
{
	vector <Point> objects_place;
	objects_place = game_map->find_objects_in_map();
	for(int object_num = 0; object_num < objects_place.size(); object_num++)
	{

		char object_symbole = game_map->get_object_symbole(objects_place[object_num]);
		make_object(object_symbole, objects_place[object_num]);
	}
}

void Process::make_object(char object_symbole, Point object_place)
{
	if(object_symbole == MARIO)
		mario = new Mario(object_place);
	if(object_symbole == AMAZING_BRICK[0] || object_symbole == AMAZING_BRICK[1] || object_symbole == AMAZING_BRICK[2])
		amazing_brick_list.push_back(new AmazingBrick(object_place,object_symbole));
	if(object_symbole == SIMPLE_BRICK)
		simple_brick_list.push_back(new SimpleBrick(object_place));
	if(object_symbole == BLOCK[0] || object_symbole == BLOCK[1])
		block_list.push_back(new Block(object_place,object_symbole));
	if(object_symbole == PIPE)
		pipe_list.push_back(new Pipe(object_place));
	if(object_symbole == FLAG)
		flags_list.push_back(new Flag(object_place)) ;
	if(object_symbole == GOOMBA)
		goomba_list.push_back(new Goomba(object_place));
	if(object_symbole == TURTLE)
		turtle_list.push_back(new Turtle(object_place));
}

void Process::apply_right_key_effect()
{
	mario->change_speed(MOMENT_SIZE*2,mario->get_mario_speed().y);
	if(mario->get_mario_speed().y == 0)
		mario->change_mario_direction(RIGHT_SIDE);
}

void Process::apply_left_key_effect()
{
	if(mario->get_place().x != window_control->get_camera_place() - WINDOW_WIDTH/2)
		mario->change_speed(-MOMENT_SIZE*2,mario->get_mario_speed().y);
	if(mario->get_mario_speed().y == 0)
		mario->change_mario_direction(LEFT_SIDE);
}

void Process::apply_top_key_effect()
{
	if(mario->get_mario_speed().y == 0)
	{
		mario->change_speed(mario->get_mario_speed().x,MARIO_JUMP_SPEED);
		window_control->win->play_sound_effect(JUMP_SOUND);
	}
}

void Process::apply_keys_press_effect()
{
	mario->change_speed(0,mario->get_mario_speed().y);
	while(window_control->win->has_pending_event()) 
	{
		Event event = window_control->win->poll_for_event();
		char pressed_char;
   		if(event.get_type()==Event::KEY_PRESS)
		{
			pressed_char = event.get_pressed_key();
			if (pressed_char == RIGHT_MOVE_KEY)
				apply_right_key_effect();
			if (pressed_char == LEFT_MOVE_KEY)
				apply_left_key_effect();
			if(pressed_char == JUMP_KEY)
				apply_top_key_effect();
		}
	}

}

class Collision
{
public:
	void handle_all_collisions(Process* process) ;
	void handle_goombas_collision(Process* process);
	void handle_turtles_collision(Process* process);
	void handle_mushrooms_collision(Process* process);
	void handle_sheels_collision(Process* process);
	void handle_coins_collision(Process* process);
	void handle_mario_collision(Process* process);
	void handle_goomba_collision(Process* process, Goomba* goomba);
	void handle_turtle_collision(Process* process, Turtle* turtle,int turtle_num);
	void handle_mushroom_collision(Process* process, Mushroom* mushroom ,int mushroom_num);
	void handle_coin_collision(Process* process, Coin* coin ,int coin_num);
	void handle_sheel_collision(Process* process, Sheel* sheel);
	void handle_mario_collision_with_a_brick(Process* process, int a_brick_num);
	void handle_big_mario_collision_with_s_brick(Process* process , int s_brick_num);
	void handle_medium_mario_collision_with_s_brick(Process* process , int s_brick_num);
	void handle_mario_collision_with_blocks(Process* process);
	void handle_mario_collision_with_flags(Process* process);
	void handle_big_mario_collision_with_a_bricks(Process* process);
	void handle_big_mario_collision_with_s_bricks(Process* process);		
	void handle_medium_mario_collision_with_a_bricks(Process* process);
	void handle_medium_mario_collision_with_s_bricks(Process* process);	
	void handle_medium_mario_collision_with_pipes(Process* process);
	void handle_goomba_collision_with_blocks(Process* process,Goomba* goomba);
	void handle_goomba_collision_with_s_bricks(Process* process,Goomba* goomba);
	void handle_goomba_collision_with_a_bricks(Process* process,Goomba* goomba);
	void handle_goomba_collision_with_pipes(Process* process,Goomba* goomba);
	void handle_goomba_collision_with_medium_mario(Process* process,Goomba* goomba);
	void handle_goomba_collision_with_big_mario(Process* process,Goomba* goomba);
	void handle_turtle_collision_with_blocks(Process* process,Turtle* turtle);
	void handle_turtle_collision_with_s_bricks(Process* process,Turtle* turtle);
	void handle_turtle_collision_with_a_bricks(Process* process,Turtle* turtle);
	void handle_turtle_collision_with_pipes(Process* process,Turtle* turtle);
	void handle_turtle_collision_with_medium_mario(Process* process, Turtle* turtle, int turtle_num);
	void handle_turtle_collision_with_big_mario(Process* process, Turtle* turtle, int turtle_num);
	void handle_mushroom_collision_with_blocks(Process* process,Mushroom* mushroom);
	void handle_mushroom_collision_with_s_bricks(Process* process,Mushroom* mushroom );
	void handle_mushroom_collision_with_a_bricks(Process* process,Mushroom* mushroom );
	void handle_mushroom_collision_with_pipes(Process* process,Mushroom* mushroom );
	void handle_mushroom_collision_with_mario(Process* process,Mushroom* mushroom ,int mushroom_num);
	void handle_sheel_collision_with_blocks(Process* process,Sheel* sheel);
	void handle_sheel_collision_with_s_bricks(Process* process,Sheel* sheel);
	void handle_sheel_collision_with_a_bricks(Process* process,Sheel* sheel);
	void handle_sheel_collision_with_pipes(Process* process,Sheel* sheel);
	void handle_sheel_collision_with_medium_mario(Process* process,Sheel* sheel);
	void handle_sheel_collision_with_big_mario(Process* process,Sheel* sheel);
	bool do_medium_equal_objects_collides_together(Point target_place , Point hiter_place);
	bool do_big_equal_objects_collides_together(Point target_place , Point hiter_place);
	bool do_unequal_objects_collides_together(Point target_place , Point hiter_place);
	string find_collision_direction(Point target_place , Point hiter_place);
};

bool Collision::do_medium_equal_objects_collides_together(Point target_place , Point hiter_place)
{
	for(int x = target_place.x; x < (target_place.x + MAP_ROOM_SIZE); x++ )
		for(int y = target_place.y; y < (target_place.y + MAP_ROOM_SIZE); y++ )
			if( 0 <= x-hiter_place.x && x-hiter_place.x <= MAP_ROOM_SIZE-2 && -1 <= y-hiter_place.y && y-hiter_place.y <= MAP_ROOM_SIZE )
				return true;
	return false;
}

bool Collision::do_big_equal_objects_collides_together(Point target_place , Point hiter_place)
{
	for(int x = target_place.x; x < (target_place.x + MAP_ROOM_SIZE); x++ )
		for(int y = target_place.y - MAP_ROOM_SIZE ; y < (target_place.y + MAP_ROOM_SIZE); y++ )
			if( 0 <= x-hiter_place.x && x-hiter_place.x <= MAP_ROOM_SIZE && -MAP_ROOM_SIZE <= y-hiter_place.y && y-hiter_place.y <= MAP_ROOM_SIZE )
				return true;
	return false;
}

bool Collision::do_unequal_objects_collides_together(Point target_place , Point hiter_place)
{
	for(int x = target_place.x; x < (target_place.x + MAP_ROOM_SIZE); x++ )
		for(int y = target_place.y; y < (target_place.y + MAP_ROOM_SIZE); y++ )
			if( 0 <= x-hiter_place.x && x-hiter_place.x <= MAP_ROOM_SIZE-2 && -MAP_ROOM_SIZE-1 <= y-hiter_place.y && y-hiter_place.y <= MAP_ROOM_SIZE )
				return true;
	return false;
}

void Collision::handle_all_collisions(Process* process)
{
	handle_goombas_collision(process);
	handle_turtles_collision(process);
	handle_mushrooms_collision(process);
	handle_sheels_collision(process);
	handle_coins_collision(process);
	handle_mario_collision(process);
}

void Collision::handle_goombas_collision(Process* process)
{
	for(int goomba_num = 0; goomba_num < process->goomba_list.size(); goomba_num++)
		handle_goomba_collision(process , process->goomba_list[goomba_num])	;	
}

void Collision::handle_goomba_collision_with_blocks(Process* process, Goomba* goomba)
{
	for(int block_num = 0; block_num < process->block_list.size(); block_num++)
	{
		if(do_medium_equal_objects_collides_together(goomba->get_place(),process->block_list[block_num]->get_place()))
		{
			if(goomba->get_speed().y != 0)
				goomba->change_goomba_speed(goomba->get_speed().x , 0);
			else if(goomba->get_speed().y == 0 && process->block_list[block_num]->get_block_kind() == SIMPLE_BLOCK)
				goomba->change_goomba_speed(goomba->get_speed().x * -1 , 0);
		}
	}
}

void Collision::handle_goomba_collision_with_s_bricks(Process* process, Goomba* goomba)
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(goomba->get_place(),process->simple_brick_list[s_brick_num]->get_place()))
			if(goomba->get_speed().y != 0)
				goomba->change_goomba_speed(goomba->get_speed().x , 0);
	}
}

void Collision::handle_goomba_collision_with_a_bricks(Process* process, Goomba* goomba)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(goomba->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			if(goomba->get_speed().y != 0)
				goomba->change_goomba_speed(goomba->get_speed().x , 0);
	}

}

void Collision::handle_goomba_collision_with_pipes(Process* process, Goomba* goomba)
{
	for(int pipe_num = 0; pipe_num < process->pipe_list.size(); pipe_num++)
	{
		if(do_medium_equal_objects_collides_together(goomba->get_place(),process->pipe_list[pipe_num]->get_place()))
		{
			if(goomba->get_speed().y != 0)
				goomba->change_goomba_speed(goomba->get_speed().x , 0);
			else if(goomba->get_speed().y == 0 )
			{
				goomba->change_goomba_speed(goomba->get_speed().x * -1 , 0);
				break;
			}
		}
	}
}

void Collision::handle_goomba_collision_with_medium_mario(Process* process, Goomba* goomba)
{
	if(do_medium_equal_objects_collides_together(goomba->get_place(),process->mario->get_place()))
	{
		if( (goomba->get_speed().y != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
			throw MarioDieException();
		else if(goomba->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
		{
			process->window_control->win->play_sound_effect(ENEMY_STOMP_SOUND);
			goomba->get_to_die_mood();
			process->mario->change_speed(MOMENT_SIZE*2,-25);
			return ;
		}
	}
}

void Collision::handle_goomba_collision_with_big_mario(Process* process, Goomba* goomba)
{
	if(do_unequal_objects_collides_together(goomba->get_place(),process->mario->get_place()))
	{
		if( (goomba->get_speed().y != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
		{
			process->mario->get_small();
			process->mario->set_to_ghost_state();
		}
		else if(goomba->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
		{
			process->window_control->win->play_sound_effect(ENEMY_STOMP_SOUND);
			goomba->get_to_die_mood();
			process->mario->change_speed(MOMENT_SIZE*2,-25);
			return ;
		}
	}
}

void Collision::handle_goomba_collision(Process* process, Goomba* goomba)
{ 
	handle_goomba_collision_with_blocks(process, goomba);
	handle_goomba_collision_with_s_bricks(process, goomba);
	handle_goomba_collision_with_a_bricks(process, goomba);
	handle_goomba_collision_with_pipes(process, goomba);
	if(process->mario->get_the_physique() == "medium")
		handle_goomba_collision_with_medium_mario(process, goomba);
	else
		handle_goomba_collision_with_big_mario(process, goomba);
}

void Collision::handle_turtles_collision(Process* process)
{
	for(int turtle_num = 0; turtle_num < process->turtle_list.size(); turtle_num++)
		handle_turtle_collision(process , process->turtle_list[turtle_num], turtle_num)	;	
}

void Collision::handle_turtle_collision_with_blocks(Process* process,Turtle* turtle)
{
	for(int block_num = 0; block_num < process->block_list.size(); block_num++)
	{
		if(do_medium_equal_objects_collides_together(turtle->get_place(),process->block_list[block_num]->get_place()))
		{
			if(turtle->get_speed().y != 0)
				turtle->change_turtle_speed(turtle->get_speed().x , 0);
			else if(turtle->get_speed().y == 0 && process->block_list[block_num]->get_block_kind() == SIMPLE_BLOCK )
				turtle->change_turtle_speed(turtle->get_speed().x * -1 , 0);
		}
	}
}

void Collision::handle_turtle_collision_with_s_bricks(Process* process,Turtle* turtle)
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(turtle->get_place(),process->simple_brick_list[s_brick_num]->get_place()))
			if(turtle->get_speed().y != 0)
				turtle->change_turtle_speed(turtle->get_speed().x , 0);
	}
}

void Collision::handle_turtle_collision_with_a_bricks(Process* process,Turtle* turtle)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(turtle->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			if(turtle->get_speed().y != 0)
				turtle->change_turtle_speed(turtle->get_speed().x , 0);
	}
}

void Collision::handle_turtle_collision_with_pipes(Process* process,Turtle* turtle)
{
	for(int pipe_num = 0; pipe_num < process->pipe_list.size(); pipe_num++)
	{
		if(do_medium_equal_objects_collides_together(turtle->get_place(),process->pipe_list[pipe_num]->get_place()))
		{
			if(turtle->get_speed().y != 0)
				turtle->change_turtle_speed(turtle->get_speed().x , 0);
			else if(turtle->get_speed().y == 0 )
			{
				turtle->change_turtle_speed(turtle->get_speed().x * -1 , 0);
				break;
			}
		}
	}
}

void Collision::handle_turtle_collision_with_medium_mario(Process* process, Turtle* turtle, int turtle_num)
{
	if(do_medium_equal_objects_collides_together(turtle->get_place(),process->mario->get_place()))
	{
		if( (turtle->get_speed().y != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
			throw MarioDieException();
		else if(turtle->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
		{
			process->window_control->win->play_sound_effect(ENEMY_STOMP_SOUND);
			process->convert_turtle_to_sheel(turtle_num);
			process->mario->change_place(0,-45);
			process->mario->change_speed(MOMENT_SIZE*2,-25);
		}
	}
}

void Collision::handle_turtle_collision_with_big_mario(Process* process, Turtle* turtle, int turtle_num)
{
	if(do_unequal_objects_collides_together(turtle->get_place(),process->mario->get_place()))
	{
		if( (turtle->get_speed().y != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
		{
			process->mario->get_small();
			process->mario->set_to_ghost_state();
		}
		else if(turtle->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
		{
			process->window_control->win->play_sound_effect(ENEMY_STOMP_SOUND);
			process->convert_turtle_to_sheel(turtle_num);
			process->mario->change_place(0,-45);
			process->mario->change_speed(MOMENT_SIZE*2,-25);
		}
	}
}

void Collision::handle_turtle_collision(Process* process,Turtle* turtle ,int turtle_num)
{
	handle_turtle_collision_with_blocks( process, turtle);
	handle_turtle_collision_with_s_bricks( process, turtle);
	handle_turtle_collision_with_a_bricks( process,turtle);
	handle_turtle_collision_with_pipes( process,turtle);
	if(process->mario->get_the_physique() == "medium")
		handle_turtle_collision_with_medium_mario( process, turtle, turtle_num);
	else
		handle_turtle_collision_with_big_mario(process, turtle, turtle_num);
}

void Collision::handle_mushrooms_collision(Process* process)
{
	for(int mushroom_num = 0; mushroom_num < process->mushroom_list.size(); mushroom_num++)
		handle_mushroom_collision(process , process->mushroom_list[mushroom_num], mushroom_num)	;	
}

void Collision::handle_mushroom_collision_with_blocks(Process* process, Mushroom* mushroom)
{
	for(int block_num = 0; block_num < process->block_list.size(); block_num++)
	{
		if(do_medium_equal_objects_collides_together(mushroom->get_place(),process->block_list[block_num]->get_place()))
		{
			if(mushroom->get_speed().y != 0)
				mushroom->change_mushroom_speed(mushroom->get_speed().x , 0);
			else if(mushroom->get_speed().y == 0 && process->block_list[block_num]->get_block_kind() == SIMPLE_BLOCK )
				mushroom->change_mushroom_speed(mushroom->get_speed().x * -1 , 0);
		}
	}
}

void Collision::handle_mushroom_collision_with_s_bricks(Process* process, Mushroom* mushroom )
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(mushroom->get_place(),process->simple_brick_list[s_brick_num]->get_place()))
			if(mushroom->get_speed().y != 0)
				mushroom->change_mushroom_speed(mushroom->get_speed().x , 0);
	}
}

void Collision::handle_mushroom_collision_with_a_bricks(Process* process, Mushroom* mushroom )
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(mushroom->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			if(mushroom->get_speed().y != 0)
				mushroom->change_mushroom_speed(mushroom->get_speed().x , 0);
	}
}

void Collision::handle_mushroom_collision_with_pipes(Process* process, Mushroom* mushroom )
{
	for(int pipe_num = 0; pipe_num < process->pipe_list.size(); pipe_num++)
	{
		if(do_medium_equal_objects_collides_together(mushroom->get_place(),process->pipe_list[pipe_num]->get_place()))
		{
			if(mushroom->get_speed().y != 0)
				mushroom->change_mushroom_speed(mushroom->get_speed().x , 0);
			else if(mushroom->get_speed().y == 0 )
			{
				mushroom->change_mushroom_speed(mushroom->get_speed().x * -1 , 0);
				break;
			}
		}
	}
}

void Collision::handle_mushroom_collision_with_mario(Process* process, Mushroom* mushroom ,int mushroom_num)
{
	if(do_medium_equal_objects_collides_together(mushroom->get_place(),process->mario->get_place()))
	{
		if(mushroom->get_mushroom_type() == RED_MUSHROOM )
		{
			process->window_control->win->play_sound_effect(POWERUP_SOUND);
			process->mario->grow_up();
		}
		if(mushroom->get_mushroom_type() == HEALTH_MUSHROOM )
		{
			process->window_control->win->play_sound_effect(LIVES_UP_SOUND);
			process->increase_lives_num();
		}
		process->delete_mushroom(mushroom_num);
	}
}

void Collision::handle_mushroom_collision(Process* process, Mushroom* mushroom ,int mushroom_num)
{
	handle_mushroom_collision_with_blocks(process, mushroom);
	handle_mushroom_collision_with_s_bricks(process, mushroom );
	handle_mushroom_collision_with_a_bricks(process, mushroom );
	handle_mushroom_collision_with_pipes(process, mushroom );
	handle_mushroom_collision_with_mario(process, mushroom , mushroom_num);
}

void Collision::handle_sheels_collision(Process* process)
{
	for(int sheel_num = 0; sheel_num < process->sheel_list.size(); sheel_num++)
		handle_sheel_collision(process , process->sheel_list[sheel_num]);	
}

void Collision::handle_sheel_collision_with_blocks(Process* process, Sheel* sheel)
{
	for(int block_num = 0; block_num < process->block_list.size(); block_num++)
	{
		if(do_medium_equal_objects_collides_together(sheel->get_place(),process->block_list[block_num]->get_place()))
		{
			if(sheel->get_speed().y != 0)
				sheel->change_sheel_speed(sheel->get_speed().x , 0);
			else if(sheel->get_speed().y == 0 && process->block_list[block_num]->get_block_kind() == SIMPLE_BLOCK)
				sheel->change_sheel_speed(sheel->get_speed().x * -1 , 0);
		}
	}
}

void Collision::handle_sheel_collision_with_s_bricks(Process* process, Sheel* sheel)
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(sheel->get_place(),process->simple_brick_list[s_brick_num]->get_place()))
			if(sheel->get_speed().y != 0)
				sheel->change_sheel_speed(sheel->get_speed().x , 0);
	}	
}

void Collision::handle_sheel_collision_with_a_bricks(Process* process, Sheel* sheel)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(sheel->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			if(sheel->get_speed().y != 0)
				sheel->change_sheel_speed(sheel->get_speed().x , 0);
	}
}

void Collision::handle_sheel_collision_with_pipes(Process* process, Sheel* sheel)
{
	for(int pipe_num = 0; pipe_num < process->pipe_list.size(); pipe_num++)
	{
		if(do_medium_equal_objects_collides_together(sheel->get_place(),process->pipe_list[pipe_num]->get_place()))
		{
			if(sheel->get_speed().y != 0)
				sheel->change_sheel_speed(sheel->get_speed().x , 0);
			else if(sheel->get_speed().y == 0 )
			{
				sheel->change_sheel_speed(sheel->get_speed().x * -1 , 0);
				break;
			}
		}
	}
}

void Collision::handle_sheel_collision_with_medium_mario(Process* process, Sheel* sheel)
{
	if(do_medium_equal_objects_collides_together(sheel->get_place(),process->mario->get_place()))
	{
		if( (sheel->get_speed().y != 0 || sheel->get_speed().x != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
		{
			throw MarioDieException();
		}
		else if(sheel->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
			process->hit_the_sheel_to_move(sheel);
	}
}

void Collision::handle_sheel_collision_with_big_mario(Process* process, Sheel* sheel)
{
	if(do_unequal_objects_collides_together(sheel->get_place(),process->mario->get_place()))
	{
		if( (sheel->get_speed().y != 0 || sheel->get_speed().x != 0 || process->mario->get_mario_speed().y ==0 ) && !process->mario->is_mario_in_ghost_state())
		{
			process->mario->get_small();
			process->mario->set_to_ghost_state();
		}
		else if(sheel->get_speed().y == 0 && process->mario->get_mario_speed().y !=0)
			process->hit_the_sheel_to_move(sheel);
	}
}

void Collision::handle_sheel_collision(Process* process, Sheel* sheel)
{
	handle_sheel_collision_with_blocks(process, sheel);
	handle_sheel_collision_with_s_bricks(process, sheel);
	handle_sheel_collision_with_a_bricks(process, sheel);
	handle_sheel_collision_with_pipes(process, sheel);
	if(process->mario->get_the_physique() == "medium")
		handle_sheel_collision_with_medium_mario(process, sheel);
	else
		handle_sheel_collision_with_big_mario(process, sheel);
}

void Collision::handle_coins_collision(Process* process)
{
	for(int coin_num = 0; coin_num < process->coin_list.size(); coin_num++)
		handle_coin_collision(process , process->coin_list[coin_num], coin_num)	;	
}

void Collision::handle_coin_collision(Process* process, Coin* coin ,int coin_num)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
	{
		if(do_medium_equal_objects_collides_together(coin->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			process->delete_coin(coin_num);
	}
}

void Collision::handle_mario_collision_with_blocks(Process* process)
{
	for(int block_num = 0; block_num < process->block_list.size(); block_num++)
	{
		if(do_medium_equal_objects_collides_together(process->mario->get_place(),process->block_list[block_num]->get_place()))
		{
			if(process->mario->get_mario_speed().y > 0)
			{
				process->mario->change_place(0,process->block_list[block_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
				process->mario->change_speed(process->mario->get_mario_speed().x , 0);
			}
			else if(process->mario->get_mario_speed().y == 0 && process->block_list[block_num]->get_block_kind() == SIMPLE_BLOCK )
			{
				if(process->mario->get_place().x == process->block_list[block_num]->get_place().x - MAP_ROOM_SIZE/2 )
					process->mario->change_place(0,process->block_list[block_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
				else
					process->mario->change_place(-MAP_ROOM_SIZE/2 , 0);
				process->mario->change_speed(0 , 0);
			}
		}
	}
}

void Collision::handle_mario_collision_with_flags(Process* process)
{
	for(int flag_num = 0; flag_num < process->flags_list.size(); flag_num++)
	{
		if(do_medium_equal_objects_collides_together(process->mario->get_place(),process->flags_list[flag_num]->get_place()))
			throw MarioWinException() ;
	}
}

void Collision::handle_mario_collision_with_a_brick(Process* process,int a_brick_num)
{
	if(process->mario->get_mario_speed().y < 0 && (process->amazing_brick_list[a_brick_num]->get_place().y < process->mario->get_place().y))
	{
		if(process->amazing_brick_list[a_brick_num]->get_strike_num() == 0 )
		{
			process->make_a_brick_content(process->amazing_brick_list[a_brick_num]->get_brick_kind(),process->amazing_brick_list[a_brick_num]->get_place());
			process->amazing_brick_list[a_brick_num]->increase_strike_num();
		}
		process->mario->change_place(0,process->amazing_brick_list[a_brick_num]->get_place().y + MAP_ROOM_SIZE - process->mario->get_place().y +45);
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
		process->window_control->win->play_sound_effect(BUMP_SOUND);
	}
	else if(process->mario->get_mario_speed().y < 0  && process->mario->get_mario_speed().x != 0)
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
	else if(process->mario->get_mario_speed().y > 0 )
	{
		process->mario->change_place(0,process->amazing_brick_list[a_brick_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
		process->mario->change_speed(process->mario->get_mario_speed().x,0);		
	}
}

void Collision::handle_big_mario_collision_with_a_bricks(Process* process)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
		if(do_unequal_objects_collides_together(process->amazing_brick_list[a_brick_num]->get_place(),process->mario->get_place()))
			handle_mario_collision_with_a_brick( process,a_brick_num);
}

void Collision::handle_medium_mario_collision_with_a_bricks(Process* process)
{
	for(int a_brick_num = 0; a_brick_num < process->amazing_brick_list.size(); a_brick_num++)
		if(do_medium_equal_objects_collides_together(process->mario->get_place(),process->amazing_brick_list[a_brick_num]->get_place()))
			handle_mario_collision_with_a_brick( process,a_brick_num);
}

void Collision::handle_big_mario_collision_with_s_brick(Process* process , int s_brick_num)
{
	if(process->mario->get_mario_speed().y < 0 && (process->simple_brick_list[s_brick_num]->get_place().y < process->mario->get_place().y))
	{
		process->simple_brick_list[s_brick_num]->break_the_brick();
		process->mario->change_place(0,process->simple_brick_list[s_brick_num]->get_place().y + MAP_ROOM_SIZE - process->mario->get_place().y +45);
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
		process->window_control->win->play_sound_effect(BRICK_SMASH_SOUND);
	}
	else if(process->mario->get_mario_speed().y < 0  && process->mario->get_mario_speed().x != 0)
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
	else if(process->mario->get_mario_speed().y > 0 )
	{
		process->mario->change_place(0,process->simple_brick_list[s_brick_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
		process->mario->change_speed(process->mario->get_mario_speed().x,0);
	}
}

void Collision::handle_big_mario_collision_with_s_bricks(Process* process)
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
		if(do_unequal_objects_collides_together(process->simple_brick_list[s_brick_num]->get_place(),process->mario->get_place()))
			handle_big_mario_collision_with_s_brick( process , s_brick_num);
}

void Collision::handle_medium_mario_collision_with_s_brick(Process* process ,int s_brick_num)
{
	if(process->mario->get_mario_speed().y < 0 && (process->simple_brick_list[s_brick_num]->get_place().y < process->mario->get_place().y))
	{
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
		process->mario->change_place(0,process->simple_brick_list[s_brick_num]->get_place().y + MAP_ROOM_SIZE - process->mario->get_place().y +1);
		process->window_control->win->play_sound_effect(BUMP_SOUND);
	}
	else if(process->mario->get_mario_speed().y < 0  && process->mario->get_mario_speed().x != 0)
		process->mario->change_speed(0,MAP_ROOM_SIZE/2);
	else if(process->mario->get_mario_speed().y > 0 )
	{
		process->mario->change_place(0,process->simple_brick_list[s_brick_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
		process->mario->change_speed(process->mario->get_mario_speed().x,0);
	}
}

void Collision::handle_medium_mario_collision_with_s_bricks(Process* process)
{
	for(int s_brick_num = 0; s_brick_num < process->simple_brick_list.size(); s_brick_num++)
		if(do_medium_equal_objects_collides_together(process->mario->get_place(),process->simple_brick_list[s_brick_num]->get_place()))
			handle_medium_mario_collision_with_s_brick( process , s_brick_num);
}

void Collision::handle_medium_mario_collision_with_pipes(Process* process)
{
	for(int pipe_num = 0; pipe_num < process->pipe_list.size(); pipe_num++)
	{
		if(do_medium_equal_objects_collides_together( process->mario->get_place(),process->pipe_list[pipe_num]->get_place()))
		{
			if(process->mario->get_mario_speed().y > 0 )
			{
				process->mario->change_place(0,process->pipe_list[pipe_num]->get_place().y - process->mario->get_place().y - MAP_ROOM_SIZE);
				process->mario->change_speed(process->mario->get_mario_speed().x,0);
			}
			if(process->mario->get_mario_speed().y == 0 && process->mario->get_mario_speed().x != 0 && process->pipe_list[pipe_num]->get_pipe_type()== PIPE_BODY )
			{
				if(process->mario->get_mario_speed().x > 0)
					process->mario->change_place(-MAP_ROOM_SIZE/2 , 0);
				if(process->mario->get_mario_speed().x < 0)
					process->mario->change_place(MAP_ROOM_SIZE/2 , 0);
				process->mario->change_speed(0,0);
			}
		}
	}
}

void Collision::handle_mario_collision(Process* process)
{
	if(process->mario->get_mario_speed().y == 0)
		process->mario->change_speed(process->mario->get_mario_speed().x , 5);

	handle_mario_collision_with_blocks( process);
	handle_mario_collision_with_flags( process);
	if(process->mario->get_the_physique() == "big")
	{
		handle_big_mario_collision_with_a_bricks( process);
		handle_big_mario_collision_with_s_bricks( process);		
	}
	else
	{
		handle_medium_mario_collision_with_a_bricks( process);
		handle_medium_mario_collision_with_s_bricks( process);	
	}
	handle_medium_mario_collision_with_pipes( process);
}

int main(int argc, char *argv[])
{
	GameMap* game_map = new GameMap();
	game_map->read_all_the_map(argv[1]);
	Window win(WINDOW_WIDTH,600,"Super Mario") ;
	Collision* collision ;
	int live_num = 3 ;
	while(live_num)
	{
		win.play_music(BACKGROUND_MUSIC);
		Background* background = new Background(WINDOW_WIDTH,game_map->get_map_row_num() * MAP_ROOM_SIZE,&win);
		WindowControl* window_control = new WindowControl(WINDOW_WIDTH,game_map->get_map_row_num(),&win,background);
		Process* process = new Process(window_control, &live_num);
		process->make_objects_of_game(game_map);
		while(true)
		{
			background->draw_background();
			background->show_texts(live_num,process->get_coin_num());
			process->apply_keys_press_effect();
			process->process_objects_state();
			window_control->update_camera_place(process->mario->get_place());
			try{
				collision->handle_all_collisions(process);
			} catch(MarioDieException ex){
				delete window_control;
				delete process;
				delete background;
				win.stop_music();
				win.play_sound_effect(MARIO_DEATH_SOUND);
				win.update_screen();
				delay(3000);
				break;
			} catch(MarioWinException ex){
				win.stop_music();
				win.clear();
				win.show_text("You Win",Point(WINDOW_WIDTH/2-MAP_ROOM_SIZE*2,MAP_ROOM_SIZE),RED,"FreeSans.ttf",50);
				win.update_screen();
				win.play_sound_effect(LEVEL_CLEAR_SOUND);
				delay(6000);
				exit ;
			}
			win.update_screen();
			delay(100);
		}
		live_num--;
	}
	win.clear();
	win.show_text("You Lose",Point(WINDOW_WIDTH/2-MAP_ROOM_SIZE*2,MAP_ROOM_SIZE),RED,"FreeSans.ttf",50);
	win.update_screen();
	win.play_sound_effect(GAMEOVER_SOUND);
	delay(4000);
}