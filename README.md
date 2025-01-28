gomponent
==================================

This is an open.mp component for loading gamemodes written in Go with the [omp](https://github.com/kodeyeen/omp) package.
The name `Gomponent` is composed of three word-forming elements:
1. Go
2. omp (short for open.mp)
3. Component

Similar to goroutines (go coroutines) in Go.

## Usage

1. Download the latest version from [here](https://github.com/kodeyeen/gomponent/releases/latest).
2. Put the `Go.dll` or `Go.so` file into server's `components` directory.
3. Make sure you have some built [omp](https://github.com/kodeyeen/omp) gamemode in the `gamemodes` folder.
4. Specify the gamemode name (without .dll or .so extension) to be loaded in your `config.json`:

```json
"go": {
    "gamemode": "<YOUR GAMEMODE NAME>"
}
```

5. Run the server.
