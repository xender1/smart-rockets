#pragma once
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
using namespace std;
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 900;

//Rocket properties
//start position
static constexpr double ROCKET_START_POSX = SCREEN_WIDTH / 2;
static constexpr double ROCKET_START_POSY = SCREEN_HEIGHT - 100;
//max acceleration and velocity rates
static constexpr double MAX_ROCKET_VEL = 3.0;
static constexpr double MAX_ROCKET_ACC = 2.0;
//dna length
static const int ROCKET_DNA_LENGTH = 10;

//Gene properties
static constexpr double MIN_GENE_VELOCITY = -3.0;
static constexpr double MAX_GENE_VELOCITY = 3.0;
static const int MAX_GENE_TIME = 3000;

//Mutation properties
const int MUTATION_SINGLE_GENE_CHANCE = 5;
const int MUTATION_DNA_SEQUENCE_CHANCE = 3;
