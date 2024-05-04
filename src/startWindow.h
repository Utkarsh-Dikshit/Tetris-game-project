#pragma once

#include "raylib.h"
#include "raymath.h"

class startWindow
{
public:
    startWindow();

    Texture2D BGtexture, MainLogoTexture, ControlTexture, BGtexture2;
    Texture2D LBlockTex, JBlockTex, OBlockTex, IBlockTex, TBlockTex, SBlockTex, ZBlockTex;

    struct Blocks;

    void Draw();

private:
    int MinRotationSpeed, MaxRotationSpeed;
    int MinVelocity, MaxVelocity;
    float scrolling;

    Vector2 GetPosition();
    Vector2 GetVelocity();

    void CreateBlocks();

    void InitBlock(Blocks *blocks, Vector2 origin, Texture2D Tex);
    void DrawBlocks();
    void UpdateBlocks(Blocks *blocks, Vector2 position, Vector2 velocity, int rotationSpeed);
};