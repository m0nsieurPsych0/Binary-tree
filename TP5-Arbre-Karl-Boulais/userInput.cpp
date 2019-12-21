#include "userInput.h"
#include "main.h"
#include "cvm.h"
#include<iostream>


void FlushTampons()
{
	if (std::cin.fail()) std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
}




