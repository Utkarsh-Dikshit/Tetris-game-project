#include "startWindow.h"

startWindow::startWindow()
{
    BGtexture = LoadTexture("resources/Images/bg.png");
    BGtexture2 = LoadTexture("resources/Images/bg2.png");
    MainLogoTexture = LoadTexture("resources/Images/MainLogo.png");
    ControlTexture = LoadTexture("resources/Images/Control.png");

    LBlockTex = LoadTexture("resources/Images/Blocks/LBlock.png");
    JBlockTex = LoadTexture("resources/Images/Blocks/JBlock.png");
    OBlockTex = LoadTexture("resources/Images/Blocks/OBlock.png");
    IBlockTex = LoadTexture("resources/Images/Blocks/IBlock.png");
    TBlockTex = LoadTexture("resources/Images/Blocks/TBlock.png");
    SBlockTex = LoadTexture("resources/Images/Blocks/SBlock.png");
    ZBlockTex = LoadTexture("resources/Images/Blocks/ZBlock.png");

    MinRotationSpeed = -4;
    MaxRotationSpeed = 4;

    MinVelocity = -3;
    MaxVelocity = 3;

    scrolling = 0.0f;

    CreateBlocks();
}

struct startWindow::Blocks
{
    Texture2D Tex;
    Vector2 position;
    Vector2 velocity;
    Vector2 origin;
    int rotation;
    int rotationSpeed;
};

startWindow::Blocks LBlock, JBlock, OBlock, IBlock, TBlock, SBlock, ZBlock;

Vector2 startWindow::GetPosition()
{
    return {(float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight())};
}
Vector2 startWindow::GetVelocity()
{
    return {(float)GetRandomValue(MinVelocity, MaxVelocity), (float)GetRandomValue(MinVelocity, MaxVelocity)};
}

void startWindow::InitBlock(Blocks *blocks, Vector2 origin, Texture2D Tex)
{
    blocks->Tex = Tex;
    blocks->position = GetPosition();
    blocks->velocity = GetVelocity();
    blocks->origin = origin;
    blocks->rotation = rand() % 360;
    blocks->rotationSpeed = GetRandomValue(MinRotationSpeed, MaxRotationSpeed);
}

void startWindow::CreateBlocks()
{
    InitBlock(&LBlock, {30, 45}, LBlockTex);
    InitBlock(&JBlock, {30, 45}, JBlockTex);
    InitBlock(&OBlock, {30, 30}, OBlockTex);
    InitBlock(&IBlock, {15, 60}, IBlockTex);
    InitBlock(&TBlock, {30, 45}, TBlockTex);
    InitBlock(&SBlock, {30, 45}, SBlockTex);
    InitBlock(&ZBlock, {30, 45}, ZBlockTex);
}

void startWindow::UpdateBlocks(Blocks *blocks, Vector2 position, Vector2 velocity, int rotationSpeed)
{
    blocks->position = Vector2Add(position, velocity);
    blocks->rotation += rotationSpeed;
    if (rotationSpeed == 0)
    {
        blocks->rotationSpeed = GetRandomValue(MinRotationSpeed, MaxRotationSpeed);
    }
    if (blocks->position.x < 0 || blocks->position.x > GetScreenWidth())
    {
        blocks->velocity.x = -(blocks->velocity.x);
    }
    if (blocks->position.y > GetScreenHeight() || blocks->position.y < 0)
    {
        blocks->velocity.y = -(blocks->velocity.y);
    }
}

void startWindow::DrawBlocks()
{
    if (IsWindowResized()) CreateBlocks();

    DrawTexturePro(LBlock.Tex, Rectangle{0, 0, (float)LBlock.Tex.width, (float)LBlock.Tex.height}, Rectangle{(float)LBlock.position.x, (float)LBlock.position.y, (float)LBlock.Tex.width, (float)LBlock.Tex.height}, LBlock.origin, LBlock.rotation, WHITE);
    DrawTexturePro(JBlock.Tex, Rectangle{0, 0, (float)JBlock.Tex.width, (float)JBlock.Tex.height}, Rectangle{(float)JBlock.position.x, (float)JBlock.position.y, (float)JBlock.Tex.width, (float)JBlock.Tex.height}, JBlock.origin, JBlock.rotation, WHITE);
    DrawTexturePro(OBlock.Tex, Rectangle{0, 0, (float)OBlock.Tex.width, (float)OBlock.Tex.height}, Rectangle{(float)OBlock.position.x, (float)OBlock.position.y, (float)OBlock.Tex.width, (float)OBlock.Tex.height}, OBlock.origin, OBlock.rotation, WHITE);
    DrawTexturePro(IBlock.Tex, Rectangle{0, 0, (float)IBlock.Tex.width, (float)IBlock.Tex.height}, Rectangle{(float)IBlock.position.x, (float)IBlock.position.y, (float)IBlock.Tex.width, (float)IBlock.Tex.height}, IBlock.origin, IBlock.rotation, WHITE);
    DrawTexturePro(TBlock.Tex, Rectangle{0, 0, (float)TBlock.Tex.width, (float)TBlock.Tex.height}, Rectangle{(float)TBlock.position.x, (float)TBlock.position.y, (float)TBlock.Tex.width, (float)TBlock.Tex.height}, TBlock.origin, TBlock.rotation, WHITE);
    DrawTexturePro(SBlock.Tex, Rectangle{0, 0, (float)SBlock.Tex.width, (float)SBlock.Tex.height}, Rectangle{(float)SBlock.position.x, (float)SBlock.position.y, (float)SBlock.Tex.width, (float)SBlock.Tex.height}, SBlock.origin, SBlock.rotation, WHITE);
    DrawTexturePro(ZBlock.Tex, Rectangle{0, 0, (float)ZBlock.Tex.width, (float)ZBlock.Tex.height}, Rectangle{(float)ZBlock.position.x, (float)ZBlock.position.y, (float)ZBlock.Tex.width, (float)ZBlock.Tex.height}, ZBlock.origin, ZBlock.rotation, WHITE);

    UpdateBlocks(&LBlock, LBlock.position, LBlock.velocity, LBlock.rotationSpeed);
    UpdateBlocks(&JBlock, JBlock.position, JBlock.velocity, JBlock.rotationSpeed);
    UpdateBlocks(&OBlock, OBlock.position, OBlock.velocity, OBlock.rotationSpeed);
    UpdateBlocks(&IBlock, IBlock.position, IBlock.velocity, IBlock.rotationSpeed);
    UpdateBlocks(&TBlock, TBlock.position, TBlock.velocity, TBlock.rotationSpeed);
    UpdateBlocks(&SBlock, SBlock.position, SBlock.velocity, SBlock.rotationSpeed);
    UpdateBlocks(&ZBlock, ZBlock.position, ZBlock.velocity, ZBlock.rotationSpeed);
}

void startWindow::Draw()
{
    scrolling += 0.7f;
    if (scrolling >= BGtexture.width * 2){
        scrolling = 0;
    }
    
    DrawTexturePro(BGtexture, Rectangle{scrolling, 0, (float)BGtexture.width, (float)BGtexture.height}, Rectangle{0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, Vector2{0, 0}, 0, WHITE);
    DrawBlocks();

}