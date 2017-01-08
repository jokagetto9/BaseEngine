//********************************* INITIALIZATION *********************************
#include "Commands.h"
Command Commands::nothing;

Commands:: Commands(){
	refresh = &nothing;
	animation = &nothing;

}