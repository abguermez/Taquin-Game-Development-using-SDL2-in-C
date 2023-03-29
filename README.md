# Taquin-Game-Development-using-SDL2-in-C
In this project, we developed a Taquin game using the SDL2 library and the C programming language. The game featured a graphical user interface, allowing players to move tiles and rearrange the board to solve the puzzle. We implemented various game mechanics and features, such as the ability to shuffle the board and track the player's progress.
#### - Teams:
  - [Abdellah ELGuermez](https://www.linkedin.com/in/abguermez/)
  - [Yahya Benbaba](https://www.linkedin.com/in/yahya-benbaba-0027a8171/)
  - [Meryem Iben el rhazi](https://www.linkedin.com/in/meryem-iben-el-rhazi-345227246/)
  - [Najlae Hmimina](https://www.linkedin.com/in/najlae-hmimina-a23048249/)
## - Why SDL2?
I used the SDL2 library in C to build my taquin game for several reasons. Firstly, SDL2 is a powerful and popular cross-platform library that provides access to audio, graphics, input, and networking functionalities. This allowed me to create a smooth and engaging gaming experience with responsive controls and high-quality visuals. Additionally, SDL2 is relatively easy to learn and use, making it a great choice for developers of all skill levels. Finally, SDL2 has excellent documentation and an active community, which provided me with valuable resources and support throughout the development process. Overall, I found that SDL2 was the ideal choice for creating my taquin game, and I would recommend it to anyone looking to build a similar project.
## - Guide to use SDL2?
A step-by-step guide to installing SDL2 in C on your computer and using it in VS Code:

1- Download the SDL2 library: The first step is to download the SDL2 library. You can find the latest version of the library on the official SDL website (https://www.libsdl.org/download-2.0.php). Choose the appropriate version for your operating system and download it.

2- Install SDL2: Once you have downloaded the SDL2 library, you need to install it on your computer. The installation process may vary depending on your operating system. Here are the installation instructions for some popular operating systems:
  - Windows: Extract the downloaded SDL2 archive to a directory of your choice. Then, copy the "SDL2.dll" file from the "lib" folder to your project's directory.
  - macOS: Double-click on the downloaded SDL2 disk image file to mount it. Then, drag the SDL2.framework file to your project's directory.
  - Linux: Use your distribution's package manager to install the SDL2 library.

3- Create a new C project in VS Code: Open VS Code and create a new C project by selecting "File > New Project..." from the menu. Choose a directory to store your project and give it a name.

4- Configure the project: Open the terminal in VS Code and navigate to your project directory. Create a new file called "Makefile" and add the following code:
```
CC = gcc
CFLAGS = -Wall -Iinclude
LIBS = -lSDL2

SRC = src/*.c
OBJ = $(SRC:.c=.o)
EXEC = bin/your_program_name

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(OBJ) $(LIBS) -o $@

%.o: %.c
    $(CC) -c $(CFLAGS) $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)
```
This Makefile specifies the compiler and flags needed to compile the code, the location of the SDL2 library, and the source files to compile. You may need to modify the file to match your project's structure.

5 - Write your code: Create a new source file in the "src" folder of your project and write your SDL2 code. Here's a simple example program that creates a window using SDL2:

```C
#include <SDL2/SDL.h>

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Hello SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
```
6- Build the project: Open the terminal in VS Code and navigate to your project directory. Type "make" to build the project. This will compile your code and create an executable file in the "bin" folder of your project.

7- Run the program: Open the terminal in VS Code and navigate to your project directory. Type "./bin/your_program_name" to run your program. A window should appear with the title "Hello SDL2".

That's it! You should now have SDL2 installed in C on your computer and be able to use it in VS Code to create games and other graphical applications.
