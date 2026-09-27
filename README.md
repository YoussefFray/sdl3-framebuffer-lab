# Pixel Manipulation & Frame Buffers with SDL3

you write colors directly into an array (the **frame buffer**), then hand that
array to SDL3 to show on screen.

## How it works

1. `pixels[]` is a plain array with one number per pixel (its color).
2. `putPixel(x, y, r, g, b)` writes one color into that array at position `(x, y)`.
3. `drawFrame()` runs every frame and fills `pixels[]` with a moving color
   pattern, plus a white circle drawn pixel-by-pixel.
4. `SDL_UpdateTexture()` copies `pixels[]` into a texture.
5. `SDL_RenderTexture()` + `SDL_RenderPresent()` draw that texture to the window.

That's it — no shapes API, no drawing library. Every pixel on screen came from
our own array.

## Build

Open a terminal in this folder and run:

```bash
g++ main.cpp -o main.exe -I "C:\Users\HP\Desktop\DSA-T-PP\c++\SDL\x86_64-w64-mingw32\include" -L "C:\Users\HP\Desktop\DSA-T-PP\c++\SDL\x86_64-w64-mingw32\lib" -lSDL3
```

## Run

`SDL3.dll` must be next to `main.exe` (it already is in this folder).

```bash
./main.exe
```

You should see a window with shifting colors and a white circle moving in a
circular path. Close the window to quit.

## Things to try

- Change `WIDTH` / `HEIGHT` to make the frame buffer bigger or smaller.
- In `drawFrame()`, change the formulas for `r`, `g`, `b` to make different patterns.
- Add another shape by writing a new loop that calls `putPixel()`.
