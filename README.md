# aig
AiGames framework for messing around with AI.
Please note that this is meant for AI vs AI tests, not AI vs Humans. However, it would be easy enough to implement an "agent" that accepts commands from a human.

Warning: very raw and written by inexperienced programmer.


## How to build it
CMake is the preferred build system. You don't need the GUI, there are no CMake variables for this. Just get the CLI version from your package manager/website.
### Linux
You need the SDL2-dev or SDL2-devel library (usually called something like `libsdl2-dev` in your package manager). Please use SDL 2.0.x and not 1.x.
If you are building from source, remember to `make install` after building so that CMake installs it and knows how to find it later on.

* Clone the repo via `git clone`/downloading/etc.
* Navigate to the topmost folder (`aig`).
* Make a build directory. Navigate into it.
* Run CMake to generate build files in the build directory.
* Build.

(Since you're probably too lazy for that here's the commands) <br>
Assuming you're in the `aig` folder
* `mkdir build`
* `cd build`
* `cmake -G "Unix Makefiles" ..`
* `make`

The output is an executable called `aigmain`. Run that. To use SDL2 you probably first need to activate dynamic linking for it. This is done by appending the location of its compiled binary blob to the `LD_LIBRARY_PATH`
environment variable BEFORE running it. Google time.
### Windows
SDL2 Visual Studio development libraries are available on the SDL2 website.

You can use CMake similarly on Windows, except that you'll be generating Visual Studio solutions and not Makefiles. Google it up.
Alternatively, there's a premade Visual Studio solution that you can use, it's in the `aig/aigmain` folder. You have to go to project properties and manually change the include directories to point to your library installation and the additional libraries directories to point to the x86 libraries folder. It's a bit tedious and documented here: http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvsnet2010u/index.php

Also, before running it you need to put a copy of `SDL2.dll` (available in the `lib` folder of the download) into either System32 (not recommended) or in your Debug folder (recommended). Just build it once and drop it where the built EXE file is.

## How to use it
`IAgent` is a parametrized interface (i.e. interface that takes template type parameters) which represents a generic agent _for a particular game_ (agents are unique to a game). 

The game is processed in _frames_. Each frame corresponds to one "still" moment in time. Eg. for ultrasmooth play the general framerate is 60 FPS or so, at this speed each frame takes 16.67 ms or so. The internal game system (which you don't need to worry about if you're a user and not a library developer) uses `IAgent`'s primary method `Decide`. `Decide` is called _once per frame_, before state changes (i.e. motion via physics, etc.) occur. 

`Decide` on its own cannot affect the game state. This is so that the AI code is decoupled from the state change code (and also so that the AI can't change more that it's supposed to). Instead, `Decide` returns a _command_ (the type of command is particular to a game) which the state change code can interpret. For example, in Pong the AI can tell the game system to move a paddle up by returning the `PONG_GO_UP` command. 

To facilitate decision making, `Decide` is given restricted access to the current game state, via the state's `GetProperty` method. The `GetProperty` methods depend on the type of state, but you can always assume that each state type has it, and that it basically works in the same way, even though the function signature might be different (eg. `DummyGameState`'s method returns a `double`, while `PongGameState`'s method returns a `Vector2`). It is also given the time elapsed since the previous frame. Note: use `GetProperty` as sparingly as possible, for things like wall positions it's better to query that stuff once and store it in your agent object.

Each agent has a token number assigned to it by the game system. This token is stored in the `_id` protected variable of the `IAgent` interface. When querying the game state for data the agent also needs to pass in its token, so that the game state can decide whether said agent allowed to access the data or not (this is useful for games like strategy games, in which giving the AI too much information eg. data about terrain covered by the fog of war, is basically allowing it to cheat). Note, this is not working yet (or necessary). But it's a good thing to have for later.

Therefore, to implement your own agent do the following
* Decide which game you're implementing it for.
* Include the header file of the game (generally, this pulls in all the required headers).
* Create your agent class by implementing (i.e. subclassing) the `IAgent<GameType>` interface (eg. for Pong it's `IAgent<PongGame>`). If you have multiple agents (say, by different people), create multiple subclasses (i.e. multiple classes each subclassing `IAgent`, _not_ a chain of subclasses). You'll necessarily have to override the `Decide` method because it's declared as a pure virtual method in `IAgent`). In `Decide`, query the game state and return commands.
* Register the agents with the GameSystem.
* Run the game via the game system.

Another way to get information from inside the `Decide` method is the events system, implemented using the `Observer` and `ObservationTarget` classes. Each `ObservationTarget` has a list of `Observer`s to which it can push events. Note: `Observer`s cannot push events (duh). There is a default `ObservationTarget` inside each game class and an `Observer` inside each `IAgent` (it's called `observer`). The agent `Observer`s are wired up to the game's `ObservationTarget` automatically by the game system, so every agent will recieve a copy of every event (this will be changed later on with support for multiple event streams). Events can help look for things like "this ball hit that paddle" and can be used as another information input to your AI algorithm. Note: please clear the agent's event queue every frame even if you're not using events, otherwise the queue will just keep getting longer and will eat up memory.

Other ways to get help:

* Every header file has some comments. They might help. Will add more comments later.
* The default implementation comes with a `main.cpp` with an example agent already made. Just follow the same pattern.