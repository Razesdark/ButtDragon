CXX = g++
# Update these paths to match your installation
# You may also need to update the linker option rpath, which sets where to look for
# the SDL2 libraries at runtime to match your install
SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
# You may need to change -std=c++11 to -std=c++0x if your compiler is a bit older
CXXFLAGS = -Wall -c -std=c++11 $(SDL_INCLUDE)
LDFLAGS = $(SDL_LIB)
EXE = runme

all: $(EXE)

$(EXE): main.o game.o game_entity.o player.o projectile.o stars.o enemy.o
	$(CXX) $^ $(LDFLAGS) -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
game.o: game.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
game_entity.o: game_entity.cpp
		$(CXX) $(CXXFLAGS) $< -o $@
player.o: player.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
projectile.o: projectile.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
stars.o: stars.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
enemy.o: enemy.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
